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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_RBEGIN_H
#define CANN_ASC_STL_ASC_STD___RANGES_RBEGIN_H

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
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/auto_cast.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
namespace __rbegin_detail {
template <class T>
CANN_ASC_STL_API constexpr auto call(T&& value, int) -> decltype(static_cast<T&&>(value).rbegin())
{
    return static_cast<T&&>(value).rbegin();
}
template <class T>
CANN_ASC_STL_API constexpr auto call(
    T&& value, long) -> reverse_iterator<decltype(ranges::end(static_cast<T&&>(value)))>
{
    return reverse_iterator<decltype(ranges::end(static_cast<T&&>(value)))>(ranges::end(static_cast<T&&>(value)));
}
struct __fn {
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const -> decltype(call(static_cast<T&&>(value), 0))
    {
        return call(static_cast<T&&>(value), 0);
    }
};
}  // namespace __rbegin_detail
inline constexpr __rbegin_detail::__fn rbegin{};
struct __crbegin_fn {
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T& value) const -> decltype(rbegin(static_cast<const T&>(value)))
    {
        return rbegin(static_cast<const T&>(value));
    }
};
inline constexpr __crbegin_fn crbegin{};
}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_RBEGIN_H
