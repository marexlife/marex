#ifndef MAREX_PARSE_EXPRFACTORY_H
#define MAREX_PARSE_EXPRFACTORY_H
#include <memory>

#include "nodes/Expr.h"

namespace marex::parse {
class ExprFactory final {
   public:
    [[nodiscard]] static std::unique_ptr<Expr>
    new_expression(const TokenStream& stream);

   private:
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_EXPRFACTORY_H
