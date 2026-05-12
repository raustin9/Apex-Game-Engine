#pragma once
#include "system_detection.h"
#include "system_type.h"
#include <string_view>

#ifdef APEX_PLATFORM_APPLE
namespace apx::system
{
    struct SystemTraits
    {
        constexpr static std::string_view system_name        = "MacOS";
        constexpr static SystemType       system_type        = SystemType::MAC_OS;
        constexpr static bool             mouse_available    = true;
        constexpr static bool             keyboard_available = true;
    };
} // namespace apx
#endif // APEX_PLATFORM_APPLE
