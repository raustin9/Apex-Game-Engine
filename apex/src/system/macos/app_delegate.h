#pragma once
#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <Quartz/Quartz.h>

#include <memory>

namespace apx::system
{
    class AppDelegateHandler
    {
      public:
        [[nodiscard]] explicit AppDelegateHandler(System *system) noexcept : m_system(system) {}

        void
        handle_key_down(const Key::Code key_code)
        {
            m_system->dispatch_event<KeyDown>(key_code);
        }

      private:
        friend class System;

        void
        update_system(System *system) noexcept
        {
            m_system = system;
        }

        System *m_system;
    };
} // namespace apx::system

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property(nonatomic, assign) std::shared_ptr<apx::system::AppDelegateHandler> system_handler;
- (instancetype)initWithSystem:(apx::system::System *)system;
@end

#endif // APEX_PLATFORM_APPLE
