#ifndef MAREX_PARSE_STATEMENTBUILDER_H
#define MAREX_PARSE_STATEMENTBUILDER_H
#include <memory>

#include "nodes/expr.h"
#include "token_stream.h"

namespace marex::parse {
[[nodiscard]] std::unique_ptr<Expr> build_expr(
    TokenStream& stream);
}  // namespace marex::parse
#endif  // MAREX_PARSE_STATEMENTBUILDER_H
