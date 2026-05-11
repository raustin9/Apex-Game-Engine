#include "apex_window.h"
#include "keyboard.h"

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

-(void)setupListeners
{
    NSNotificationCenter *notification_center;
    NSWindow *window = self.data.window;

    notification_center = [NSNotificationCenter defaultCenter];

    if ([window delegate] != nil)
    {
//        [notification_center addObserver:self selector:@selector()];
    }
}

@end

@implementation ApexView
- (instancetype)initWithFrameAndData:(NSRect)frame withData:(ApexWindowData *)data
{
    self = [super initWithFrame:frame];

    if (self)
    {
        _data = data;
    }

    return self;
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)mouseMoved:(NSEvent *)event
{
    NSPoint position = event.locationInWindow;

    self.data.display.lock()->__dispatch_event(apx::system::MouseMoved{
        .position = apx::Vec2u(position.x, position.y)
    });
}

- (void)keyDown:(NSEvent *)event
{
    if ([event isARepeat])
        return;

    apx::Key key = apx::system::translate_key([event keyCode]);
    self.data.display.lock()->__dispatch_event(apx::system::KeyDown{ .key = key });
}

- (void)keyUp:(NSEvent *)event
{
    if ([event isARepeat])
        return;

    apx::Key key = apx::system::translate_key([event keyCode]);
    self.data.display.lock()->__dispatch_event(apx::system::KeyUp{ .key = key });
}

@end

#endif // APEX_PLATFORM_APPLE
