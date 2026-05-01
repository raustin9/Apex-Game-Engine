#pragma once
#include <vector>

namespace apx::containers
{
    /// @brief A SlotMap<T> is meant to store data of type T in a linear memory model while
    /// providing automatic cleanup for removed items
    template <typename T>
    class SlotMap
    {
        // Info
      public:
        using ElementType = std::remove_cv_t<T>;
        using IndexType   = std::size_t;

        struct Handle
        {
            IndexType     index;
            std::uint32_t generation;
        };

        // Observers
      public:
        [[nodiscard]] bool
        has_stale_frees() const noexcept
        {
            return !m_free_list.empty();
        }

        [[nodiscard]] std::size_t
        raw_elements_size() const noexcept
        {
            return m_elements.size();
        }

        [[nodiscard]] std::size_t
        free_list_size() const noexcept
        {
            return m_free_list.size();
        }

        [[nodiscard]] std::size_t
        num_elements() const noexcept
        {
            return raw_elements_size() - free_list_size();
        }

        // Public methods
      public:
        /// @brief Apply a callback function for each valid slot
        template <typename Fn>
        void
        for_each_valid(Fn &&fn) noexcept(std::is_nothrow_invocable_v<Fn>)
        {
            for ( auto &element : m_elements )
                {
                    if ( element.occupied )
                        fn(element.element);
                }
        }

        // Modifiers
      public:
        [[nodiscard]] Handle
        insert(ElementType value) noexcept
        {
            if ( auto free_index = get_next_free_index(); free_index.has_value() )
                {
                    m_elements[*free_index] = { .element = std::move(value),
                                                m_elements[*free_index].generation,
                                                .occupied = true };

                    return Handle{ .index      = *free_index,
                                   .generation = m_elements[*free_index].generation };
                }

            m_elements.push_back(
                { .element = std::move(value), .generation = 0, .occupied = true });

            return Handle{ .index      = static_cast<std::uint32_t>(m_elements.size() - 1),
                           .generation = 0 };
        }

        /// @brief Remove a slot corresponding to the input handle from the map
        bool
        remove(Handle handle) noexcept
        {
            if ( !valid_handle(handle) )
                return false;

            m_elements[handle.index].occupied = false;
            m_elements[handle.index].generation += 1;
            m_free_list.push_back(handle.index);
            return true;
        }

        /// @brief Determine if a handle is valid
        [[nodiscard]] bool
        valid_handle(Handle h) const noexcept
        {
            return m_elements.size() > h.index && m_elements[h.index].generation == h.generation
                   && m_elements[h.index].occupied;
        }

      private:
        [[nodiscard]] std::optional<std::uint32_t>
        get_next_free_index() noexcept
        {
            if ( has_stale_frees() )
                {
                    std::uint32_t index = m_free_list.back();
                    m_free_list.pop_back();
                    return index;
                }

            return std::nullopt;
        }

      private:
        struct Slot
        {
            ElementType   element;
            std::uint32_t generation;
            bool          occupied = false;
        };

        std::vector<Slot>      m_elements;
        std::vector<IndexType> m_free_list;
    };
} // namespace apx::containers