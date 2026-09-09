#include "App.h"

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <format>
#include <iostream>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "ActionPicker.h"
#include "Fetcher.h"
#include "HelpScreen.h"
#include "Lexer.h"
#include "LexerPrinter.h"
#include "Logging.h"
#include "Parser.h"
#include "Walker.h"

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
    std::cout << help_screen;

    std::exit(EXIT_SUCCESS);
}

void App::compile(
    std::string&& source_code,
    std::optional<std::string> filename) {
    std::vector<lex::Token> tokens =
        lexer.run(std::move(source_code), filename);

    lex::LexerPrinter::print_tokens(
        tokens);

    auto translation_unit =
        parse::Parser::run(std::move(tokens));

    walk::Walker::run(std::move(translation_unit));
}

void App::compile_file(std::string_view argument) {
    const bool is_directory =
        std::filesystem::is_regular_file(argument);

    if (!is_directory) [[unlikely]] {
        core::log_fatal_error(std::format(
            "{} argument is not a file", argument));

        return;
    }

    std::string source_code =
        fetch::Fetcher::run(argument);

    core::log_info(
        std::format("source code:\n{}", source_code));

    App::compile(std::move(source_code),
                 std::string{argument});
}

std::string App::query_user_command() {
    static const std::string_view message =
        "Input a command...\n";

    std::cout << message;

    std::string user_command;
    std::getline(std::cin, user_command);

    return user_command;
}

void App::execute_user_command(
    std::string&& user_command) {
    App::compile(std::move(user_command));
}

void App::run_shell_iteration() {
    std::string user_command = query_user_command();

    App::execute_user_command(std::move(user_command));

    std::cin.get();
}

void App::run_shell_mode() {
    static const std::string_view message =
        "Shell mode:\n";

    std::cout << message;

    for (;;) {
        try {
            App::run_shell_iteration();
        } catch (const std::exception& exception) {
            std::cout << exception.what() << '\n';
        } catch (...) {
            static const std::string_view
                error_message = "unkown error\n";

            std::cout << error_message;
        }
    }
}
}  // namespace marex::app
