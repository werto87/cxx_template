#include "hello.hxx"
#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>

boost::asio::awaitable<void> helloWorld() {
    namespace asio = boost::asio;
    using asio::ip::tcp;
    using namespace asio::experimental::awaitable_operators;

    tcp::socket s(co_await asio::this_coro::executor);
    auto token = asio::use_awaitable;
    co_await (s.async_connect({}, token) && s.async_connect({}, token));

    co_return;
}

int abc() { return 42; }
