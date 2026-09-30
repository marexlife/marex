#ifndef MAREX_PARSE_OPFACTORY_H
#define MAREX_PARSE_OPFACTORY_H
#include <memory>

#include "nodes/op_node.h"
#include "nodes/operand.h"
#include "nodes/operator.h"
#include "token.h"

namespace marex::parse {
class OpFactory final {
   public:
    OpFactory() = delete;

    [[nodiscard]] static std::unique_ptr<OpNode> create_op_node(
        lex::Token&& token);

   private:
    [[nodiscard]] static std::unique_ptr<Operator> create_operator(
        lex::Token&& token, lex::BindingPower binding_power);

    [[nodiscard]] static std::unique_ptr<Operand> create_operand(
        lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_OPFACTORY_H