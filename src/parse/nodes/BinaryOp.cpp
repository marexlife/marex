#include "BinaryOp.h"

#include <utility>

namespace marex::parse {
BinaryOp::BinaryOp(lex::Token&& token,
                  BinaryOpKind binary_op_kind)
    : Expr(std::move(token)),
      binary_op_kind(binary_op_kind) {}

void BinaryOp::set(std::unique_ptr<Expr> lhs,
                   std::unique_ptr<Expr> rhs) {
    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);
}
}  // namespace marex::parse