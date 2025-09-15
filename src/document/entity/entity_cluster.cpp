#include "entity_cluster.hpp"
#include "nlohmann/json.hpp"
#include "util/glm_util.hpp"
#include "util/json_util.hpp"
#include "util/bbox_accumulator.hpp"
#include "document/document.hpp"
#include "entity_workplane.hpp"
#include "entityt_impl.hpp"
#include "document/constraint/constraint.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <format>

namespace dune3d {
EntityCluster::EntityCluster(const UUID &uu) : Base(uu), m_content(ClusterContent::create())
{
}

EntityCluster::EntityCluster(const UUID &uu, const json &j)
    : Base(uu, j), m_origin(j.at("origin").get<glm::dvec2>()), m_scale_x(j.at("scale_x").get<double>()),
      m_scale_y(j.at("scale_y").get<double>()), m_angle(j.at("angle").get<double>()),
      m_lock_scale_x(j.value("lock_scale_x", false)), m_lock_scale_y(j.value("lock_scale_y", false)),
      m_lock_aspect_ratio(j.value("lock_aspect_ratio", false)), m_lock_angle(j.value("lock_angle", false)),
      m_wrkpl(j.at("wrkpl").get<UUID>()), m_exploded_group(j.at("exploded_group").get<UUID>())
{
    m_content = ClusterContent::from_json(j);
    for (const auto &[k, v] : j.at("anchors").items()) {
        EntityAndPoint enp = v;
        m_anchors.emplace(std::stoi(k), enp);
        m_anchors_transformed.emplace(std::stoi(k), transform(get_anchor_point(enp)));
    }
}


json EntityCluster::serialize() const
{
    json j = Entity::serialize();
    j["origin"] = m_origin;
    j["scale_x"] = m_scale_x;
    j["scale_y"] = m_scale_y;
    j["lock_scale_x"] = m_lock_scale_x;
    j["lock_scale_y"] = m_lock_scale_y;
    j["lock_aspect_ratio"] = m_lock_aspect_ratio;
    j["lock_angle"] = m_lock_angle;
    j["angle"] = m_angle;
    j["wrkpl"] = m_wrkpl;
    j["exploded_group"] = m_exploded_group;
    m_content->serialize(j);
    {
        json o = json::object();
        for (const auto &[k, v] : m_anchors) {
            o[std::to_string(k)] = v;
        }
        j["anchors"] = o;
    }
    return j;
}

double EntityCluster::get_param(unsigned int point, unsigned int axis) const
{
    if (point == 1) {
        return m_origin[axis];
    }
    else if (point == 2) {
        if (axis == 0)
            return m_scale_x;
        else
            return m_scale_y;
    }
    else if (point == 3) {
        return glm::radians(m_angle);
    }
    else if (m_anchors_transformed.contains(point)) {
        return m_anchors_transformed.at(point)[axis];
    }
    return NAN;
}

void EntityCluster::set_param(unsigned int point, unsigned int axis, double value)
{
    if (point == 1) {
        m_origin[axis] = value;
    }
    else if (point == 2) {
        if (axis == 0)
            m_scale_x = value;
        else
            m_scale_y = value;
    }
    else if (point == 3) {
        m_angle = glm::degrees(value);
    }
    else if (m_anchors_transformed.contains(point)) {
        m_anchors_transformed.at(point)[axis] = value;
    }
}

std::string EntityCluster::get_point_name(unsigned int point) const
{
    switch (point) {
    case 1:
        return "origin";
    default:
        if (m_anchors.contains(point))
            return std::format("anchor {}", point);
        else
            return "";
    }
}

glm::dvec2 EntityCluster::get_point_in_workplane(unsigned int point) const
{
    if (point == 1)
        return m_origin;
    else if (m_anchors_transformed.contains(point))
        return m_anchors_transformed.at(point);
    else
        return {NAN, NAN};
}

glm::dvec3 EntityCluster::get_point(unsigned int point, const Document &doc) const
{
    auto &wrkpl = doc.get_entity<EntityWorkplane>(m_wrkpl);
    return wrkpl.transform(get_point_in_workplane(point));
}

bool EntityCluster::is_valid_point(unsigned int point) const
{
    return point == 1 || m_anchors_transformed.contains(point);
}

std::set<UUID> EntityCluster::get_referenced_entities() const
{
    auto ents = Entity::get_referenced_entities();
    ents.insert(m_wrkpl);
    return ents;
}

glm::dvec2 EntityCluster::transform(const glm::dvec2 &p) const
{
    return m_origin + glm::rotate(p * glm::dvec2{m_scale_x, m_scale_y}, glm::radians(m_angle));
}

void EntityCluster::add_anchor(unsigned int i, const EntityAndPoint &enp)
{
    m_anchors.emplace(i, enp);
    m_anchors_transformed.emplace(i, transform(get_anchor_point(enp)));
}

void EntityCluster::remove_anchor(unsigned int i)
{
    m_anchors.erase(i);
    m_anchors_transformed.erase(i);
}

bool EntityCluster::delete_point(unsigned int point)
{
    if (m_anchors.contains(point)) {
        remove_anchor(point);
        return true;
    }
    return false;
}

glm::dvec2 EntityCluster::get_anchor_point(const EntityAndPoint &enp) const
{
    return dynamic_cast<const IEntityInWorkplane &>(*m_content->m_entities.at(enp.entity))
            .get_point_in_workplane(enp.point);
}

void EntityCluster::add_available_anchors()
{
    m_anchors_available.clear();
    unsigned int aid = s_available_anchor_offset;
    for (const auto &[uu, en] : m_content->m_entities) {
        for (unsigned int point = 1; point <= 4; point++) {
            if (!en->is_valid_point(point))
                break;
            EntityAndPoint enp{uu, point};
            bool anchor_exists = false;
            for (const auto &[i, a] : m_anchors) {
                if (a == enp) {
                    anchor_exists = true;
                    break;
                }
            }
            if (anchor_exists)
                continue;

            m_anchors_available.emplace(aid++, enp);
        }
    }
}

bool EntityCluster::is_supported_entity(const Entity &en)
{
    return en.of_type(Entity::Type::LINE_2D, Entity::Type::ARC_2D, Entity::Type::CIRCLE_2D, Entity::Type::BEZIER_2D);
}

bool EntityCluster::can_delete(const Document &doc) const
{
    if (!Entity::can_delete(doc))
        return false;
    return m_exploded_group == UUID{};
}

void EntityCluster::move(const Entity &last, const glm::dvec2 &delta, unsigned int point)
{
    auto &en_last = dynamic_cast<const EntityCluster &>(last);
    if (point == 0 || point == 1)
        m_origin = en_last.m_origin + delta;
    else if (m_anchors_transformed.contains(point) && en_last.m_anchors_transformed.contains(point))
        m_anchors_transformed.at(point) = en_last.m_anchors_transformed.at(point) + delta;
}

std::pair<glm::dvec2, glm::dvec2> EntityCluster::get_bbox() const
{
    const auto bb = m_content->get_bbox();
    BBoxAccumulator<glm::dvec2> acc;
    acc.accumulate(transform(bb.first));
    acc.accumulate(transform({bb.first.x, bb.second.y}));
    acc.accumulate(transform(bb.second));
    acc.accumulate(transform({bb.second.x, bb.first.y}));
    return acc.get().value();
}

void EntityCluster::update_cluster_content_for_new_workplane(const UUID &wrkpl)
{
    auto clone_result = m_content->clone_for_new_workplane(wrkpl);
    m_content = clone_result.content;
    for (auto &[i, enp] : m_anchors) {
        if (clone_result.entity_xlat.contains(enp.entity))
            enp.entity = clone_result.entity_xlat.at(enp.entity);
    }
}

} // namespace dune3d
