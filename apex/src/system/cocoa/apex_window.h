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

@interface                                                    ApexWindowData : NSObject
@property(nonatomic, assign) std::weak_ptr<apx::sys::Display> display;
@property(nonatomic, strong) NSWindow                        *window;
@end
// @property(nonatomic, strong) NSView                             *content_view;

@interface                                   ApexWindowDelegate2 : NSResponder <NSWindowDelegate>
// Similar to SDL https://github.com/libsdl-org/SDL/blob/main/src/video/cocoa/SDL_cocoawindow.h
// this is a weak
@property(nonatomic, assign) ApexWindowData *data;

- (void)setupListeners;

@end

@interface                                   ApexView : NSView
@property(nonatomic, assign) ApexWindowData *data;

- (instancetype)initWithFrameAndData:(NSRect)frame withData:(ApexWindowData *)data;
- (BOOL)acceptsFirstResponder;
- (void)mouseMoved:(NSEvent *)event;
@end

#endif // APEX_PLATFORM_APPLE
