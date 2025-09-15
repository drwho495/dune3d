#include "solid_model.hpp"
#include "solid_model_occ.hpp"
#include "document/document.hpp"
#include "document/group/group.hpp"
#include "document/group/igroup_solid_model.hpp"

namespace dune3d {

SolidModel::~SolidModel() = default;

const IGroupSolidModel *SolidModel::get_last_solid_model_group(const Document &doc, const Group &group,
                                                               IncludeGroup include_group)
{
    const IGroupSolidModel *last_solid_model_group = nullptr;

    auto this_body = &group.find_body(doc).body;

    for (auto gr : doc.get_groups_sorted()) {
        if (include_group == IncludeGroup::NO && gr->m_uuid == group.m_uuid)
            break;
        if (auto gr_solid = dynamic_cast<const IGroupSolidModel *>(gr)) {
            if (auto solid_model = dynamic_cast<const SolidModelOcc *>(gr_solid->get_solid_model())) {
                auto body = &gr->find_body(doc).body;
                if (body != this_body)
                    continue;
                if (!solid_model->m_shape_acc.IsNull())
                    last_solid_model_group = gr_solid;
            }
        }
        if (include_group == IncludeGroup::YES && gr->m_uuid == group.m_uuid)
            break;
    }

    return last_solid_model_group;
}

const SolidModel *SolidModel::get_last_solid_model(const Document &doc, const Group &group, IncludeGroup include_group)
{
    auto gr = get_last_solid_model_group(doc, group, include_group);
    if (gr)
        return gr->get_solid_model();
    else
        return nullptr;
}

} // namespace dune3d
