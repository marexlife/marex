#ifndef MAREX_PARSE_PARSE_H
#define MAREX_PARSE_PARSE_H
#include <vector>

#include "token.h"
#include "translation_unit.h"

namespace marex::parse {
[[nodiscard]] std::expected<
    parse::TranslationUnit,
    std::unique_ptr<core::Error>>
parse(std::pmr::vector<lex::Token>&& tokens);
}  // namespace marex::parse
#endif  // MAREX_PARSE_PARSE_H
