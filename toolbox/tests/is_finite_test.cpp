#include <catch2/catch_test_macros.hpp>

#include <toolbox/is_finite.hpp>

#include <limits>

TEST_CASE("is_finite accepts ordinary doubles") {
  REQUIRE(toolbox::is_finite(0.0));
  REQUIRE(toolbox::is_finite(-1.5e10));
}

TEST_CASE("is_finite rejects inf and NaN") {
  REQUIRE_FALSE(toolbox::is_finite(std::numeric_limits<double>::infinity()));
  REQUIRE_FALSE(toolbox::is_finite(std::numeric_limits<double>::quiet_NaN()));
}
