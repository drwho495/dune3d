#include "entity_bezier2d.hpp"
#include "nlohmann/json.hpp"
#include "util/glm_util.hpp"
#include "util/json_util.hpp"
#include "util/template_util.hpp"
#include "util/bbox_accumulator.hpp"
#include "document/document.hpp"
#include "entity_workplane.hpp"
#include "entityt_impl.hpp"

namespace dune3d {
EntityBezier2D::EntityBezier2D(const UUID &uu) : Base(uu)
{
}

EntityBezier2D::EntityBezier2D(const UUID &uu, const json &j)
    : Base(uu, j), m_p1(j.at("p1").get<glm::dvec2>()), m_p2(j.at("p2").get<glm::dvec2>()),
      m_c1(j.at("c1").get<glm::dvec2>()), m_c2(j.at("c2").get<glm::dvec2>()), m_wrkpl(j.at("wrkpl").get<UUID>())
{
}


json EntityBezier2D::serialize() const
{
    json j = Entity::serialize();
    j["p1"] = m_p1;
    j["p2"] = m_p2;
    j["c1"] = m_c1;
    j["c2"] = m_c2;
    j["wrkpl"] = m_wrkpl;
    return j;
}

double EntityBezier2D::get_param(unsigned int point, unsigned int axis) const
{
    if (point == 1) {
        return m_p1[axis];
    }
    else if (point == 2) {
        return m_p2[axis];
    }
    else if (point == 3) {
        return m_c1[axis];
    }
    else if (point == 4) {
        return m_c2[axis];
    }
    return NAN;
}

void EntityBezier2D::set_param(unsigned int point, unsigned int axis, double value)
{
    if (point == 1) {
        m_p1[axis] = value;
    }
    else if (point == 2) {
        m_p2[axis] = value;
    }
    else if (point == 3) {
        m_c1[axis] = value;
    }
    else if (point == 4) {
        m_c2[axis] = value;
    }
}

std::string EntityBezier2D::get_point_name(unsigned int point) const
{
    switch (point) {
    case 1:
        return "from";
    case 2:
        return "to";
    case 3:
        return "from handle";
    case 4:
        return "to handle";
    default:
        return "";
    }
}

glm::dvec2 EntityBezier2D::get_tangent_in_workplane(double t, const EntityWorkplane &wrkpl) const
{
    return get_tangent(t);
}

glm::dvec2 EntityBezier2D::get_interpolated(double t) const
{
    return m_p1 * pow(1 - t, 3) + 3. * m_c1 * pow(1 - t, 2) * t + 3. * m_c2 * (1 - t) * pow(t, 2) + m_p2 * pow(t, 3);
}

glm::dvec2 EntityBezier2D::get_tangent(double t) const
{
    return m_p1 * (-3 * pow(1 - t, 2)) + m_c1 * (3 * pow(1 - t, 2) - 6 * t * (1 - t))
           + m_c2 * (-3 * pow(t, 2) + 6 * t * (1 - t)) + m_p2 * 3. * pow(t, 2);
}

glm::dvec2 EntityBezier2D::get_second_derivative(double t) const
{
    return (6 * (1 - t)) * (m_c2 - 2. * m_c1 + m_p1) + 6 * t * (m_p2 - 2. * m_c2 + m_c1);
}

double EntityBezier2D::get_curvature(double t) const
{
    // https://pomax.github.io/bezierinfo/#curvature
    const auto d = get_tangent(t);
    const auto dd = get_second_derivative(t);
    const auto numerator = d.x * dd.y - dd.x * d.y;
    const auto denominator = pow(d.x * d.x + d.y * d.y, 3. / 2);
    if (denominator == 0)
        return NAN;
    return numerator / denominator;
}

glm::dvec2 EntityBezier2D::get_point_in_workplane(unsigned int point) const
{
    if (point == 1)
        return m_p1;
    else if (point == 2)
        return m_p2;
    else if (point == 3)
        return m_c1;
    else if (point == 4)
        return m_c2;
    else
        return {NAN, NAN};
}

glm::dvec3 EntityBezier2D::get_point(unsigned int point, const Document &doc) const
{
    auto &wrkpl = doc.get_entity<EntityWorkplane>(m_wrkpl);
    return wrkpl.transform(get_point_in_workplane(point));
}

bool EntityBezier2D::is_valid_point(unsigned int point) const
{
    return any_of(point, 1u, 2u, 3u, 4u);
}

glm::dvec2 EntityBezier2D::get_tangent_at_point(unsigned int point) const
{
    if (point == 1)
        return m_p1 - m_c1;
    else
        return m_p2 - m_c2;
}

bool EntityBezier2D::is_valid_tangent_point(unsigned int point) const
{
    return any_of(point, 1u, 2u);
}

std::set<UUID> EntityBezier2D::get_referenced_entities() const
{
    auto ents = Entity::get_referenced_entities();
    ents.insert(m_wrkpl);
    return ents;
}

void EntityBezier2D::move(const Entity &last, const glm::dvec2 &delta, unsigned int point)
{
    auto &en_last = dynamic_cast<const EntityBezier2D &>(last);
    if (point == 0 || point == 1) {
        m_p1 = en_last.m_p1 + delta;
    }
    if (point == 0 || point == 2) {
        m_p2 = en_last.m_p2 + delta;
    }
    if (point == 0 || point == 3 || point == 1) {
        m_c1 = en_last.m_c1 + delta;
    }
    if (point == 0 || point == 4 || point == 2) {
        m_c2 = en_last.m_c2 + delta;
    }
}

std::pair<glm::dvec2, glm::dvec2> EntityBezier2D::get_bbox() const
{
    BBoxAccumulator<glm::dvec2> acc;
    acc.accumulate(m_p1);
    acc.accumulate(m_p2);
    acc.accumulate(m_c1);
    acc.accumulate(m_c2);
    return acc.get().value();
}

} // namespace dune3d
