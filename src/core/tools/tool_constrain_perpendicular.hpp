#include "tool_common_constrain.hpp"

namespace dune3d {

class ToolConstrainPerpendicular : public ToolCommonConstrain {
public:
    using ToolCommonConstrain::ToolCommonConstrain;

    ToolResponse begin(const ToolArgs &args) override;
    CanBegin can_begin() override;
    bool can_preview_constrain() override;
};
} // namespace dune3d
