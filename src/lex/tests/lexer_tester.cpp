#include "lexer_tester.h"

#include <cassert>
#include <cstddef>
#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "lexer.h"
#include "token.h"
#include "token_kind.h"

namespace marex::lex::tests {
int LexTester::test_lex() {
    marex::lex::Lexer lexer{};

    std::string_view input =
        R"(some_func(x: int): int {
    return 1
})";

    std::cerr << std::format("input: '{}'\n", input);

    std::vector<Token> output = lexer.run(std::string{input});

    std::vector<Token> expected = {
        Token{"some_func", TokenKind::Identifier},
        Token{TokenKind::OpenBracket},
        Token{"x", TokenKind::Identifier},
        Token{TokenKind::Colon},
        Token{TokenKind::Int32Decl},
        Token{TokenKind::CloseBracket},
        Token{TokenKind::Colon},
        Token{TokenKind::Int32Decl},
        Token{TokenKind::OpenBrace},
        Token{TokenKind::Return},
        Token{TokenKind::IntLiteral},
        Token{TokenKind::CloseBrace},
    };

    for (auto& got_element : output) {
        std::cerr << std::format("got: {},\n",
                                 *got_element.get_kind());
    }

    for (std::size_t i = 0; i < (output.size() | expected.size());
         ++i) {
        std::cerr << std::format(
            "expected: {} '{}', got: {} '{}'\n",
            *expected.at(i).get_kind(),
            expected.at(i).get_lexeme_or_empty_if_none(),
            *output.at(i).get_kind(),
            expected.at(i).get_lexeme_or_empty_if_none());

        if (expected.at(i) != output.at(i)) {
            return -1;
        }
    }

    return 0;
}
}  // namespace marex::lex::tests