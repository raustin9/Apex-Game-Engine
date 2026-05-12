#pragma once
#include <format>
#include <iostream>
#include <source_location>

// #if defined(APEX) || defined(_DEBUG) || defined(DEBUG)
// #define APEX_DEBUG
// #endif

namespace apx
{
    consteval bool
    is_debug() noexcept
    {
#ifdef APEX_DEBUG
        return true;
#else
        return false;
#endif // APEX_DEBUG
    }

    template <typename T>
    void
    debug_assert(const T &expr, std::string_view msg = "",
                 std::source_location source_location = std::source_location::current())
    {
        if constexpr ( is_debug() )
            {
                if ( !static_cast<bool>(expr) )
                    {
                        std::cerr << std::format("Assertion failed: [{}]\n\t-> {}\n\t\t-> {}:{}",
                                                 msg, source_location.file_name(),
                                                 source_location.line(),
                                                 source_location.function_name());
                        std::abort();
                    }
            }
        else
            {
                std::cout << "NOT DEBUG\n";
            }
    }
} // namespace apx