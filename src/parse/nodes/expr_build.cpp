#include "expr_build.h"

#include <cstddef>
#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

#include "binding_power.h"
#include "defer.h"
#include "nodes/binary_op.h"
#include "nodes/expr.h"
#include "nodes/identifier.h"
#include "nodes/op_node.h"
#include "nodes/operand.h"
#include "token.h"
#include "token_kind.h"
#include "token_stream.h"

namespace marex {
namespace parse {
struct Op final {
    Op(lex::Token&& token, lex::BindingPower binding_power)
        : token(std::move(token)), binding_power(binding_power) {}

    lex::Token token;
    lex::BindingPower binding_power{};
};

[[nodiscard]] static std::unique_ptr<parse::OpNode> make_op_node(
    lex::Token&& token);

[[nodiscard]] static std::unique_ptr<parse::Operand>
make_operand_node(lex::Token&& token);
}  // namespace parse

std::unique_ptr<parse::Expr> parse::build_expr(TokenStream& stream) {
    auto get_current_is_more_powerful =
        [](lex::BindingPower previous_binding_power,
           lex::BindingPower current_binding_power) {
            return std::to_underlying(previous_binding_power) <
                   std::to_underlying(current_binding_power);
        };

    std::optional<std::reference_wrapper<Op>> previous_op =
        std::nullopt;
    std::optional<std::reference_wrapper<lex::Token>>
        previous_operand = std::nullopt;

    constexpr std::size_t reserve_non_operators = 100;
    constexpr std::size_t reserve_operators =
        reserve_non_operators / 2;

    std::vector<Op> operators;
    std::vector<lex::Token> non_operators;

    operators.reserve(reserve_operators);
    non_operators.reserve(reserve_non_operators);

    stream.run_until_stmt_end([&](TokenStream::RunUntilStmtEndPack
                                      pack) {
        auto token = pack.token.get();

        core::Defer iter_defer = [&] {
            if (auto binding_power = token.get_binding_power()) {
                Op current_op{lex::Token(token), *binding_power};
                previous_op = current_op;

                operators.emplace_back(current_op);
            } else {
                previous_operand = token;

                non_operators.emplace_back(lex::Token(token));
            }
        };

        auto current_binding_power = token.get_binding_power();

        if (!current_binding_power) {
            return;
        }

        auto previous_operand_node =
            make_operand_node(lex::Token(previous_operand->get()));

        if (!previous_op) {
            if (previous_operand) {
                auto node = make_op_node(lex::Token(token));

                switch (node->get_op_node_kind()) {
                    case OpNodeKind::BinaryOp: {
                        BinaryOp& binary_node =
                            node->cast<BinaryOp>();

                        binary_node.set_lhs(
                            std::move(previous_operand_node));
                    } break;
                    case OpNodeKind::MonoOp: {
                        throw std::runtime_error(
                            "not implemented yet");
                    } break;
                    default:
                        std::unreachable();
                }
            }

            return;
        }

        lex::BindingPower previous_binding_power =
            previous_op->get().binding_power;

        if (std::invoke(get_current_is_more_powerful,
                        *current_binding_power,
                        previous_binding_power)) {
            auto node_from_current = make_op_node(lex::Token(token));

            switch (node_from_current->get_op_node_kind()) {
                case OpNodeKind::BinaryOp: {
                    BinaryOp& binary_node =
                        node_from_current->cast<BinaryOp>();

                    binary_node.set_lhs(
                        std::move(previous_operand_node));
                } break;
                case OpNodeKind::MonoOp: {
                    throw std::runtime_error("not implemented yet");
                } break;
                default:
                    std::unreachable();
            }
        } else {
            auto node_from_previous =
                make_op_node(lex::Token(previous_op->get().token));

            switch (node_from_previous->get_op_node_kind()) {
                case OpNodeKind::BinaryOp: {
                    BinaryOp& binary_node =
                        node_from_previous->cast<BinaryOp>();

                    binary_node.set_rhs(
                        std::move(previous_operand_node));
                } break;
                case OpNodeKind::MonoOp: {
                    throw std::runtime_error("not implemented yet");
                } break;
                default:
                    std::unreachable();
            }
        }
    });

    throw std::runtime_error("not implemented yet");
}

[[nodiscard]] std::unique_ptr<parse::OpNode> parse::make_op_node(
    lex::Token&& token) {
    switch (token.get_kind()) {
        case lex::TokenKind::OpAdd:
            return std::make_unique<BinaryOp>(std::move(token),
                                              BinaryOpKind::Add);
        case lex::TokenKind::OpSub:
            return std::make_unique<BinaryOp>(std::move(token),
                                              BinaryOpKind::Sub);
        case lex::TokenKind::OpMul:
            return std::make_unique<BinaryOp>(std::move(token),
                                              BinaryOpKind::Mul);
        case lex::TokenKind::OpDiv:
            return std::make_unique<BinaryOp>(std::move(token),
                                              BinaryOpKind::Div);
        default:
            throw std::runtime_error(
                "internal "
                "error, op "
                "not covered "
                "in expr "
                "build");
    }
}

std::unique_ptr<parse::Operand> parse::make_operand_node(
    [[maybe_unused]] lex::Token&& token) {
    switch (token.get_kind()) {
        case lex::TokenKind::Identifier:
            return std::make_unique<Identifier>(lex::Token(token));
        default:
            std::unreachable();
    }
}
}  // namespace marex
