#ifndef MAREX_FETCH_FETCHER_H
#define MAREX_FETCH_FETCHER_H
#include <string>

namespace marex::fetch {
class Fetcher final {
public:
    static const std::size_t result_reserve_amount
        = 100;

    Fetcher() = delete;
    Fetcher(Fetcher&&) = delete;
    Fetcher& operator=(Fetcher&&) = delete;
    Fetcher(const Fetcher&) = delete;
    Fetcher& operator=(const Fetcher&) = delete;
    ~Fetcher() = delete;

    [[nodiscard]] static std::pmr::string run(
        std::string_view filepath);
};
} // namespace marex::fetch
#endif // MAREX_FETCH_FETCHER_H
