#include "IdentNode.h"

#include <string>
#include <utility>

#include "ParserPack.h"
#include "Token.h"
#include "TokenKind.h"

namespace marex::parse {
IdentNode::IdentNode(lex::Token&& token)
    : AstNode(std::move(token)) {}

[[nodiscard]] std::string IdentNode::as_c() {
    return std::string{IdentNode::get_lexeme()};
}

void IdentNode::parse(
    [[maybe_unused]] TokenStream& pack) {
    value = pack.advance_if_matches_or_throw(
        lex::TokenKind::Identifier);
}
}  // namespace marex::parse
