#pragma once
#include "apex/core/core.h"

namespace apx
{
    /// @brief Used for defining a set/list of events
    template <typename... Events>
    using EventList = TypeList<Events...>;
} // namespace apx