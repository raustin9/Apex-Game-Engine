#include "apex/system/system.h"
#ifdef APEX_PLATFORM_APPLE

#include "apex_window.h"

namespace apx::system
{
    struct Display::NativeData
    {
        ApexWindowData *data;

        template <typename T>
        void dispatch_event(T data) noexcept
        {
            data->display->template dispatch_event<T>(data);
        }
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

            NSRect frame = NSMakeRect(
                0,
                0,
                options.extent.width,
                options.extent.height
            );
            NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
            native_data->data.window = [[ApexWindow2 alloc] initWithContentRect:frame
                                                      styleMask:style
                                                        backing:NSBackingStoreBuffered
                                                          defer:NO];
            NSView *content_view = [[ApexView alloc] initWithFrameAndData:frame withData:native_data->data];

            ApexWindowDelegate2 *delegate = [[ApexWindowDelegate2 alloc] init];
            delegate.data = native_data->data;
            [native_data->data.window setDelegate:delegate];

            [native_data->data.window setTitle:@(options.title.data())];
            [native_data->data.window setContentView:content_view];

            [native_data->data.window setAcceptsMouseMovedEvents:YES];

            [native_data->data.window center];
            [native_data->data.window makeKeyAndOrderFront:nil];

            native_data->data.display = std::weak_ptr(display);

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
