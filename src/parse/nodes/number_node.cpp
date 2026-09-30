#include "number_node.h"

#include <utility>

#include "nodes/operand.h"

namespace marex::parse {
NumberNode::NumberNode(lex::Token&& token)
    : Operand(std::move(token)) {}
}  // namespace marex::parse