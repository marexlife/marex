#include "op_node.h"

#include <memory>

namespace marex::parse {
OpNode::OpNode(lex::Token&& token)
    : Expr(std::move(token)),
      std::enable_shared_from_this<OpNode>(*this) {}
}  // namespace marex::parse