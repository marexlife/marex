#ifndef MAREX_PARSE_OPFACTORY_H
#define MAREX_PARSE_OPFACTORY_H
#include <memory>

#include "nodes/binary_op.h"
#include "token.h"

namespace marex::parse {
class OpNode;
class Operator;
class Operand;
class BinaryOp;

class OpFactory final {
   public:
    OpFactory() = delete;

    [[nodiscard]] static std::unique_ptr<OpNode> create_op_node(
        lex::Token&& token);

   private:
    [[nodiscard]] static std::unique_ptr<Operator> create_operator(
        lex::Token&& token, lex::BindingPower binding_power);

    [[nodiscard]] static std::unique_ptr<Operator>
    create_mono_operator(lex::Token&& token,
                         lex::BindingPower binding_power);

    [[nodiscard]] static std::optional<BinaryOpKind>
    get_binary_op_kind(const lex::Token& token);

    [[nodiscard]] static std::unique_ptr<BinaryOp>
    create_bin_operator(lex::Token&& token,
                        lex::BindingPower binding_power,
                        BinaryOpKind binary_op_kind);

    [[nodiscard]] static std::unique_ptr<Operand> create_operand(
        lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_OPFACTORY_H