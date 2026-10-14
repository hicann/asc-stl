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
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/cstring>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

// Optional allocator member probing framework: absent members fall back as
// the standard prescribes (pointer→T*, propagate_*→false_type,
// is_always_equal→is_empty, rebind→template-parameter rebinding, etc.), so
// C++20 minimal allocators are usable.
#define CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(NAME, PROPERTY) \
    template <class Allocator, class = void>                         \
    inline constexpr bool NAME##_v = false;                          \
    template <class Allocator>                                       \
    inline constexpr bool NAME##_v<Allocator, void_t<typename Allocator::PROPERTY>> = true;

// __allocator_pointer: falls back to value_type* when Allocator::pointer is absent.
CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(__allocator_has_pointer, pointer)
template <class T, class Allocator, bool = __allocator_has_pointer_v<Allocator>>
struct __allocator_pointer {
    using type = typename Allocator::pointer;
};
template <class T, class Allocator>
struct __allocator_pointer<T, Allocator, false> {
    using type = T*;
};

// __allocator_const_pointer: rebound through pointer_traits when Allocator::const_pointer is absent.
CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(__allocator_has_const_pointer, const_pointer)
template <class T, class Pointer, class Allocator, bool = __allocator_has_const_pointer_v<Allocator>>
struct __allocator_const_pointer {
    using type = typename Allocator::const_pointer;
};
template <class T, class Pointer, class Allocator>
struct __allocator_const_pointer<T, Pointer, Allocator, false> {
    using type = typename pointer_traits<Pointer>::template rebind<const T>;
};

// __allocator_void_pointer: rebound through pointer_traits when Allocator::void_pointer is absent.
CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(__allocator_has_void_pointer, void_pointer)
template <class Pointer, class Allocator, bool = __allocator_has_void_pointer_v<Allocator>>
struct __allocator_void_pointer {
    using type = typename Allocator::void_pointer;
};
template <class Pointer, class Allocator>
struct __allocator_void_pointer<Pointer, Allocator, false> {
    using type = typename pointer_traits<Pointer>::template rebind<void>;
};

// __allocator_const_void_pointer: rebound through pointer_traits when Allocator::const_void_pointer is absent.
CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(__allocator_has_const_void_pointer, const_void_pointer)
template <class Pointer, class Allocator, bool = __allocator_has_const_void_pointer_v<Allocator>>
struct __allocator_const_void_pointer {
    using type = typename Allocator::const_void_pointer;
};
template <class Pointer, class Allocator>
struct __allocator_const_void_pointer<Pointer, Allocator, false> {
    using type = typename pointer_traits<Pointer>::template rebind<const void>;
};

// __allocator_difference_type: takes the pointer_traits difference type when
// Allocator::difference_type is absent.
CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(__allocator_has_difference_type, difference_type)
template <class Allocator, class Pointer, bool = __allocator_has_difference_type_v<Allocator>>
struct __allocator_difference_type {
    using type = typename Allocator::difference_type;
};
template <class Allocator, class Pointer>
struct __allocator_difference_type<Allocator, Pointer, false> {
    using type = typename pointer_traits<Pointer>::difference_type;
};

// __allocator_size_type: takes the unsigned version of the difference type
// when Allocator::size_type is absent.
CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(__allocator_has_size_type, size_type)
template <class Allocator, class DifferenceType, bool = __allocator_has_size_type_v<Allocator>>
struct __allocator_size_type {
    using type = typename Allocator::size_type;
};
template <class Allocator, class DifferenceType>
struct __allocator_size_type<Allocator, DifferenceType, false> {
    using type = make_unsigned_t<DifferenceType>;
};

// __allocator_propagate_on_*: falls back to false_type when the propagation
// policy is absent.
CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(
    __allocator_has_propagate_on_container_copy_assignment, propagate_on_container_copy_assignment)
template <class Allocator, bool = __allocator_has_propagate_on_container_copy_assignment_v<Allocator>>
struct __allocator_propagate_on_container_copy_assignment {
    using type = typename Allocator::propagate_on_container_copy_assignment;
};
template <class Allocator>
struct __allocator_propagate_on_container_copy_assignment<Allocator, false> {
    using type = false_type;
};

CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(
    __allocator_has_propagate_on_container_move_assignment, propagate_on_container_move_assignment)
template <class Allocator, bool = __allocator_has_propagate_on_container_move_assignment_v<Allocator>>
struct __allocator_propagate_on_container_move_assignment {
    using type = typename Allocator::propagate_on_container_move_assignment;
};
template <class Allocator>
struct __allocator_propagate_on_container_move_assignment<Allocator, false> {
    using type = false_type;
};

CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(__allocator_has_propagate_on_container_swap, propagate_on_container_swap)
template <class Allocator, bool = __allocator_has_propagate_on_container_swap_v<Allocator>>
struct __allocator_propagate_on_container_swap {
    using type = typename Allocator::propagate_on_container_swap;
};
template <class Allocator>
struct __allocator_propagate_on_container_swap<Allocator, false> {
    using type = false_type;
};

// __allocator_is_always_equal: falls back to is_empty<Allocator> when absent.
CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX(__allocator_has_is_always_equal, is_always_equal)
template <class Allocator, bool = __allocator_has_is_always_equal_v<Allocator>>
struct __allocator_is_always_equal {
    using type = typename Allocator::is_always_equal;
};
template <class Allocator>
struct __allocator_is_always_equal<Allocator, false> {
    using type = is_empty<Allocator>;
};

// __allocator_has_member_rebind: probes whether Allocator::rebind<U>::other is available.
template <class T, class U, class = void>
struct __allocator_has_member_rebind : false_type {};
template <class T, class U>
struct __allocator_has_member_rebind<T, U, void_t<typename T::template rebind<U>::other>> : true_type {};

// __allocator_traits_rebind: the member rebind takes precedence; a
// template-shaped allocator (Alloc<T, Args...>) falls back to Alloc<U, Args...>
// when the member rebind is absent.
template <class T, class U, bool = __allocator_has_member_rebind<T, U>::value>
struct __allocator_traits_rebind {
    static_assert(__allocator_has_member_rebind<T, U>::value, "This allocator has to implement rebind");
    using type = typename T::template rebind<U>::other;
};
template <template <class, class...> class Alloc, class T, class... Args, class U>
struct __allocator_traits_rebind<Alloc<T, Args...>, U, false> {
    using type = Alloc<U, Args...>;
};

// __allocator_has_allocate_hint: probes for the hinted allocate(n, hint) overload.
template <class Allocator, class SizeType, class ConstVoidPointer, class = void>
inline constexpr bool __allocator_has_allocate_hint = false;
template <class Allocator, class SizeType, class ConstVoidPointer>
inline constexpr bool __allocator_has_allocate_hint<Allocator, SizeType, ConstVoidPointer,
    void_t<decltype((void)::asc::std::declval<Allocator&>().allocate(
        ::asc::std::declval<SizeType>(), ::asc::std::declval<ConstVoidPointer>()))>> = true;

// __allocator_has_construct: probes for an allocator-provided construct member.
template <class, class Allocator, class... Args>
inline constexpr bool __allocator_has_construct_impl = false;
template <class Allocator, class... Args>
inline constexpr bool __allocator_has_construct_impl<
    decltype((void)::asc::std::declval<Allocator&>().construct(::asc::std::declval<Args>()...)), Allocator, Args...> =
    true;
template <class Allocator, class... Args>
inline constexpr bool __allocator_has_construct = __allocator_has_construct_impl<void, Allocator, Args...>;

// __allocator_has_destroy: probes for an allocator-provided destroy member.
template <class Allocator, class Pointer, class = void>
inline constexpr bool __allocator_has_destroy = false;
template <class Allocator, class Pointer>
inline constexpr bool __allocator_has_destroy<Allocator, Pointer,
    void_t<decltype((void)::asc::std::declval<Allocator&>().destroy(::asc::std::declval<Pointer>()))>> = true;

// __allocator_has_max_size: probes for an allocator-provided max_size member
// (const-qualified, matching the call site).
template <class Allocator, class = void>
inline constexpr bool __allocator_has_max_size = false;
template <class Allocator>
inline constexpr bool
    __allocator_has_max_size<Allocator, void_t<decltype((void)::asc::std::declval<const Allocator&>().max_size())>> =
        true;

// __allocator_has_select_on_container_copy_construction: probes for the
// copy-construction selection hook (const-qualified).
template <class Allocator, class = void>
inline constexpr bool __allocator_has_select_on_container_copy_construction = false;
template <class Allocator>
inline constexpr bool __allocator_has_select_on_container_copy_construction<Allocator,
    void_t<decltype((void)::asc::std::declval<const Allocator&>().select_on_container_copy_construction())>> = true;

template <class Allocator>
struct allocator_traits {
    using allocator_type = Allocator;
    using value_type = typename Allocator::value_type;
    using pointer = typename __allocator_pointer<value_type, Allocator>::type;
    using const_pointer = typename __allocator_const_pointer<value_type, pointer, Allocator>::type;
    using void_pointer = typename __allocator_void_pointer<pointer, Allocator>::type;
    using const_void_pointer = typename __allocator_const_void_pointer<pointer, Allocator>::type;
    using difference_type = typename __allocator_difference_type<Allocator, pointer>::type;
    using size_type = typename __allocator_size_type<Allocator, difference_type>::type;
    using propagate_on_container_copy_assignment =
        typename __allocator_propagate_on_container_copy_assignment<Allocator>::type;
    using propagate_on_container_move_assignment =
        typename __allocator_propagate_on_container_move_assignment<Allocator>::type;
    using propagate_on_container_swap = typename __allocator_propagate_on_container_swap<Allocator>::type;
    using is_always_equal = typename __allocator_is_always_equal<Allocator>::type;
    template <class T>
    using rebind_alloc = typename __allocator_traits_rebind<Allocator, T>::type;
    template <class T>
    using rebind_traits = allocator_traits<rebind_alloc<T>>;

    CANN_ASC_STL_API static constexpr pointer allocate(Allocator& allocator, size_type count)
    {
        return allocator.allocate(count);
    }
    CANN_ASC_STL_API static constexpr pointer allocate(Allocator& allocator, size_type count, const_void_pointer hint)
    {
        if constexpr (__allocator_has_allocate_hint<Allocator, size_type, const_void_pointer>) {
            return allocator.allocate(count, hint);
        } else {
            (void)hint;
            return allocator.allocate(count);
        }
    }
    CANN_ASC_STL_API static constexpr void deallocate(Allocator& allocator, pointer value, size_type count) noexcept
    {
        allocator.deallocate(value, count);
    }
    template <class T, class... Args>
    CANN_ASC_STL_API static constexpr void construct(Allocator& allocator, T* location, Args&&... args)
    {
        if constexpr (__allocator_has_construct<Allocator&, T*, Args...>) {
            allocator.construct(location, ::asc::std::forward<Args>(args)...);
        } else {
            (void)allocator;
            (void)::asc::std::__construct_at(
                location, ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
        }
    }
    template <class T>
    CANN_ASC_STL_API static constexpr void destroy(Allocator& allocator, T* location)
    {
        if constexpr (__allocator_has_destroy<Allocator&, T*>) {
            allocator.destroy(location);
        } else {
            (void)allocator;
            ::asc::std::__destroy_at(location);
        }
    }
    CANN_ASC_STL_API static constexpr size_type max_size(const Allocator& allocator) noexcept
    {
        if constexpr (__allocator_has_max_size<const Allocator>) {
            return allocator.max_size();
        } else {
            return numeric_limits<size_type>::max() / sizeof(value_type);  // NOLINT(build/include_what_you_use)
        }
    }
    CANN_ASC_STL_API static constexpr Allocator select_on_container_copy_construction(const Allocator& allocator)
    {
        if constexpr (__allocator_has_select_on_container_copy_construction<const Allocator>) {
            return allocator.select_on_container_copy_construction();
        } else {
            return allocator;
        }
    }
};

#undef CANN_ASC_STL_DETAIL_ALLOCATOR_TRAITS_HAS_XXX

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_ALLOCATOR_TRAITS_H
