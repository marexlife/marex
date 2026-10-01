#include "op_node.h"

#include <memory>

namespace marex::parse {
OpNode::OpNode(lex::Token&& token, OpNodeKind op_node_kind)
    : Expr(std::move(token)),
      std::enable_shared_from_this<OpNode>(*this),
      op_node_kind_(op_node_kind) {}
}  // namespace marex::parse