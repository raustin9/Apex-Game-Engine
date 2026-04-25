#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
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
        [NSApplication sharedApplication];
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
                }
            } while (ev);
        }
    }

    void System::shutdown() noexcept
    {
        std::cout << "Shutting down..." << std::endl;

    }

    bool System::is_running() const noexcept
    {
        return m_is_running;
    }
}


#endif // APEX_PLATFORM_APPLE
