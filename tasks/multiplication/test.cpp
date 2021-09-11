#include <catch.hpp>
#include <multiplication.h>

TEST_CASE("Simple") {
    REQUIRE(6 == Multiply(2, 3));
}
