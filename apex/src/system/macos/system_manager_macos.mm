#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import "application.h"
#include <iostream>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <Quartz/Quartz.h>

namespace apx::system
{
    expected<System, SystemError> System::create(const WindowOptions window_options)
    {
        System system{};
        [ApexApplication sharedApplication];
        system.setup_delegate();

        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp finishLaunching];

        if (auto window = Window::create(window_options)) {
            system.m_window = window.value();
        } else {
            return unexpected(window.error());
        }

        system.m_is_running = true;
        system.m_window.open();
        return system;
    }

    void System::update() noexcept
    {
        @autoreleasepool {
            NSEvent* ev { nullptr };
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

    void System::shutdown() noexcept
    {
        NSLog(@"Shutting down");
    }

    bool System::is_running() const noexcept
    {
        return m_window.is_open();
    }

    void System::setup_delegate() noexcept
    {
        m_delegate = [[AppDelegate alloc] initWithSystem:this];
        [NSApp setDelegate:m_delegate];
    }

    void System::update_delegate() noexcept
    {
        NSLog(@"Updating system delegates");
        m_delegate.system_handler->update_system(this);
    }
}


#endif // APEX_PLATFORM_APPLE
