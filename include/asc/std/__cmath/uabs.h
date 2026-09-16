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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_UABS_H
#define CANN_ASC_STL_ASC_STD___CMATH_UABS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__cmath/neg.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct __uabs_type;
template <>
struct __uabs_type<char> {
    using type = unsigned char;
};
template <>
struct __uabs_type<signed char> {
    using type = unsigned char;
};
template <>
struct __uabs_type<unsigned char> {
    using type = unsigned char;
};
template <>
struct __uabs_type<short> {
    using type = unsigned short;
};
template <>
struct __uabs_type<unsigned short> {
    using type = unsigned short;
};
template <>
struct __uabs_type<int> {
    using type = unsigned int;
};
template <>
struct __uabs_type<unsigned int> {
    using type = unsigned int;
};
template <>
struct __uabs_type<long> {
    using type = unsigned long;
};
template <>
struct __uabs_type<unsigned long> {
    using type = unsigned long;
};
template <>
struct __uabs_type<long long> {
    using type = unsigned long long;
};
template <>
struct __uabs_type<unsigned long long> {
    using type = unsigned long long;
};

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr typename __uabs_type<T>::type __uabs(T value) noexcept
{
    using U = typename __uabs_type<T>::type;
    return value < T(0) ? static_cast<U>(__neg(value)) : static_cast<U>(value);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_UABS_H
