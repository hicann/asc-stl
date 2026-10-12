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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_REVERSE_ACCESS_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_REVERSE_ACCESS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class C>
CANN_ASC_STL_API constexpr auto rbegin(C& value) noexcept(noexcept(value.rbegin())) -> decltype(value.rbegin())
{
    return value.rbegin();
}
template <class C>
CANN_ASC_STL_API constexpr auto rbegin(const C& value) noexcept(noexcept(value.rbegin())) -> decltype(value.rbegin())
{
    return value.rbegin();
}
template <class T, size_t N>
CANN_ASC_STL_API constexpr reverse_iterator<T*> rbegin(T (&array)[N]) noexcept
{
    return reverse_iterator<T*>(array + N);
}
template <class C>
CANN_ASC_STL_API constexpr auto rend(C& value) noexcept(noexcept(value.rend())) -> decltype(value.rend())
{
    return value.rend();
}
template <class C>
CANN_ASC_STL_API constexpr auto rend(const C& value) noexcept(noexcept(value.rend())) -> decltype(value.rend())
{
    return value.rend();
}
template <class T, size_t N>
CANN_ASC_STL_API constexpr reverse_iterator<T*> rend(T (&array)[N]) noexcept
{
    return reverse_iterator<T*>(array);
}
template <class C>
CANN_ASC_STL_API constexpr auto crbegin(const C& value) noexcept(
    noexcept(::asc::std::rbegin(value))) -> decltype(::asc::std::rbegin(value))
{
    return ::asc::std::rbegin(value);
}
template <class C>
CANN_ASC_STL_API constexpr auto crend(const C& value) noexcept(
    noexcept(::asc::std::rend(value))) -> decltype(::asc::std::rend(value))
{
    return ::asc::std::rend(value);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_REVERSE_ACCESS_H
