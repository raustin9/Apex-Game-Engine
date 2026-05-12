#pragma once
#include "apex/core/core.h"
#include "apex/event/event.h"
#include "system_events.h"
#include "system_key.h"

namespace apx::system
{
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

        /// @brief Determine if this event is of a given type
        template <typename T>
        constexpr bool
        is() const noexcept
        {
            return std::holds_alternative<T>(m_event);
        }

        /// @brief Get the T typed data of the event
        template <typename T>
        constexpr T
        get() const noexcept
        {
            return std::get<T>(m_event);
        }

      private:
        using Storage = std::variant<Events...>;

        Storage m_event;
    };

    /// @brief Event for system level events
    using SystemEvent = Event<SystemEventList>;
} // namespace apx::system

namespace apx
{
    /// @brief See `apx::system::SystemEvent`
    using SystemEvent = system::SystemEvent;
} // namespace apx