#pragma once
#include "system_traits_macos.h"
#include "system_type.h"

#include <concepts>
#include <string_view>

namespace apx
{
    namespace sys
    {
        template <typename Traits>
        concept ValidSystemTraits = requires {
            { Traits::system_name } -> std::same_as<const std::string_view &>;
            { Traits::system_type } -> std::same_as<const SystemType &>;
            { Traits::mouse_available } -> std::same_as<const bool &>;
            { Traits::keyboard_available } -> std::same_as<const bool &>;
        };

        static_assert(ValidSystemTraits<SystemTraits>);
    } // namespace system

    /// Convenience alias for system::SystemTraits
    using system_traits = sys::SystemTraits;
} // namespace apx::sys