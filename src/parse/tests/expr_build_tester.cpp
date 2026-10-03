#include "expr_build_tester.h"

#include <memory>

#include "nodes/expr_build.h"
#include "token.h"
#include "token_kind.h"
#include "token_stream.h"

namespace marex::parse::tests {
bool ExprBuildTester::test_expr_build() {
    TokenStream token_stream{{
        lex::Token{lex::TokenKind::IntLiteral},
        lex::Token{lex::TokenKind::OpAdd},
        lex::Token{lex::TokenKind::IntLiteral},
        lex::Token{lex::TokenKind::OpMul},
        lex::Token{lex::TokenKind::IntLiteral},
    }};

    auto result =
        build_expr(token_stream, lex::TokenKind::StatementEnd);

    return result->get_kind() == lex::TokenKind::OpAdd;
}
}  // namespace marex::parse::tests