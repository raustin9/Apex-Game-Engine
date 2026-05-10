#include "apex/core/core.h"
#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import "cocoa_window.h"

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
        window.m_title = options.title;
        window.m_extent = options.extent;

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
        copy(other);
        update_delegate();
    }

    Window::Window(Window&& other) noexcept
    {
        move(std::move(other));
        update_delegate();
    }

    Window& Window::operator=(const Window& other) noexcept
    {
        if (this != &other)
        {
            copy(other);
            update_delegate();
        }

        return *this;
    }

    Window& Window::operator=(Window&& other) noexcept
    {
        if (this != &other)
        {
            move(std::move(other));
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
        [m_native_data.window makeKeyAndOrderFront:nil];
        [NSApp activateIgnoringOtherApps:YES];
    }

    void Window::close() noexcept
    {
        if (is_open()) {
            [m_native_data.display_link invalidate];
            m_native_data.display_link = nullptr;
            m_is_open = false;
        }
    }

    void Window::resize(const Extent2D_u32 new_extent) noexcept
    {
        NSSize new_size = NSMakeSize(new_extent.width.get(), new_extent.height.get());

        NSRect content_rect = NSMakeRect(
            m_native_data.window.frame.origin.x,
            m_native_data.window.frame.origin.y,
            new_size.width,
            new_size.height
        );
        NSRect frame_rect = [m_native_data.window frameRectForContentRect:content_rect];

        [m_native_data.window setFrame:frame_rect display:YES animate:NO];
        [m_native_data.window setContentSize:new_size];
        __resize_callback(new_extent);
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

    void Window::__resize_callback(Extent2D_u32 new_extent) noexcept
    {
        m_extent = new_extent;
    }

} // namespace apex::system
#endif // APEX_PLATFORM_APPLE
