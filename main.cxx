#include "src/hello.hxx"
#include <format>
#include <print>

int
main ()
{
  std::println ("{}", helloWorld ());
  return 0;
}