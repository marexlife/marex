#include "operator.h"

#include <utility>

namespace marex::parse {
Operator::Operator(lex::Token&& token, OpNodeKind op_node_kind,
                   lex::BindingPower binding_power)
    : OpNode(std::move(token), op_node_kind),
      binding_power_(binding_power) {}
}  // namespace marex::parse