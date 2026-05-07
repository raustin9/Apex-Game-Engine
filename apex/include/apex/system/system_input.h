#pragma once
#include "apex/core/core.h"
#include "apex/event/event.h"
#include "system_key.h"

#include <tuple>
#include <variant>

namespace apx::system
{
    struct WindowClosed
    {
    };

    struct WindowResized
    {
        Extent2D_f32 extent;
    };

    struct KeyDown
    {
        Key key;
    };

    using SystemEvent  = std::variant<KeyDown, WindowResized>;
    using SystemEvents = EventList<WindowClosed, WindowResized, KeyDown>;

    template <typename EventList>
    class InputHandler;

    template <typename... Events>
    class InputHandler<EventList<Events...>>
    {
      public:
        [[nodiscard]] explicit InputHandler() noexcept = default;

        template <typename T, typename... Args>
        void
        fire(Args &&...args)
        {
            get_broker<T>().fire(T{ std::forward<Args>(args)... });
        }

      private:
        template <typename T>
        [[nodiscard]] EventBroker<T> &
        get_broker() noexcept
        {
            return std::get<EventBroker<T>>(m_brokers);
        }

        std::tuple<EventBroker<Events>...> m_brokers{};
    };
} // namespace apx::system