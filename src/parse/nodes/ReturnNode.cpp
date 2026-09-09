#include "ReturnNode.h"

#include <format>
#include <stdexcept>
#include <string>
#include <utility>

#include "ExpressionKind.h"
#include "Logging.h"
#include "ParserPack.h"
#include "Token.h"
#include "TokenKind.h"

namespace marex::parse {
ReturnNode::ReturnNode(lex::Token&& token)
    : AstNode(std::move(token)) {}

std::string ReturnNode::as_c() {
    if (!value) {
        throw std::runtime_error(
            "no value in return node");
    }

    return std::format("return {};\n", value.value());
}

void ReturnNode::parse(TokenStream& pack) {
    core::log_info("pre parse return");
    pack.advance_if_matches_or_throw(
        lex::TokenKind::Return);

    expression_kind =
        expression_kind_from_literal_or_throw(pack);

    value = pack.get_lexeme_and_advance();

    core::log_info("post parse return");
}
}  // namespace marex::parse