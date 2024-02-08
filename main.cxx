#include "src/hello.hxx"
#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>

struct my_token_t : boost::asio::use_awaitable_t<> { } static inline constexpr my_token;
template <typename... Sigs>
struct boost::asio::async_result<my_token_t, Sigs...> : async_result<use_awaitable_t<>, Sigs...> {};

int main() {
    namespace asio = boost::asio;
    using asio::ip::tcp;
    using namespace asio::experimental::awaitable_operators;

    asio::io_context ioc;
    tcp::socket      s(ioc);

    auto token = my_token;
    co_spawn(
        ioc,
        (s.async_connect({}, token) && s.async_connect({}, token)),
        asio::detached);
    abc();
}
