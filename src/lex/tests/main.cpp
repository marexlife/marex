#include "test_lex.h"

#include <cassert>
#include <format>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "lexer.h"
#include "passkey.h"
#include "token.h"
#include "token_kind.h"

namespace marex::lex {
int LexTester::test_lex() {
    marex::lex::Lexer lexer{};

    std::string input =
        R"(some_func(x: int): int {
    return 1
})";

    std::cerr << std::format("input: '{}'\n", input);

    std::vector<Token> result = lexer.run(std::move(input));

    std::vector<Token> expected = {
        Token{core::Passkey<LexTester>{}, "some_func",
              TokenKind::Identifier},
        Token{core::Passkey<LexTester>{}, TokenKind::OpenBracket},
        Token{core::Passkey<LexTester>{}, "x", TokenKind::Identifier},
        Token{core::Passkey<LexTester>{}, TokenKind::Colon},
        Token{core::Passkey<LexTester>{}, TokenKind::Int32Decl},
        Token{core::Passkey<LexTester>{}, TokenKind::CloseBracket},
        Token{core::Passkey<LexTester>{}, TokenKind::OpenBrace},
        Token{core::Passkey<LexTester>{}, TokenKind::CloseBrace},
    };

    for (auto& got_element : result) {
        for (auto& expected_element : expected) {
            std::cerr << std::format(
                "expected: {} '{}', got: {} '{}'\n",
                *expected_element.get_kind(),
                expected_element.get_lexeme_or_empty_if_none(),
                *got_element.get_kind(),
                expected_element.get_lexeme_or_empty_if_none());

            if (expected_element != got_element) {
                return -1;
            }
        }
    }

    return 0;
}
}  // namespace marex::lex

int main() { return marex::lex::LexTester::test_lex(); }