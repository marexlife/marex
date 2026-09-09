#include "Assignment.h"

#include <utility>

#include "nodes/Expr.h"

namespace marex::parse {
Assignment::Assignment(lex::Token&& token)
    : Expr(std::move(token)) {}

void Assignment::set_lhs(std::unique_ptr<Expr> lhs) {
    this->lhs = std::move(lhs);
}

void Assignment::set_rhs(std::unique_ptr<Expr> rhs) {
    this->rhs = std::move(rhs);
}
}  // namespace marex::parse
