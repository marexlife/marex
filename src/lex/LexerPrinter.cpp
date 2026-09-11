#include "LexerPrinter.h"

#include <format>
#include <vector>

#include "Logging.h"
#include "Token.h"

namespace marex::lex
{
void LexerPrinter::print_tokens(
    std::vector<lex::Token> &token_stream)
{
    core::log_info("\nLexer print start\n");

    for (lex::Token &token : token_stream)
    {
        core::log_info(std::format(
            "Token lexeme: '{}', Token kind: '{}'\n",
            *token.GetKind(), token.get_lexeme()));
    }

    core::log_info("Lexer print end\n\n");

    core::flush();
}
} // namespace marex::lex
