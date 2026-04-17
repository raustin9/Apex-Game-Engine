#pragma once
#include <type_traits>

namespace apx::traits
{
    template <typename T>
    concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;
} // namespace apx::traits