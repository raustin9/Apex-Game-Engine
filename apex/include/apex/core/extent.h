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

    template <traits::Numeric WidthT, traits::Numeric HeightT = WidthT>
    struct Extent2D
    {
        Width<WidthT>   width;
        Height<HeightT> height;
    };

    using Extent2D_u32 = Extent2D<std::uint32_t>;
    using Extent2D_i32 = Extent2D<std::int32_t>;
    using Extent2D_f32 = Extent2D<float>;
    using Extent2D_f64 = Extent2D<double>;

    template <traits::Numeric WidthT, traits::Numeric HeightT, traits::Numeric ZT>
    struct Extent3D
    {
        Width<WidthT>   width;
        Height<HeightT> height;
        Dimension<ZT>   z;
    };

    using Width_f32 = Width<float>;
    using Width_f64 = Width<double>;
    using Width_i32 = Width<int32_t>;
    using Width_i64 = Width<int64_t>;
    using Width_u8  = Width<uint8_t>;
    using Width_u16 = Width<uint16_t>;
    using Width_u32 = Width<uint32_t>;
    using Width_u64 = Width<uint64_t>;

    using Height_f32 = Height<float>;
    using Height_f64 = Height<double>;
    using Height_i32 = Height<int32_t>;
    using Height_i64 = Height<int64_t>;
    using Height_u8  = Height<uint8_t>;
    using Height_u16 = Height<uint16_t>;
    using Height_u32 = Height<uint32_t>;
    using Height_u64 = Height<uint64_t>;

    template <traits::Numeric N>
    struct Point2D
    {
        Dimension<N> x;
        Dimension<N> y;

        // TODO: math?
    };

    template <traits::Numeric N>
    struct Point3D
    {
        Dimension<N> x;
        Dimension<N> y;
        Dimension<N> z;

        // TODO: math?
    };

    template <traits::Numeric N>
    struct Vec2 : Point2D<N>
    {
    };

    using Vec2f32 = Vec2<float>;
    using Vec2f64 = Vec2<double>;

    using Vec2u32 = Vec2<std::uint32_t>;
    using Vec2u64 = Vec2<std::uint64_t>;
    using Vec2i32 = Vec2<std::int32_t>;
    using Vec2i64 = Vec2<std::int64_t>;

    using Vec2f = Vec2f32;
    using Vec2u = Vec2u32;
    using Vec2i = Vec2i32;
} // namespace apx