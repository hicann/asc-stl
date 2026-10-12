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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_WRAP_ITER_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_WRAP_ITER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/void_t.h>

// Migrated from dev __asc/dialect.h: base asc/__config has no standard-version
// number macro, so key it on CANN_ASC_STL_DETAIL_CPLUSPLUS instead.
#ifndef CANN_ASC_STL_DETAIL_STD_VER
#if CANN_ASC_STL_DETAIL_CPLUSPLUS <= 199711L
#define CANN_ASC_STL_DETAIL_STD_VER 2003
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201103L
#define CANN_ASC_STL_DETAIL_STD_VER 2011
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201402L
#define CANN_ASC_STL_DETAIL_STD_VER 2014
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201703L
#define CANN_ASC_STL_DETAIL_STD_VER 2017
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202002L
#define CANN_ASC_STL_DETAIL_STD_VER 2020
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202302L
#define CANN_ASC_STL_DETAIL_STD_VER 2023
#else
#define CANN_ASC_STL_DETAIL_STD_VER 2024
#endif
#endif  // CANN_ASC_STL_DETAIL_STD_VER

CANN_ASC_STL_BEGIN_NAMESPACE

// Minimal local equivalent of the traversal probe used by the migrated
// implementation: the shared probe of the dev tree lives in its iterator
// traits header, which the base keeps protected, so keep a file-local copy
// (same pattern as other base headers). Both sub-probes are SFINAE-friendly
// in C++17 mode.
namespace __wrap_iter_detail {
template <class Iter, class Tag, class = void>
inline constexpr bool __has_iterator_category_convertible_to = false;

template <class Iter, class Tag>
inline constexpr bool
    __has_iterator_category_convertible_to<Iter, Tag, void_t<typename iterator_traits<Iter>::iterator_category>> =
        is_convertible_v<typename iterator_traits<Iter>::iterator_category, Tag>;

template <class Iter, class Tag, class = void>
inline constexpr bool __has_iterator_concept_convertible_to = false;

template <class Iter, class Tag>
inline constexpr bool __has_iterator_concept_convertible_to<Iter, Tag, void_t<typename Iter::iterator_concept>> =
    is_convertible_v<typename Iter::iterator_concept, Tag>;

// __has_contiguous_traversal determines if an iterator is known to be
// contiguous, either because it advertises itself as such via its
// iterator_concept or because its iterator_category says so. Wrappers around
// (possibly fancy) pointer types opt in via explicit specializations below.
template <class Iter>
inline constexpr bool __has_contiguous_traversal =
    __has_iterator_category_convertible_to<Iter, contiguous_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, contiguous_iterator_tag>;
}  // namespace __wrap_iter_detail

template <class _Iter>
class __wrap_iter {
public:
    using iterator_type = _Iter;
    using value_type = typename iterator_traits<iterator_type>::value_type;
    using difference_type = typename iterator_traits<iterator_type>::difference_type;
    using pointer = typename iterator_traits<iterator_type>::pointer;
    using reference = typename iterator_traits<iterator_type>::reference;
    using iterator_category = typename iterator_traits<iterator_type>::iterator_category;

    using iterator_concept = contiguous_iterator_tag;

private:
    iterator_type __i_;

public:
    CANN_ASC_STL_API constexpr __wrap_iter() noexcept : __i_()
    {}
    template <class _Up>
    CANN_ASC_STL_API constexpr __wrap_iter(
        const __wrap_iter<_Up>& __u, typename enable_if<is_convertible_v<_Up, iterator_type>>::type* = nullptr) noexcept
        : __i_(__u.base())
    {}
    CANN_ASC_STL_API constexpr reference operator*() const noexcept
    {
        return *__i_;
    }
    CANN_ASC_STL_API constexpr pointer operator->() const noexcept
    {
        return ::asc::std::to_address(__i_);
    }
    CANN_ASC_STL_API constexpr __wrap_iter& operator++() noexcept
    {
        ++__i_;
        return *this;
    }
    CANN_ASC_STL_API constexpr __wrap_iter operator++(int) noexcept
    {
        __wrap_iter __tmp(*this);
        ++(*this);
        return __tmp;
    }

    CANN_ASC_STL_API constexpr __wrap_iter& operator--() noexcept
    {
        --__i_;
        return *this;
    }
    CANN_ASC_STL_API constexpr __wrap_iter operator--(int) noexcept
    {
        __wrap_iter __tmp(*this);
        --(*this);
        return __tmp;
    }
    CANN_ASC_STL_API constexpr __wrap_iter operator+(difference_type __n) const noexcept
    {
        __wrap_iter __w(*this);
        __w += __n;
        return __w;
    }
    CANN_ASC_STL_API constexpr __wrap_iter& operator+=(difference_type __n) noexcept
    {
        __i_ += __n;
        return *this;
    }
    CANN_ASC_STL_API constexpr __wrap_iter operator-(difference_type __n) const noexcept
    {
        return *this + (-__n);
    }
    CANN_ASC_STL_API constexpr __wrap_iter& operator-=(difference_type __n) noexcept
    {
        *this += -__n;
        return *this;
    }
    CANN_ASC_STL_API constexpr reference operator[](difference_type __n) const noexcept
    {
        return __i_[__n];
    }

    CANN_ASC_STL_API constexpr iterator_type base() const noexcept
    {
        return __i_;
    }

private:
    CANN_ASC_STL_API constexpr __wrap_iter(iterator_type __x) noexcept : __i_(__x)
    {}

    template <class _Up>
    friend class __wrap_iter;
    template <class _CharT, class _Traits, class _Alloc>
    friend class basic_string;
    template <class _Tp, class _Alloc>
    friend class vector;
    template <class _Tp, size_t>
    friend class span;
};

template <class _Iter1>
CANN_ASC_STL_API constexpr bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) noexcept
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
CANN_ASC_STL_API constexpr bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) noexcept
{
    return __x.base() == __y.base();
}

template <class _Iter1>
CANN_ASC_STL_API constexpr bool operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) noexcept
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
CANN_ASC_STL_API constexpr bool operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) noexcept
{
    return __x.base() < __y.base();
}

template <class _Iter1>
CANN_ASC_STL_API constexpr bool operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) noexcept
{
    return !(__x == __y);
}

template <class _Iter1, class _Iter2>
CANN_ASC_STL_API constexpr bool operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) noexcept
{
    return !(__x == __y);
}

template <class _Iter1>
CANN_ASC_STL_API constexpr bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) noexcept
{
    return __y < __x;
}

template <class _Iter1, class _Iter2>
CANN_ASC_STL_API constexpr bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) noexcept
{
    return __y < __x;
}

template <class _Iter1>
CANN_ASC_STL_API constexpr bool operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) noexcept
{
    return !(__x < __y);
}

template <class _Iter1, class _Iter2>
CANN_ASC_STL_API constexpr bool operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) noexcept
{
    return !(__x < __y);
}

template <class _Iter1>
CANN_ASC_STL_API constexpr bool operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) noexcept
{
    return !(__y < __x);
}

template <class _Iter1, class _Iter2>
CANN_ASC_STL_API constexpr bool operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) noexcept
{
    return !(__y < __x);
}

template <class _Iter1, class _Iter2>
CANN_ASC_STL_API constexpr auto operator-(
    const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) noexcept -> decltype(__x.base() - __y.base())
{
    return __x.base() - __y.base();
}

template <class _Iter1>
CANN_ASC_STL_API constexpr __wrap_iter<_Iter1> operator+(
    typename __wrap_iter<_Iter1>::difference_type __n, __wrap_iter<_Iter1> __x) noexcept
{
    __x += __n;
    return __x;
}

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017
namespace __wrap_iter_detail {
template <class _It>
inline constexpr bool __has_contiguous_traversal<__wrap_iter<_It>> = true;
}  // namespace __wrap_iter_detail
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017

template <class _It>
struct pointer_traits<__wrap_iter<_It>> {
    using pointer = __wrap_iter<_It>;
    using element_type = typename pointer_traits<_It>::element_type;
    using difference_type = typename pointer_traits<_It>::difference_type;

    CANN_ASC_STL_API constexpr static element_type* to_address(pointer __w) noexcept
    {
        return ::asc::std::to_address(__w.base());
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_WRAP_ITER_H
