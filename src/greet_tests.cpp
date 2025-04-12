#include <catch2/catch_test_macros.hpp>

#include "greet.h"

TEST_CASE("greet", "[greet]") {
  REQUIRE(greet("World") == "Hello World!\n");
}