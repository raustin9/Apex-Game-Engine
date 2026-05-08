#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import "application.h"

void
apx::system::SystemHandler::handle_cocoa_event(NSEvent *event) noexcept
{
    switch ([event type])
    {
        case NSEventTypeLeftMouseDown:
        case NSEventTypeRightMouseDown:
        case NSEventTypeLeftMouseUp:
        case NSEventTypeRightMouseUp:
        case NSEventTypeLeftMouseDragged:
        case NSEventTypeRightMouseDragged:
        case NSEventTypeOtherMouseDragged:
        case NSEventTypeMouseMoved:
        case NSEventTypeScrollWheel:
        case NSEventTypeMouseEntered:
        case NSEventTypeMouseExited:
            NSLog(@"mouse event");
            break;
        case NSEventTypeKeyDown:
        case NSEventTypeKeyUp:
            NSLog(@"key event");
            break;
        default:
            break;
    }
}

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
    _system_handler->handle_cocoa_event(event);
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