#include <catch.hpp>

#include "unixpath.h"

TEST_CASE("UnixPath") {
    UnixPath path("/home");

    path.ChangeDirectory(".");
    REQUIRE("/home" == path.GetAbsolutePath());

    path.ChangeDirectory("/home/user");
    REQUIRE("/home/user" == path.GetAbsolutePath());
    REQUIRE("./user" == path.GetAbsolutePath());

    path.ChangeDirectory("..");
    REQUIRE("/home" == path.GetAbsolutePath());
    REQUIRE("." == path.GetAbsolutePath());

    path.ChangeDirectory(".././././tmp/dir/..");
    REQUIRE("/tmp" == path.GetAbsolutePath());
    REQUIRE("../../tmp" == path.GetAbsolutePath());
}
