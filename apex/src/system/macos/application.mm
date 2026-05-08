#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import "application.h"

@implementation ApexApplication : NSApplication
-(instancetype)initWithSystem:(apx::system::System*)system
{
    self = [super init];
    if (self) {
        _system_handler = std::make_shared<apx::system::SystemHandler>(system);
    }

    return self;
}

-(void) sendEvent:(NSEvent *)event
{
    // TODO: handle cocoa events
    [super sendEvent:event];
}

@end

@implementation AppDelegate
-(instancetype)initWithSystem:(apx::system::System*)system
{
    self = [super init];
    if (self) {
        _system_handler = std::make_shared<apx::system::SystemHandler>(system);
    }

    return self;
}

-(void)applicationDidFinishLaunching:(NSNotification *)notification
{
    NSLog(@"ApplicationDidFinishLaunching");

    [NSEvent addLocalMonitorForEventsMatchingMask:(NSEventMaskKeyDown)
    handler:^NSEvent * _Nullable(NSEvent *event) {
        NSLog(@"KEY_DOWN");
        _system_handler->handle_key_down(apx::Key::Code::A);
        return event;
    }];
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