#include "hello.hxx"
#include "myWebsocket.hxx"
#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>
#include <boost/beast.hpp>
#include <string>
using namespace boost::beast;
using namespace boost::asio;
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>
using tcp_acceptor = use_awaitable_t<>::as_default_on_t<tcp::acceptor>;
typedef boost::asio::use_awaitable_t<>::as_default_on_t<boost::asio::basic_waitable_timer<boost::asio::chrono::system_clock> > CoroTimer;

boost::asio::awaitable<void>
helloWorld ()
{
  using namespace boost::asio;
  auto executor = co_await this_coro::executor;
  tcp_acceptor acceptor (executor, {});
  using namespace boost::asio::experimental::awaitable_operators;
  auto socket = co_await (acceptor.async_accept ());
  typedef boost::beast::websocket::stream<boost::asio::use_awaitable_t<>::as_default_on_t<boost::beast::tcp_stream> > Websocket;
  auto connection = std::make_shared<Websocket> (Websocket{ std::move (socket) });
  connection->set_option (websocket::stream_base::timeout::suggested (role_type::server));
  connection->set_option (websocket::stream_base::decorator ([] (websocket::response_type &res) { res.set (http::field::server, std::string (BOOST_BEAST_VERSION_STRING) + " websocket-server-async"); }));
  co_await connection->async_accept ();
  auto myWebsocket = std::make_shared<MyWebsocket<Websocket> > (MyWebsocket<Websocket>{ connection, "userMatchmaking", std::to_string (2) });
  boost::asio::co_spawn (executor, myWebsocket->readLoop ([] (const std::string &msg) mutable {}) && myWebsocket->writeLoop (), [] (auto eptr) {});
}