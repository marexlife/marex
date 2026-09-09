#ifndef MAREX_PARSE_EXPRFACTORY_H
#define MAREX_PARSE_EXPRFACTORY_H
#include <memory>

#include "nodes/Expr.h"

namespace marex::parse {
class ExprFactory final {
   public:
    [[nodiscard]] std::unique_ptr<Expr>
    new_expression();

   private:
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_EXPRFACTORY_H