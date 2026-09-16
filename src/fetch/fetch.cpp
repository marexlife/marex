#include "fetch.h"

#include <fstream>
#include <string>
#include <string_view>

namespace marex {
static const std::size_t result_reserve_amount = 100;

[[nodiscard]] std::pmr::string fetch::fetch(
    std::string_view filepath) {
    std::ifstream stream{filepath.data()};
    std::pmr::string result;

    result.reserve(result_reserve_amount);

    while (!stream.eof()) {
        result += static_cast<char>(stream.get());
    }

    result.pop_back();

    return result;
}
}  // namespace marex
