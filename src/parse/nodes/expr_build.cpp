#include "expr_build.h"

#include <memory>
#include <stdexcept>

#include "nodes/expr.h"
#include "token.h"
#include "token_stream.h"

namespace marex {
std::unique_ptr<parse::Expr> parse::build_expr(
    TokenStream& stream) {
    [[maybe_unused]] bool previous_was_more_powerful =
        false;

    stream.run_until_stmt_end(
        [&]([[maybe_unused]] const lex::Token& token) {

        });

    throw std::runtime_error("not implemented yet");
}

}  // namespace marex
