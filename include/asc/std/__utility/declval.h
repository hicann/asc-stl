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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_DECLVAL_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_DECLVAL_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// Handy in concept definitions for turning:
//   requires (T&& t) { ... std::forward<T>(t) ...; }
// into:
//   requires (__declfn_t<T> t) { ... t() ...; }
//
// NOTE: Unlike std::declval, the return type of __declfn_t is not
// rvalue-reference-qualified. In most cases this does not matter, except when _Tp is an
// incomplete class type. In places where that matters, use __declfn_t<_Tp&&> instead of
// __declfn_t<_Tp>.
template <class _Tp, bool _Noexcept = true>
using __declfn_t = _Tp (*)() noexcept(_Noexcept);

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !CANN_ASC_STL_DETAIL_COMPILER(MSVC, <, 19, 39)

// When variable templates and noexcept function types are available, a faster
// implementation of declval is available. It compiles approximately 2x faster
// than the fallback. The use of the `__declfn_t` alias helps MSVC parse the
// declaration correctly.
template <class _Tp, class = void>
extern __declfn_t<void> declval;

template <class _Tp>
extern __declfn_t<_Tp&&> declval<_Tp, void_t<_Tp&&>>;

#else  // ^^^ fast declval ^^^ / vvv default impl vvv

// Suppress deprecation notice for volatile-qualified return type resulting
// from volatile-qualified types _Tp.
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
template <class _Tp>
CANN_ASC_STL_API _Tp&& __declval(int);
template <class _Tp>
CANN_ASC_STL_API _Tp __declval(long);
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

template <class _Tp>
CANN_ASC_STL_API decltype(::asc::std::__declval<_Tp>(0)) declval() noexcept;

#endif  // default impl

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_DECLVAL_H
