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
#include <asc/std/complex>

namespace asc::std::linalg {
namespace __conj_detail {

template <class T>
T&& declval() noexcept;

template <class...>
using void_t = void;

template <class T>
CANN_ASC_STL_API constexpr auto adl_conj(const T& value) noexcept(noexcept(conj(value))) -> decltype(conj(value))
{
    return conj(value);
}

template <class T, class = void>
struct has_conj {
    static constexpr bool value = false;
};

template <class T>
struct has_conj<T, void_t<decltype(adl_conj(declval<const T&>()))>> {
    static constexpr bool value = true;
};

struct conj_if_needed_fn {
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(const T& value) const
    {
        if constexpr (is_arithmetic_v<T> || !has_conj<T>::value) {
            return value;
        } else {
            return adl_conj(value);
        }
    }
};

}  // namespace __conj_detail

inline constexpr __conj_detail::conj_if_needed_fn conj_if_needed{};

}  // namespace asc::std::linalg

#endif  // CANN_ASC_STL_ASC_STD___LINALG_CONJ_IF_NEEDED_H
