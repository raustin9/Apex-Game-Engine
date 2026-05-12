#include "apex/core/core.h"
#include "apex/system/system.h"
#ifdef APEX_PLATFORM_APPLE

#include "apex_application.h"

#include <memory>

namespace apx::system
{
    struct DisplayServer::NativeData
    {
        ApexApplicationData *data = nullptr;
    };

    DisplayServer::DisplayServer() noexcept
    {}

    DisplayServer::~DisplayServer() noexcept
    {
        close_remaining_displays();
        native_shutdown();
    }

    expected<std::shared_ptr<DisplayServer>, SystemError>
    DisplayServer::create() noexcept
    {
        std::shared_ptr<DisplayServer> server{ new DisplayServer() };
        std::unique_ptr<NativeData> native_data = std::make_unique<NativeData>();

        native_data->data = [[ApexApplicationData alloc] init];
        native_data->data.display_server = server;

//        ApexApplication2 *app = [ApexApplication2 sharedApplication];

//        app.data = native_data->data;
        [NSApplication sharedApplication];

        server->m_native_data = std::move(native_data);
        server->m_is_running = true;

        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp finishLaunching];

        return server;
    }

    expected<std::shared_ptr<Display>, SystemError>
    DisplayServer::spawn_display(const Display::CreateOptions& options) noexcept
    {
        expected<std::shared_ptr<Display>, SystemError> exp_display
            = Display::create(options, this);

        if (!exp_display)
            {
                return unexpected(exp_display.error());
            }

        std::shared_ptr<Display> display{ exp_display.value() };

        m_displays.insert({display->handle(), display});
        return display;
    }

    void DisplayServer::pump_events() noexcept
    {
        @autoreleasepool {
            NSEvent *ev { nullptr };
            do {
                ev = [NSApp nextEventMatchingMask: NSEventMaskAny
                                        untilDate: nil
                                           inMode: NSDefaultRunLoopMode
                                          dequeue: YES];
                if (ev) {
                    [NSApp sendEvent: ev];
                    [NSApp updateWindows];
                }
            } while (ev);
        }
    }

    void
    DisplayServer::native_shutdown() noexcept
    {}
} // namespace apx::system
#endif // APEX_PLATFORM_APPLE
