#include "write.h"

#include <format>
#include <fstream>
#include <string_view>

#include "logging.h"

namespace marex {
static const std::string_view output_file = "main.c";

void write::write(
    parse::TranslationUnit&& translation_unit) {
    std::ofstream stream{output_file.data()};

    stream << translation_unit.as_c();

    core::log_info("wrote {}", output_file);
}
}  // namespace marex