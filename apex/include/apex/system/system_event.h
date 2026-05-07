#pragma once
#include "apex/core/core.h"
#include "apex/event/event.h"
#include "system_key.h"

namespace apx::system
{
    /// @brief Triggers when a window is opened
    struct WindowOpen
    {
    };

    // /// @brief Triggers when a window is closed
    // struct WindowClosed
    // {
    // };
    //
    // /// @brief Triggers when a key is pressed
    // struct KeyDown
    // {
    //     /// @brief The key that is pressed
    //     Key key;
    // };

    /// @brief Triggers when a key that is pressed is released
    struct KeyUp
    {
        /// @brief The key that was released
        Key key;
    };

    // /// @brief Triggers when the window is resized.
    // struct WindowResized
    // {
    //     /// @brief The extent of the renderable content of the window after the resize
    //     Extent2D_f32 extent;
    // };

    using SystemEventList = EventList<WindowOpen, KeyUp>;

    template <typename EventKinds>
    class Event;

    template <typename... Events>
    class Event<EventList<Events...>>
    {
      public:
        template <typename T>
        constexpr explicit Event(const T &t) noexcept : m_event{ std::move(t) }
        {
        }

        template <typename T>
        constexpr explicit Event(T &&t) noexcept : m_event{ std::move(t) }
        {
        }

        template <typename T>
        constexpr bool
        is() const noexcept
        {
            return std::holds_alternative<T>(m_event);
        }

        template <typename T>
        constexpr T
        get() noexcept
        {
            return std::get<T>(m_event);
        }

      private:
        using Storage = std::variant<Events...>;

        Storage m_event;
    };
} // namespace apx::system

namespace apx
{
    using Event = system::Event<system::SystemEventList>;
} // namespace apx