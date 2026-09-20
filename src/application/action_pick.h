#ifndef MAREX_APP_ACTIONPICK_H
#define MAREX_APP_ACTIONPICK_H
#include <functional>
#include <string_view>
#include <type_traits>

namespace marex::app {
class App;

template <typename FileAction, typename ShellAction,
          typename ShowHelpScreenAction>
static void select_action(
    App* app, int argc, char* argv[],
    FileAction file_action, ShellAction shell_action,
    ShowHelpScreenAction show_help_screen_action) {
    if (argc < 2) {
        std::invoke(shell_action, app);

        return;
    }

    const std::string_view first_argument = argv[1];

    if (first_argument == "--help") [[unlikely]] {
        std::invoke(show_help_screen_action);

        return;
    }

    std::invoke(file_action, app, argc, argv);
}
}  // namespace marex::app
#endif  // MAREX_APP_ACTIONPICK_H