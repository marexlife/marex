#include "binary_op.h"

#include <memory>
#include <utility>

#include "nodes/op_node.h"
#include "nodes/operator.h"

namespace marex::parse {
BinaryOp::BinaryOp(lex::Token&& token,
                   lex::BindingPower binding_power,
                   BinaryOpKind binary_op_kind)
    : Operator(std::move(token), OpNodeKind::BinaryOp, binding_power),
      binary_op_kind_(binary_op_kind) {}

void BinaryOp::set(std::shared_ptr<OpNode> lhs,
                   std::shared_ptr<OpNode> rhs) {
    set_lhs(std::move(lhs));
    set_rhs(std::move(rhs));
}

void BinaryOp::set_lhs(std::shared_ptr<OpNode> lhs) {
    lhs_ = std::move(lhs);
}

void BinaryOp::set_rhs(std::shared_ptr<OpNode> rhs) {
    rhs_ = std::move(rhs);
}
}  // namespace marex::parse