#include <catch.hpp>

#include "checkers_topology.h"
#include "knight_topology.h"
#include "overflow_topology.h"
#include "planar_topology.h"
#include "robot.h"

#include <algorithm>
#include <sstream>

namespace {
std::vector<std::vector<bool>> ParseMap(const std::vector<std::string>& text_map) {
    std::vector<std::vector<bool>> bool_map;

    for (const auto& line : text_map) {
        bool_map.emplace_back();
        std::transform(line.begin(), line.end(), std::back_inserter(bool_map.back()),
                       [](char ch) { return ch == '*'; });
    }

    return bool_map;
}
}  // namespace

TEST_CASE("RobotPlanar") {
    {
        const auto& map = ParseMap({
            ".*.",
            ".*.",
            "...",
        });

        PlanarTopology topology;

        REQUIRE(PathExists(topology, {.x = 0, .y = 0}, {.x = 2, .y = 2}));
    }
    {
        const auto& map = ParseMap({
            ".*.",
            ".*.",
            ".*.",
        });

        PlanarTopology topology;

        REQUIRE(!PathExists(topology, {.x = 0, .y = 0}, {.x = 2, .y = 2}));
    }
}

TEST_CASE("RobotOverflow") {
    {
        const auto& map = ParseMap({
            ".*.",
            "***",
            ".*.",
        });

        OverflowTopology topology;

        REQUIRE(PathExists(topology, {.x = 0, .y = 0}, {.x = 2, .y = 2}));
    }
    {
        const auto& map = ParseMap({
            ".***",
            ".*.*",
            ".***",
        });

        OverflowTopology topology;

        REQUIRE(!PathExists(topology, {.x = 0, .y = 0}, {.x = 2, .y = 1}));
    }
}

TEST_CASE("RobotCheckers") {
    {
        const auto& map = ParseMap({
            ".*....",
            "*.*...",
            "..*.*.",
            "......",
        });

        CheckersTopology topology;

        REQUIRE(PathExists(topology, {.x = 0, .y = 0}, {.x = 4, .y = 0}));
    }
    {
        const auto& map = ParseMap({
            "..",
            "..",
        });

        CheckersTopology topology;

        REQUIRE(!PathExists(topology, {.x = 0, .y = 0}, {.x = 1, .y = 0}));
    }
}

TEST_CASE("RobotKnight") {
    {
        const auto& map = ParseMap({
            ".*.",
            "***",
            "...",
        });

        KnightTopology topology;

        REQUIRE(PathExists(topology, {.x = 0, .y = 0}, {.x = 2, .y = 0}));
    }
    {
        const auto& map = ParseMap({
            ".*.",
            "*..",
            "...",
        });

        KnightTopology topology;

        REQUIRE(!PathExists(topology, {.x = 0, .y = 0}, {.x = 2, .y = 2}));
    }
}
