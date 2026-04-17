#pragma once
#include "apex/core/core.h"
#include "window_error.h"

namespace apx::media
{
    class Window
    {
      public:
        struct Options
        {
            std::string   title;
            std::uint32_t width;
            std::uint32_t height;
        };

        static expected<Window, WindowError> create(const Options window_options) noexcept
        {
            if (window_options.title.empty())
                {
                    return unexpected(WindowError(WindowError::Code::InitFailed));
                }
            return Window();
        }

      private:
        explicit Window() noexcept = default;
    };
} // namespace apx::media