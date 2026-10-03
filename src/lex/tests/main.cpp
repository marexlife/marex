#include <print>

#include "lexer_tester.h"

int main() {
    auto result = marex::lex::tests::LexTester::test_lex();

    std::println("Lexer Test: success = ", result == 0);

    return result;
}