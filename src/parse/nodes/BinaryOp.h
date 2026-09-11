#ifndef MAREX_PARSE_BINARYOP_H
#define MAREX_PARSE_BINARYOP_H
#include <cstdint>
#include <memory>

#include "Token.h"
#include "nodes/Expr.h"

namespace marex::parse {
enum struct [[nodiscard]] BinaryOpKind : std::uint8_t {
    None = 0,
    Add,
    Sub,
    Mul,
    Div,
};

class BinaryOp final : public Expr {
   public:
    explicit BinaryOp(lex::Token&& token,
                      BinaryOpKind binary_op_kind);

    void set(std::unique_ptr<Expr> lhs,
             std::unique_ptr<Expr> rhs);

    [[nodiscard]] BinaryOpKind get_binary_op() const {
        return binary_op_kind;
    }

   private:
    BinaryOpKind binary_op_kind{};
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_BINARYOP_H