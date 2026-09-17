#ifndef MAREX_CORE_LOGGER_H
#define MAREX_CORE_LOGGER_H
#include <format>
#include <print>
#include <source_location>
#include <string>
#include <utility>

namespace marex::core {
namespace detail {
inline const bool log_infos = false;
}

void flush();

template <typename... Ts>
void log_info(std::format_string<Ts...> message,
              Ts... args) {
    if (detail::log_infos) {
        std::println(message,
                     std::forward<Ts>(args)...);
    }
}

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
