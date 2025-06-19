#include "src/hello.hxx"
#include <catch2/catch_test_macros.hpp>

TEST_CASE ("hello", "[hello]") { REQUIRE (helloWorld () == "Hello World!"); }