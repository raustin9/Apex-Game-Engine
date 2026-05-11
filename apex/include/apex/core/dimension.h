#pragma once
#include "traits.h"

namespace apx
{
    // NOLINTBEGIN(google-explicit-constructor)
    template <traits::Numeric N>
    class Dimension
    {
      public:
        using value_type      = N;
        using difference_type = value_type;
        using size_type       = std::size_t;

      public:
        constexpr explicit Dimension(N n) noexcept : m_value{ n } {}

        // Basic comparison
      public:
        friend constexpr bool
        operator==(const Dimension &lhs, const Dimension &rhs) noexcept
        {
            return lhs.get() == rhs.get();
        }

        friend constexpr bool
        operator>=(const Dimension &lhs, const Dimension &rhs) noexcept
        {
            return lhs.get() >= rhs.get();
        }

        friend constexpr bool
        operator<=(const Dimension &lhs, const Dimension &rhs) noexcept
        {
            return lhs.get() <= rhs.get();
        }

        friend constexpr bool
        operator>(const Dimension &lhs, const Dimension &rhs) noexcept
        {
            return lhs.get() > rhs.get();
        }

        friend constexpr bool
        operator<(const Dimension &lhs, const Dimension &rhs) noexcept
        {
            return lhs.get() < rhs.get();
        }

        // Conversion comparisons from other Dimension<U> types
      public:
        template <typename U>
            requires(std::is_convertible_v<U, N>)
        friend constexpr bool
        operator==(const Dimension<U> &lhs, const Dimension &rhs) noexcept
        {
            return lhs.get() == rhs.get();
        }

        template <typename U>
            requires(std::is_convertible_v<U, N>)
        friend constexpr bool
        operator>=(const Dimension<U> &lhs, const Dimension &rhs) noexcept
        {
            return lhs.get() >= rhs.get();
        }

        template <typename U>
            requires(std::is_convertible_v<U, N>)
        friend constexpr bool
        operator<=(const Dimension<U> &lhs, const Dimension &rhs) noexcept
        {
            return lhs.get() <= rhs.get();
        }

        template <typename U>
            requires(std::is_convertible_v<U, N>)
        friend constexpr bool
        operator>(const Dimension<U> &lhs, const Dimension &rhs) noexcept
        {
            return lhs.get() > rhs.get();
        }

        template <typename U>
            requires(std::is_convertible_v<U, N>)
        friend constexpr bool
        operator<(const Dimension<U> &lhs, const Dimension &rhs) noexcept
        {
            return lhs.get() < rhs.get();
        }

        // modifiers
      public:
        template <traits::Numeric U>
        friend constexpr Dimension
        operator+(const Dimension<U> &lhs, const Dimension &rhs) noexcept
        {
            return Dimension(lhs.get() + rhs.get());
        }

        constexpr Dimension &
        operator+=(const Dimension &other) noexcept
        {
            if ( this != &other )
                {
                    m_value += other.get();
                }
            return *this;
        }

        constexpr Dimension &
        operator+=(value_type n) noexcept
        {
            m_value += n;
            return *this;
        }

        template <traits::Numeric U>
        friend constexpr Dimension
        operator-(const Dimension<U> &lhs, const Dimension &rhs) noexcept
        {
            return Dimension(lhs.get() - rhs.get());
        }

        constexpr Dimension &
        operator-=(const Dimension &other) noexcept
        {
            if ( this != &other )
                {
                    m_value -= other.get();
                }
            return *this;
        }

        constexpr Dimension &
        operator-=(value_type n) noexcept
        {
            m_value -= n;
            return *this;
        }

        template <traits::Numeric U>
        friend constexpr Dimension
        operator*(const Dimension<U> &lhs, const Dimension &rhs) noexcept
        {
            return Dimension(lhs.get() * rhs.get());
        }

        constexpr Dimension &
        operator*=(const Dimension &other) noexcept
        {
            if ( this != &other )
                {
                    m_value *= other.get();
                }
            return *this;
        }

        constexpr Dimension &
        operator*=(value_type n) noexcept
        {
            m_value *= n;
            return *this;
        }

        template <traits::Numeric U>
        friend constexpr Dimension
        operator/(const Dimension<U> &lhs, const Dimension &rhs) noexcept
        {
            return Dimension(lhs.get() / rhs.get());
        }

        constexpr Dimension &
        operator/=(const Dimension &other) noexcept
        {
            if ( this != &other )
                {
                    m_value /= other.get();
                }
            return *this;
        }

        constexpr Dimension &
        operator/=(value_type n) noexcept
        {
            m_value /= n;
            return *this;
        }

        // Observers
      public:
        N
        get() const noexcept
        {
            return m_value;
        }

        explicit(false) constexpr
        operator N() const noexcept
        {
            return get();
        }

        template <traits::Numeric U>
        constexpr Dimension<U>
        as() const noexcept
        {
            return Dimension<U>{ static_cast<U>(get()) };
        }

      private:
        N m_value{};
    };

    using Dimension_u32 = Dimension<std::uint32_t>;
    using Dimension_i32 = Dimension<std::int32_t>;
    using Dimension_f32 = Dimension<float>;
    // NOLINTEND(google-explicit-constructor)
} // namespace apx