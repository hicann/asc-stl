/*
 * Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CANN_ASC_STL_ASC___UTILITY_STATIC_FOR_H
#define CANN_ASC_STL_ASC___UTILITY_STATIC_FOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/climits>
#include <asc/std/cstdint>

namespace asc::detail {

template <class T>
inline constexpr bool utility_index_type_v =
    asc::std::is_same_v<T, signed char> || asc::std::is_same_v<T, unsigned char> || asc::std::is_same_v<T, short> ||
    asc::std::is_same_v<T, unsigned short> || asc::std::is_same_v<T, int> || asc::std::is_same_v<T, unsigned int> ||
    asc::std::is_same_v<T, long> || asc::std::is_same_v<T, unsigned long> || asc::std::is_same_v<T, long long> ||
    asc::std::is_same_v<T, unsigned long long>;

template <class T>
inline constexpr bool utility_range_type_v = utility_index_type_v<T> || asc::std::is_same_v<T, float> ||
    (!CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() &&
        (asc::std::is_same_v<T, double> || asc::std::is_same_v<T, long double>));

// Macro constants also work in the Host phase of pure SIMT compilation.
template <class T>
inline constexpr T utility_integer_min_v = static_cast<T>(asc::std::is_same_v<T, signed char> ? SCHAR_MIN :
        asc::std::is_same_v<T, short>                                                         ? SHRT_MIN :
        asc::std::is_same_v<T, int>                                                           ? INT_MIN :
        asc::std::is_same_v<T, long>                                                          ? LONG_MIN :
        asc::std::is_same_v<T, long long>                                                     ? LLONG_MIN :
                                                                                                0);

template <class IndexType, IndexType Value>
using static_for_index = asc::std::integral_constant<IndexType, Value>;

template <class IndexType, IndexType Start, IndexType End, IndexType Step>
struct static_for_shape {
    static_assert(Step != 0, "static_for step must be nonzero");
    using unsigned_type = asc::std::make_unsigned_t<IndexType>;
    using wide_type = asc::std::uintmax_t;
    static constexpr bool ascending = Step > 0;
    static constexpr bool active = (ascending && Start < End) || (Step < 0 && Start > End);
    // Convert back to unsigned_type after integer promotion of narrow types.
    static constexpr wide_type distance = ascending ?
        static_cast<unsigned_type>(static_cast<unsigned_type>(End) - static_cast<unsigned_type>(Start)) :
        static_cast<unsigned_type>(static_cast<unsigned_type>(Start) - static_cast<unsigned_type>(End));
    static constexpr wide_type magnitude = ascending ?
        static_cast<unsigned_type>(Step) :
        static_cast<unsigned_type>(unsigned_type{0} - static_cast<unsigned_type>(Step));
    static constexpr wide_type count = active ? wide_type{1} + (distance - wide_type{1}) / magnitude : wide_type{0};
    static_assert(count <= static_cast<asc::std::size_t>(-1), "static_for sequence is too large");
    static constexpr asc::std::size_t size = static_cast<asc::std::size_t>(count);

    template <asc::std::size_t Position>
    struct index_value {
        static_assert(Position < count, "static_for index is outside the generated sequence");
        // Position * magnitude < distance: only visited offsets are formed.
        static constexpr wide_type offset = static_cast<wide_type>(Position) * magnitude;
        static constexpr wide_type start_magnitude = Start < 0 ?
            static_cast<unsigned_type>(unsigned_type{0} - static_cast<unsigned_type>(Start)) :
            static_cast<unsigned_type>(Start);
        static constexpr bool negative =
            ascending ? Start < 0 && offset < start_magnitude : Start < 0 || offset > start_magnitude;
        static constexpr wide_type result_magnitude = ascending ?
            (Start < 0 ? (offset < start_magnitude ? start_magnitude - offset : offset - start_magnitude) :
                         start_magnitude + offset) :
            (Start < 0 ? start_magnitude + offset :
                         (offset > start_magnitude ? offset - start_magnitude : start_magnitude - offset));
        static constexpr IndexType minimum = utility_integer_min_v<IndexType>;
        static constexpr wide_type minimum_magnitude =
            static_cast<unsigned_type>(unsigned_type{0} - static_cast<unsigned_type>(minimum));
        // Never convert an out-of-range unsigned value to a signed type.
        static constexpr IndexType value = negative ?
            (result_magnitude == minimum_magnitude ?
                    minimum :
                    static_cast<IndexType>(-static_cast<IndexType>(result_magnitude))) :
            static_cast<IndexType>(result_magnitude);
    };

    template <asc::std::size_t Position>
    using index = static_for_index<IndexType, index_value<Position>::value>;
};

template <class Index, class Callable, class... Args>
CANN_ASC_STL_API constexpr void static_for_one(Callable& callable, Args&&... args) noexcept(
    noexcept(static_cast<void>(callable(Index{}, static_cast<Args&&>(args)...))))
{
    // A separate full-expression destroys each result before the next call.
    static_cast<void>(callable(Index{}, static_cast<Args&&>(args)...));
}

template <class Shape, class Callable, asc::std::size_t... Positions, class... Args>
CANN_ASC_STL_API constexpr void static_for_expand(
    Callable& callable, asc::std::index_sequence<Positions...>, Args&&... args) noexcept((true && ... &&
    noexcept(static_for_one<typename Shape::template index<Positions>>(callable, static_cast<Args&&>(args)...))))
{
    (static_for_one<typename Shape::template index<Positions>>(callable, static_cast<Args&&>(args)...), ...);
}

template <class IndexType, IndexType Start, IndexType End, IndexType Step, class Callable, class... Args>
CANN_ASC_STL_API constexpr void static_for_range(Callable&& callable, Args&&... args) noexcept(
    noexcept(static_for_expand<static_for_shape<IndexType, Start, End, Step>>(callable,
        asc::std::make_index_sequence<static_for_shape<IndexType, Start, End, Step>::size>{},
        static_cast<Args&&>(args)...)))
{
    using shape = static_for_shape<IndexType, Start, End, Step>;
    static_for_expand<shape>(callable, asc::std::make_index_sequence<shape::size>{}, static_cast<Args&&>(args)...);
}

template <class IndexType, IndexType Size, class Callable, class... Args>
CANN_ASC_STL_API constexpr void static_for_count(Callable&& callable, Args&&... args) noexcept(
    noexcept(static_for_range<IndexType, IndexType{0}, Size, IndexType{1}>(callable, static_cast<Args&&>(args)...)))
{
    static_for_range<IndexType, IndexType{0}, Size, IndexType{1}>(callable, static_cast<Args&&>(args)...);
}

template <auto Start, auto End, auto Step, class Callable>
CANN_ASC_STL_API constexpr void static_for_auto(Callable&& callable) noexcept(noexcept(
    static_for_range<decltype(Start), Start, static_cast<decltype(Start)>(End), static_cast<decltype(Start)>(Step)>(
        callable)))
{
    using IndexType = decltype(Start);
    static_for_range<IndexType, static_cast<IndexType>(Start), static_cast<IndexType>(End),
        static_cast<IndexType>(Step)>(callable);
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___UTILITY_STATIC_FOR_H
