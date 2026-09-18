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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_CONJUNCTION_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_CONJUNCTION_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class...>
using __expand_to_true = true_type;

template <class... _Pred>
CANN_ASC_STL_HOST_DEVICE __expand_to_true<enable_if_t<_Pred::value>...> __and_helper(int);

template <class...>
CANN_ASC_STL_HOST_DEVICE false_type __and_helper(long);

// _And always performs lazy evaluation of its arguments.
//
// However, `_And<_Pred...>` itself will evaluate its result immediately (without having to
// be instantiated) since it is an alias, unlike `conjunction<_Pred...>`, which is a struct.
// If you want to defer the evaluation of `_And<_Pred...>` itself, use `_Lazy<_And, _Pred...>`.
template <class... _Pred>
using _And = decltype(__and_helper<_Pred...>(0));

template <class...>
struct conjunction : true_type {};

template <class _Arg>
struct conjunction<_Arg> : _Arg {};

template <class _Arg, class... _Args>
struct conjunction<_Arg, _Args...>
    : _If<!bool(_Arg::value), _Arg, conjunction<_Args...>> {  // NOLINT(readability/casting)
};  // NOLINT(readability/casting)

template <class... _Args>
inline constexpr bool conjunction_v = conjunction<_Args...>::value;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_CONJUNCTION_H
