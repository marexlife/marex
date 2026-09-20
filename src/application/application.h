#ifndef MAREX_APP_APP_H
#define MAREX_APP_APP_H
#include <optional>
#include <string_view>

#include "lexer.h"

namespace marex::app {
class App final {
   public:
    App() = default;
    ~App() = default;

    App(App&&) = delete;
    App& operator=(App&&) = delete;
    App(const App&) = delete;
    App& operator=(const App&) = delete;

    void run(int argc, char** argv);

   private:
    static void show_help_screen();
    void compile_files(int argc, char* argv[]);

    void compile_file(std::string_view argument);

    void compile(std::pmr::string&& source_code,
                 std::optional<std::string_view>
                     filename = std::nullopt);

    void run_shell_mode();
    void run_shell_iteration();
    [[nodiscard]] static std::pmr::string
    query_user_command();
    void execute_user_command(
        std::pmr::string&& user_command);

    lex::Lexer lexer;
};
}  // namespace marex::app
#endif  // MAREX_APP_APP_H
