#include "ExprFactory.h"

#include <memory>
#include <stdexcept>

#include "Token.h"
#include "nodes/Expr.h"

namespace marex::parse
{
std::unique_ptr<Expr> ExprFactory::new_expr(
    lex::Token &&token)
{
    switch (token.GetKind())
    {
    default:
        throw std::runtime_error("not implemented");
    }
}
} // namespace marex::parse
