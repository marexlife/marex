#include "op_factory.h"

#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>

#include "binding_power.h"
#include "nodes/binary_op.h"
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

    throw std::runtime_error("not implemented");
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
    [[maybe_unused]] lex::Token&& token) {
    throw std::runtime_error("create operand not implemented");
}
}  // namespace marex::parse