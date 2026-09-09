#include "Parser.h"

#include <sys/types.h>

#include <utility>
#include <vector>

#include "TokenStream.h"
#include "TranslationUnit.h"

namespace marex::parse {
TranslationUnit Parser::run(
    std::vector<lex::Token>&& tokens) {
    return parse(TokenStream{std::move(tokens)});
}

TranslationUnit Parser::parse(TokenStream&& stream) {
    TranslationUnit translation_unit{};

    translation_unit.parse(stream);

    return translation_unit;
}
}  // namespace marex::parse
