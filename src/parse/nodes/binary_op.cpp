#include "binary_op.h"

#include <utility>

#include "nodes/op_node.h"

namespace marex::parse {
BinaryOp::BinaryOp(lex::Token&& token,
                   BinaryOpKind binary_op_kind)
    : OpNode(std::move(token), OpNodeKind::BinaryOp),
      binary_op_kind_(binary_op_kind) {}

void BinaryOp::set(std::unique_ptr<Expr> lhs,
                   std::unique_ptr<Expr> rhs) {
    lhs_ = std::move(lhs);
    rhs_ = std::move(rhs);
}
}  // namespace marex::parse