#import "window_delegate.h"

@implementation WindowDelegate
- (instancetype)initWithWindow:(apx::system::Window *)window {
    self = [super init];
    if (self) {
        NSLog(@"setting window");
        _window = window;
    }

    return self;
}

- (void)windowDidBecomeKey:(NSNotification *)notification {
    NSLog(@"Window: become key");
}

- (void)windowDidBecomeMain:(NSNotification *)notification {
    NSLog(@"Window: become main");
}

- (void)windowDidResignKey:(NSNotification *)notification {
    NSLog(@"Window: resign key");
}

- (void)windowDidResignMain:(NSNotification *)notification {
    NSLog(@"Window: resign main");
}

- (void)windowWillClose:(NSNotification *)notification
{
    NSLog(@"Window: will close");
    _window->close();
}
@end