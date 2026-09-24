#include "test_lex.h"

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

    std::string source_text =
        R"(
some_func(x: int) {
}
)";

    std::vector<Token> result = lexer.run(std::move(source_text));

    std::vector<Token> expected = {
        Token{core::Passkey<LexTester>{}, TokenKind::Identifier},
    };

    for (auto& result_element : result) {
        for (auto& expected_element : expected) {
            if (result_element != expected_element) {
                return -1;
            }
        }
    }

    return 0;
}
}  // namespace marex::lex

int main() {
    auto result = marex::lex::LexTester::test_lex();

    return result;
}