#pragma once
#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <Quartz/Quartz.h>

#include <memory>

using ScanCode = unsigned short;

namespace apx::system
{
    class SystemHandler
    {
      public:
        [[nodiscard]] explicit SystemHandler(System *system) noexcept : m_system(system) {}

        void
        handle_key_down(const Key::Code key_code)
        {
            // m_system->dispatch_event<KeyDown>(key_code);
        }

        void handle_cocoa_event(NSEvent *event) noexcept;

      private:
        friend class System;

        void                    handle_cocoa_key_event(NSEvent *event) noexcept;
        void                    handle_cocoa_mouse_event(NSEvent *event) noexcept;

        [[nodiscard]] Key::Code translate_key(const ScanCode scan_code) noexcept;

        void
        update_system(System *system) noexcept
        {
            m_system = system;
        }

        System *m_system;
    };
} // namespace apx::system

@interface ApexApplication : NSApplication
@property(nonatomic, assign) std::shared_ptr<apx::system::SystemHandler> system_handler;

/// @brief Init the application with a system
- (instancetype)initWithSystem:(apx::system::System *)system;

/// @brief Handle sending the cocoa events
- (void)sendEvent:(NSEvent *)event;
@end

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property(nonatomic, assign) std::shared_ptr<apx::system::SystemHandler> system_handler;

/// @brief Init the application delegate with a system
- (instancetype)initWithSystem:(apx::system::System *)system;
@end

#endif // APEX_PLATFORM_APPLE
