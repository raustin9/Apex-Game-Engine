#pragma once
#include "apex/core/core.h"
#include "native/native_types.h"
#include "system_error.h"
#include "system_window.h"

#include <memory>

namespace apx::system
{
    class System
    {
      public:
        [[nodiscard]] static expected<System, SystemError> create(const WindowOptions options = {});
        void                                               shutdown() noexcept;
        void                                               update() noexcept;
        bool                                               is_running() const noexcept;

      private:
        [[nodiscard]] explicit System() noexcept = default;

        // Private members
      private:
        Window m_window;

#if defined(APEX_PLATFORM_APPLE)
        bool m_is_running = false;
#endif
    };
} // namespace apex::system