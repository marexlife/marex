#include "operator.h"

#include <utility>

#include "nodes/op_node.h"

namespace marex::parse {
Operator::Operator(lex::Token&& token, OpNodeKind op_node_kind,
                   lex::BindingPower binding_power)
    : OpNode(std::move(token), op_node_kind),
      binding_power(binding_power) {}
}  // namespace marex::parse