#include "test_lex.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "lexer.h"
#include "token.h"

namespace marex {
bool lex::test_lex() {
    marex::lex::Lexer lexer{};

    std::string source_text =
        R"(
some_func(x: int): void {
}
)";

    std::vector<Token> result =
        lexer.run(std::move(source_text));

    std::vector<Token> expected{

    };

    for (auto& result_element : result) {
        for (auto& expected_element : expected) {
            if (result_element != expected_element) {
                return false;
            }
        }
    }

    return true;
}
}  // namespace marex

int main() {
    auto result = marex::lex::test_lex();

    std::cerr << "result " << result << '\n';
}