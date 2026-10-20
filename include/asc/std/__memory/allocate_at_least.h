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
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

// [allocator.globals]: count uses the second template parameter (defaulting
// to size_t), staying compatible with the standard allocation_result and with
// existing single-argument uses (through the default argument).
template <class Pointer, class SizeType = ::asc::std::size_t>
struct allocation_result {
    Pointer ptr;
    SizeType count;
};
CANN_ASC_STL_DETAIL_CTAD_SUPPORTED_FOR_TYPE(allocation_result);

namespace __allocate_at_least_detail {
template <class Alloc, class = void>
struct has_member : false_type {};

template <class Alloc>
struct has_member<Alloc,
    void_t<decltype(::asc::std::declval<Alloc&>().allocate_at_least(::asc::std::declval<::asc::std::size_t&>()))>>
    : true_type {};
}  // namespace __allocate_at_least_detail

template <class Alloc>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr allocation_result<typename allocator_traits<Alloc>::pointer>
allocate_at_least(Alloc& __alloc, ::asc::std::size_t __n)
{
    if constexpr (__allocate_at_least_detail::has_member<Alloc>::value) {
        return __alloc.allocate_at_least(__n);
    } else {
        return {__alloc.allocate(__n), __n};
    }
}

template <class Alloc>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto __allocate_at_least(Alloc& __alloc, ::asc::std::size_t __n)
{
    return ::asc::std::allocate_at_least(__alloc, __n);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_ALLOCATE_AT_LEAST_H
