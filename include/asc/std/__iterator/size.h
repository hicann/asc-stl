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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_SIZE_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_SIZE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/make_signed.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Container>
CANN_ASC_STL_API constexpr auto size(const Container& value) noexcept(noexcept(value.size())) -> decltype(value.size())
{
    return value.size();
}

template <class T, size_t Size>
CANN_ASC_STL_API constexpr size_t size(const T (&)[Size]) noexcept
{
    return Size;
}

template <class Container>
CANN_ASC_STL_API constexpr auto ssize(
    const Container& value) noexcept -> common_type_t<ptrdiff_t, make_signed_t<decltype(value.size())>>
{
    using Result = common_type_t<ptrdiff_t, make_signed_t<decltype(value.size())>>;
    return static_cast<Result>(value.size());
}

template <class T, ptrdiff_t Size>
CANN_ASC_STL_API constexpr ptrdiff_t ssize(const T (&)[Size]) noexcept
{
    return Size;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_SIZE_H
