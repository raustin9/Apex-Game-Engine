#include "apex/core/core.h"
#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import "window_delegate.h"

// Apple
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

// std
#include <utility>

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
        window.setup_delegate();

        [window.m_native_data.window setAcceptsMouseMovedEvents:YES];

        return window;
    }

    Window::Window(const Window& other) noexcept
    {
        m_native_data = other.m_native_data;
        m_is_open = other.m_is_open;
        update_delegate();
    }

    Window::Window(Window&& other) noexcept
    {
        m_native_data = other.m_native_data;
        m_is_open = other.m_is_open;
        update_delegate();
    }

    Window& Window::operator=(const Window& other) noexcept
    {
        if (this != &other)
        {
            m_native_data = other.m_native_data;
            m_is_open = other.m_is_open;
            update_delegate();
        }

        return *this;
    }

    Window& Window::operator=(Window&& other) noexcept
    {
        if (this != &other)
        {
            m_native_data = other.m_native_data;
            m_is_open = other.m_is_open;
            update_delegate();
        }

        return *this;
    }

    Window::~Window() noexcept
    {

    }

    void Window::open() noexcept
    {
        m_is_open = true;
//        [m_native_data.window setCollectionBehavior: NSWindowCollectionBehaviorFullScreenPrimary];
        [m_native_data.window makeKeyAndOrderFront:nil];
        [NSApp activateIgnoringOtherApps:YES];
        NSLog(@"Window opened");
        NSLog(m_is_open ? @"m_is_open:true" : @"m_is_open:false");
    }

    void Window::close() noexcept
    {
        NSLog(m_is_open ? @"m_is_open:true" : @"m_is_open:false");
        if (is_open()) {
            NSLog(@"Closing window");
            [m_native_data.display_link invalidate];
            m_native_data.display_link = nullptr;
            m_is_open = false;
        } else {
            NSLog(@"Cannot close closed window");
        }
    }

    void Window::setup_delegate() noexcept
    {
        m_native_data.delegate = [[WindowDelegate alloc] initWithWindow:this];
        [m_native_data.window setDelegate:m_native_data.delegate];
    }

    void Window::update_delegate() noexcept
    {
        m_native_data.delegate.window = this;
    }
} // namespace apex::system
#endif // APEX_PLATFORM_APPLE
