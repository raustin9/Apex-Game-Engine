#pragma once
#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

namespace apx::sync
{
    template <typename T>
    class AtomicQueue
    {
      public:
        [[nodiscard]] AtomicQueue() noexcept = default;
        ~AtomicQueue() noexcept              = default;

        /// @brief Push a value onto the queue
        void
        push(T value) noexcept
        {
            std::unique_lock lock{ m_mutex };
            m_queue.push(std::move(value));
            m_condition.notify_one();
        }

        /// @brief Pop a value from the queue
        [[nodiscard]] T
        blocked_pop() noexcept
        {
            std::unique_lock lock{ m_mutex };

            m_condition.wait(lock, [&] { return !m_queue.empty(); });
            T value = std::move(m_queue.front());
            m_queue.pop();

            return std::move(value);
        }

        /// @brief Pop a value from the queue
        [[nodiscard]] std::optional<T>
        try_pop() noexcept
        {
            std::unique_lock lock{ m_mutex };

            if ( m_queue.empty() )
                return std::nullopt;

            T value = std::move(m_queue.front());
            m_queue.pop();

            return std::move(value);
        }

      private:
        std::queue<T>           m_queue;
        std::mutex              m_mutex;
        std::condition_variable m_condition;
    };
} // namespace apx::sync