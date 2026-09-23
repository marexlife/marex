#include "expr_build.h"

#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

#include "binding_power.h"
#include "defer.h"
#include "nodes/expr.h"
#include "token.h"
#include "token_kind.h"
#include "token_stream.h"

namespace marex {
namespace parse {
struct Op final {
    Op(lex::TokenKind token_kind,
       lex::BindingPower binding_power)
        : token_kind(token_kind),
          binding_power(binding_power) {}

    lex::TokenKind token_kind{};
    lex::BindingPower binding_power{};
};
}  // namespace parse

std::unique_ptr<parse::Expr> parse::build_expr(
    TokenStream& stream) {
    auto get_is_current_more_powerful =
        [](lex::BindingPower previous_binding_power,
           lex::BindingPower current_binding_power) {
            return std::to_underlying(
                       previous_binding_power) <
                   std::to_underlying(
                       current_binding_power);
        };

    std::optional<std::reference_wrapper<Op>>
        previous_op = std::nullopt;

    std::vector<Op> operators;
    std::vector<lex::TokenKind> non_operators;

    stream.run_until_stmt_end(
        [&](TokenStream::RunUntilStmtEndPack pack) {
            auto token = pack.token.get();

            core::Defer iter_defer = [&] {
                if (auto binding_power =
                        token.get_binding_power()) {
                    Op current_op{token.get_kind(),
                                  *binding_power};
                    previous_op = current_op;

                    operators.emplace_back(current_op);
                } else {
                    non_operators.emplace_back(
                        token.get_kind());
                }
            };

            if (!previous_op) {
                return;
            }

            auto current_binding_power =
                token.get_binding_power();

            if (!current_binding_power) {
                return;
            }

            lex::BindingPower previous_binding_power =
                previous_op->get().binding_power;

            if (std::invoke(
                    get_is_current_more_powerful,
                    *current_binding_power,
                    previous_binding_power)) {
            }
        });

    throw std::runtime_error("not implemented yet");
}

}  // namespace marex
