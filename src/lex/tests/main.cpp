#include "main.h"

#include <cassert>
#include <cstddef>
#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "lexer.h"
#include "passkey.h"
#include "token.h"
#include "token_kind.h"

namespace marex::lex {
int LexTester::test_lex() {
    marex::lex::Lexer lexer{};

    std::string_view input =
        R"(some_func(x: int): int {
    return 1
})";

    std::cerr << std::format("input: '{}'\n", input);

    std::vector<Token> output = lexer.run(std::string{input});

    std::vector<Token> expected = {
        Token{core::Passkey<LexTester>{}, "some_func",
              TokenKind::Identifier},
        Token{core::Passkey<LexTester>{}, TokenKind::OpenBracket},
        Token{core::Passkey<LexTester>{}, "x", TokenKind::Identifier},
        Token{core::Passkey<LexTester>{}, TokenKind::Colon},
        Token{core::Passkey<LexTester>{}, TokenKind::Int32Decl},
        Token{core::Passkey<LexTester>{}, TokenKind::CloseBracket},
        Token{core::Passkey<LexTester>{}, TokenKind::Colon},
        Token{core::Passkey<LexTester>{}, TokenKind::Int32Decl},
        Token{core::Passkey<LexTester>{}, TokenKind::OpenBrace},
        Token{core::Passkey<LexTester>{}, TokenKind::Return},
        Token{core::Passkey<LexTester>{}, TokenKind::IntLiteral},
        Token{core::Passkey<LexTester>{}, TokenKind::CloseBrace},
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
}  // namespace marex::lex

int main() { return marex::lex::LexTester::test_lex(); }