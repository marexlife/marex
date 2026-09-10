#include "BinaryOp.h"

#include <utility>

namespace marex::parse {
void BinaryOp::set(std::unique_ptr<Expr> lhs,
                   std::unique_ptr<Expr> rhs) {
    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);
}
}  // namespace marex::parse