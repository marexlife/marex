#include "error.h"

#include <memory>
#include <string>
#include <utility>

#include "passkey.h"

namespace marex::core {
std::unique_ptr<Error> Error::from_message(
    std::string&& error_message) {
    return std::make_unique<Error>(
        Passkey<Error>{}, std::move(error_message));
}

std::unique_ptr<Error> Error::from_exception(
    const std::exception& exception) {
    return std::make_unique<Error>(Passkey<Error>{},
                                   exception.what());
}

std::unique_ptr<Error> Error::from_nothing() {
    return std::make_unique<Error>(Passkey<Error>{},
                                   "unkown error");
}

Error::Error([[maybe_unused]] core::Passkey<Error> passkey,
             std::string&& error_message)
    : error_message_(std::move(error_message)) {}
}  // namespace marex::core