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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_REVERSE_ITERATOR_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_REVERSE_ITERATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// The conditional include of the __compare family resolves to "absent" under the
// reviewed dependency decision (the __compare headers are not part of this tree and
// three-way comparison is disabled on both sides), so comparison semantics are
// provided by the classic relational operators below (operator</>/<=/>=, with
// comparison directions reversed under reverse-iterator semantics). The
// diagnostic-suppression wrapper around the class body has no counterpart
// compilation model here and is not carried over.
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__fwd/iterator.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__iterator/prev.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_convertible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Iter, class = void>
inline constexpr bool __noexcept_rev_iter_iter_move = false;

template <class _Iter>
inline constexpr bool __noexcept_rev_iter_iter_move<_Iter, void_t<decltype(--::asc::std::declval<_Iter&>())>> =
    is_nothrow_copy_constructible_v<_Iter> &&
    noexcept(::asc::std::ranges::__iter_move_cpo{}(--::asc::std::declval<_Iter&>()));

template <class _Iter, class _Iter2, class = void>
inline constexpr bool __noexcept_rev_iter_iter_swap = false;

template <class _Iter, class _Iter2>
inline constexpr bool __noexcept_rev_iter_iter_swap<_Iter, _Iter2, enable_if_t<indirectly_swappable<_Iter, _Iter2>>> =
    is_nothrow_copy_constructible_v<_Iter> && is_nothrow_copy_constructible_v<_Iter2> &&
    noexcept(::asc::std::ranges::__iter_swap_cpo{}(--::asc::std::declval<_Iter&>(), --::asc::std::declval<_Iter2&>()));

// MSVC historically has issues with is_nothrow_convertible_v here, so use the noexcept expression instead.
template <class _Iter, class _Iter2, class = void>
inline constexpr bool __noexcept_rev_iter_convertible = false;

template <class _Iter, class _Iter2>
inline constexpr bool
    __noexcept_rev_iter_convertible<_Iter, _Iter2, enable_if_t<is_convertible_v<_Iter const&, _Iter2>>> =
        noexcept(_Iter2(::asc::std::declval<const _Iter&>()));

CANN_ASC_STL_DETAIL_ACCL_BEGIN_HIDDEN_FRIEND_NAMESPACE

template <class _Iter>
class reverse_iterator {
private:
#if CANN_ASC_STL_DETAIL_STD_VER > 2017
    static_assert(__has_bidirectional_traversal<_Iter> || bidirectional_iterator<_Iter>,
        "reverse_iterator<It> requires It to be a bidirectional iterator.");
#endif  // CANN_ASC_STL_DETAIL_STD_VER > 2017

protected:
    _Iter current;

public:
    using iterator_type = _Iter;

    using iterator_category = _If<__has_random_access_traversal<_Iter>, random_access_iterator_tag,
        __iterator_traits_category_or_concept_t<_Iter>>;
    using pointer = typename iterator_traits<_Iter>::pointer;
    using iterator_concept = _If<random_access_iterator<_Iter>, random_access_iterator_tag, bidirectional_iterator_tag>;
    using value_type = iter_value_t<_Iter>;
    using difference_type = iter_difference_t<_Iter>;
    using reference = iter_reference_t<_Iter>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _It2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_default_constructible_v<_It2>)
    CANN_ASC_STL_API constexpr reverse_iterator() noexcept(is_nothrow_default_constructible_v<_It2>) : current()
    {}

    CANN_ASC_STL_API constexpr explicit reverse_iterator(_Iter __x) noexcept(is_nothrow_copy_constructible_v<_Iter>)
        : current(__x)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        (!is_same_v<_Up, _Iter>)CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_Up const&, _Iter>)
    CANN_ASC_STL_API constexpr reverse_iterator(const reverse_iterator<_Up>& __u) noexcept(
        __noexcept_rev_iter_convertible<_Up, _Iter>)
        : current(__u.base())
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        (!is_same_v<_Up, _Iter>)CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_Up const&, _Iter>
            CANN_ASC_STL_DETAIL_ACCL_AND is_assignable_v<_Iter&, _Up const&>)
    CANN_ASC_STL_API constexpr reverse_iterator& operator=(const reverse_iterator<_Up>& __u) noexcept(
        is_nothrow_assignable_v<_Iter&, _Up const&>)
    {
        current = __u.base();
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr _Iter base() const noexcept(is_nothrow_copy_constructible_v<_Iter>)
    {
        return current;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr reference operator*() const
    {
        return *::asc::std::prev(current);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Iter2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__has_const_arrow<_Iter2>)
    CANN_ASC_STL_API constexpr pointer operator->() const
    {
        if constexpr (is_pointer_v<_Iter>) {
            return ::asc::std::prev(current);
        } else {
            return ::asc::std::prev(current).operator->();
        }
    }

    CANN_ASC_STL_API constexpr reverse_iterator& operator++()
    {
        --current;
        return *this;
    }

    CANN_ASC_STL_API constexpr reverse_iterator operator++(int)
    {
        reverse_iterator __tmp{*this};
        --current;
        return __tmp;
    }

    CANN_ASC_STL_API constexpr reverse_iterator& operator--()
    {
        ++current;
        return *this;
    }

    CANN_ASC_STL_API constexpr reverse_iterator operator--(int)
    {
        reverse_iterator __tmp{*this};
        ++current;
        return __tmp;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr reverse_iterator operator+(difference_type __n) const
    {
        return reverse_iterator{current - __n};
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr reverse_iterator operator+(
        difference_type __n, const reverse_iterator& __x)
    {
        return reverse_iterator{__x.base() - __n};
    }

    CANN_ASC_STL_API constexpr reverse_iterator& operator+=(difference_type __n)
    {
        current -= __n;
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr reverse_iterator operator-(difference_type __n) const
    {
        return reverse_iterator{current + __n};
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator-(const reverse_iterator& __x,
        const reverse_iterator<_Iter2>& __y) -> decltype(::asc::std::declval<const _Iter2&>() -
                                                 ::asc::std::declval<const _Iter&>())
    {
        return __y.base() - __x.base();
    }

    CANN_ASC_STL_API constexpr reverse_iterator& operator-=(difference_type __n)
    {
        current += __n;
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr reference operator[](difference_type __n) const
    {
        return *(*this + __n);
    }

    template <class _Iter2 = _Iter>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_rvalue_reference_t<_Iter2> iter_move(
        const reverse_iterator& __i) noexcept(__noexcept_rev_iter_iter_move<_Iter2>)
    {
        auto __tmp = __i.base();
        return ::asc::std::ranges::__iter_move_cpo{}(--__tmp);
    }

    template <class _Iter2>
    CANN_ASC_STL_API friend constexpr auto iter_swap(const reverse_iterator& __x,
        const reverse_iterator<_Iter2>& __y) noexcept(__noexcept_rev_iter_iter_swap<_Iter, _Iter2>)
        CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES(void)(indirectly_swappable<_Iter2, _Iter>)
    {
        auto __xtmp = __x.base();
        auto __ytmp = __y.base();
        return ::asc::std::ranges::__iter_swap_cpo{}(--__xtmp, --__ytmp);
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator==(const reverse_iterator& __x,
        const reverse_iterator<_Iter2>& __y) noexcept(noexcept(static_cast<bool>(::asc::std::declval<const _Iter&>() ==
        ::asc::std::declval<const _Iter2&>()))) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() ==
                                                    ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() == __y.base();
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator!=(const reverse_iterator& __x,
        const reverse_iterator<_Iter2>& __y) noexcept(noexcept(static_cast<bool>(::asc::std::declval<const _Iter&>() !=
        ::asc::std::declval<const _Iter2&>()))) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() !=
                                                    ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() != __y.base();
    }

    // The three-way-comparison branch is removed by the reviewed dependency decision:
    // comparison semantics are provided by the relational operators below, with the
    // comparison direction reversed (the exposed < compares via the underlying >).
    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator<(const reverse_iterator& __x,
        const reverse_iterator<_Iter2>& __y) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() >
                                                 ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() > __y.base();
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator>(const reverse_iterator& __x,
        const reverse_iterator<_Iter2>& __y) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() <
                                                 ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() < __y.base();
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator>=(const reverse_iterator& __x,
        const reverse_iterator<_Iter2>& __y) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() <=
                                                 ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() <= __y.base();
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator<=(const reverse_iterator& __x,
        const reverse_iterator<_Iter2>& __y) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() >=
                                                 ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() >= __y.base();
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_HIDDEN_FRIEND_NAMESPACE(reverse_iterator)

template <class _Iter1, class _Iter2>
inline constexpr bool disable_sized_sentinel_for<reverse_iterator<_Iter1>, reverse_iterator<_Iter2>> =
    !sized_sentinel_for<_Iter1, _Iter2>;

template <class _Iter>
[[nodiscard]] CANN_ASC_STL_API constexpr reverse_iterator<_Iter> make_reverse_iterator(_Iter __i) noexcept(
    is_nothrow_copy_constructible_v<_Iter>)
{
    return reverse_iterator<_Iter>{__i};
}

template <template <class> class _RevIter1, template <class> class _RevIter2, class _Iter>
struct __unwrap_reverse_iter_impl {
    using _UnwrappedIter = decltype(__unwrap_iter_impl<_Iter>::__unwrap(::asc::std::declval<_Iter>()));
    using _ReverseWrapper = _RevIter1<_RevIter2<_Iter>>;

    CANN_ASC_STL_API static constexpr _ReverseWrapper __rewrap(
        _ReverseWrapper __orig_iter, _UnwrappedIter __unwrapped_iter)
    {
        return _ReverseWrapper(
            _RevIter2<_Iter>(__unwrap_iter_impl<_Iter>::__rewrap(__orig_iter.base().base(), __unwrapped_iter)));
    }

    CANN_ASC_STL_API static constexpr _UnwrappedIter __unwrap(_ReverseWrapper __i) noexcept
    {
        return __unwrap_iter_impl<_Iter>::__unwrap(__i.base().base());
    }
};

template <class _Iter, bool __b>
struct __unwrap_iter_impl<reverse_iterator<reverse_iterator<_Iter>>, __b>
    : __unwrap_reverse_iter_impl<reverse_iterator, reverse_iterator, _Iter> {};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_REVERSE_ITERATOR_H
