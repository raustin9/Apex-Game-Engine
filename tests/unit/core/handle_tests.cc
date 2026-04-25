#include <catch2/catch_test_macros.hpp>
#include <apex/apex.h>

TEST_CASE("basic", "[handle]")
{
    auto handle = apx::handle_u32::make();
    REQUIRE(handle.get() == 0);
}

TEST_CASE("unordered_map", "[handle]")
{
    std::unordered_map<apx::handle_u32, int> values;

    auto handle = apx::handle_u32::make();
    values[handle] = handle.get();

    REQUIRE(values.begin()->first == handle);
    REQUIRE(values.begin()->second == handle.get());
}