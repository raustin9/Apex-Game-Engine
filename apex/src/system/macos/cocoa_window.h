#pragma once
#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@interface                                        WindowDelegate : NSObject <NSWindowDelegate>
@property(nonatomic, assign) apx::system::Window *window;
- (instancetype)initWithWindow:(apx::system::Window *)window;
@end

@interface ApexWindow : NSWindow <NSDraggingDestination>
- (BOOL)canBecomeKeyWindow;
- (BOOL)canBecomeMainWindow;
- (void)sendEvent:(NSEvent *)event;
- (void)doCommandBySelector:(SEL)selector;
@end

@interface ApexWindowListener : NSResponder <NSWindowDelegate>

@end
#endif // APEX_PLATFORM_APPLE
