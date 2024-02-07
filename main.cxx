#include "src/hello.hxx"
int
main ()
{
  using namespace boost::asio::experimental::awaitable_operators;
  auto test = helloWorld () && helloWorld ();
}