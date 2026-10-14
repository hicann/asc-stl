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

#ifndef CANN_ASC_STL_ASC_STD___LINALG_CONJ_IF_NEEDED_H
#define CANN_ASC_STL_ASC_STD___LINALG_CONJ_IF_NEEDED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/complex>

namespace asc::std::linalg {
namespace __conj_if_needed {

// Whether a qualified ::asc::std::conj is viable for T (ADL conj is
// deliberately not searched).
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class T>
inline constexpr bool _HasConj = requires(const T& value) { static_cast<void>(::asc::std::conj(value)); };
#else
template <class T, class = void>
inline constexpr bool __has_conj_impl = false;

template <class T>
inline constexpr bool
    __has_conj_impl<T, void_t<decltype(static_cast<void>(::asc::std::conj(::asc::std::declval<const T&>())))> > = true;

template <class T>
inline constexpr bool _HasConj = __has_conj_impl<T>;
#endif

struct __conj_if_needed {
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(const T& value) const
    {
        // Arithmetic types are short-circuited first: evaluating _HasConj for an
        // arithmetic T would instantiate this library's float-only complex<T>
        // (the scalar overload of ::asc::std::conj returns complex<T>), causing
        // a hard error.
        if constexpr (is_arithmetic_v<T>) {
            return value;
        } else if constexpr (!_HasConj<T>) {
            return value;
        } else {
            return ::asc::std::conj(value);
        }
    }
};

}  // namespace __conj_if_needed

inline constexpr __conj_if_needed::__conj_if_needed conj_if_needed{};

}  // namespace asc::std::linalg

#endif  // CANN_ASC_STL_ASC_STD___LINALG_CONJ_IF_NEEDED_H
