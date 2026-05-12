#pragma once
#include "apex/core/core.h"
#include "apex/event/event.h"
#include "system_key.h"
#include "system_mouse.h"

#include <array>

namespace apx::sys
{
    /// @brief Possible states for a pressable key
    enum class KeyState : std::uint8_t
    {
        UP,
        DOWN
    };

    /// @brief Possible states for a pressable mouse button
    using MousePressState = KeyState;

    class InputHandler
    {
      public:
        [[nodiscard]] explicit InputHandler() noexcept = default;

        /// @brief Determine if a key is currently down
        [[nodiscard]] bool     is_key_down(const Key::Code key_code) const noexcept;

        /// @brief Determine if a key is currently up
        [[nodiscard]] bool     is_key_up(const Key::Code key_code) const noexcept;

        /// @brief Get the state of a given key
        [[nodiscard]] KeyState current_key_state(const Key::Code key_code) const noexcept;

        /// @brief Get the state of a given key
        [[nodiscard]] KeyState previous_key_state(const Key::Code key_code) const noexcept;

        /// @brief Determine if a key was previously down
        [[nodiscard]] bool     was_key_down(const Key::Code key_code) const noexcept;

        /// @brief Determine if a key was previously up
        [[nodiscard]] bool     was_key_up(const Key::Code key_code) const noexcept;

        /// @brief Get the current mouse button's pressed state
        [[nodiscard]] MousePressState
        current_mouse_button_pressed_state(const MouseButton button) const noexcept;

        /// @brief Get the previous mouse button's pressed state
        [[nodiscard]] MousePressState
        previous_mouse_button_pressed_state(const MouseButton button) const noexcept;

        /// @brief Determine if a mouse button is currently pressed
        [[nodiscard]] bool  is_mouse_button_pressed(const MouseButton button) const noexcept;

        /// @brief Determine if a mouse button was previously pressed
        [[nodiscard]] bool  was_mouse_button_pressed(const MouseButton button) const noexcept;

        /// @brief Return the current coordinates of the mouse
        [[nodiscard]] Vec2u mouse_position() const noexcept;

      private:
        friend class Display;

        /// @brief Set the previous key state
        void set_current_key_state(const Key::Code key_code, const KeyState state) noexcept;

        /// @brief Set the previous key state
        void set_previous_key_state(const Key::Code key_code, const KeyState state) noexcept;

        /// @brief Update a key with a new state
        /// @note If the provided `state` is the same as `current_key_state()` then this will do
        /// nothing
        void update_key(const Key::Code key_code, const KeyState state) noexcept;

        void update_mouse_position(const Vec2u mouse_position) noexcept;

        struct KeyboardState
        {
            using KeyTable = std::array<KeyState, static_cast<std::size_t>(Key::Code::COUNT)>;

            KeyTable previous;
            KeyTable current;
        };

        struct MouseState
        {
            using PressableTable
                = std::array<MousePressState, static_cast<std::size_t>(MouseButton::COUNT)>;

            PressableTable previous;
            PressableTable current;
            Vec2u          mouse_position{ Vec2u(0, 0) };
        };

        KeyboardState m_key_state;
        MouseState    m_mouse_state;
    };
} // namespace apx::sys