#include "Statement.h"

#include <utility>

#include "Token.h"
#include "nodes/AstNode.h"

namespace marex::parse {
Statement::Statement(lex::Token&& token)
    : AstNode(std::move(token)) {}
}  // namespace marex::parse