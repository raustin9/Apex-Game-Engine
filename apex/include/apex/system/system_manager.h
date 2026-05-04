#pragma once
#include "apex/core/core.h"
#include "native/native_types.h"
#include "system_error.h"
#include "system_input.h"
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

        System(const System &) noexcept;
        System(System &&) noexcept;
        System &operator=(const System &) noexcept;
        System &operator=(System &&) noexcept;

        // API
      public:
        [[nodiscard]] bool is_running() const noexcept;
        void               shutdown() noexcept;
        void               update() noexcept;

        [[nodiscard]] Window &
        main_window() noexcept
        {
            return m_window;
        }

      private:
        [[nodiscard]] explicit System() noexcept = default;

        /// @brief Dispatch a system event
        /// @tparam T the type of the system event to dispatch. i.e KeyDown or WindowClosed
        template <typename T, typename... Args>
        void
        dispatch_event(Args &&...args) noexcept
        {
            m_input_handler->fire<T>(std::forward<Args>(args)...);
        }

        // Private members
      private:
        Window                                      m_window;
        std::shared_ptr<InputHandler<SystemEvents>> m_input_handler
            = std::make_shared<InputHandler<SystemEvents>>();

        void
        copy(const System &from) noexcept
        {
            m_window        = from.m_window;
            m_input_handler = from.m_input_handler;

            copy_native(from);
        }

        void
        move(System &&from) noexcept
        {
            m_window        = std::move(from.m_window);
            m_input_handler = std::move(from.m_input_handler);

            move_native(std::move(from));
        }

        void copy_native(const System &from) noexcept;
        void move_native(System &&from) noexcept;

#if defined(APEX_PLATFORM_APPLE)
        friend class AppDelegateHandler;
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