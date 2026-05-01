#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("default construction", "[slot_map]")
{
    apx::containers::SlotMap<int> map;
    REQUIRE(map.num_elements() == 0);
    REQUIRE_FALSE(map.has_stale_frees());
}

TEST_CASE("basic insertion and removal", "[slot_map]")
{
    apx::containers::SlotMap<int> map;
    REQUIRE(map.num_elements() == 0);

    auto handle = map.insert(0);
    REQUIRE(map.num_elements() == 1);
    REQUIRE(map.valid_handle(handle));
    REQUIRE_FALSE(map.has_stale_frees());

    map.remove(handle);
    REQUIRE(map.num_elements() == 0);
    REQUIRE_FALSE(map.valid_handle(handle));
    REQUIRE(map.has_stale_frees());
}

TEST_CASE("callback application for elements", "[slot_map]")
{
    const int                     num_insertions{ 10 };
    const int                     expected{ 10 };
    apx::containers::SlotMap<int> map;
    for ( int i = 0; i < num_insertions; i++ )
        (void)map.insert(expected);

    map.for_each_valid([](int i) { REQUIRE(i == expected); });
}
