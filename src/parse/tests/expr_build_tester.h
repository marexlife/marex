#ifndef MAREX_PARSE_TESTS_EXPRBUILD_H
#define MAREX_PARSE_TESTS_EXPRBUILD_H
namespace marex::parse::tests {
class ExprBuildTester final {
   public:
    ExprBuildTester() = delete;

    [[nodiscard]] static int test_expr_build();
};
}  // namespace marex::parse::tests
#endif  // MAREX_PARSE_TESTS_EXPRBUILD_H