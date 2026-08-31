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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DISJUNCTION_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DISJUNCTION_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <bool>
struct _OrImpl;

template <>
struct _OrImpl<true> {
    template <class _Res, class _First, class... _Rest>
    using _Result = typename _OrImpl<!bool(_First::value) &&  // NOLINT(readability/casting)
        sizeof...(_Rest) != 0>::template _Result<_First,      // NOLINT(readability/casting)
        _Rest...>;                                            // NOLINT(readability/casting)
};

template <>
struct _OrImpl<false> {
    template <class _Res, class...>
    using _Result = _Res;
};

// _Or always performs lazy evaluation of its arguments.
//
// However, `_Or<_Pred...>` itself will evaluate its result immediately (without having to
// be instantiated) since it is an alias, unlike `disjunction<_Pred...>`, which is a struct.
// If you want to defer the evaluation of `_Or<_Pred...>` itself, use `_Lazy<_Or, _Pred...>`
// or `disjunction<_Pred...>` directly.
template <class... _Args>
using _Or = typename _OrImpl<sizeof...(_Args) != 0>::template _Result<false_type, _Args...>;

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)
template <class... _Args>
struct disjunction : false_type {};

template <class _First, class... _Rest>
struct disjunction<_First, _Rest...> : _OrImpl<true>::template _Result<false_type, _First, _Rest...> {};
#else
template <class... _Args>
struct disjunction : _Or<_Args...> {};
#endif  // !CANN_ASC_STL_DETAIL_COMPILER(MSVC)

template <class... _Args>
inline constexpr bool disjunction_v = _Or<_Args...>::value;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DISJUNCTION_H
