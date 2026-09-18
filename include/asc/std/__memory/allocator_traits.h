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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_ALLOCATOR_TRAITS_H
#define CANN_ASC_STL_ASC_STD___MEMORY_ALLOCATOR_TRAITS_H

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
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/cstring>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Allocator, class = void>
struct __allocator_const_pointer {
    using type =
        typename pointer_traits<typename Allocator::pointer>::template rebind<const typename Allocator::value_type>;
};
template <class Allocator>
struct __allocator_const_pointer<Allocator, void_t<typename Allocator::const_pointer>> {
    using type = typename Allocator::const_pointer;
};
template <class Allocator, class = void>
struct __allocator_size_type {
    using type = make_unsigned_t<typename pointer_traits<typename Allocator::pointer>::difference_type>;
};
template <class Allocator>
struct __allocator_size_type<Allocator, void_t<typename Allocator::size_type>> {
    using type = typename Allocator::size_type;
};
template <class Allocator>
struct allocator_traits {
    using allocator_type = Allocator;
    using value_type = typename Allocator::value_type;
    using pointer = typename Allocator::pointer;
    using const_pointer = typename __allocator_const_pointer<Allocator>::type;
    using void_pointer = typename pointer_traits<pointer>::template rebind<void>;
    using const_void_pointer = typename pointer_traits<pointer>::template rebind<const void>;
    using difference_type = typename pointer_traits<pointer>::difference_type;
    using size_type = typename __allocator_size_type<Allocator>::type;
    template <class T>
    using rebind_alloc = typename Allocator::template rebind<T>::other;
    template <class T>
    using rebind_traits = allocator_traits<rebind_alloc<T>>;

    CANN_ASC_STL_API static constexpr pointer allocate(Allocator& allocator, size_type count)
    {
        return allocator.allocate(count);
    }
    CANN_ASC_STL_API static constexpr pointer allocate(Allocator& allocator, size_type count, const_void_pointer hint)
    {
        return allocator.allocate(count, hint);
    }
    CANN_ASC_STL_API static constexpr void deallocate(Allocator& allocator, pointer value, size_type count)
    {
        allocator.deallocate(value, count);
    }
    template <class T, class... Args>
    CANN_ASC_STL_API static constexpr void construct(Allocator&, T* location, Args&&... args)
    {
        (void)::asc::std::construct_at(
            location, ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
    }
    template <class T>
    CANN_ASC_STL_API static constexpr void destroy(Allocator&, T* location)
    {
        location->~T();
    }
    CANN_ASC_STL_API static constexpr size_type max_size(const Allocator&) noexcept
    {
        return numeric_limits<size_type>::max() / sizeof(value_type);  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API static constexpr Allocator select_on_container_copy_construction(const Allocator& allocator)
    {
        return allocator;
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_ALLOCATOR_TRAITS_H
