#include "IdentNode.h"

#include <string>
#include <utility>

#include "Token.h"
#include "TokenKind.h"
#include "TokenStream.h"

namespace marex::parse {
IdentNode::IdentNode(lex::Token&& token)
    : AstNode(std::move(token)) {}

[[nodiscard]] std::string IdentNode::as_c() {
    return std::string{IdentNode::get_lexeme()};
}

void IdentNode::parse(TokenStream& stream) {
    value = stream.advance_if_matches_or_throw(
        lex::TokenKind::Identifier);
}
}  // namespace marex::parse
