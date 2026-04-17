#pragma once

#include <rtl/expected.h>

namespace apx
{
    // Alias of the rtl::expected class
    template <typename T, typename E>
    using expected = rtl::expected<T, E>;

    // Alias of the rtl::unexpected class
    template <typename E>
    using unexpected = rtl::unexpected<E>;
} // namespace apx