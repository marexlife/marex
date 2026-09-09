#include "ExprFactory.h"

#include <memory>
#include <stdexcept>

#include "ParserPack.h"
#include "TokenKind.h"
#include "nodes/Assignment.h"
#include "nodes/Expr.h"

namespace marex::parse {
std::unique_ptr<Expr> ExprFactory::new_expression(
    const ParserPack& pack) {
    switch (pack.get_kind()) {
        case marex::lex::TokenKind::Assignment:
            return std::make_unique<Assignment>(
                pack.copy_out_token());
        default:
            throw std::runtime_error(
                "not implemented");
    }
}
}  // namespace marex::parse