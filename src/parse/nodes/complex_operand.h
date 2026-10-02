#ifndef MAREX_PARSE_COMPLEXOPERAND_H
#define MAREX_PARSE_COMPLEXOPERAND_H
#include <memory>

#include "nodes/operand.h"
#include "nodes/operator.h"
#include "token.h"

namespace marex::parse {
class ComplexOperand final : public Operand {
   public:
    explicit ComplexOperand(lex::Token&& token,
                            std::unique_ptr<Operator> operand);

   private:
    std::unique_ptr<Operator> operand_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_COMPLEXOPERAND_H