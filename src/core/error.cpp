#include "error.h"

#include <string>
#include <utility>

namespace marex::core {
Error::Error(std::string&& error_message)
    : error_message_(std::move(error_message)) {}
}  // namespace marex::core