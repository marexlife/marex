#ifndef MAREX_PARSE_BINARYOP_H
#define MAREX_PARSE_BINARYOP_H
#include <memory>
#include <optional>

#include "binary_op_kind.h"
#include "binding_power.h"
#include "nodes/op_node.h"
#include "nodes/operator.h"
#include "token.h"

namespace marex::parse {
class BinaryOp final : public Operator {
   public:
    explicit BinaryOp(lex::Token&& token,
                      lex::BindingPower binding_power,
                      BinaryOpKind binary_op_kind);

    void set(std::shared_ptr<OpNode> lhs,
             std::shared_ptr<OpNode> rhs);
    void set_lhs(std::shared_ptr<OpNode> lhs);
    void set_rhs(std::shared_ptr<OpNode> rhs);

    [[nodiscard]] BinaryOpKind get_binary_op() const {
        return binary_op_kind_;
    }

    [[nodiscard]] bool completed() const override {
        return lhs_finished() && rhs_finished();
    }

    [[nodiscard]] bool lhs_finished() const {
        return lhs_.has_value();
    }

    [[nodiscard]] bool rhs_finished() const {
        return rhs_.has_value();
    }

    [[nodiscard]] std::string as_c() override {
        return std::format("({} {} {})", lhs_.value()->as_c(),
                           to_c(binary_op_kind_),
                           rhs_.value()->as_c());
    }

   private:
    BinaryOpKind binary_op_kind_{};
    std::optional<std::shared_ptr<OpNode>> lhs_;
    std::optional<std::shared_ptr<OpNode>> rhs_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_BINARYOP_H