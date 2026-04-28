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
        // Info
      public:
        static constexpr Width_u32  DEFAULT_WIDTH{ 800 };
        static constexpr Height_u32 DEFAULT_HEIGHT{ 600 };

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
        /// @brief Attempt to create a window with the given options
        /// @returns `apx::unexpected<apx::system::SystemError>` on failure and
        /// `apx::system::Window` on success
        [[nodiscard]] static expected<Window, SystemError> create(WindowOptions options) noexcept;

        Window(const Window &) noexcept;
        Window(Window &&) noexcept;
        Window &operator=(const Window &) noexcept;
        Window &operator=(Window &&) noexcept;
        ~Window() noexcept;

        // Observers
      public:
        /// @brief Get the current extent of the window's inner contents
        [[nodiscard]] Extent2D_u32
        extent() const noexcept
        {
            return m_extent;
        }

        /// @brief Get the current width of the window's inner contents
        [[nodiscard]] Width_u32
        width() const noexcept
        {
            return extent().width;
        }

        /// @brief Get the current height of the window's inner contents
        [[nodiscard]] Height_u32
        height() const noexcept
        {
            return extent().height;
        }

        /// @brief Get the current aspect ratio of the window's inner contents
        template <traits::FloatingPoint RT = float>
        [[nodiscard]] Dimension<RT>
        aspect_ratio() const noexcept
        {
            return extent().aspect_ratio<RT>();
        }

        /// @brief Returns the current title of the window
        [[nodiscard]] std::string_view
        title() const noexcept
        {
            return m_title;
        }

        /// @brief Check if the window is currently open
        [[nodiscard]] bool
        is_open() const noexcept
        {
            return m_is_open;
        }

        // Mutators
      public:
        /// @brief Open the window
        void open() noexcept;

        /// @brief Close the window
        void close() noexcept;

        /// @brief Resize the window to a new extent
        /// @note This is resizes the inner content extent of the window
        void resize(Extent2D_u32 new_extent) noexcept;

        /// @brief Resize the window to a new width and height
        /// @note This is resizes the inner content extent of the window
        void
        resize(const Width_u32 new_width, const Height_u32 new_height) noexcept
        {
            resize(Extent2D_u32{ new_width, new_height });
        }

        /// @brief Resize the window to a new width
        /// @note This is resizes the inner content width of the window
        void
        resize_width(const Width_u32 new_width) noexcept
        {
            resize(Extent2D_u32(new_width, height()));
        }

        /// @brief Resize the window to a new height
        /// @note This is resizes the inner content height of the window
        void
        resize_height(const Height_u32 new_height) noexcept
        {
            resize(Extent2D_u32(width(), new_height));
        }

      private:
        friend class System;

        explicit Window() noexcept = default;

        // Private members
      private:
        NativeData   m_native_data{};
        bool         m_is_open;
        std::string  m_title;
        Extent2D_u32 m_extent{ .width = DEFAULT_WIDTH, .height = DEFAULT_HEIGHT };

        // Agnostic Private methods
      private:
        /// @brief Platform-agnostic copy behavior
        void
        copy(const Window &from) noexcept
        {
            m_native_data = from.m_native_data;
            m_is_open     = from.m_is_open;
            m_title       = from.m_title;
            m_extent      = from.m_extent;
        }

        /// @brief Platform-agnostic move behavior
        /// @note For now, this just uses the `copy()` method internally
        void
        move(Window &&from) noexcept
        {
            copy(from);
        }

        // Apple private methods
      private:
#ifdef APEX_PLATFORM_APPLE
        /// @brief Get the NSView corresponding to the window's content view
        [[nodiscard]] OBJC_TYPE(NSView) get_view() const noexcept
        {
            return m_native_data.content_view;
        }

        /// @brief Set up the WindowDelegate used internally
        void setup_delegate() noexcept;

        /// @brief Update the internal WindowDelegate
        /// @note The WindowDelegate holds a pointer to this object. This method updates that
        /// pointer in case of a move or copy
        void update_delegate() noexcept;
#endif

        // Internal methods
      public:
        /// @brief Callback function for use by the WindowDelegate when the window is resized
        void __resize_callback(Extent2D_u32) noexcept;
    };
} // namespace apx::system