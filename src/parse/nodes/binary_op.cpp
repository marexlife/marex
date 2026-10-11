#include "binary_op.h"

#include <memory>
#include <utility>

#include "error_format.h"
#include "logging.h"
#include "nodes/op_node.h"
#include "nodes/operator.h"

namespace marex::parse {
BinaryOp::BinaryOp(lex::Token&& token,
                   lex::BindingPower binding_power,
                   BinaryOpKind binary_op_kind)
    : Operator(std::move(token), binding_power),
      binary_op_kind_(binary_op_kind) {}

void BinaryOp::set_lhs(std::shared_ptr<OpNode> lhs,
                       std::source_location source_location) {
    core::log_info("set lhs from: ",
                   core::source_location_to_string(source_location));

    lhs_ = std::move(lhs);
}

void BinaryOp::set_rhs(std::shared_ptr<OpNode> rhs,
                       std::source_location source_location) {
    core::log_info("set rhs from: ",
                   core::source_location_to_string(source_location));

    rhs_ = std::move(rhs);
}
}  // namespace marex::parse