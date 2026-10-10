#include "complex_operand.h"

#include <memory>
#include <string>
#include <utility>

#include "nodes/operator.h"
#include "token.h"
#include "token_kind.h"

namespace marex::parse {
ComplexOperand::ComplexOperand(std::shared_ptr<Operator>&& operand)
    : Operand(lex::Token("complex", lex::TokenKind::Complex)),
      operator_(std::move(operand)) {}

std::string ComplexOperand::as_c() { return operator_->as_c(); }
}  // namespace marex::parse