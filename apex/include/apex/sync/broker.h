#pragma once
#include "apex/containers/slot_map.h"
#include "apex/core/core.h"

#include <iostream>
#include <memory>

namespace apx::sync
{
    template <typename Data>
    class Broker
    {
      public:
        using Subscription       = std::function<void(Data)>;
        using Storage            = containers::SlotMap<Subscription>;
        using SubscriptionHandle = typename Storage::Handle;

      private:
        struct State
        {
            Storage subscriptions;

            /// @brief Notify all subscribers with this data.
            /// @note This is intended to be called by Publisher alone
            void
            notify(Data data) noexcept
            {
                subscriptions.for_each_valid(
                    [data = std::move(data)](Subscription callback) { callback(data); });
            }
        };

      public:
        class Publisher
        {
          public:
            [[nodiscard]] explicit Publisher(std::shared_ptr<State> state) noexcept
                : m_state{ state }
            {
            }

            void
            notify(Data data)
            {
                m_state.lock()->notify(std::move(data));
            }

          private:
            std::weak_ptr<State> m_state;
        };

        // Special Members
      public:
        /// @brief Private constructor. Use `create()` instead.
        [[nodiscard]] explicit Broker() noexcept : m_state{ std::make_shared<State>() } {}

        // Not copyable
        Broker(const Broker &)            = delete;
        Broker &operator=(const Broker &) = delete;

        // Movable
        Broker(Broker &&)            = default;
        Broker &operator=(Broker &&) = default;

        // Mutators
      public:
        [[nodiscard]] SubscriptionHandle
        // subscribe(Subscription &&subscriber) noexcept
        subscribe(Subscription subscriber) noexcept
        {
            return m_state->subscriptions.insert(subscriber);
        }

        bool
        unsubscribe(SubscriptionHandle handle) noexcept
        {
            return m_state->subscriptions.remove(handle);
        }

        [[nodiscard]] Publisher
        get_publisher() const noexcept
        {
            return Publisher{ m_state };
        }

        // Observers
      public:
        [[nodiscard]] std::size_t
        num_subscriptions() const noexcept
        {
            return m_state->subscriptions.num_elements();
        }

      private:
        std::shared_ptr<State> m_state = std::make_shared<State>();
    };
} // namespace apx::sync::mpmc
