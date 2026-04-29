#pragma once
#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE
#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <Quartz/Quartz.h>

@interface                                        AppDelegate : NSObject <NSApplicationDelegate>
@property(nonatomic, assign) apx::system::System *system;
- (instancetype)initWithSystem:(apx::system::System *)system;
@end

#endif // APEX_PLATFORM_APPLE
