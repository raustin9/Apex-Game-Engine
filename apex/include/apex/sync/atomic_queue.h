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

        /// @brief Close the queue
        void
        close() noexcept
        {
            std::unique_lock<std::mutex> lock{ m_mutex };
            m_closed = true;
            m_condition.notify_all();
        }

        /// @brief Determine if the queue is empty
        [[nodiscard]] bool
        is_empty() const noexcept
        {
            return m_queue.empty();
        }

        /// @brief Push a value onto the queue
        void
        push(T value) noexcept
        {
            std::unique_lock lock{ m_mutex };
            m_queue.push(std::move(value));
            m_condition.notify_one();
        }

        /// @brief Pop a value from the queue
        /// @note This will block the calling thread until a value is pushed into the queue
        [[nodiscard]] T
        blocked_pop() noexcept
        {
            std::unique_lock lock{ m_mutex };

            m_condition.wait(lock, [&] { return !is_empty() || m_closed; });
            T value = std::move(m_queue.front());
            m_queue.pop();

            return std::move(value);
        }

        /// @brief Pop a value from the queue
        /// @note This is non-blocking, but returns std::nullopt if no value is in the queue
        [[nodiscard]] std::optional<T>
        try_pop() noexcept
        {
            std::unique_lock lock{ m_mutex };

            if ( is_empty() )
                return std::nullopt;

            T value = std::move(m_queue.front());
            m_queue.pop();

            return std::move(value);
        }

      private:
        std::queue<T>           m_queue;
        std::mutex              m_mutex;
        std::condition_variable m_condition;
        bool                    m_closed{ false };
    };
} // namespace apx::sync