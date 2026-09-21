#include "parse.h"

#include <utility>
#include <vector>

namespace marex {
parse::TranslationUnit parse::parse(
    std::vector<lex::Token>&& tokens) {
    return TranslationUnit::compile(std::move(tokens));
}
}  // namespace marex
