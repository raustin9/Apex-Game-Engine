#pragma once
#include <type_traits>

namespace apx::traits
{
    template <typename T>
    concept Integral = std::is_integral_v<T>;

    template <typename T>
    concept FloatingPoint = std::is_floating_point_v<T>;

    template <typename T>
    concept Numeric = Integral<T> || FloatingPoint<T>;
} // namespace apx::traits