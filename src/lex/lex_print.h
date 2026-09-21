#ifndef MAREX_DEBUG_LEXPRINT_H
#define MAREX_DEBUG_LEXPRINT_H
#include <vector>

namespace marex::lex {
class Token;

void print_tokens(
    std::vector<lex::Token>& token_stream);
}  // namespace marex::lex
#endif  // MAREX_DEBUG_LEXPRINT_H
