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

    template <typename T>
    concept POD = std::is_pod_v<T>;
} // namespace apx::traits