#include <catch2/catch_test_macros.hpp>
#include <apex/test.h>

TEST_CASE( "init", "[unit]" )
{
    REQUIRE(apx::test());
}
