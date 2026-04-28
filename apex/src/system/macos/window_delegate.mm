#import "window_delegate.h"

#include "apex/core/core.h"

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

//- (void)windowDidResize:(NSNotification *)notification {
//    NSWindow *window = notification.object;
//
//    if (!window.contentView) return;
//    NSSize new_size = window.contentLayoutRect.size;
//    NSLog(@"Window resized: %f, %f", new_size.width, new_size.height);
//    _window->__resize_callback(
//        apx::Extent2D_u32 {
//            .width = apx::Width_u32(static_cast<std::uint32_t>(new_size.width)),
//            .height = apx::Height_u32(static_cast<std::uint32_t>(new_size.height)),
//        }
//    );
//}

- (void)windowDidEndLiveResize:(NSNotification *)notification {
    NSWindow *window = notification.object;

    if (!window.contentView) return;
    NSSize new_size = window.contentLayoutRect.size;
    NSLog(@"Window resized: %f, %f", new_size.width, new_size.height);
    _window->__resize_callback(
        apx::Extent2D_u32 {
            .width = apx::Width_u32(static_cast<std::uint32_t>(new_size.width)),
            .height = apx::Height_u32(static_cast<std::uint32_t>(new_size.height)),
        }
    );
}

- (void)windowWillClose:(NSNotification *)notification
{
    NSLog(@"Window: will close");
    _window->close();
}
@end