#ifndef MAREX_PARSE_TESTS_LEXERTESTER_H
#define MAREX_PARSE_TESTS_LEXERTESTER_H
namespace marex::lex::tests {
class LexTester final {
   public:
    LexTester() = delete;

    [[nodiscard]] static int test_lex();
};
}  // namespace marex::lex::tests
#endif  // MAREX_PARSE_TESTS_LEXERTESTER_H