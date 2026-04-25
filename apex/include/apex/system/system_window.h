#pragma once
#include "apex/core/core.h"
#include "system_error.h"

namespace apx::system
{
    struct WindowOptions
    {
        std::string_view title = "Apex Window";
        Extent2D_u32     extent{ Width_u32{ 800 }, Height_u32{ 600 } };
    };

    class Window
    {
        // info
      public:
        struct NativeData
        {
#if defined(APEX_PLATFORM_APPLE)
            OBJC_TYPE(NSWindow) window;
            OBJC_TYPE(CADisplayLink) display_link;
            OBJC_TYPE(NSView) content_view;
#endif // Platforms
        };

      public:
        [[nodiscard]] static expected<Window, SystemError> create(WindowOptions options) noexcept;

        // Observers
      public:
        [[nodiscard]] Extent2D_u32 extent() const noexcept;
        [[nodiscard]] Width_u32    width() const noexcept;
        [[nodiscard]] Height_u32   height() const noexcept;

        // Mutators
      public:
        void open() noexcept;
        void close() noexcept;

      private:
        friend class System;
        NativeData m_native_data{};

        // Apple private methods
      private:
#ifdef APEX_PLATFORM_APPLE
        OBJC_TYPE(NSView)
        get_view() const noexcept { return m_native_data.content_view; }
#endif
    };
} // namespace apx::system