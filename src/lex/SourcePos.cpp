#include "SourcePos.h"

#include <format>
#include <string>

namespace marex::lex {
SourcePos::SourcePos(
    std::optional<std::pmr::string> filename)
    : filename(filename) {}

void SourcePos::advance_column() { ++column; }
void SourcePos::reset() {
    line = {};
    column = {};
}
void SourcePos::advance_line() {
    ++line;
    column = {};
}

[[nodiscard]] std::string SourcePos::as_string()
    const {
    if (filename) {
        return std::format("{}:{}:{}",
                           filename.value(), line,
                           column);
    }

    return std::format("{}:{}", filename.value(), line,
                       column);
}
}  // namespace marex::lex