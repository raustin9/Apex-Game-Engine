#pragma once
#include <queue>

namespace apx::sync::mpmc
{
    template <typename T>
    class Channel
    {
      public:
        class Reader;
        class Writer;

        [[nodiscard]] static std::pair<Reader, Writer>
        create()
        {
            std::shared_ptr<Channel> channel(new Channel());

            return std::make_pair(Channel<T>::Reader{ channel }, Channel<T>::Writer{ channel });
        }

        Channel(const Channel &)            = delete;
        Channel(Channel &&)                 = delete;
        Channel &operator=(const Channel &) = delete;
        Channel &operator=(Channel &&)      = delete;

      private:
        [[nodiscard]] explicit Channel() noexcept = default;

        friend class Reader;
        friend class Writer;

        void
        push(T value) noexcept
        {
            std::unique_lock lock{ m_mutex };
            m_queue.push(std::move(value));
            m_condition.notify_one();
        }

        T
        pop() noexcept
        {
            std::unique_lock lock{ m_mutex };

            m_condition.wait(lock, [this] { return !m_queue.empty(); });
            T value = std::move(m_queue.front());
            m_queue.pop();

            return std::move(value);
        }

      private:
        std::queue<T>           m_queue;
        std::mutex              m_mutex;
        std::condition_variable m_condition;
    };

    template <typename T>
    class Channel<T>::Reader
    {
      public:
        [[nodiscard]] explicit Reader(std::shared_ptr<Channel> channel) noexcept
            : m_channel{ std::move(channel) }
        {
        }

        // Reader is non-copyable
        Reader(const Reader &)            = default;
        Reader &operator=(const Reader &) = default;

        // Reader is movable
        Reader(Reader &&)            = default;
        Reader &operator=(Reader &&) = default;

        // API
      public:
        [[nodiscard]] T
        read() noexcept
        {
            return m_channel->pop();
        }

      private:
        std::shared_ptr<Channel> m_channel;
    };

    template <typename T>
    class Channel<T>::Writer
    {
      public:
        [[nodiscard]] explicit Writer(std::shared_ptr<Channel> channel) noexcept
            : m_channel{ std::move(channel) }
        {
        }

        // Copyable + Moveable
        Writer(const Writer &)            = default;
        Writer &operator=(const Writer &) = default;
        Writer(Writer &&)                 = default;
        Writer &operator=(Writer &&)      = default;

        void
        write(T value) noexcept
            requires(std::is_copy_assignable_v<T>)
        {
            m_channel->push(value);
        }

        void
        write(T &&value) noexcept
            requires(std::is_move_assignable_v<T>)
        {
            m_channel->push(std::move(value));
        }

      private:
        std::shared_ptr<Channel> m_channel;
    };
} // namespace apx::sync::mpmc
