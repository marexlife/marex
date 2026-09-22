#include "expr_build.h"

#include <cstddef>
#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include "binding_rank.h"
#include "defer.h"
#include "expr_factory.h"
#include "logging.h"
#include "nodes/expr.h"
#include "token.h"
#include "token_kind.h"
#include "token_stream.h"

namespace marex {
namespace parse {}  // namespace parse

std::unique_ptr<parse::Expr> parse::build_expr(
    TokenStream& stream) {
    throw std::runtime_error("not implemented yet");
}

}  // namespace marex
