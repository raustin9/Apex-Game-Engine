#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import "app_delegate.h"

using CallbackUserData = apx::system::System;

static CVReturn display_link_callback(
    CVDisplayLinkRef display_link,
    const CVTimeStamp *now,
    const CVTimeStamp *output_time,
    CVOptionFlags flags_in,
    CVOptionFlags flags_out,
    void *user_data
) {
    return kCVReturnSuccess;
}

@implementation AppDelegate
-(instancetype)initWithSystem:(apx::system::System*)system
{
    self = [super init];
    if (self) {
        _system = system;
    }

    return self;
}

-(void)applicationDidFinishLaunching:(NSNotification *)notification
{
    NSLog(@"ApplicationDidFinishLaunching");
}

-(void)applicationWillTerminate:(NSApplication*)application
{
    NSLog(@"ApplicationWillTerminate");
}

-(void)tick:(CADisplayLink*)sender
{

}
@end

#endif // APEX_PLATFORM_APPLE
