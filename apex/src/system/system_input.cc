#include "apex/system/system.h"

namespace apx::system
{
    KeyState
    InputHandler::current_key_state(const Key::Code key_code) const noexcept
    {
        return m_key_state.current[static_cast<std::size_t>(key_code)];
    }

    KeyState
    InputHandler::previous_key_state(const Key::Code key_code) const noexcept
    {
        return m_key_state.previous[static_cast<std::size_t>(key_code)];
    }

    bool
    InputHandler::is_key_down(const Key::Code key_code) const noexcept
    {
        return current_key_state(key_code) == KeyState::DOWN;
    }

    bool
    InputHandler::is_key_up(const Key::Code key_code) const noexcept
    {
        return previous_key_state(key_code) == KeyState::UP;
    }

    bool
    InputHandler::was_key_down(const Key::Code key_code) const noexcept
    {
        return previous_key_state(key_code) == KeyState::DOWN;
    }

    bool
    InputHandler::was_key_up(const Key::Code key_code) const noexcept
    {
        return previous_key_state(key_code) == KeyState::UP;
    }

    void
    InputHandler::set_previous_key_state(const Key::Code key_code, const KeyState state) noexcept
    {
        m_key_state.previous[static_cast<std::size_t>(key_code)] = state;
    }

    void
    InputHandler::set_current_key_state(const Key::Code key_code, const KeyState state) noexcept
    {
        m_key_state.current[static_cast<std::size_t>(key_code)] = state;
    }

    void
    InputHandler::update_key(const Key::Code key_code, const KeyState state) noexcept
    {
        if ( current_key_state(key_code) == state )
            return;

        set_previous_key_state(key_code, current_key_state(key_code));
        set_current_key_state(key_code, state);
    }

    MousePressState
    InputHandler::current_mouse_button_pressed_state(const MouseButton button) const noexcept
    {
        return m_mouse_state.current[static_cast<std::size_t>(button)];
    }

    MousePressState
    InputHandler::previous_mouse_button_pressed_state(const MouseButton button) const noexcept
    {
        return m_mouse_state.previous[static_cast<std::size_t>(button)];
    }

    bool
    InputHandler::is_mouse_button_pressed(const MouseButton button) const noexcept
    {
        return current_mouse_button_pressed_state(button) == MousePressState::DOWN;
    }

    bool
    InputHandler::was_mouse_button_pressed(const MouseButton button) const noexcept
    {
        return previous_mouse_button_pressed_state(button) == MousePressState::DOWN;
    }

    Vec2u
    InputHandler::mouse_position() const noexcept
    {
        return m_mouse_state.mouse_position;
    }

    void
    InputHandler::update_mouse_position(const Vec2u mouse_position) noexcept
    {
        m_mouse_state.mouse_position = mouse_position;
    }
}