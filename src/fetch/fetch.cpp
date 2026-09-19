#include "fetch.h"

#include <cstddef>
#include <exception>
#include <expected>
#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

#include "error.h"

namespace marex {
[[nodiscard]] std::expected<
    std::pmr::string, std::unique_ptr<core::Error>>
fetch::fetch(std::string_view filepath,
             std::size_t default_reserves_size) {
    std::string result;

    result.reserve(default_reserves_size);

    try {
        std::ifstream stream{filepath.data()};

        if (!stream.is_open()) {
            return std::unexpected(
                core::Error::from_message(
                    "file is not open"));
        }

        while (!stream.eof()) {
            result += static_cast<char>(stream.get());
        }

        result.pop_back();

        return std::expected<
            std::pmr::string,
            std::unique_ptr<core::Error>>(
            std::move(result));
    } catch (const std::exception& exception) {
        return std::unexpected(
            core::Error::from_exception(exception));
    } catch (...) {
        return std::unexpected(
            core::Error::from_nothing());
    }
}
}  // namespace marex
