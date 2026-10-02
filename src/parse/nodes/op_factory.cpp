#include "op_factory.h"

#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>

#include "binding_power.h"
#include "exceptions/invalid_token_exception.h"
#include "nodes/binary_op.h"
#include "nodes/identifier.h"
#include "nodes/literal.h"
#include "nodes/literal_kind.h"
#include "nodes/op_node.h"
#include "nodes/operand.h"
#include "nodes/operator.h"
#include "token_kind.h"

namespace marex::parse {
std::unique_ptr<OpNode> OpFactory::create_op_node(
    lex::Token&& token) {
    if (auto binding_power = token.get_binding_power()) {
        return create_operator(std::move(token), *binding_power);
    }

    return create_operand(std::move(token));
}

std::unique_ptr<Operator> OpFactory::create_operator(
    lex::Token&& token, lex::BindingPower binding_power) {
    if (auto binary_op_kind = get_binary_op_kind(token)) {
        return create_bin_operator(std::move(token), binding_power,
                                   *binary_op_kind);
    }

    throw InvalidTokenException(token.get_pos(), token.get_kind(),
                                "expected an operator");
}

std::optional<BinaryOpKind> OpFactory::get_binary_op_kind(
    const lex::Token& token) {
    switch (token.get_kind()) {
        case lex::TokenKind::OpAdd:
            return std::optional(BinaryOpKind::Add);
        case lex::TokenKind::OpSub:
            return std::optional(BinaryOpKind::Sub);
        case lex::TokenKind::OpMul:
            return std::optional(BinaryOpKind::Mul);
        case lex::TokenKind::OpDiv:
            return std::optional(BinaryOpKind::Div);
        default:
            return std::nullopt;
    }
}

std::unique_ptr<Operator> OpFactory::create_mono_operator(
    [[maybe_unused]] lex::Token&& token,
    [[maybe_unused]] lex::BindingPower binding_power) {
    throw std::runtime_error(
        "creating mono op is not implemented yet");
}

std::unique_ptr<BinaryOp> OpFactory::create_bin_operator(
    lex::Token&& token, lex::BindingPower binding_power,
    BinaryOpKind binary_op_kind) {
    return std::make_unique<BinaryOp>(std::move(token), binding_power,
                                      binary_op_kind);
}

std::unique_ptr<Operand> OpFactory::create_operand(
    lex::Token&& token) {
    if (auto literal_kind = to_literal_kind(token)) {
        return create_literal_operand(std::move(token),
                                      *literal_kind);
    }

    if (token.get_kind() == lex::TokenKind::Identifier) [[likely]] {
        return create_identifier_operand(std::move(token));
    }

    throw InvalidTokenException(token.get_pos(), "expected operand");
}

std::optional<LiteralKind> OpFactory::to_literal_kind(
    const lex::Token& token) {
    switch (token.get_kind()) {
        case lex::TokenKind::FloatLiteral:
            return LiteralKind::Float;
        case lex::TokenKind::BoolLiteral:
            return LiteralKind::Bool;
        case lex::TokenKind::IntLiteral:
            return LiteralKind::Int;
        case lex::TokenKind::StringLiteral:
            return LiteralKind::String;
        default:
            return std::nullopt;
    }
}

std::unique_ptr<Literal> OpFactory::create_literal_operand(
    lex::Token&& token, LiteralKind literal_kind) {
    return std::make_unique<Literal>(std::move(token), literal_kind);
}

std::unique_ptr<Identifier> OpFactory::create_identifier_operand(
    lex::Token&& token) {
    return std::make_unique<Identifier>(std::move(token));
}
}  // namespace marex::parse