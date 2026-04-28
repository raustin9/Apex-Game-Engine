#include "apex/system/system.h"

#ifdef APEX_PLATFORM_APPLE

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@interface                                        WindowDelegate : NSObject <NSWindowDelegate>
@property(nonatomic, assign) apx::system::Window *window;
- (instancetype)initWithWindow:(apx::system::Window *)window;
@end
#endif // APEX_PLATFORM_APPLE
