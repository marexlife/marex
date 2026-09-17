#include "expr_factory.h"

#include <memory>
#include <stdexcept>

#include "token.h"
#include "nodes/expr.h"

namespace marex::parse {
std::unique_ptr<Expr> ExprFactory::new_expr(
    lex::Token&& token) {
    switch (token.get_kind()) {
        default:
            throw std::runtime_error(
                "not implemented");
    }
}
}  // namespace marex::parse
