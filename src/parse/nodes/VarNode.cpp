#include "VarNode.h"

#include <format>
#include <string>
#include <utility>

#include "ExpressionKind.h"
#include "ParserPack.h"
#include "TokenKind.h"
#include "nodes/Statement.h"

namespace marex::parse {
VarNode::VarNode(lex::Token&& token)
    : Statement(std::move(token)) {}

std::string VarNode::as_c() {
    return std::format("{} {} = {};\n", *type_kind,
                       name, value);
}

void VarNode::parse(ParserPack& pack) {
    pack.advance_if_matches_or_throw(
        lex::TokenKind::Var);
    name = pack.advance_if_matches_or_throw(
        lex::TokenKind::Identifier);

    pack.advance_if_matches_or_throw(
        lex::TokenKind::Colon);
    type_kind =
        expression_kind_from_decl_or_throw(pack);
    pack.advance();

    pack.advance_if_matches_or_throw(
        lex::TokenKind::Assignment);

    [[maybe_unused]] auto not_needed =
        expression_kind_from_literal_or_throw(pack);

    value = pack.get_lexeme();

    pack.advance();
}
}  // namespace marex::parse