#include "element_map.hpp"
#include "nlohmann/json.hpp"
#include <memory>
#include <vector>

namespace dune3d {

void ElementMap::set_history_node(const IndexedName &sub_element_indexed_name, const std::shared_ptr<HistoryNode> &node) {
    // TODO: handle duplicates
    m_internal_data[sub_element_indexed_name].push_back(node);
}

void ElementMap::set_history_nodes(const IndexedName &sub_element_indexed_name, const std::vector<std::shared_ptr<HistoryNode>> &nodes) {
    // TODO: handle duplicates
    m_internal_data[sub_element_indexed_name] = nodes;
}

json ElementMap::serialize() const {
    auto serializedMap = json{
        {"type", "element_map"}
    };

    auto serializedInternalData = json{};

    // std::pair<IndexedName, std::vector<std::shared_ptr<HistoryNode>>>
    for (const auto& entry : m_internal_data) {
        std::vector<json> serializedNodeList;

        if (entry.second.size()) {
            serializedNodeList.reserve(entry.second.size());

            for (const std::shared_ptr<HistoryNode> &node : entry.second) {
                serializedNodeList.push_back(node->serialize());
            }

            serializedInternalData[entry.first.to_string()] = serializedNodeList;
        }
    }

    serializedMap["data"] = serializedInternalData;

    return serializedMap;
}

const std::vector<std::shared_ptr<HistoryNode>>& ElementMap::get_history_nodes(const IndexedName &sub_element_indexed_name) const {
    auto internalDataIterator = m_internal_data.find(sub_element_indexed_name);

    if (internalDataIterator != m_internal_data.end()) {
        return internalDataIterator->second;
    }

    return EMPTY_NODE_LIST;
}

} // namespace dune3d