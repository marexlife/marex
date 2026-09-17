#include "logging.h"

#include <iostream>
#include <print>
#include <stdexcept>
#include <string>

#include "error_format.h"

namespace marex {
void core::flush() { std::cout.flush(); }

void core::log_error(
    std::string&& message,
    std::source_location source_location) {
    std::string format_result =
        merge_message_with_source_location(
            message, source_location);

    std::println("{}", format_result);
}

void core::log_fatal_error(
    std::string&& message,
    std::source_location source_location) {
    throw std::runtime_error(
        merge_message_with_source_location(
            message, source_location));
}

void core::log_fatal_internal_error(
    std::string&& message,
    std::source_location source_location) {
    throw std::runtime_error(
        merge_message_with_source_location(
            message, source_location));
}
}  // namespace marex
