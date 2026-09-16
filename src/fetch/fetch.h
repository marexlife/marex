#ifndef MAREX_FETCH_FETCH_H
#define MAREX_FETCH_FETCH_H
#include <string>

namespace marex::fetch {
[[nodiscard]] std::pmr::string fetch(
    std::string_view filepath);
}  // namespace marex::fetch
#endif  // MAREX_FETCH_FETCH_H
