#ifndef MAREX_PARSE_FUNCARG_H
#define MAREX_PARSE_FUNCARG_H
#include <string>

#include "expr_kind.h"

namespace marex::parse {
struct FuncArg final {
    FuncArg(std::string&& arg_name, ExprKind expr_kind)
        : arg_name(std::move(arg_name)), expr_kind(expr_kind) {}

    std::string arg_name;
    ExprKind expr_kind{};
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_FUNCARG_H