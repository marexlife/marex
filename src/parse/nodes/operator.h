#ifndef MAREX_PARSE_OPERATOR_H
#define MAREX_PARSE_OPERATOR_H
#include "binding_power.h"
#include "nodes/op_node.h"
#include "token.h"

namespace marex::parse {
class Operator : public OpNode {
   public:
    Operator(lex::Token&& token, OpNodeKind op_node_kind,
             lex::BindingPower binding_power);

   private:
    lex::BindingPower binding_power{};
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_OPERATOR_H