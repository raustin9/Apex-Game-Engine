#pragma once
#include "apex/system/system_detection.h"

#ifdef APEX_PLATFORM_APPLE

#ifdef __OBJC__
#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <Quartz/Quartz.h>
#define OBJC_TYPE(Type) Type *

#define FORWARD_OBJC_TYPE(Type) @class Type
#else
#define OBJC_TYPE(Type) void *
#define FORWARD_OBJC_TYPE(Type)
#endif

#endif // APEX_PLATFORM_APPLE
