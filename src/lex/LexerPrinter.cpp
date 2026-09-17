#include "LexerPrinter.h"

#include <format>
#include <vector>

#include "Token.h"
#include "logging.h"

namespace marex {
void lex::print_tokens(
    std::pmr::vector<lex::Token>& token_stream) {
    core::log_info("\nLexer print start\n");

    for (lex::Token& token : token_stream) {
        core::log_info(
            "Token lexeme: '{}', Token kind: '{}'\n",
            *token.get_kind(), token.get_lexeme());
    }

    core::log_info("Lexer print end\n\n");

    core::flush();
}
}  // namespace marex
