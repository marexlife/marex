#include "binary_op.h"

#include <utility>

#include "nodes/op_node.h"

namespace marex::parse {
BinaryOp::BinaryOp(lex::Token&& token, BinaryOpKind binary_op_kind)
    : OpNode(std::move(token), OpNodeKind::BinaryOp),
      binary_op_kind_(binary_op_kind) {}

void BinaryOp::set(std::unique_ptr<OpNode> lhs,
                   std::unique_ptr<OpNode> rhs) {
    set_lhs(std::move(lhs));
    set_rhs(std::move(rhs));
}

void BinaryOp::set_lhs(std::unique_ptr<OpNode> lhs) {
    lhs_ = std::move(lhs);
}

void BinaryOp::set_rhs(std::unique_ptr<OpNode> rhs) {
    rhs_ = std::move(rhs);
}
}  // namespace marex::parse