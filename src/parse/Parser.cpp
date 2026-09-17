#include "Parser.h"

#include <utility>
#include <vector>

#include "TokenStream.h"
#include "TranslationUnit.h"

namespace marex {
parse::TranslationUnit parse::parse(
    std::pmr::vector<lex::Token>&& tokens) {
    TranslationUnit translation_unit{};
    TokenStream token_stream{std::move(tokens)};
    translation_unit.parse(token_stream);

    return translation_unit;
}
}  // namespace marex
