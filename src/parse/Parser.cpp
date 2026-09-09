#include "Parser.h"

#include <sys/types.h>

#include <utility>
#include <vector>

#include "ParserPack.h"
#include "TranslationUnit.h"

namespace marex::parse {
TranslationUnit Parser::run(
    std::vector<lex::Token>&& tokens) {
    return parse(TokenStream{std::move(tokens)});
}

TranslationUnit Parser::parse(TokenStream&& pack) {
    TranslationUnit translation_unit{};

    translation_unit.parse(pack);

    return translation_unit;
}
}  // namespace marex::parse
