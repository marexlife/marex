#include "operand.h"

#include <utility>

#include "nodes/op_node.h"
#include "token.h"

namespace marex::parse {
Operand::Operand(lex::Token&& token)
    : OpNode(std::move(token), OpNodeKind::Operand) {}
}  // namespace marex::parse