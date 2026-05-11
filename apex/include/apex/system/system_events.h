#pragma once
#include "apex/core/core.h"
#include "apex/event/event.h"
#include "system_input.h"

namespace apx::system
{
    /// @brief Triggers when a display is opened
    struct DisplayOpen
    {
    };

    /// @brief Triggers when a display is closed
    struct DisplayClose
    {
    };

    /// @brief Triggers when a key is first pressed
    struct KeyDown
    {
        Key key;
    };

    /// @brief Triggers when a key is lifted
    struct KeyUp
    {
        Key key;
    };

    /// @brief Triggers when
    struct DisplayResized
    {
        Extent2D_u32 extent;
    };

    /// @brief Triggers when the mouse is moved
    struct MouseMoved
    {
        Vec2u position;
    };

    using SystemEventList
        = EventList<DisplayOpen, DisplayClose, KeyDown, KeyUp, DisplayResized, MouseMoved>;
} // namespace apx::system