#pragma once
#include "apex/event/event_broker.h"
#include "apex/event/event_list.h"
#include "apex/sync/sync.h"
#include "system_event.h"

namespace apx::sys
{
    template <typename EventKinds>
    class SystemEventHandler;

    template <typename... Ts>
    class SystemEventHandler<EventList<Ts...>>
    {
      public:
        /// @brief A unified version of all the events specified for this handler
        using UnifiedEvent = Event<EventList<Ts...>>;

        /// @brief A listener callback for type T
        template <typename T>
        using Listener = typename EventBroker<T>::Listener;

        /// @brief A handle to a listener of type T
        template <typename T>
        using Handle = typename EventBroker<T>::Handle;

      public:
        [[nodiscard]] explicit SystemEventHandler() noexcept
        {
            // register a callback to insert each event type into the queue
            // NOTE: ignore the return type here since they get cleaned up anyway
            ((void)get_broker<Ts>().add_listener(
                 [this](Ts data) { m_event_queue.push(UnifiedEvent(data)); }),
             ...);
        }

        /// @brief Dispatch an event
        /// @tparam T the type of event to dispatch
        template <typename T>
        void
        dispatch(T data) noexcept
        {
            return get_broker<T>().fire(std::move(data));
        }

        /// @brief Add a listener for the event type
        /// @tparam T the type of the event to add the listener for
        template <typename T>
        [[nodiscard]] typename EventBroker<T>::Handle
        on(typename EventBroker<T>::Listener listener) noexcept
        {
            return get_broker<T>().add_listener(std::move(listener));
        }

        /// @brief Attempt to remove a listener
        /// @returns `true` if handle is found and removed. `false` otherwise
        template <typename T>
        [[nodiscard]] bool
        remove_listener(const typename EventBroker<T>::Handle handle) noexcept
        {
            return get_broker<T>().remove_listener(handle);
        }

        /// @brief Get and pop the next event from the queue
        [[nodiscard]] std::optional<UnifiedEvent>
        next_event() noexcept
        {
            return m_event_queue.try_pop();
        }

      private:
        friend class Display;
        friend class DisplayServer;

        /// @brief Get a broker for the corresponding data type
        template <typename T>
        [[nodiscard]] EventBroker<T> &
        get_broker() noexcept
        {
            return std::get<EventBroker<T>>(m_event_brokers);
        }

        /// @brief Close the handler from
        void
        end_polling() noexcept
        {
            m_event_queue.close();
        }

        std::tuple<EventBroker<Ts>...>  m_event_brokers{};
        sync::AtomicQueue<UnifiedEvent> m_event_queue{};
    };
} // namespace apx::sys