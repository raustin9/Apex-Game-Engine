#pragma once
#include "apex/core/core.h"
#include "apex/system/system.h"
#ifdef APEX_PLATFORM_APPLE

#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>

@interface                                                          ApexApplicationData : NSObject
@property(nonatomic, assign) std::weak_ptr<apx::sys::DisplayServer> display_server;
@end

@interface                                        ApexApplication2 : NSApplication
@property(nonatomic, assign) ApexApplicationData *data;

- (instancetype)initWithData:(ApexApplicationData *)data;
- (void)terminate:(id)sender;
- (void)sendEvent:(NSEvent *)event;
@end

#endif // APEX_PLATFORM_APPLE
