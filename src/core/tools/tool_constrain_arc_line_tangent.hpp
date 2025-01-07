#include "tool_common_constrain.hpp"

namespace dune3d {

enum class EntityType;

class ToolConstrainArcLineTangent : public ToolCommonConstrain {
public:
    using ToolCommonConstrain::ToolCommonConstrain;

    ToolResponse begin(const ToolArgs &args) override;
    CanBegin can_begin() override;
    bool can_preview_constrain() override
    {
        return true;
    }

private:
    EntityType get_curve_type() const;
};

} // namespace dune3d
