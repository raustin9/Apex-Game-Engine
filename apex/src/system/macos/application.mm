#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import "application.h"

#include <limits>

namespace apx::system
{

void
SystemHandler::handle_cocoa_event(NSEvent *event) noexcept
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
//            NSLog(@"mouse event");
            break;
        case NSEventTypeKeyDown:
        case NSEventTypeKeyUp:
            handle_cocoa_key_event(event);
            break;
        default:
            break;
    }
}

void SystemHandler::handle_cocoa_key_event(NSEvent *event) noexcept
{
    const ScanCode scan_code = [event keyCode];
    const Key key{ translate_key(scan_code) };

    switch ([event type])
    {
        case NSEventTypeKeyDown:
            // Only handle if the key is not already down
            if (![event isARepeat])
            {
                NSLog(@"KEY DOWN: %s", key.c_str());
            }
            break;
        case NSEventTypeKeyUp:
                NSLog(@"KEY UP: %s", key.c_str());
            break;
        default:
            break;
    }
}

Key::Code SystemHandler::translate_key(const ScanCode scan_code) noexcept
{
    switch (scan_code)
    {
        /* Lexical */
        case 0:
            return Key::Code::A;
        case 11:
            return Key::Code::B;
        case 8:
            return Key::Code::C;
        case 2:
            return Key::Code::D;
        case 14:
            return Key::Code::E;
        case 3:
            return Key::Code::F;
        case 5:
            return Key::Code::G;
        case 4:
            return Key::Code::H;
        case 34:
            return Key::Code::I;
        case 38:
            return Key::Code::J;
        case 40:
            return Key::Code::K;
        case 37:
            return Key::Code::L;
        case 46:
            return Key::Code::M;
        case 45:
            return Key::Code::N;
        case 31:
            return Key::Code::O;
        case 35:
            return Key::Code::P;
        case 12:
            return Key::Code::Q;
        case 15:
            return Key::Code::R;
        case 1:
            return Key::Code::S;
        case 17:
            return Key::Code::T;
        case 32:
            return Key::Code::U;
        case 9:
            return Key::Code::V;
        case 13:
            return Key::Code::W;
        case 7:
            return Key::Code::X;
        case 16:
            return Key::Code::Y;
        case 6:
            return Key::Code::Z;

        /* Numbers */
        case 18:
            return Key::Code::Num1;
        case 19:
            return Key::Code::Num2;
        case 20:
            return Key::Code::Num3;
        case 21:
            return Key::Code::Num4;
        case 23:
            return Key::Code::Num5;
        case 22:
            return Key::Code::Num6;
        case 26:
            return Key::Code::Num7;
        case 28:
            return Key::Code::Num8;
        case 25:
            return Key::Code::Num9;
        case 29:
            return Key::Code::Num0;

        /* Special Keys */
        case 49:
            return Key::Code::Space;
        case 36:
            return Key::Code::Enter;
        case 48:
            return Key::Code::Tab;
        case 51:
            return Key::Code::Backspace;
        case 53:
            return Key::Code::Esc;
        case 55:
            return Key::Code::LeftSystem;
        case 56:
            return Key::Code::LeftShift;
//        case 57:
//            return Key::Code::CapsLock;
        case 59:
            return Key::Code::LeftCtrl;
//        case 63:
//            return Key::Code::Fn;

        default:
            break;
    }

    return Key::Code::Unknown;
}

} // namespace apx::system

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