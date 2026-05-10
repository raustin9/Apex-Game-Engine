#include "apex/system/system.h"
#ifdef APEX_PLATFORM_APPLE

#include "apex_window.h"

namespace apx::system
{
    struct Display::NativeData
    {
        ApexWindowData *data;
    };

    Display::Display(const CreateOptions &options,DisplayServer *server) noexcept
        : m_title(options.title), m_max_aspect_ratio(options.max_aspect_ratio),
          m_min_aspect_ratio(options.min_aspect_ratio), m_current_extent(options.extent),
          m_handle{ Handle_u32::make() }, m_server{ server }
    {
    }

    Display::~Display() noexcept
    {}

    expected<std::shared_ptr<Display>, SystemError>
    Display::create(const Display::CreateOptions &options, DisplayServer* server) noexcept
    {
        std::shared_ptr<Display> display { new Display(options, server) };
        std::unique_ptr<NativeData> native_data = std::make_unique<NativeData>();

        // Native data
        {
            native_data->data = [[ApexWindowData alloc] init];
            native_data->data.display = display;

            NSRect rect = NSMakeRect(0, 0, options.extent.width, options.extent.height);
            NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
            ApexWindow2 *window = [[ApexWindow2 alloc] initWithContentRect:rect
                                                      styleMask:style
                                                        backing:NSBackingStoreBuffered
                                                          defer:NO];
            native_data->data.window = window;

            [native_data->data.window setTitle:@(options.title.data())];
            [native_data->data.window setAcceptsMouseMovedEvents:YES];

            display->m_native_data = std::move(native_data);
        }

        return display;
    }

    bool Display::request_close() noexcept
    {
        return true;
    }
} // namespace apx::system

#endif // APEX_PLATFORM_APPLE
