#ifndef MAREX_CORE_ERRORFROMAT_H
#define MAREX_CORE_ERRORFROMAT_H
#include <source_location>
#include <string>

namespace marex::core {
[[nodiscard]] std::string
merge_message_with_source_location(
    std::string_view message,
    const std::source_location& source_location);

[[nodiscard]] std::string source_location_to_string(
    const std::source_location& source_location);
}  // namespace marex::core
#endif  // MAREX_CORE_ERRORFROMAT_H
