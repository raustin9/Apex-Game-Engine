#pragma once
#include "apex/core/core.h"
#include "native/native_types.h"
#include "system_error.h"
#include "system_window.h"

#include <memory>

#ifdef APEX_PLATFORM_APPLE
FORWARD_OBJC_TYPE(AppDelegate);
#endif // APEX_PLATFORM_APPLE

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
        friend class AppDelegate;
        OBJC_TYPE(AppDelegate) m_delegate;
        bool m_is_running = false;
#endif

        // MacOS private methods
#if defined(APEX_PLATFORM_APPLE)
        void setup_delegate() noexcept;
        void update_delegate() noexcept;
#endif
    };
} // namespace apex::system