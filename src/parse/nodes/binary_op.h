#ifndef MAREX_PARSE_BINARYOP_H
#define MAREX_PARSE_BINARYOP_H
#include <cstdint>
#include <memory>
#include <stdexcept>

#include "nodes/expr.h"
#include "token.h"

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
    [[nodiscard]] std::string as_c() override {
        throw std::runtime_error(
            "not implemented yet");
    }

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