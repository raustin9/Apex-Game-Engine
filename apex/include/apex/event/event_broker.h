#pragma once
#include "apex/sync/sync.h"
#include "event_traits.h"

#include <iostream>

namespace apx
{
    template <typename T>
    class EventBroker
    {
      public:
        using EventType = T;
        using Handle    = typename sync::Broker<T>::SubscriptionHandle;
        using Listener  = typename sync::Broker<T>::Subscription;
        using Publisher = typename sync::Broker<T>::Publisher;

      public:
        [[nodiscard]] explicit EventBroker() noexcept = default;

        [[nodiscard]] Handle
        add_listener(Listener listener) noexcept
        // add_listener(Listener &&listener) noexcept
        {
            return m_broker.subscribe(listener);
        }

        bool
        remove_listener(Handle handle) noexcept
        {
            return m_broker.unsubscribe(handle);
        }

        void
        fire(T event) noexcept
        {
            m_broker.get_publisher().notify(event);
        }

      private:
        sync::Broker<T> m_broker{};
    };
} // namespace apx