#pragma once

#if defined(__APPLE__)
#include <TargetConditionals.h>

#if TARGET_OS_OSX
#define APEX_PLATFORM_APPLE
#endif // TARGET_OS_X

#else // TODO: more systems

#endif // __APPLE__