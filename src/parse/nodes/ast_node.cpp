#include "ast_node.h"

#include <utility>

#include "token.h"

namespace marex::parse {
AstNode::AstNode(lex::Token&& token) : token_(std::move(token)) {}
}  // namespace marex::parse