#pragma once
#include "dimension.h"
#include "traits.h"

namespace apx
{
    template <traits::Numeric N>
    struct Width : Dimension<N>
    {
        explicit Width(N width) : Dimension<N>(width) {}
    };

    template <traits::Numeric N>
    struct Height : Dimension<N>
    {
        explicit Height(N height) : Dimension<N>(height) {}
    };

    template <traits::Numeric N1, traits::Numeric N2>
    struct Extent2D
    {
        Width<N1>  width;
        Height<N2> height;
    };
}