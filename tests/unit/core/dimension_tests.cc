#include <apex/apex.h>
#include <cassert>
#include <catch2/catch_test_macros.hpp>

template <typename T>
void
validate(T value) noexcept
{
    assert(value != 0 && "Cannot validate properly with value of 0");
    apx::Dimension<T> d{ value };
    REQUIRE(d.get() == value);
    REQUIRE(d == value);
    REQUIRE(d > value - 1);
    REQUIRE(d < value + 1);
    REQUIRE(d <= value + 1);
    REQUIRE(d >= value - 1);
}

TEST_CASE("dimension construction from standard types", "[dimension]")
{
    validate<int>(1);
    validate<float>(3991.f);
    validate<double>(43284.f);
    validate<long>(1l);
    validate<long long>(1ll);

    validate<unsigned int>(1);
    validate<unsigned long>(1l);
    validate<unsigned long long>(1ll);

    validate<std::int8_t>(10);
    validate<std::int16_t>(10);
    validate<std::int32_t>(10);
    validate<std::int64_t>(10);
    validate<std::uint8_t>(10);
    validate<std::uint16_t>(10);
    validate<std::uint32_t>(10);
    validate<std::uint64_t>(10);
}

template <apx::traits::Numeric U, apx::traits::Numeric T>
void
validate(U u, T t) noexcept
{
    apx::Dimension<U> d_u{ u };
    apx::Dimension<T> d_t{ t };

    REQUIRE(d_u.get() == u);
    REQUIRE(d_u == u);
    REQUIRE(d_t.get() == t);
    REQUIRE(d_t == t);

    REQUIRE((d_u == d_t) == (u == t));
    REQUIRE((d_u >= d_t) == (u >= t));
    REQUIRE((d_u <= d_t) == (u <= t));
    REQUIRE((d_u < d_t) == (u < t));
    REQUIRE((d_u > d_t) == (u > t));

    REQUIRE((d_u == t) == (u == t));
    REQUIRE((d_u >= t) == (u >= t));
    REQUIRE((d_u <= t) == (u <= t));
    REQUIRE((d_u < t) == (u < t));
    REQUIRE((d_u > t) == (u > t));

    REQUIRE((d_t == u) == (t == u));
    REQUIRE((d_t >= u) == (t >= u));
    REQUIRE((d_t <= u) == (t <= u));
    REQUIRE((d_t < u) == (t < u));
    REQUIRE((d_t > u) == (t > u));
}

TEST_CASE("dimension comparison from other dimension types", "[dimension]")
{
    validate<int, int>(5, 10);
    validate<int, long>(5, 10);
    validate<int, float>(5, 10);
    validate<int, double>(5, 10);
    validate<int, unsigned int>(5, 10);
    validate<int, unsigned long>(5, 10);
    validate<int, long long>(5, 10);
    validate<int, unsigned long long>(5, 10);

    validate<std::int32_t, int>(5, 10);
    validate<std::int32_t, long>(5, 10);
    validate<std::int32_t, float>(5, 10);
    validate<std::int32_t, double>(5, 10);
    validate<std::int32_t, unsigned int>(5, 10);
    validate<std::int32_t, unsigned long>(5, 10);
    validate<std::int32_t, long long>(5, 10);
    validate<std::int32_t, unsigned long long>(5, 10);
}

template <apx::traits::Numeric U, apx::traits::Numeric T>
void
validate_operations(U u, T t) noexcept
{
    apx::Dimension<U> d_u{ u };
    apx::Dimension<T> d_t{ t };

    REQUIRE((d_u + d_t) == (u + t));
    REQUIRE((d_t + d_u) == (t + u));

    d_u += d_t;
    REQUIRE(d_u == (t + u));
    d_u -= d_t;
    REQUIRE(d_u == u);

    d_t += 1;
    REQUIRE(d_t == (t + 1));
    d_t -= 1;
    REQUIRE(d_t == t);

    d_u *= d_t;
    REQUIRE(d_u == (t * u));
    d_u /= d_t;
    REQUIRE(d_u == u);

    d_t *= 1;
    REQUIRE(d_t == (t * 1));
    d_t /= 1;
    REQUIRE(d_t == t);
}
TEST_CASE("dimension operations", "[dimension]")
{
    validate_operations<int, int>(5, 10);
    validate_operations<int, float>(5, 10.f);
    validate_operations<float, float>(5, 10.f);
    validate_operations<float, double>(5, 10.f);
    validate_operations<float, int>(5, 10.f);
}