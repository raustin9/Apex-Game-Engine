#include "system_detection.h"

#if defined(APEX_PLATFORM_APPLE)
#else
#endif // APEX_PLATFORM_APPLE

namespace apx::system
{
    struct SystemWindow::NativeData
    {
#if defined(APEX_PLATFORM_APPLE)
        void *ns_application;
        void *main_window;
#else
#endif // APEX_PLATFORM_APPLE
    };
} // namespace apx::system