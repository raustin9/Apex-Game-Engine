#pragma once
#include "apex/core/core.h"
#include "apex/event/event.h"
#include "system_error.h"
#include "system_event.h"
#include "system_event_handler.h"

#include <optional>
#include <ranges>
#include <string>

namespace apx::system
{
    /// @brief An interactive display
    class Display
    {
        using EventHandler = SystemEventHandler<SystemEventList>;

      public:
        static constexpr uint32_t         DefaultWidth  = 800;
        static constexpr uint32_t         DefaultHeight = 600;
        static constexpr std::string_view DefaultName   = "Apex Display";
        using Handle                                    = Handle_u32;

        /// @brief Options for creating a
        struct CreateOptions
        {
            /// @brief Title of the display
            std::string_view     title{ DefaultName };

            /// @brief The extent to create the display at.
            Extent2D_u32         extent{ .width  = Width_u32{ DefaultWidth },
                                         .height = Height_u32{ DefaultHeight } };

            /// @brief The maximum allowed aspect ratio
            std::optional<float> max_aspect_ratio = std::nullopt;

            /// @brief The minimum allowed aspect ratio
            std::optional<float> min_aspect_ratio = std::nullopt;
        };

        /// @note Defined by each platform
        ~Display() noexcept;

        [[nodiscard]] static expected<std::shared_ptr<Display>, SystemError>
        create(const CreateOptions &options, class DisplayServer *server) noexcept;

        // Observers
      public:
        /// @brief Get the set maximum aspect ratio of the display
        [[nodiscard]] std::optional<float>
        max_aspect_ratio() const noexcept
        {
            return m_max_aspect_ratio;
        }

        /// @brief Get the set minumum aspect ratio of the display
        [[nodiscard]] std::optional<float>
        min_aspect_ratio() const noexcept
        {
            return m_min_aspect_ratio;
        }

        /// @brief Get the current extent of the display
        [[nodiscard]] Extent2D_u32
        current_extent() const noexcept
        {
            return m_current_extent;
        }

        /// @brief Get the current width of the display
        [[nodiscard]] Width_u32
        current_width() const noexcept
        {
            return current_extent().width;
        }

        /// @brief Get the current height of the display
        [[nodiscard]] Height_u32
        current_height() const noexcept
        {
            return current_extent().height;
        }

        /// @brief Get the title of the display
        [[nodiscard]] std::string_view
        title() const noexcept
        {
            return m_title;
        }

        // Mutators
      public:
        /// @brief Request to close this display
        bool request_close() noexcept;

        /// @brief Update the title of this display
        bool set_title(std::string_view title) noexcept;

        // Event handling
      public:
        /// @brief Register a listener callback to trigger on a given event
        /// @tparam T The type of event
        template <typename T>
        [[nodiscard]] EventHandler::Handle<T>
        on(EventHandler::Listener<T> listener) noexcept
        {
            return m_event_handler.on<T>(listener);
        }

        /// @brief Get the next event received from the window
        [[nodiscard]] std::optional<EventHandler::UnifiedEvent>
        next_event() noexcept
        {
            return m_event_handler.next_event();
        }

        /// @brief Remove a listener from the window
        /// @tparam T The type of event
        template <typename T>
        [[nodiscard]] bool
        remove_listener(const EventHandler::Handle<T> handle) noexcept
        {
            return m_event_handler.remove_listener<T>(handle);
        }

        /// @brief Dispatch an event sent from this window
        /// @note This should only be called internally
        template <typename T>
        void
        __dispatch_event(T data) noexcept
        {
            m_event_handler.dispatch(std::move(data));
        }

        /// @brief Handle a key down event
        /// @note This should only be called internally
        void __handle_key_down(const Key::Code code);

        /// @brief Handle a key down event
        /// @note This should only be called internally
        void __handle_mouse_move(std::uint32_t x, std::uint32_t y) noexcept;

      private:
        friend class DisplayServer;

        // Defined by each platform
        struct NativeData;
        friend struct NativeData;

        /// @note Private constructor only accessible from DisplayServer class
        /// @note Implemented by each platform
        [[nodiscard]] explicit Display(const CreateOptions &options,
                                       class DisplayServer *server) noexcept;

        /// @brief Get the handle for this window
        /// @note This is meant to be used by the DisplayServer for managing this display
        [[nodiscard]] Handle
        handle() const noexcept
        {
            return m_handle;
        }

        /* Non-native data */

        std::string                 m_title;
        std::optional<float>        m_max_aspect_ratio;
        std::optional<float>        m_min_aspect_ratio;
        Extent2D_u32                m_current_extent;
        Handle                      m_handle;
        DisplayServer              *m_server;
        EventHandler                m_event_handler;

        std::unique_ptr<NativeData> m_native_data{ nullptr };
    };

    /// @brief  Handle for retrieving Display
    using DisplayHandle = Display::Handle;

    /// @brief An interface for managing interactive displays
    class DisplayServer
    {
      public:
        /// @brief Create a new display server
        [[nodiscard]] static expected<std::shared_ptr<DisplayServer>, SystemError>
        create() noexcept;

        ~DisplayServer() noexcept;

        /// @brief Create a new display managed by the server
        /// @returns `std::shared_ptr<Display>` on success. `SystemError` on failure
        [[nodiscard]] expected<std::shared_ptr<Display>, SystemError>
        spawn_display(const Display::CreateOptions &) noexcept;

        // Observers
      public:
        /// @brief Determine if the display server holds a display from a specified handle
        [[nodiscard]] bool
        contains_display(const DisplayHandle handle) const noexcept
        {
            return m_displays.find(handle) != m_displays.end();
        }

        /// @brief Get a display from its handle
        [[nodiscard]] std::optional<std::shared_ptr<Display>>
        get_display(const DisplayHandle handle) const noexcept
        {
            if ( !contains_display(handle) )
                return std::nullopt;

            return m_displays.find(handle)->second;
        }

        // Mutators
      public:
        /// @brief Close the remaining displays
        void
        close_remaining_displays() noexcept
        {
            for ( const std::shared_ptr<Display> display : m_displays | std::views::values )
                {
                    (void)display->request_close();
                }
        }

        // TODO: remove this when real message passing is done
        void
        send_close() noexcept
        {
            m_event_handler.dispatch(DisplayClose{});
        }

        /// @brief Pump the events
        void pump_events() noexcept;

      private:
        /// @brief Internal data that is native to the platform being compiled
        struct NativeData;

        /// @brief Native shutdown behavior
        void native_shutdown() noexcept;

        /// @note Private constructor. Use factory instead
        [[nodiscard]] explicit DisplayServer() noexcept;

        std::unordered_map<DisplayHandle, std::shared_ptr<Display>> m_displays;
        std::unique_ptr<NativeData>                                 m_native_data{ nullptr };
        bool                                                        m_is_running{ false };
        SystemEventHandler<SystemEventList>                         m_event_handler;
    };
} // namespace apx::system