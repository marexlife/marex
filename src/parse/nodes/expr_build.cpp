#include "expr_build.h"

#include <functional>
#include <list>
#include <memory>
#include <stdexcept>

#include "nodes/expr.h"
#include "nodes/op_node.h"
#include "token.h"
#include "token_stream.h"

namespace marex {

std::unique_ptr<parse::Expr> parse::build_expr(TokenStream& stream) {
    std::list<std::unique_ptr<OpNode>> operators;

    stream.run_until_stmt_end(
        [&](TokenStream::RunUntilStmtEndPack pack) {
            auto token = pack.token.get();
        });

    throw std::runtime_error("not implemented yet");
}
}  // namespace marex
