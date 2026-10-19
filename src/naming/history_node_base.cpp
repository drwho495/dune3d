#include "history_node_base.hpp"
#include "nlohmann/json.hpp"

namespace dune3d {

json HistoryNode::serialize() const {
    auto serializedNode = json{
        {"type", get_type()}
    };

    return serializedNode;
}

} // namespace dune3d
