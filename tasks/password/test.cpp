#include <catch.hpp>
#include <password.h>

TEST_CASE("ValidatePassword") {
    REQUIRE(!ValidatePassword(""));
    REQUIRE(!ValidatePassword("qwerty"));
}
