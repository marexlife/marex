#ifndef MAREX_CORE_LOGGER_H
#define MAREX_CORE_LOGGER_H
#include <format>
#include <iostream>
#include <source_location>
#include <string>
#include <utility>

namespace marex {
namespace core {
namespace detail {
inline const bool log_infos = true;
inline const bool input_breaks = true;
}  // namespace detail

void flush();

template <typename... Ts>
constexpr void log_info(std::format_string<Ts...> message = "",
                        Ts... args);

template <typename... Ts>
constexpr void input_break(std::format_string<Ts...> message = "",
                           Ts... args);

void log_error(std::string&& message,
               std::source_location source_location =
                   std::source_location::current());

[[noreturn]] void log_fatal_error(
    std::string&& message, std::source_location source_location =
                               std::source_location::current());

[[noreturn]] void log_fatal_internal_error(
    std::string&& message, std::source_location source_location =
                               std::source_location::current());
}  // namespace core

template <typename... Ts>
constexpr void core::input_break(std::format_string<Ts...> message,
                                 Ts... args) {
    if constexpr (!detail::input_breaks) {
        return;
    }

    log_info(message, std::forward<Ts>(args)...);

    std::cin.get();
}

template <typename... Ts>
constexpr void core::log_info(std::format_string<Ts...> message,
                              Ts... args) {
    if constexpr (!detail::log_infos) {
        return;
    }

    std::cerr << std::format(message, std::forward<Ts>(args)...)
              << "\n";

    std::cerr.flush();
}
}  // namespace marex
#endif  // MAREX_CORE_LOGGER_H
