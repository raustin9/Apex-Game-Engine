#pragma once
#include "apex/core/core.h"
#include "apex/system/display_server.h"
#include "apex/system/system.h"
#ifdef APEX_PLATFORM_APPLE

#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>

#include <memory>

@interface ApexWindow2 : NSWindow <NSDraggingDestination>
- (BOOL)canBecomeKeyWindow;
- (BOOL)canBecomeMainWindow;
- (void)sendEvent:(NSEvent *)event;
@end

@interface                                                       ApexWindowData : NSObject
@property(nonatomic, assign) std::weak_ptr<apx::system::Display> display;
@property(nonatomic, assign) ApexWindow2                        *window;
@end

@interface                                 ApexWindowDelegate : NSResponder <NSWindowDelegate>
// Similar to SDL https://github.com/libsdl-org/SDL/blob/main/src/video/cocoa/SDL_cocoawindow.h
// this is a weak
@property(nonatomic, weak) ApexWindowData *data;

@end

#endif // APEX_PLATFORM_APPLE
