#include "hello.hxx"
#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>

static boost::asio::awaitable<void> helloWorld() {
  using namespace boost::asio::experimental::awaitable_operators;
  auto ioContext = boost::asio::io_context{};
  boost::asio::ip::tcp::socket socket(ioContext);
  auto test = socket.async_connect({}, boost::asio::use_awaitable) &&
              socket.async_connect({}, boost::asio::use_awaitable);
  co_return;
}

int abc() { return 42; }
