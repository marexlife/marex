#ifndef MAREX_FETCH_FETCH_H
#define MAREX_FETCH_FETCH_H
#include <cstddef>
#include <expected>
#include <memory>
#include <string>
#include <string_view>

#include "error.h"

namespace marex::fetch {
namespace detail {
inline const std::size_t default_reserved_size = 100;
}
[[nodiscard]] std::expected<
    std::pmr::string, std::unique_ptr<core::Error>>
fetch(std::string_view filepath,
      std::size_t default_reserves_size =
          detail::default_reserved_size);
}  // namespace marex::fetch
#endif  // MAREX_FETCH_FETCH_H
