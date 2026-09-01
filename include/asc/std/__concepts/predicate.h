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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_PREDICATE_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_PREDICATE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/boolean_testable.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Fn, class... _Args>
concept predicate = regular_invocable<_Fn, _Args...> && __boolean_testable<invoke_result_t<_Fn, _Args...>>;
#else
template <class _Fn, class _Void, class... _Args>
inline constexpr bool __predicate_impl = false;

template <class _Fn, class... _Args>
inline constexpr bool __predicate_impl<_Fn, void_t<invoke_result_t<_Fn, _Args...>>, _Args...> =
    regular_invocable<_Fn, _Args...> && __boolean_testable<invoke_result_t<_Fn, _Args...>>;

template <class _Fn, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT predicate = __predicate_impl<_Fn, void, _Args...>;
#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_PREDICATE_H
