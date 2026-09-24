#include "test_lex.h"

#include <cassert>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <utility>
#include <vector>

#include "lexer.h"
#include "passkey.h"
#include "token.h"
#include "token_kind.h"

namespace marex::lex {
void LexTester::test_lex() {
    marex::lex::Lexer lexer{};

    std::string source_text =
        R"(
some_func(x: int) {
}
)";

    std::vector<Token> result = lexer.run(std::move(source_text));

    std::vector<Token> expected = {
        Token{core::Passkey<LexTester>{}, TokenKind::Identifier},
        Token{core::Passkey<LexTester>{}, TokenKind::OpenBracket},
        Token{core::Passkey<LexTester>{}, TokenKind::Identifier},
        Token{core::Passkey<LexTester>{}, TokenKind::Colon},
        Token{core::Passkey<LexTester>{}, TokenKind::Int32Decl},
        Token{core::Passkey<LexTester>{}, TokenKind::CloseBracket},
        Token{core::Passkey<LexTester>{}, TokenKind::OpenBrace},
        Token{core::Passkey<LexTester>{}, TokenKind::CloseBrace},
    };

    for (auto& result_element : result) {
        for (auto& expected_element : expected) {
            REQUIRE(result_element != expected_element);
        }
    }
}
}  // namespace marex::lex

int main() { marex::lex::LexTester::test_lex(); }