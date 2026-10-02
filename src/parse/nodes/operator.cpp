#include "operator.h"

#include <utility>

#include "nodes/op_node.h"

namespace marex::parse {
Operator::Operator(lex::Token&& token, OpNodeKind op_node_kind,
                   lex::BindingPower binding_power)
    : OpNode(std::move(token), op_node_kind),
      binding_power_(binding_power) {}

std::shared_ptr<ComplexOperand> Operator::to_complex_operand() {
    return std::make_shared<ComplexOperand>(
        lex::Token(get_token()),
        std::static_pointer_cast<Operator>(shared_from_this()));
}
}  // namespace marex::parse