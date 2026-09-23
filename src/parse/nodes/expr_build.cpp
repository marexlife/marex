#include "expr_build.h"

#include <memory>
#include <stdexcept>
#include <vector>

#include "binding_power.h"
#include "nodes/expr.h"
#include "token.h"
#include "token_stream.h"

namespace marex {
std::unique_ptr<parse::Expr> parse::build_expr(
    TokenStream& stream) {
    [[maybe_unused]] bool previous_was_more_powerful =
        false;

    std::vector<lex::BindingPower> binding_powers;

    stream.run_until_stmt_end(
        [&](TokenStream::RunUntilStmtEndPack pack) {
            if (auto binding_power =
                    pack.token.get()
                        .get_binding_power()) {
            }
        });

    throw std::runtime_error("not implemented yet");
}

}  // namespace marex
