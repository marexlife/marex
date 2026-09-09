#include "Assignment.h"

#include <stdexcept>
#include <string>
#include <utility>

#include "ParserPack.h"
#include "nodes/Expr.h"

namespace marex::parse {
Assignment::Assignment(lex::Token&& token) : Expr(std::move(token)) {}

std::string Assignment::as_c() {
    throw std::runtime_error(
        "Assignment as_c not implemented yet");
}

void Assignment::parse(
    [[maybe_unused]] TokenStream& pack) {
    parse_lhs(pack);
    parse_rhs(pack);
}

void Assignment::parse_lhs(
    [[maybe_unused]] TokenStream& pack) {

}

void Assignment::parse_rhs(
    [[maybe_unused]] TokenStream& pack) {}
}  // namespace marex::parse
