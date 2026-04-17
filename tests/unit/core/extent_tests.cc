#include <catch2/catch_test_macros.hpp>
#include <apex/core/core.h>

template <apx::traits::Numeric N>
apx::Width<N>
create_and_validate_width(N n) noexcept
{
    apx::Width<N> w{ n };
    REQUIRE(w == n);
    REQUIRE(w.get() == n);
    return w;
}

TEST_CASE("basic width", "[extent]")
{
    (void) create_and_validate_width<int>(10);
    (void) create_and_validate_width<long>(10);
    (void) create_and_validate_width<long long>(10);
    (void) create_and_validate_width<unsigned int>(10);
    (void) create_and_validate_width<unsigned long>(10);
    (void) create_and_validate_width<unsigned long long>(10);
    (void) create_and_validate_width<float>(10);
    (void) create_and_validate_width<double>(10);

    (void) create_and_validate_width<std::int32_t>(10);
    (void) create_and_validate_width<std::int64_t>(10);
    (void) create_and_validate_width<std::uint32_t>(10);
    (void) create_and_validate_width<std::uint64_t>(10);
}

template <apx::traits::Numeric N>
apx::Height<N>
create_and_validate_height(N n) noexcept
{
    apx::Height<N> w{ n };
    REQUIRE(w == n);
    REQUIRE(w.get() == n);
    return w;
}

TEST_CASE("basic height", "[extent]")
{
    (void) create_and_validate_height<int>(10);
    (void) create_and_validate_height<long>(10);
    (void) create_and_validate_height<long long>(10);
    (void) create_and_validate_height<unsigned int>(10);
    (void) create_and_validate_height<unsigned long>(10);
    (void) create_and_validate_height<unsigned long long>(10);
    (void) create_and_validate_height<float>(10);
    (void) create_and_validate_height<double>(10);

    (void) create_and_validate_height<std::int32_t>(10);
    (void) create_and_validate_height<std::int64_t>(10);
    (void) create_and_validate_height<std::uint32_t>(10);
    (void) create_and_validate_height<std::uint64_t>(10);
}

TEST_CASE("basic Extent2D", "[extent]")
{
    apx::Width<int> w{ 640 };
    apx::Height<int> h{ 480 };

    apx::Extent2D extent(w, h);

    REQUIRE(extent.width == w);
    REQUIRE(extent.height == h);
}

TEST_CASE("Extent2D construction", "[extent]")
{
    apx::Extent2D extent {
        .width = apx::Width(640),
        .height = apx::Height(480),
    };

    REQUIRE(extent.width == 640);
    REQUIRE(extent.height == 480);
}

TEST_CASE("Extend2D as class member", "[extent]")
{
    struct Test
    {
        apx::Extent2D<std::uint32_t, std::uint32_t> extent;
    };
}