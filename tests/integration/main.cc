#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE( "init", "[integration]" ) {
  REQUIRE(apx::test());
}