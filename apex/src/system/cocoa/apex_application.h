#pragma once
#include "apex/core/core.h"
#include "apex/system/system.h"
#ifdef APEX_PLATFORM_APPLE

#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>

@interface ApexApplicationData : NSObject
@property(nonatomic, assign) std::weak_ptr<apx::system::DisplayServer> display_server;
@end

@interface                                        ApexApplication : NSApplication
@property(nonatomic, assign) ApexApplicationData *data;

- (instancetype)initWithData:(ApexApplicationData *)data;
- (void)terminate:(id)sender;
@end

#endif // APEX_PLATFORM_APPLE
