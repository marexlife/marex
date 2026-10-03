#include <print>

#include "expr_build_tester.h"

int main() {
    auto result =
        marex::parse::tests::ExprBuildTester::test_expr_build();

    std::println("Parser test: success = {}", result);

    return result ? 0 : -1;
}