#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#include "apex/system/system_window.h"

namespace apx::system
{
    void
    System::copy_native(const System &from) noexcept
    {
        m_delegate = from.m_delegate;
    }

    void
    System::move_native(System &&from) noexcept
    {
        m_delegate = std::move(from.m_delegate);
    }

    System::System(const System &other) noexcept
    {
        copy(other);
        update_delegate();
    }

    System &
    System::operator=(const System &other) noexcept
    {
        if ( this != &other )
            {
                copy(other);
                update_delegate();
            }

        return *this;
    }

    System::System(System &&other) noexcept
    {
        move(std::move(other));
        update_delegate();
    }

    System &
    System::operator=(System &&other) noexcept
    {
        if ( this != &other )
            {
                move(std::move(other));
                update_delegate();
            }

        return *this;
    }
} // namespace apx::system

#endif // APEX_PLATFORM_APPLE
