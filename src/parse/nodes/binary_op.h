#ifndef MAREX_PARSE_BINARYOP_H
#define MAREX_PARSE_BINARYOP_H
#include <cstdint>
#include <memory>
#include <optional>

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

    void set(std::unique_ptr<OpNode> lhs,
             std::unique_ptr<OpNode> rhs);
    void set_lhs(std::unique_ptr<OpNode> lhs);
    void set_rhs(std::unique_ptr<OpNode> rhs);

    [[nodiscard]] BinaryOpKind get_binary_op() const {
        return binary_op_kind_;
    }

   private:
    BinaryOpKind binary_op_kind_{};
    std::optional<std::unique_ptr<OpNode>> lhs_;
    std::optional<std::unique_ptr<OpNode>> rhs_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_BINARYOP_H