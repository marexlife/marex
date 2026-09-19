#include "var_decl.h"

#include <format>
#include <string>
#include <utility>

#include "expr_kind.h"
#include "nodes/ast_node.h"
#include "token_kind.h"

namespace marex::parse {
VarDecl::VarDecl(lex::Token&& token)
    : AstNode(std::move(token)) {}

std::string VarDecl::as_c() {
    return std::format("{} {} = {};\n", *type_kind_,
                       name_, value_);
}

std::expected<void, std::unique_ptr<core::Error>>
VarDecl::parse(TokenStream& stream) {
    stream.advance_if_matches_or_throw(
        lex::TokenKind::Var);
    name_ = stream.advance_if_matches_or_throw(
        lex::TokenKind::Identifier);

    stream.advance_if_matches_or_throw(
        lex::TokenKind::Colon);
    type_kind_ =
        expression_kind_from_decl_or_throw(stream);
    stream.advance();

    stream.advance_if_matches_or_throw(
        lex::TokenKind::Assignment);

    [[maybe_unused]] auto not_needed =
        expression_kind_from_literal_or_throw(stream);

    value_ = stream.get_lexeme();

    stream.advance();

    return std::expected<
        void, std::unique_ptr<core::Error>>();
}
}  // namespace marex::parse
