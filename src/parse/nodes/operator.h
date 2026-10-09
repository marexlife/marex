#ifndef MAREX_PARSE_OPERATOR_H
#define MAREX_PARSE_OPERATOR_H
#include <memory>

#include "binding_power.h"
#include "nodes/complex_operand.h"
#include "nodes/op_node.h"
#include "token.h"

namespace marex::parse {
class ComplexOperand;

class Operator : public OpNode {
   public:
    Operator(lex::Token&& token, lex::BindingPower binding_power);

    [[nodiscard]] lex::BindingPower get_binding_power() const {
        return binding_power_;
    }

    [[nodiscard]] std::shared_ptr<ComplexOperand>
    to_complex_operand();

    [[nodiscard]] virtual bool completed() const = 0;

   private:
    lex::BindingPower binding_power_{};
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_OPERATOR_H