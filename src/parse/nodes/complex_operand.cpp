#include "complex_operand.h"

#include <utility>

#include "nodes/operand.h"

namespace marex::parse {
ComplexOperand::ComplexOperand(lex::Token&& token,
                               std::unique_ptr<Operator> operand)
    : Operand(std::move(token)), operand_(std::move(operand)) {}
}  // namespace marex::parse