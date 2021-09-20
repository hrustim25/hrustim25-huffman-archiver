#include <catch.hpp>

#include "unixpath.h"

TEST_CASE("NormalizePath") {
    REQUIRE("/" == NormalizePath("/", "."));
    REQUIRE("/home/user2" == NormalizePath("/home/user1", "../user2"));

    REQUIRE(NormalizePath("/", "..").empty());
    REQUIRE(NormalizePath("/home", "../../tmp").empty());
}
