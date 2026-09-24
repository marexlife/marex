#include "expr_build_tester.h"

#include <memory>

#include "nodes/expr_build.h"
#include "token_kind.h"
#include "token_stream.h"

namespace marex::parse::tests {
int ExprBuildTester::test_expr_build() {
    TokenStream token_stream;

    auto result = build_expr(token_stream);

    return result->get_kind() == lex::TokenKind::OpAdd ? 0 : -1;
}
}  // namespace marex::parse::tests