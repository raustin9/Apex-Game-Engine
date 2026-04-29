#pragma once
#include "apex/core/core.h"

namespace apx
{
    template <typename E>
    concept ValidEvent = traits::POD<E>;
} // namespace apx