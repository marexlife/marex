#ifndef MAREX_PARSE_BINARYOP_H
#define MAREX_PARSE_BINARYOP_H
#include <cstdint>
#include <memory>

#include "nodes/expr.h"
#include "nodes/op_node.h"
#include "token.h"

namespace marex::parse {
enum struct [[nodiscard]] BinaryOpKind : std::uint8_t {
    None = 0,
    Add,
    Sub,
    Mul,
    Div,
};

class BinaryOp final : public OpNode {
   public:
    explicit BinaryOp(lex::Token&& token,
                      BinaryOpKind binary_op_kind);

    void set(std::unique_ptr<Expr> lhs,
             std::unique_ptr<Expr> rhs);

    [[nodiscard]] BinaryOpKind get_binary_op() const {
        return binary_op_kind_;
    }

   private:
    BinaryOpKind binary_op_kind_{};
    std::unique_ptr<Expr> lhs_;
    std::unique_ptr<Expr> rhs_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_BINARYOP_H