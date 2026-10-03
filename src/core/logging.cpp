#include "logging.h"

#include <iostream>
#include <stdexcept>
#include <string>

#include "error_format.h"

namespace marex {
void core::flush() { std::cerr.flush(); }

void core::log_error(std::string&& message,
                     std::source_location source_location) {
    std::string format_result =
        merge_message_with_source_location(message, source_location);

    std::cerr << std::format("{}\n", format_result);
    std::cerr.flush();
}

void core::log_fatal_error(std::string&& message,
                           std::source_location source_location) {
    throw std::runtime_error(
        merge_message_with_source_location(message, source_location));
}

void core::log_fatal_internal_error(
    std::string&& message, std::source_location source_location) {
    throw std::runtime_error(
        merge_message_with_source_location(message, source_location));
}
}  // namespace marex
