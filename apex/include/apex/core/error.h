#pragma once
#include <ostream>
#include <string_view>

namespace apx
{
    template <typename E, typename Code>
    class ErrorBase
    {
      public:
        [[nodiscard]] std::string_view
        message() const noexcept
        {
            return self().to_string();
        }

        constexpr friend std::ostream &
        operator<<(std::ostream &os, ErrorBase const &err) noexcept
        {
            return os << err.message();
        }

        [[nodiscard]] Code
        code() const noexcept
        {
            return self().code();
        }

        // CRTP utils
      protected:
        E &
        self() noexcept
        {
            return static_cast<E &>(*this);
        }
        const E &
        self() const noexcept
        {
            return static_cast<E &>(*this);
        }
    };
} // namespace apx