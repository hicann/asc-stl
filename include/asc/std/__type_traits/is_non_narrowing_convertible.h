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

#ifndef CANN_ASC_STL_ASC_STD___TYPE_TRAITS_IS_NON_NARROWING_CONVERTIBLE_H
#define CANN_ASC_STL_ASC_STD___TYPE_TRAITS_IS_NON_NARROWING_CONVERTIBLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/compiler.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __asc_internal {

// Ranked-probe declval: no variadic catch-all, so both Host compilers and CCE
// aicore parsing accept the detection.
template <class T>
T&& __asc_declval(int);
template <class T>
T __asc_declval(long);
template <class T>
decltype(__asc_internal::__asc_declval<T>(0)) __asc_declval() noexcept;

// Accepts any implicitly convertible argument.
template <class T>
void __asc_accepts_implicit_conversion(T) noexcept;

template <class...>
using __asc_void_t = void;

template <class To, class From, class = void>
struct __is_non_narrowing_convertible {
    static constexpr bool value = false;
};

// Braced initialization of the destination rejects narrowing arithmetic
// conversions, so a viable implicit conversion plus a viable braced
// initialization together prove a non-narrowing conversion.
template <class To, class From>
struct __is_non_narrowing_convertible<To, From,
    __asc_void_t<decltype(__asc_internal::__asc_accepts_implicit_conversion<To>(__asc_internal::__asc_declval<From>())),
        decltype(To{__asc_internal::__asc_declval<From>()})>> {
    static constexpr bool value = true;
};

}  // namespace __asc_internal

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TYPE_TRAITS_IS_NON_NARROWING_CONVERTIBLE_H
