#ifndef MAREX_PARSE_OPFACTORY_H
#define MAREX_PARSE_OPFACTORY_H
#include <memory>
#include <optional>

#include "nodes/binary_op_kind.h"
#include "nodes/identifier.h"
#include "nodes/literal.h"
#include "token.h"

namespace marex::parse {
class OpNode;
class Operator;
class Operand;
class BinaryOp;

enum struct LiteralKind : std::uint8_t;

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

    [[nodiscard]] static std::optional<LiteralKind> to_literal_kind(
        const lex::Token& token);

    [[nodiscard]] static std::unique_ptr<Literal>
    create_literal_operand(lex::Token&& token,
                           LiteralKind literal_kind);

    [[nodiscard]] static std::unique_ptr<Identifier>
    create_identifier_operand(lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_OPFACTORY_H