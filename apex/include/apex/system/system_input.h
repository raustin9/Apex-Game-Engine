#pragma once
#include "apex/core/core.h"
#include "apex/event/event.h"
#include "system_key.h"

#include <array>

namespace apx::system
{
    class InputHandler
    {
      public:
        [[nodiscard]] explicit InputHandler() noexcept = default;

        void key_down(const Key::Code key_code) noexcept;

      private:
        struct KeyState
        {
            using KeyTable = std::array<bool, static_cast<std::size_t>(Key::Code::NUM_KEYS)>;

            KeyTable previous;
            KeyTable current;
        };

        KeyState m_key_state;
    };
} // namespace apx::system