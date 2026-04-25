#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <Quartz/Quartz.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    CADisplayLink       *m_display_link;
    apx::system::System *m_system;
}
@end

#endif // APEX_PLATFORM_APPLE
