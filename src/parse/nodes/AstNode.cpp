#include "AstNode.h"

#include <utility>

#include "token.h"

namespace marex::parse {
AstNode::AstNode(lex::Token&& token)
    : token(std::move(token)) {}
}  // namespace marex::parse