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

#ifndef CANN_ASC_STL_STD_DETAIL_IS_NON_NARROWING_CONVERTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_IS_NON_NARROWING_CONVERTIBLE_H

#include <asc/std/__asc/compiler.h>

namespace __asc_internal {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class _Tp>
CANN_ASC_STL_HOST_DEVICE _Tp&& __asc_declval(int);
template <class _Tp>
CANN_ASC_STL_HOST_DEVICE _Tp __asc_declval(long);
template <class _Tp>
CANN_ASC_STL_HOST_DEVICE decltype(__asc_internal::__asc_declval<_Tp>(0)) __asc_declval() noexcept;

// This requires a type to be implicitly convertible (also non-arithmetic)
template <class _Tp>
CANN_ASC_STL_HOST_DEVICE void __asc_accepts_implicit_conversion(_Tp) noexcept;
#else   // ^^^ device compilation ^^^ / vvv host compilation
template <class _Tp>
_Tp&& __asc_declval(int);
template <class _Tp>
_Tp __asc_declval(long);
template <class _Tp>
decltype(__asc_internal::__asc_declval<_Tp>(0)) __asc_declval() noexcept;

// This requires a type to be implicitly convertible (also non-arithmetic)
template <class _Tp>
void __asc_accepts_implicit_conversion(_Tp) noexcept;
#endif  // host compilation

template <class... _Ts>
struct __asc_make_void {
    using type = void;
};
template <class... _Ts>
using __asc_void_t = typename __asc_make_void<_Ts...>::type;

template <class _Dest, class _Source, class = void>
struct __is_non_narrowing_convertible {
    static constexpr bool value = false;
};

// This also prohibits narrowing conversion in case of arithmetic types
template <class _Dest, class _Source>
struct __is_non_narrowing_convertible<_Dest, _Source,
    __asc_void_t<decltype(__asc_internal::__asc_accepts_implicit_conversion<_Dest>(
                     __asc_internal::__asc_declval<_Source>())),
        decltype(_Dest{__asc_internal::__asc_declval<_Source>()})>> {
    static constexpr bool value = true;
};
}  // namespace __asc_internal

#endif  // CANN_ASC_STL_STD_DETAIL_IS_NON_NARROWING_CONVERTIBLE_H
