#pragma once
#include "apex/core/core.h"
#include <string_view>

namespace apx::sys
{
    enum class ErrorCode
    {
        InitFailed
    };

    class SystemError : public ErrorBase<SystemError, ErrorCode>
    {
      public:
        [[nodiscard]] explicit SystemError(const ErrorCode code, std::string_view message) noexcept
            : m_code{ code }, m_message{ message }
        {
        }

        [[nodiscard]] std::string_view
        message() const noexcept
        {
            return m_message;
        }

        [[nodiscard]] ErrorCode
        code() const noexcept
        {
            return m_code;
        }

        [[nodiscard]] std::string_view
        to_string() const noexcept
        {
            return message();
        }

      private:
        ErrorCode   m_code;
        std::string m_message;
    };
}