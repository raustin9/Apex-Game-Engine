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

#endif // APEX_PLATFORM_APPLE
