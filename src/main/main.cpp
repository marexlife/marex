#include <exception>
#include <format>
#include <print>

#include "application.h"

int main(int argc, char* argv[]) {
    try {
        marex::app::App app{};

        app.run(argc, argv);

        return 0;
    } catch (const std::exception& exception) {
        std::println("{}", exception.what());
    } catch (...) {
        std::println("unkown error");
    }

    return -1;
}
