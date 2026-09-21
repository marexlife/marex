#include "invalid_context_exceteption.h"

#include <utility>

namespace marex::parse {
InvalidContextException::InvalidContextException(
    std::string&& message)
    : message_(std::move(message)) {}
}  // namespace marex::parse