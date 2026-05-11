#pragma once
#include "apex/core/core.h"
#include "apex/event/event.h"
#include "system_key.h"

#include <array>

namespace apx::system
{
    enum class KeyState : std::uint8_t
    {
        UP,
        DOWN
    };

    class InputHandler
    {
      public:
        [[nodiscard]] explicit InputHandler() noexcept = default;

        /// @brief Determine if a key is currently down
        [[nodiscard]] bool     is_key_down(const Key::Code key_code) const noexcept;

        /// @brief Determine if a key is currently up
        [[nodiscard]] bool     is_key_up(const Key::Code key_code) const noexcept;

        /// @brief Get the state of a given key
        [[nodiscard]] KeyState get_key_state(const Key::Code key_code) const noexcept;

      private:
        struct KeyboardState
        {
            using KeyTable = std::array<KeyState, static_cast<std::size_t>(Key::Code::NUM_KEYS)>;

            KeyTable previous;
            KeyTable current;
        };

        KeyboardState m_key_state;
    };
} // namespace apx::system