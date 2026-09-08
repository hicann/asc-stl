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
#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_TUPLE_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_TUPLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct __get_complex_impl {
    template <size_t Index>
    CANN_ASC_STL_API static constexpr T& get(complex<T>& value) noexcept
    {
        static_assert(Index < 2, "complex index out of range");
        return Index == 0 ? value.real_ : value.imag_;
    }
    template <size_t Index>
    CANN_ASC_STL_API static constexpr const T& get(const complex<T>& value) noexcept
    {
        static_assert(Index < 2, "complex index out of range");
        return Index == 0 ? value.real_ : value.imag_;
    }
};
template <size_t Index, class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T& get(complex<T>& value) noexcept
{
    return __get_complex_impl<T>::template get<Index>(value);
}
template <size_t Index, class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr const T& get(const complex<T>& value) noexcept
{
    return __get_complex_impl<T>::template get<Index>(value);
}
template <size_t Index, class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T&& get(complex<T>&& value) noexcept
{
    return ::asc::std::move(get<Index>(value));  // NOLINT(build/include_what_you_use)
}
template <size_t Index, class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr const T&& get(const complex<T>&& value) noexcept
{
    return ::asc::std::move(get<Index>(value));  // NOLINT(build/include_what_you_use)
}
template <class T>
struct tuple_size<complex<T>> : integral_constant<size_t, 2> {};
template <size_t Index, class T>
struct tuple_element<Index, complex<T>> {
    static_assert(Index < 2, "complex index out of range");
    using type = T;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_TUPLE_H
