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
    _data.display.lock()->__dispatch_event<apx::system::DisplayClose>({});
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

-(void)windowDidMove:(NSNotification *)notification
{
    NSPoint new_origin = [self.data.window frame].origin;
    self.data.display.lock()->__dispatch_event(apx::system::DisplayMoved{ apx::Point2D_u32(new_origin.x, new_origin.y) });
}

-(void)windowDidResize:(NSNotification *)notification
{
    NSWindow *ns_window = self.data.window;
    NSRect rect = [[ns_window contentView] frame];
    NSRect converted_rect = [self convertRect:rect];

    self.data.display.lock()->__handle_resize(apx::Width_u32(converted_rect.size.width), apx::Height_u32(converted_rect.size.height));
}

-(NSRect)convertRect:(NSRect)rect
{
    NSRect converted_rect = rect;

    converted_rect.origin.y = self.data.display.lock()->inner_height() - rect.origin.y - rect.size.height;
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

// Handles the mouse move for a content view for a window
- (void)mouseMoved:(NSEvent *)event
{
    NSPoint position = event.locationInWindow;

    self.data.display.lock()->__handle_mouse_move(position.x, position.y);
}

// Handles the key down for a content view for a window
- (void)keyDown:(NSEvent *)event
{
    if ([event isARepeat])
        return;

    self.data.display.lock()->__handle_key(
        apx::system::translate_key([event keyCode]),
        apx::system::KeyState::DOWN
    );
}

// Handles the key up for a content view for a window
- (void)keyUp:(NSEvent *)event
{
    self.data.display.lock()->__handle_key(
        apx::system::translate_key([event keyCode]),
        apx::system::KeyState::UP
    );
}

@end

#endif // APEX_PLATFORM_APPLE
