#pragma once
#include "apex/core/core.h"
#include "system_error.h"

#ifdef APEX_PLATFORM_APPLE
FORWARD_OBJC_TYPE(WindowDelegate);
#endif // APEX_PLATFORM_APPLE

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
            OBJC_TYPE(WindowDelegate) delegate;
#endif // Platforms
        };

      public:
        [[nodiscard]] static expected<Window, SystemError> create(WindowOptions options) noexcept;

        Window(const Window &) noexcept;
        Window(Window &&) noexcept;
        Window &operator=(const Window &) noexcept;
        Window &operator=(Window &&) noexcept;
        ~Window() noexcept;

        // Observers
      public:
        [[nodiscard]] Extent2D_u32 extent() const noexcept;
        [[nodiscard]] Width_u32    width() const noexcept;
        [[nodiscard]] Height_u32   height() const noexcept;

        [[nodiscard]] bool
        is_open() const noexcept
        {
            return m_is_open;
        }

        // Mutators
      public:
        void open() noexcept;
        void close() noexcept;

      private:
        friend class System;

        explicit Window() noexcept = default;

        NativeData m_native_data{};
        bool       m_is_open;

        // Apple private methods
      private:
#ifdef APEX_PLATFORM_APPLE
        [[nodiscard]] OBJC_TYPE(NSView) get_view() const noexcept
        {
            return m_native_data.content_view;
        }

        void setup_delegate() noexcept;
        void update_delegate() noexcept;
#endif
    };
} // namespace apx::system