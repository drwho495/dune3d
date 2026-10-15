#include "history_transformation_base.hpp"
#include "nlohmann/json.hpp"

namespace dune3d {

json HistoryTransformation::serialize() const {
    auto serializedTransformation = json{
        {"type", get_type()}
    };

    return serializedTransformation;
}

} // namespace dune3d
