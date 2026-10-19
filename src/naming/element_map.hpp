#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <unordered_map>
#include "indexed_name.hpp"
#include "history_node_base.hpp"
#include "util/step_exporter.hpp"
#include "nlohmann/json_fwd.hpp"
#include <TopExp.hxx>
#include <vector>

namespace dune3d {

constexpr std::vector<std::shared_ptr<HistoryNode>> EMPTY_NODE_LIST {};

class ElementMap {
public:
    ElementMap() = default;
    ElementMap(const ElementMap &other_map) = default;
    ElementMap(const std::unordered_map<IndexedName, std::vector<std::shared_ptr<HistoryNode>>> &data)
        : m_internal_data(data) { };
    
    void set_history_node(const IndexedName &sub_element_indexed_name, const std::shared_ptr<HistoryNode> &node);
    void set_history_nodes(const IndexedName &sub_element_indexed_name, const std::vector<std::shared_ptr<HistoryNode>> &nodes);
    const std::vector<std::shared_ptr<HistoryNode>>& get_history_nodes(const IndexedName &sub_element_indexed_name) const;

    bool operator==(const ElementMap &other) const = default;

    json serialize() const;
private:
    std::unordered_map<IndexedName, std::vector<std::shared_ptr<HistoryNode>>> m_internal_data;
};

} // namespace dune3d
