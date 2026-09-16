#include "error_format.h"

#include <format>

namespace marex {
std::string core::merge_message_with_source_location(
    std::string_view message,
    const std::source_location& source_location) {
    return std::format(
        "{}\n{}",
        source_location_to_string(source_location),
        message);
}

std::string core::source_location_to_string(
    const std::source_location& source_location) {
    return std::format("\n{}:{}:{}",
                       source_location.file_name(),
                       source_location.line(),
                       source_location.column());
}
}  // namespace marex
