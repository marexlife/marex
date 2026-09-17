#include "ReturnNode.h"

#include <format>
#include <stdexcept>
#include <string>
#include <utility>

#include "expr_kind.h"
#include "logging.h"
#include "nodes/ast_node.h"
#include "token.h"
#include "token_kind.h"

namespace marex::parse {
ReturnNode::ReturnNode(lex::Token&& token)
    : AstNode(std::move(token)) {}

std::string ReturnNode::as_c() {
    if (!value_) {
        throw std::runtime_error(
            "no value in return node");
    }

    return std::format("return {};\n", value_.value());
}

void ReturnNode::parse(TokenStream& stream) {
    core::log_info("pre parse return");
    stream.advance_if_matches_or_throw(
        lex::TokenKind::Return);

    expression_kind_ =
        expression_kind_from_literal_or_throw(stream);

    value_ = stream.get_lexeme_and_advance();

    core::log_info("post parse return");
}
}  // namespace marex::parse
