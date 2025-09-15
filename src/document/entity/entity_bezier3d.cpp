#include "entity_bezier3d.hpp"
#include "nlohmann/json.hpp"
#include "util/glm_util.hpp"
#include "util/json_util.hpp"
#include "document/document.hpp"
#include "entityt_impl.hpp"
#include "entity_workplane.hpp"

namespace dune3d {
EntityBezier3D::EntityBezier3D(const UUID &uu) : Base(uu)
{
}

EntityBezier3D::EntityBezier3D(const UUID &uu, const json &j)
    : Base(uu, j), m_p1(j.at("p1").get<glm::dvec3>()), m_p2(j.at("p2").get<glm::dvec3>()),
      m_c1(j.at("c1").get<glm::dvec3>()), m_c2(j.at("c2").get<glm::dvec3>())
{
}

json EntityBezier3D::serialize() const
{
    json j = Entity::serialize();
    j["p1"] = m_p1;
    j["p2"] = m_p2;
    j["c1"] = m_c1;
    j["c2"] = m_c2;
    return j;
}

double EntityBezier3D::get_param(unsigned int point, unsigned int axis) const
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

void EntityBezier3D::set_param(unsigned int point, unsigned int axis, double value)
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

std::string EntityBezier3D::get_point_name(unsigned int point) const
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

glm::dvec2 EntityBezier3D::get_tangent_in_workplane(double t, const EntityWorkplane &wrkpl) const
{
    return wrkpl.project(get_tangent(t));
}

glm::dvec3 EntityBezier3D::get_point(unsigned int point, const Document &doc) const
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
        return {NAN, NAN, NAN};
}

glm::dvec3 EntityBezier3D::get_interpolated(double t) const
{
    return m_p1 * pow(1 - t, 3) + 3. * m_c1 * pow(1 - t, 2) * t + 3. * m_c2 * (1 - t) * pow(t, 2) + m_p2 * pow(t, 3);
}

glm::dvec3 EntityBezier3D::get_tangent(double t) const
{
    return m_p1 * (-3 * pow(1 - t, 2)) + m_c1 * (3 * pow(1 - t, 2) - 6 * t * (1 - t))
           + m_c2 * (-3 * pow(t, 2) + 6 * t * (1 - t)) + m_p2 * 3. * pow(t, 2);
}

bool EntityBezier3D::is_valid_point(unsigned int point) const
{
    return point == 1 || point == 2 || point == 3 || point == 4;
}

void EntityBezier3D::move(const Entity &last, const glm::dvec3 &delta, unsigned int point)
{
    auto &en_last = dynamic_cast<const EntityBezier3D &>(last);
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

} // namespace dune3d
