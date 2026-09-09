#ifndef MAREX_DEBUG_LEXPRINER_H
#define MAREX_DEBUG_LEXPRINER_H
#include <vector>

namespace marex::lex {
class Token;

class LexerPrinter final {
public:
    LexerPrinter() = delete;

    static void print_tokens(
        std::vector<lex::Token>& token_stream);
};
} // namespace marex::lex
#endif // MAREX_DEBUG_LEXPRINER_H
