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

#ifndef CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_LEAF_H
#define CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_LEAF_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__memory/allocator_arg_t.h>
#include <asc/std/__tuple/sfinae_helpers.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/is_final.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Storage strategy for one tuple element:
//  - empty non-final types are stored through private inheritance (EBO);
//  - reference and other rebinding types need value-category-preserving
//    access and assignment through the stored reference;
//  - everything else is stored as a plain value member.
enum class __tuple_leaf_specialization {
    __default,
    __synthesize_assignment,
    __empty_non_final,
};

template <class T>
inline constexpr __tuple_leaf_specialization __tuple_leaf_kind_v =
    is_empty_v<T> && !is_final_v<T>   ? __tuple_leaf_specialization::__empty_non_final :
    __must_synthesize_assignment_v<T> ? __tuple_leaf_specialization::__synthesize_assignment :
                                        __tuple_leaf_specialization::__default;

template <size_t Index, class T, __tuple_leaf_specialization Kind = __tuple_leaf_kind_v<T>>
class __tuple_leaf;

// A forwarding constructor must not capture copy/move construction of the
// leaf itself: for an rvalue leaf the forwarding overload would win over the
// copy constructor and then try to construct the element from the leaf. A
// forwardable argument therefore needs a different decayed type plus element
// constructibility.
template <class U, class T, class Current, bool = !is_same_v<remove_cvref_t<U>, Current>>
inline constexpr bool __tuple_leaf_can_forward = false;
template <class U, class T, class Current>
inline constexpr bool __tuple_leaf_can_forward<U, T, Current, true> = is_constructible_v<T, U>;

// Default storage: non-empty, non-rebinding element types. Copy and move
// construction/assignment are left implicit: declaring a defaulted move
// constructor here would delete the implicit copy assignment and make every
// regular tuple non-assignable.
template <size_t Index, class T>
class __tuple_leaf<Index, T, __tuple_leaf_specialization::__default> {
public:
    CANN_ASC_STL_API constexpr __tuple_leaf() = default;

    template <class U, enable_if_t<__tuple_leaf_can_forward<U, T, __tuple_leaf> && is_convertible_v<U, T>, int> = 0>
    CANN_ASC_STL_API constexpr __tuple_leaf(U&& value) : value_(::asc::std::forward<U>(value))
    {}
    template <class U, enable_if_t<__tuple_leaf_can_forward<U, T, __tuple_leaf> && !is_convertible_v<U, T>, int> = 0>
    CANN_ASC_STL_API constexpr explicit __tuple_leaf(U&& value) : value_(::asc::std::forward<U>(value))
    {}

    // Uses-allocator construction: the integral_constant tag carries the
    // per-element construction flavor computed by __uses_alloc_ctor
    // (0: ignore the allocator, 1: (allocator_arg, alloc, args...),
    // 2: (args..., alloc)).
    template <class Alloc>
    CANN_ASC_STL_API constexpr __tuple_leaf(integral_constant<int, 0>, const Alloc&) : value_()
    {}
    template <class Alloc, class U, enable_if_t<is_constructible_v<T, U&&>, int> = 0>
    CANN_ASC_STL_API constexpr __tuple_leaf(integral_constant<int, 0>, const Alloc&, U&& value)
        : value_(::asc::std::forward<U>(value))
    {}
    template <class Alloc, class U, enable_if_t<is_constructible_v<T, allocator_arg_t, Alloc, U&&>, int> = 0>
    CANN_ASC_STL_API constexpr __tuple_leaf(integral_constant<int, 1>, const Alloc& alloc, U&& value)
        : value_(allocator_arg, alloc, ::asc::std::forward<U>(value))
    {}
    template <class Alloc, class U, enable_if_t<is_constructible_v<T, U&&, Alloc>, int> = 0>
    CANN_ASC_STL_API constexpr __tuple_leaf(integral_constant<int, 2>, const Alloc& alloc, U&& value)
        : value_(::asc::std::forward<U>(value), alloc)
    {}

    CANN_ASC_STL_API constexpr T& __get() & noexcept
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr const T& __get() const& noexcept
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr T&& __get() && noexcept
    {
        return ::asc::std::move(value_);
    }
    CANN_ASC_STL_API constexpr const T&& __get() const&& noexcept
    {
        return ::asc::std::move(value_);
    }

    CANN_ASC_STL_API constexpr void swap(__tuple_leaf& other) noexcept(is_nothrow_swappable_v<T>)
    {
        ::asc::std::swap(value_, other.value_);
    }

private:
    T value_;
};

// Rebinding storage for reference (and similar) element types: access keeps
// the element's reference category - moving a tuple<int&> must not turn its
// element into int&&, while a tuple<int&&> hands out int&& when moved from -
// and assignment through the stored reference is synthesized element-wise by
// the tuple layer.
template <size_t Index, class T>
class __tuple_leaf<Index, T, __tuple_leaf_specialization::__synthesize_assignment> {
public:
    CANN_ASC_STL_API constexpr __tuple_leaf() noexcept(is_nothrow_default_constructible_v<T>) : value_()
    {}

    template <class U, enable_if_t<is_constructible_v<T, U&&>, int> = 0>
    CANN_ASC_STL_API constexpr explicit __tuple_leaf(U&& value) : value_(::asc::std::forward<U>(value))
    {}

    template <class Alloc>
    CANN_ASC_STL_API constexpr __tuple_leaf(integral_constant<int, 0>, const Alloc&) : value_()
    {}
    template <class Alloc, class U, enable_if_t<is_constructible_v<T, U&&>, int> = 0>
    CANN_ASC_STL_API constexpr __tuple_leaf(integral_constant<int, 0>, const Alloc&, U&& value)
        : value_(::asc::std::forward<U>(value))
    {}

    CANN_ASC_STL_API constexpr __tuple_leaf(const __tuple_leaf& other) : value_(static_cast<T>(other.value_))
    {}
    CANN_ASC_STL_API constexpr __tuple_leaf(__tuple_leaf&& other)
        : value_(static_cast<T>(::asc::std::move(other).value_))
    {}

    // Assignment is synthesized: it writes through the stored reference
    // (the implicit assignment would be deleted for reference members).
    CANN_ASC_STL_API constexpr __tuple_leaf& operator=(const __tuple_leaf& other)
    {
        __get() = other.__get();
        return *this;
    }
    CANN_ASC_STL_API constexpr __tuple_leaf& operator=(__tuple_leaf&& other)
    {
        __get() = static_cast<T&&>(other.__get());
        return *this;
    }

    CANN_ASC_STL_API constexpr T& __get() & noexcept
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr const T& __get() const& noexcept
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr T&& __get() && noexcept
    {
        return static_cast<T&&>(value_);
    }
    CANN_ASC_STL_API constexpr const T&& __get() const&& noexcept
    {
        return static_cast<const T&&>(value_);
    }

    CANN_ASC_STL_API constexpr void swap(__tuple_leaf& other) noexcept(is_nothrow_swappable_v<T>)
    {
        ::asc::std::swap(__get(), other.__get());
    }

private:
    T value_;
};

// Empty non-final types: stored through private inheritance for EBO. The
// cv-qualifiers of the element are carried by the __get() return types; the
// base itself must be unqualified.
template <size_t Index, class T>
class __tuple_leaf<Index, T, __tuple_leaf_specialization::__empty_non_final> : private remove_cv_t<T> {
    using storage = remove_cv_t<T>;

public:
    CANN_ASC_STL_API constexpr __tuple_leaf() noexcept(is_nothrow_default_constructible_v<T>) : storage()
    {}

    template <class U,
        enable_if_t<__tuple_leaf_can_forward<U, T, __tuple_leaf> && is_convertible_v<U, storage>, int> = 0>
    CANN_ASC_STL_API constexpr __tuple_leaf(U&& value) : storage(::asc::std::forward<U>(value))
    {}
    template <class U,
        enable_if_t<__tuple_leaf_can_forward<U, T, __tuple_leaf> && !is_convertible_v<U, storage>, int> = 0>
    CANN_ASC_STL_API constexpr explicit __tuple_leaf(U&& value) : storage(::asc::std::forward<U>(value))
    {}

    template <class Alloc>
    CANN_ASC_STL_API constexpr __tuple_leaf(integral_constant<int, 0>, const Alloc&) : storage()
    {}
    template <class Alloc, class U, enable_if_t<is_constructible_v<storage, U&&>, int> = 0>
    CANN_ASC_STL_API constexpr __tuple_leaf(integral_constant<int, 0>, const Alloc&, U&& value)
        : storage(::asc::std::forward<U>(value))
    {}

    CANN_ASC_STL_API constexpr T& __get() & noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API constexpr const T& __get() const& noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API constexpr T&& __get() && noexcept
    {
        return static_cast<T&&>(*this);
    }
    CANN_ASC_STL_API constexpr const T&& __get() const&& noexcept
    {
        return static_cast<const T&&>(*this);
    }

    CANN_ASC_STL_API constexpr void swap(__tuple_leaf& other) noexcept(is_nothrow_swappable_v<T>)
    {
        ::asc::std::swap(__get(), other.__get());  // NOLINT(build/include_what_you_use)
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_LEAF_H
