#include "ExprFactory.h"

#include <memory>
#include <stdexcept>
#include <utility>

#include "Token.h"
#include "TokenKind.h"
#include "nodes/Assignment.h"
#include "nodes/Expr.h"

namespace marex::parse {
std::unique_ptr<Expr> ExprFactory::new_expr(
    lex::Token&& token) {
    switch (token.get_kind()) {
        case marex::lex::TokenKind::Assignment:
            return std::make_unique<Assignment>(
                std::move(token));
        default:
            throw std::runtime_error(
                "not implemented");
    }
}
}  // namespace marex::parse
