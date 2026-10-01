#ifndef MAREX_PARSE_OPNODE_H
#define MAREX_PARSE_OPNODE_H
#include <concepts>
#include <memory>

#include "expr.h"
#include "token.h"

namespace marex::parse {
enum struct [[nodiscard]] OpNodeKind : std::uint8_t {
    None = 0,
    BinaryOp,
    MonoOp,
    Operand,
};

class OpNode : public Expr,
               public std::enable_shared_from_this<OpNode> {
   public:
    explicit OpNode(lex::Token&& token, OpNodeKind op_node_kind);

    template <std::derived_from<OpNode> T>
    [[nodiscard]] std::shared_ptr<T> cast() {
        return shared_from_this();
    }

    [[nodiscard]] OpNodeKind get_op_node_kind() const {
        return op_node_kind_;
    }

   private:
    OpNodeKind op_node_kind_{};
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_OPNODE_H
