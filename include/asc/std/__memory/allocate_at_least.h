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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_ALLOCATE_AT_LEAST_H
#define CANN_ASC_STL_ASC_STD___MEMORY_ALLOCATE_AT_LEAST_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__memory/allocator_traits.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

// C++23 allocation vocabulary delivered at the C++17 baseline: the caller
// provides an allocator that is valid in the calling execution space and
// reads the returned pointer/count pair without any owning promise.
template <class Pointer, class SizeType = asc::std::size_t>
struct allocation_result {
    Pointer ptr;
    SizeType count;
};

template <class Allocator, class SizeType, class = void>
struct __allocator_has_allocate_at_least : false_type {};
template <class Allocator, class SizeType>
struct __allocator_has_allocate_at_least<Allocator, SizeType,
    void_t<decltype(declval<Allocator&>().allocate_at_least(declval<SizeType>()))>> : true_type {};

template <class Allocator>
CANN_ASC_STL_API constexpr allocation_result<typename allocator_traits<Allocator>::pointer,
    typename allocator_traits<Allocator>::size_type>
allocator_traits<Allocator>::allocate_at_least(Allocator& allocator, size_type count)
{
    if constexpr (__allocator_has_allocate_at_least<Allocator, size_type>::value) {
        auto result = allocator.allocate_at_least(count);
        return {result.ptr, result.count};
    } else {
        return {allocator_traits::allocate(allocator, count), count};
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_ALLOCATE_AT_LEAST_H
