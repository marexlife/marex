#include "Logging.h"

#include <exception>
#include <iostream>
#include <print>
#include <string>

#include "ErrorFormatter.h"

namespace marex {
namespace core {
static const bool log_infos = false;
}

void core::flush() { std::cout.flush(); }

void core::log_info(std::string&& message) {
    if (log_infos) {
        std::println("info: {}", message);
    }
}

void core::log_error(
    std::string&& message,
    std::source_location source_location) {
    std::string format_result =
        merge_message_with_source_location(
            message, source_location);

    std::println("error: {}", format_result);
}

void core::log_fatal_error(
    std::string&& message,
    std::source_location source_location) {
    core::log_error(std::move(message),
                    source_location);
    throw std::exception();
}

void core::log_fatal_internal_error(
    std::string&& message,
    std::source_location source_location) {
    std::string format_result =
        merge_message_with_source_location(
            message, source_location);

    std::println("Internal error: {}", format_result);

    throw std::exception();
}
}  // namespace marex
