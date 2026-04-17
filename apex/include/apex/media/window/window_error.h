#pragma once
#include "apex/core/core.h"

namespace apx::media
{
    class WindowError : public ErrorBase<WindowError>
    {
      public:
        enum class ErrorCode
        {
            InitFailed,
            Unknown
        };

        using Code = ErrorCode;

        explicit WindowError(const Code code) : m_code(code) {}

        std::string_view
        to_string() const noexcept
        {
            return code_to_string(m_code);
        }

      private:
        static std::string_view
        code_to_string(const Code code) noexcept
        {
            switch ( code )
                {
                case Code::InitFailed:
                    return "InitFailed";
                case Code::Unknown:
                    return "Unknown Error";
                }

            return "Unknown error";
        }

        Code m_code{ Code::Unknown };
    };
} // namespace apx::media