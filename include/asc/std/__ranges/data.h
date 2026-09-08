/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_DATA_H
#define CANN_ASC_STL_ASC_STD___RANGES_DATA_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/auto_cast.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
namespace __data_detail {
template <class T>
CANN_ASC_STL_API constexpr auto __select(T& value, int) noexcept(noexcept(value.data())) -> decltype(value.data())
{
    return value.data();
}
template <class T>
CANN_ASC_STL_API constexpr auto __select(T& value, long) noexcept(
    noexcept(ranges::begin(value))) -> decltype(ranges::begin(value))
{
    return ranges::begin(value);
}
struct __fn {
    template <class T, size_t N>
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[N]) const noexcept
    {
        return array;
    }
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T& value) const
        noexcept(noexcept(__select(value, 0))) -> decltype(__select(value, 0))
    {
        return __select(value, 0);
    }
};
}  // namespace __data_detail
inline constexpr __data_detail::__fn data{};
namespace __cdata_detail {
struct __fn {
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T& value) const noexcept(
        noexcept(ranges::data(static_cast<const T&>(value)))) -> decltype(ranges::data(static_cast<const T&>(value)))
    {
        return ranges::data(static_cast<const T&>(value));
    }
};
}  // namespace __cdata_detail
inline constexpr __cdata_detail::__fn cdata{};
}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_DATA_H
