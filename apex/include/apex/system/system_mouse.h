#pragma once
#include <cstdint>

namespace apx::system
{
    /// @brief Enumeration of mouse buttons
    enum class MouseButton : std::uint32_t
    {
        LEFT = 0,
        MIDDLE,
        RIGHT,

        COUNT
    };
} // namespace apx::system