#include "var_decl.h"

#include <format>
#include <string>
#include <utility>

#include "nodes/ast_node.h"
#include "token_kind.h"

namespace marex::parse {
VarDecl::VarDecl(lex::Token&& token)
    : AstNode(std::move(token)) {}

std::string VarDecl::as_c() {
    return std::format("{} {} = {};\n", *type_kind_,
                       name_, value_);
}

VarDecl VarDecl::parse(TokenStream& stream) {
    std::string name;
    std::string value;
    TypeKind type_kind{};

    stream.advance_if_matches_or_throw(
        lex::TokenKind::Var);
    name = stream.advance_if_matches_or_throw(
        lex::TokenKind::Identifier);

    stream.advance_if_matches_or_throw(
        lex::TokenKind::Colon);
    type_kind =
        expression_kind_from_decl_or_throw(stream);
    stream.advance();

    stream.advance_if_matches_or_throw(
        lex::TokenKind::Assignment);

    [[maybe_unused]] auto not_needed =
        expression_kind_from_literal_or_throw(stream);

    value = stream.get_lexeme();

    stream.advance();

    return VarDecl(stream.copy_out_token(),
                   std::move(name), std::move(value),
                   type_kind);
}

VarDecl::VarDecl(lex::Token&& token,
                 std::string&& name,
                 std::string&& value,
                 TypeKind type_kind)
    : AstNode(std::move(token)),
      name_(std::move(name)),
      value_(std::move(value)),
      type_kind_(type_kind) {}
}  // namespace marex::parse
