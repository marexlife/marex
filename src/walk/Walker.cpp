#include "Walker.h"

#include <format>
#include <fstream>
#include <string_view>

#include "logging.h"

namespace marex::walk {
void Walker::run(
    parse::TranslationUnit&& translation_unit) {
    static const std::string_view output_file =
        "main.c";

    std::ofstream stream{output_file.data()};

    stream << translation_unit.as_c();

    core::log_info(
        std::format("wrote {}", output_file));
}
}  // namespace marex::walk