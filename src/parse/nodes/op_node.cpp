#include "op_node.h"

namespace marex::parse {
OpNode::OpNode(lex::Token&& token,
               OpNodeKind op_node_kind)
    : Expr(std::move(token)),
      op_node_kind_(op_node_kind) {}
}  // namespace marex::parse