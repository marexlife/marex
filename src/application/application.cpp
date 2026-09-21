#include "application.h"

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <format>
#include <iostream>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include "action_pick.h"
#include "fetch.h"
#include "help_screen.h"
#include "lex_print.h"
#include "logging.h"
#include "parse.h"
#include "write.h"

namespace marex::app {
void App::run(int argc, char* argv[]) {
    marex::app::select_action(
        this, argc, argv, &App::compile_files,
        &App::run_shell_mode, &App::show_help_screen);
}

void App::compile_files(int argc, char* argv[]) {
    for (std::size_t i = 1; std::cmp_less(i, argc);
         ++i) {
        std::println("compiling {}...", argv[i]);

        App::compile_file(argv[i]);
    }
}

void App::show_help_screen() {
    std::println("{}", help_screen);

    std::exit(EXIT_SUCCESS);
}

void App::compile(
    std::string&& source_code,
    std::optional<std::string_view> filename) {
    auto tokens =
        lexer.run(std::move(source_code), filename);

    lex::print_tokens(tokens);

    auto translation_unit =
        parse::parse(std::move(tokens));

    write::write(std::move(translation_unit));
}

void App::compile_file(std::string_view argument) {
    if (!std::filesystem::is_regular_file(argument))
        [[unlikely]] {
        throw std::runtime_error("not a file");
    }

    auto source_code = fetch::fetch(argument);

    core::log_info("source code:\n{}", source_code);

    App::compile(std::move(source_code), argument);
}

std::pmr::string App::query_user_command() {
    std::println("Input a command...");

    std::pmr::string user_command;
    std::getline(std::cin, user_command);

    return user_command;
}

void App::execute_user_command(
    std::pmr::string&& user_command) {
    App::compile(std::move(user_command));
}

void App::run_shell_iteration() {
    std::pmr::string user_command =
        query_user_command();

    App::execute_user_command(std::move(user_command));

    std::cin.get();
}

void App::run_shell_mode() {
    std::println("Shell mode:");

    for (;;) {
        try {
            App::run_shell_iteration();
        } catch (const std::exception& exception) {
            std::println("{}", exception.what());
        } catch (...) {
            std::println("unkown error");
        }
    }
}
}  // namespace marex::app
