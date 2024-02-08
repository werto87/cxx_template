#include "src/hello.hxx"
#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>
int
main ()
{
  using namespace boost::asio::experimental::awaitable_operators;
  auto ioContext = boost::asio::io_context{};
  boost::asio::ip::tcp::socket socket (ioContext);
  auto test = socket.async_connect ({}, boost::asio::use_awaitable) && socket.async_connect ({}, boost::asio::use_awaitable);
  abc ();
}