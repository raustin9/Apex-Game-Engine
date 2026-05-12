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
    }
}

-(void)windowDidResize:(NSNotification *)notification
{
    NSWindow *ns_window = self.data.window;
    NSRect rect = [ns_window frame];
    NSRect converted_rect = [self convertRect:rect];

    self.data.display.lock()->__handle_resize(apx::Width_u32(converted_rect.size.width), apx::Height_u32(converted_rect.size.height));
}

-(NSRect)convertRect:(NSRect)rect
{
    NSRect converted_rect = rect;

    converted_rect.origin.y = self.data.display.lock()->current_height() - rect.origin.y - rect.size.height;
    return converted_rect;
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

    self.data.display.lock()->__handle_mouse_move(position.x, position.y);
}

- (void)keyDown:(NSEvent *)event
{
    if ([event isARepeat])
        return;

    apx::Key key = apx::system::translate_key([event keyCode]);
    self.data.display.lock()->__handle_key(key.code(), apx::system::KeyState::DOWN);
}

- (void)keyUp:(NSEvent *)event
{
    if ([event isARepeat])
        return;

    apx::Key key = apx::system::translate_key([event keyCode]);
    self.data.display.lock()->__handle_key(key.code(), apx::system::KeyState::UP);
}

@end

#endif // APEX_PLATFORM_APPLE
