#ifndef MAREX_CORE_LOGGER_H
#define MAREX_CORE_LOGGER_H
#include <source_location>
#include <string>

namespace marex::core {
void flush();

void log_info(std::string&& message);

void log_error(std::string&& message,
               std::source_location source_location =
                   std::source_location::current());

[[noreturn]] void log_fatal_error(
    std::string&& message,
    std::source_location source_location =
        std::source_location::current());

[[noreturn]] void log_fatal_internal_error(
    std::string&& message,
    std::source_location source_location =
        std::source_location::current());
}  // namespace marex::core
#endif  // MAREX_CORE_LOGGER_H
