#include "apex/core/core.h"
#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

namespace apx::system
{
    expected<Window, SystemError> Window::create(WindowOptions options) noexcept
    {
        Window window {};

        NSRect frame = NSMakeRect(
            0,
            0,
            options.extent.width,
            options.extent.height
        );
        NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;

        window.m_native_data.window = [[NSWindow alloc] initWithContentRect:frame
                                                      styleMask:style
                                                        backing:NSBackingStoreBuffered
                                                          defer:NO];

        [window.m_native_data.window setTitle:@(options.title.data())];
        [window.m_native_data.content_view initWithFrame:frame];
        [window.m_native_data.window setContentView:window.m_native_data.content_view];
        [window.m_native_data.window setCollectionBehavior: NSWindowCollectionBehaviorFullScreenPrimary];

        return window;
    }

    void Window::open() noexcept
    {
        [m_native_data.window makeKeyAndOrderFront:nil];
    }

    void Window::close() noexcept
    {
        [m_native_data.display_link invalidate];
        m_native_data.display_link = nullptr;
    }

} // namespace apex::system
#endif // APEX_PLATFORM_APPLE
