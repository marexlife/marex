#ifndef MAREX_PARSE_PARSE_H
#define MAREX_PARSE_PARSE_H
#include <vector>

#include "TranslationUnit.h"
#include "token.h"

namespace marex::parse {
[[nodiscard]] TranslationUnit parse(
    std::pmr::vector<lex::Token>&& tokens);

}  // namespace marex::parse
#endif  // MAREX_PARSE_PARSE_H
