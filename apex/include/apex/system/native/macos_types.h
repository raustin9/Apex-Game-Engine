#pragma once
#include "apex/system/system_detection.h"

#ifdef APEX_PLATFORM_APPLE

#ifdef __OBJC__
#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <Quartz/Quartz.h>
#define OBJC_TYPE(Type) Type *
#else
#define OBJC_TYPE(Type) void *
#endif

#endif // APEX_PLATFORM_APPLE
