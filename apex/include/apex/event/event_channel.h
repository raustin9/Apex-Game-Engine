#pragma once
#include "apex/containers/slot_map.h"
#include "apex/core/core.h"
#include "apex/event/event_traits.h"

namespace apx
{
    template <typename E, typename S>
    class EventChannel
    {
      public:
        using EventType        = E;
        using SubscriptionType = S;
        using Event            = EventType;
        using Subscription     = SubscriptionType;
        using Callback         = std::function<void(const Event &)>;
        using StorageType      = containers::SlotMap<EventType>;
        using HandleType       = typename StorageType::Handle;
        using Handle           = HandleType;

      public:
        [[nodiscard]] explicit EventChannel() noexcept : m_state{ std::make_shared<State>() } {}

        class Reader;
        class Writer;

        /// @brief Get a Writer from this channel
        [[nodiscard]] Writer writer() noexcept;

        /// @brief Get a Reader from this channel
        [[nodiscard]] Reader reader() noexcept;

      private:
        friend class Writer;
        friend class Reader;

        struct State
        {
            StorageType subscriptions;
        };

        struct Entry
        {
            Callback      callback;
            std::uint32_t priority;
        };

        void
        broadcast(const Event &event) noexcept
        {
            m_state->subscriptions.for_each_valid(
                [&](const Entry &entry) { entry.callback(event); });
        }

        [[nodiscard]] HandleType
        subscribe(Callback callback, std::uint32_t priority = 0) noexcept
        {
            return m_state->subscriptions.insert(
                Entry{ .callback = callback, .priority = priority });
        }

      private:
        std::shared_ptr<State> m_state;
    };

    template <typename E, typename S>
    class EventChannel<E, S>::Reader
    {
      public:
        [[nodiscard]] explicit Reader(std::shared_ptr<State> state) noexcept
            : m_state{ std::move(state) }
        {
        }

      private:
        std::shared_ptr<State> m_state;
    };

    template <typename E, typename S>
    class EventChannel<E, S>::Writer
    {
      public:
        [[nodiscard]] explicit Writer(std::shared_ptr<State> state) noexcept
            : m_state{ std::move(state) }
        {
        }

      private:
        std::shared_ptr<State> m_state;
    };

} // namespace apx::event