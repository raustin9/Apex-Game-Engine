#include "apex/system/system.h"
#ifdef APEX_PLATFORM_APPLE

#include "apex_window.h"

#include <algorithm>

namespace apx::sys
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
    {
        if ( is_open() )
            request_close();
    }

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

    Width_u32 Display::inner_width() const noexcept
    {
        NSWindow *window = m_native_data->data.window;
        return Width_u32([[window contentView] frame].size.width);
    }

    Height_u32 Display::inner_height() const noexcept
    {
        NSWindow *window = m_native_data->data.window;
        return Height_u32([[window contentView] frame].size.height);
    }

    Point2D_u32 Display::origin() const noexcept
    {
        NSWindow *window = m_native_data->data.window;
        NSPoint origin = [window frame].origin;
        return Point2D_u32(origin.x, origin.y);
    }

    bool Display::is_open() const noexcept
    {
        return [m_native_data->data.window isVisible];
    }

    bool Display::request_close() noexcept
    {
        if ( !is_open() )
            return false;

        [m_native_data->data.window performClose:nil];
        [m_native_data->data.window close];

        return true;
    }

    bool Display::set_title(std::string_view title) noexcept
    {
        NSWindow *window = [m_native_data->data window];
        [window setTitle:@(title.data())];
        return true;
    }

    bool Display::resize(const Extent2D_u32 extent) noexcept
    {
        NSWindow *window = m_native_data->data.window;
        NSScreen *screen = [window screen] ?: [NSScreen mainScreen];
        NSRect screen_frame = [screen frame];
        NSRect visible_frame = [screen visibleFrame];

        const CGFloat new_width { static_cast<CGFloat>(extent.width.get()) };
        const CGFloat new_height { static_cast<CGFloat>(extent.height.get()) };
        const CGFloat adjusted_width = std::min(visible_frame.size.width, new_width);
        const CGFloat adjusted_height = std::min(visible_frame.size.height, new_height);

        // Adjust the origin of the window to account
        // for resizing dimensions too large for current position
        {
            NSRect window_frame = [window frame];
            NSPoint window_origin = window_frame.origin;
            NSPoint new_origin = window_origin;

            new_origin.x = adjusted_width + window_origin.x > screen_frame.size.width
                               ? screen_frame.size.width - adjusted_width
                               : window_origin.x;

            new_origin.y = adjusted_height + window_origin.y > screen_frame.size.height
                               ? screen_frame.size.height - adjusted_height
                               : window_origin.y;

            reposition(Point2D_u32(new_origin.x, new_origin.y));
        }

        // Resize the window
        {
            NSSize size = NSMakeSize(
                adjusted_width,
                adjusted_height
            );
            [m_native_data->data.window setContentSize:size];
        }

        // NOTE: we should not update the extent here because the delegate
        // should fire a DisplayResize event which the __handle_resize method will
        // take care of

        return true;
    }

    bool Display::reposition(const Point2D_u32 origin) noexcept
    {
        NSWindow *window = m_native_data->data.window;
        NSScreen *screen = [window screen] ?: [NSScreen mainScreen];
        const NSRect screen_frame = [screen frame];
        const CGFloat content_width = inner_width().get();
        const CGFloat content_height = inner_height().get();

        const NSPoint new_origin = NSMakePoint(
            std::min(static_cast<CGFloat>(origin.x), screen_frame.size.width - content_width),
            std::min(static_cast<CGFloat>(origin.y), screen_frame.size.height - content_height)
        );

        [window setFrameOrigin:new_origin];
        return true;
    }
} // namespace apx::sys

#endif // APEX_PLATFORM_APPLE
