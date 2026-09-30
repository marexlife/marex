#include "op_factory.h"

#include <stdexcept>
#include <utility>

namespace marex::parse {
std::unique_ptr<OpNode> OpFactory::create_op_node(
    lex::Token&& token) {
    if (auto binding_power = token.get_binding_power()) {
        return create_operator(std::move(token));
    }

    return create_operand(std::move(token));
}

std::unique_ptr<Operator> OpFactory::create_operator(
    [[maybe_unused]] lex::Token&& token) {
    throw std::runtime_error("create operator not implemented");
}

std::unique_ptr<Operand> OpFactory::create_operand(
    [[maybe_unused]] lex::Token&& token) {
    throw std::runtime_error("create operand not implemented");
}
}  // namespace marex::parse