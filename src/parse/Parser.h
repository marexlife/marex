#ifndef MAREX_PARSE_PARSER_H
#define MAREX_PARSE_PARSER_H
#include <vector>

#include "Token.h"
#include "TranslationUnit.h"

namespace marex::parse {
[[nodiscard]] TranslationUnit parse(
    std::pmr::vector<lex::Token>&& tokens);

}  // namespace marex::parse
#endif  // MAREX_PARSE_PARSER_H
