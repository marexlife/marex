#include "op_node_factory.h"

#include <memory>
#include <stdexcept>
#include <utility>

#include "nodes/binary_op.h"
#include "nodes/op_node.h"
#include "token.h"
#include "token_kind.h"

namespace marex::parse {
std::unique_ptr<OpNode> OpNodeFactory::create_node(
    lex::Token&& token) {
    if (auto token_op_info = token.get_token_info_optional()) {
        return create_operator(std::move(token), *token_op_info);
    }

    return create_operand(std::move(token));
}

std::unique_ptr<OpNode> OpNodeFactory::create_operator(
    lex::Token&& token, lex::TokenOpInfo token_op_info) {
    switch (token_op_info.token_op_kind) {
        case lex::TokenOpKind::BinOp: {
            auto token_kind = token.get_kind();
            return std::make_unique<BinaryOp>(
                std::move(token),
                OpNodeFactory::to_binary_op_kind(token_kind),
                token_op_info.binding_power);
        } break;
        case lex::TokenOpKind::MonoOp: {
            throw std::runtime_error(
                "mono op not implemented yet in Factory");
        } break;
        default:
            std::unreachable();
    }
}

std::unique_ptr<OpNode> OpNodeFactory::create_operand(
    [[maybe_unused]] lex::Token&& token) {
    throw std::runtime_error("not implemented");
}

BinaryOpKind OpNodeFactory::to_binary_op_kind(
    lex::TokenKind token_kind) {
    switch (token_kind) {
        case lex::TokenKind::OpAdd:
            return BinaryOpKind::Add;
        case lex::TokenKind::OpSub:
            return BinaryOpKind::Sub;
        case lex::TokenKind::OpMul:
            return BinaryOpKind::Mul;
        case lex::TokenKind::OpDiv:
            return BinaryOpKind::Div;
        default:
            std::unreachable();
    }
}
}  // namespace marex::parse