#pragma once
#include "traits.h"

namespace apx
{
    /// Utility for opaque handles to resources
    template <traits::Integral N>
    struct Handle
    {
        /// Create a new handle
        static Handle
        make()
        {
            static N id{};
            return Handle(id++);
        }

        N
        get() const noexcept
        {
            return m_value;
        }

        constexpr bool
        operator==(const Handle &other) const noexcept
        {
            return get() == other.get();
        }

        constexpr bool
        operator>=(const Handle &other) const noexcept
        {
            return get() >= other.get();
        }

        constexpr bool
        operator<=(const Handle &other) const noexcept
        {
            return get() <= other.get();
        }

        constexpr bool
        operator>(const Handle &other) const noexcept
        {
            return get() > other.get();
        }

        constexpr bool
        operator<(const Handle &other) const noexcept
        {
            return get() < other.get();
        }

      private:
        explicit Handle(N n) noexcept : m_value{ n } {}

        N m_value;
    };

    using handle_u32 = Handle<std::uint32_t>;
    using handle_u64 = Handle<std::uint32_t>;
} // namespace apx

/// NOLINTBEGIN
namespace std
{
    template <apx::traits::Integral I>
    struct hash<apx::Handle<I>>
    {
        std::size_t
        operator()(const apx::Handle<I> &h) const noexcept
        {
            return h.get();
        }
    };
} // namespace std
/// NOLINTEND
