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

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_valid_expansion.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Func, class... _Args>
using __call_result_t = decltype(::asc::std::declval<_Func>()(::asc::std::declval<_Args>()...));

template <class _Func, class... _Args>
struct __is_callable : _IsValidExpansion<__call_result_t, _Func, _Args...> {};

template <class _Func, class... _Args>
inline constexpr bool __is_callable_v = _IsValidExpansion<__call_result_t, _Func, _Args...>::value;

namespace detail {
template <class _Func, class... _Args>
using __if_nothrow_callable_t =
    ::asc::std::enable_if_t<noexcept(::asc::std::declval<_Func>()(::asc::std::declval<_Args>()...))>;
}  // namespace detail

template <class _Func, class... _Args>
struct __is_nothrow_callable : _IsValidExpansion<detail::__if_nothrow_callable_t, _Func, _Args...> {};

template <class _Func, class... _Args>
inline constexpr bool __is_nothrow_callable_v =
    _IsValidExpansion<detail::__if_nothrow_callable_t, _Func, _Args...>::value;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CALLABLE_H
