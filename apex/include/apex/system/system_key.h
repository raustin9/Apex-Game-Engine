#pragma once
#include "apex/core/core.h"

#include <cstdint>
#include <limits>
#include <ostream>
#include <string>
#include <string_view>

namespace apx
{
    class Key
    {
      public:
        using IntegralType = std::uint32_t;

        enum class Code : IntegralType
        {
            Unknown = std::numeric_limits<IntegralType>::max(),
            A       = 0,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,

            Num1,
            Num2,
            Num3,
            Num4,
            Num5,
            Num6,
            Num7,
            Num8,
            Num9,
            Num0,

            Esc,
            LeftCtrl,
            RightCtrl,
            LeftSystem,
            RightSystem,
            Menu,
            LeftBracket,
            RightBracket,
            Semicolon,
            Apostrophe,
            Comma,
            Period,
            ForwardSlash,
            BackSlash,
            Grave,
            Equal,
            Hyphen,
            Space,
            Enter,
            Backspace,
            Tab,
            PageUp,
            PageDown,
            End,
            Home,
            Insert,
            Delete,
            Add,
            Subtract,
            Multiply,
            Divide,
            ArrowLeft,
            ArrowRight,
            ArrowUp,
            ArrowDown,
            Fn1,
            Fn2,
            Fn3,
            Fn4,
            Fn5,
            Fn6,
            Fn7,
            Fn8,
            Fn9,
            Fn10,
            Fn11,
            Fn12,
            Fn13,
            Fn14,
            Fn15,
            Pause
        };

        /// @brrief Initialize a Key from a Key::Code
        [[nodiscard]] constexpr explicit(false) Key(const Code key_code) noexcept
            : m_key_code{ key_code }
        {
        }

        /// API
      public:
        /// @brief Get the Key::Code
        [[nodiscard]] constexpr Code
        code() const noexcept
        {
            return m_key_code;
        }

        /// @brief Get the integral value of the key
        [[nodiscard]] constexpr IntegralType
        as_integral() const noexcept
        {
            return code_as_integral(code());
        }

        /// @brief Get a null-terminated c-string corresponding to the Key::Code
        [[nodiscard]] constexpr const char *
        c_str() const noexcept
        {
            return code_as_c_str(code());
        }

        /// @brief Get a std::string_view corresponding to the Key::Code
        [[nodiscard]] constexpr std::string_view
        to_string() const noexcept
        {
            return std::string_view{ c_str() };
        }

        /// @brief Determine if the key is an alpha value (A-Z)
        [[nodiscard]] constexpr bool
        is_alpha() const noexcept
        {
            return as_integral() <= code_as_integral(Code::Z);
        }

        /// @brief Determine if the key is numeric value (Num1-Num0)
        [[nodiscard]] constexpr bool
        is_numeric() const noexcept
        {
            // NOTE: Code::Num0 is last in appearance in the Code enum
            return as_integral() >= code_as_integral(Code::Num1)
                   && as_integral() <= code_as_integral(Code::Num0);
        }

        /// @brief Determine if a key is alphanumeric (either a valid alpha value or valid numeric
        /// value)
        [[nodiscard]] constexpr bool
        is_alphanumeric() const noexcept
        {
            return is_alpha() || is_numeric();
        }

        // Operators
      public:
        constexpr bool
        operator==(const Key &rhs) const noexcept
        {
            return code() == rhs.code();
        }

        /// @brief Implicit conversion to std::string_view
        constexpr explicit(false) operator std::string_view() const noexcept { return to_string(); }

        /// @brief Implicit conversion to std::string
        constexpr explicit(false) operator std::string() const noexcept
        {
            return std::string(to_string());
        }

        /// @brief Insert the string value of the Code to a std::ostream
        friend std::ostream &
        operator<<(std::ostream &os, const Key &key)
        {
            os << key.to_string();
            return os;
        }

      private:
        /// @brief Get the Code as an integral type
        [[nodiscard]] constexpr static IntegralType
        code_as_integral(const Code key_code) noexcept
        {
            return static_cast<IntegralType>(key_code);
        }

        /// @brief Get a c-string for a Key::Code
        [[nodiscard]] static constexpr const char *
        code_as_c_str(const Code key_code) noexcept
        {
            switch ( key_code )
                {
                case Code::A:
                    return "A";
                case Code::B:
                    return "B";
                case Code::C:
                    return "C";
                case Code::D:
                    return "D";
                case Code::E:
                    return "E";
                case Code::F:
                    return "F";
                case Code::G:
                    return "G";
                case Code::H:
                    return "H";
                case Code::I:
                    return "I";
                case Code::J:
                    return "J";
                case Code::K:
                    return "K";
                case Code::L:
                    return "L";
                case Code::M:
                    return "M";
                case Code::N:
                    return "N";
                case Code::O:
                    return "O";
                case Code::P:
                    return "P";
                case Code::Q:
                    return "Q";
                case Code::R:
                    return "R";
                case Code::S:
                    return "S";
                case Code::T:
                    return "T";
                case Code::U:
                    return "U";
                case Code::V:
                    return "V";
                case Code::W:
                    return "W";
                case Code::X:
                    return "X";
                case Code::Y:
                    return "Y";
                case Code::Z:
                    return "Z";

                case Code::Num1:
                    return "Num1";
                case Code::Num2:
                    return "Num2";
                case Code::Num3:
                    return "Num3";
                case Code::Num4:
                    return "Num4";
                case Code::Num5:
                    return "Num5";
                case Code::Num6:
                    return "Num6";
                case Code::Num7:
                    return "Num7";
                case Code::Num8:
                    return "Num8";
                case Code::Num9:
                    return "Num9";
                case Code::Num0:
                    return "Num0";

                case Code::Esc:
                    return "Esc";
                case Code::LeftCtrl:
                    return "LeftCtrl";
                case Code::RightCtrl:
                    return "RightCtrl";
                case Code::LeftSystem:
                    return "LeftSystem";
                case Code::RightSystem:
                    return "RightSystem";
                case Code::Menu:
                    return "Menu";
                case Code::LeftBracket:
                    return "LeftBracket";
                case Code::RightBracket:
                    return "RightBracket";
                case Code::Semicolon:
                    return "Semicolon";
                case Code::Apostrophe:
                    return "Apostrophe";
                case Code::Comma:
                    return "Comma";
                case Code::Period:
                    return "Period";
                case Code::ForwardSlash:
                    return "ForwardSlash";
                case Code::BackSlash:
                    return "BackSlash";
                case Code::Grave:
                    return "Grave";
                case Code::Equal:
                    return "Equal";
                case Code::Hyphen:
                    return "Hyphen";
                case Code::Space:
                    return "Space";
                case Code::Enter:
                    return "Enter";
                case Code::Backspace:
                    return "Backspace";
                case Code::Tab:
                    return "Tab";
                case Code::PageUp:
                    return "PageUp";
                case Code::PageDown:
                    return "PageDown";
                case Code::End:
                    return "End";
                case Code::Home:
                    return "Home";
                case Code::Insert:
                    return "Insert";
                case Code::Delete:
                    return "Delete";
                case Code::Add:
                    return "Add";
                case Code::Subtract:
                    return "Subtract";
                case Code::Multiply:
                    return "Multiply";
                case Code::Divide:
                    return "Divide";
                case Code::ArrowLeft:
                    return "ArrowLeft";
                case Code::ArrowRight:
                    return "ArrowRight";
                case Code::ArrowUp:
                    return "ArrowUp";
                case Code::ArrowDown:
                    return "ArrowDown";
                case Code::Fn1:
                    return "Fn1";
                case Code::Fn2:
                    return "Fn2";
                case Code::Fn3:
                    return "Fn3";
                case Code::Fn4:
                    return "Fn4";
                case Code::Fn5:
                    return "Fn5";
                case Code::Fn6:
                    return "Fn6";
                case Code::Fn7:
                    return "Fn7";
                case Code::Fn8:
                    return "Fn8";
                case Code::Fn9:
                    return "Fn9";
                case Code::Fn10:
                    return "Fn10";
                case Code::Fn11:
                    return "Fn11";
                case Code::Fn12:
                    return "Fn12";
                case Code::Fn13:
                    return "Fn13";
                case Code::Fn14:
                    return "Fn14";
                case Code::Fn15:
                    return "Fn15";
                case Code::Pause:
                    return "Pause";
                default:
                    return "Unknown";
                }

            return "Unknown";
        }

      private:
        Code m_key_code{ Code::Unknown };
    };
} // namespace apx::system