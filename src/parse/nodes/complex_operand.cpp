#include "complex_operand.h"

#include <memory>
#include <string>
#include <utility>

#include "nodes/operator.h"

namespace marex::parse {
ComplexOperand::ComplexOperand(lex::Token&& token,
                               std::shared_ptr<Operator>&& operand)
    : Operand(std::move(token)), operator_(operand) {}

std::string ComplexOperand::as_c() { return operator_->as_c(); }
}  // namespace marex::parse