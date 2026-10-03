#include "return_node.h"

#include <format>
#include <stdexcept>
#include <string>
#include <utility>

#include "expr_kind.h"
#include "logging.h"
#include "nodes/ast_node.h"
#include "nodes/expr_build.h"
#include "token.h"
#include "token_kind.h"

namespace marex::parse {
ReturnNode::ReturnNode(lex::Token&& token)
    : AstNode(std::move(token)) {}

std::string ReturnNode::as_c() {
    if (!value_) {
        throw std::runtime_error("no value in return node");
    }

    return std::format("return {};\n", (*value_)->as_c());
}

void ReturnNode::parse(TokenStream& stream) {
    core::log_info("pre parse return");

    stream.advance_if_matches_or_throw(lex::TokenKind::Return);

    if (stream.matches(lex::TokenKind::StatementEnd)) {
        return;
    }

    constexpr auto end = lex::TokenKind::StatementEnd;

    value_ = build_expr(stream, end);

    stream.advance_if_matches_or_throw(end);

    core::log_info("post parse return");
}
}  // namespace marex::parse
