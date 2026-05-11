#pragma once

namespace apx
{
    /// @brief A utility for containing a list of types
    template <typename... Ts>
    struct TypeList
    {
        constexpr static std::size_t num_types = sizeof...(Ts);
    };
} // namespace apx