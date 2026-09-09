#include "OpNode.h"

namespace marex::parse {
OpNode::OpNode(lex::Token&& token)
    : Expr(std::move(token)) {}
}  // namespace marex::parse