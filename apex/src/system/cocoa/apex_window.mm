#include "apex_window.h"
#ifdef APEX_PLATFORM_APPLE

@implementation ApexWindowData
@end

@implementation ApexWindow2

-(BOOL)canBecomeKeyWindow
{
    return YES;
}

-(BOOL)canBecomeMainWindow
{
    return YES;
}

-(void)sendEvent:(NSEvent *)event
{
    [super sendEvent:event];
}

@end

@implementation ApexWindowDelegate2

-(BOOL)windowShouldClose:(id)sender
{
    NSLog(@"windowShouldClose");
    _data.display.lock()->__dispatch_event<apx::system::DisplayClose>({});
    NSLog(@"post dispatch");
    return NO;
}

@end

#endif // APEX_PLATFORM_APPLE
