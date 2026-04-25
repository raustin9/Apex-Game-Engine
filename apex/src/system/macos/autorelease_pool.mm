#include "apex/system/system.h"
#include "autorelease_pool.h"

#ifdef APEX_PLATFORM_APPLE
#import <Foundation/Foundation.h>

namespace apx::system::priv
{
    AutoreleasePool::AutoreleasePool() {
        m_ref = [[NSAutoReleasePool alloc] init];
    }

    AutoreleasePool::~AutoreleasePool() {
        [m_ref release];
    }
} // namespace apx::system::priv

#endif // APEX_PLATFORM_APPLE
