#include "apex/system/system.h"

namespace apx::system
{
    KeyState
    InputHandler::get_key_state(const Key::Code key_code) const noexcept
    {
        return m_key_state.current[static_cast<std::size_t>(key_code)];
    }

    bool
    InputHandler::is_key_down(const Key::Code key_code) const noexcept
    {
        return get_key_state(key_code) == KeyState::DOWN;
    }

    bool
    InputHandler::is_key_up(const Key::Code key_code) const noexcept
    {
        return get_key_state(key_code) == KeyState::UP;
    }
}