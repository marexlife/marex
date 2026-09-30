#ifndef MAREX_PARSE_BINARYOP_H
#define MAREX_PARSE_BINARYOP_H
#include <memory>
#include <optional>

#include "binding_power.h"
#include "nodes/op_node.h"
#include "nodes/operator.h"
#include "token.h"
#include "binary_op_kind.h"

namespace marex::parse {
class BinaryOp final : public Operator {
   public:
    explicit BinaryOp(lex::Token&& token,
                      lex::BindingPower binding_power,
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