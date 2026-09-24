#include "test_expr_build.h"

#include "expr_build.h"
#include "token_stream.h"

namespace marex::parse {
void test_build_expr() {
    TokenStream token_stream{{}};
    auto result = build_expr(token_stream);

    
}
}  // namespace marex::parse