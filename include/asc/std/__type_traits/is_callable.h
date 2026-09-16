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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CALLABLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CALLABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_valid_expansion.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Func, class... Args>
using __call_result_t = decltype(asc::std::declval<Func>()(asc::std::declval<Args>()...));

template <class Func, class... Args>
struct __is_callable : _IsValidExpansion<__call_result_t, Func, Args...> {};

template <class Func, class... Args>
inline constexpr bool __is_callable_v = _IsValidExpansion<__call_result_t, Func, Args...>::value;

namespace detail {
template <class Func, class... Args>
using __if_nothrow_callable_t =
    asc::std::enable_if_t<noexcept(asc::std::declval<Func>()(asc::std::declval<Args>()...))>;
}  // namespace detail

template <class Func, class... Args>
struct __is_nothrow_callable : _IsValidExpansion<detail::__if_nothrow_callable_t, Func, Args...> {};

template <class Func, class... Args>
inline constexpr bool __is_nothrow_callable_v =
    _IsValidExpansion<detail::__if_nothrow_callable_t, Func, Args...>::value;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CALLABLE_H
