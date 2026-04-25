#pragma once
#include "apex/system/system.h"

#if __OBJC__

@class NSAutoReleasePool;
using NSAutoReleasePoolRef = NSAutoReleasePool *;

#else

using NSAutoReleasePoolRef = void *;

#endif // __OBJC__

namespace apx::system::priv
{
    class AutoreleasePool
    {
      public:
        [[nodiscard]] explicit AutoreleasePool();
        ~AutoreleasePool();

      private:
        NSAutoReleasePoolRef m_ref;
    };
}