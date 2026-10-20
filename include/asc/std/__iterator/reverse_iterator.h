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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_REVERSE_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_REVERSE_ITERATOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
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
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __reverse_iterator_detail {

// Minimal local traversal probes: a category probe against iterator_traits
// and a concept probe against a member iterator_concept, both SFINAE-friendly
// in C++17 mode.
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

template <class Iter>
inline constexpr bool __has_input_traversal = __has_iterator_category_convertible_to<Iter, input_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, input_iterator_tag>;

template <class Iter>
inline constexpr bool __has_forward_traversal = __has_iterator_category_convertible_to<Iter, forward_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, forward_iterator_tag>;

template <class Iter>
inline constexpr bool __has_bidirectional_traversal =
    __has_iterator_category_convertible_to<Iter, bidirectional_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, bidirectional_iterator_tag>;

template <class Iter>
inline constexpr bool __has_random_access_traversal =
    __has_iterator_category_convertible_to<Iter, random_access_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, random_access_iterator_tag>;

template <class Iter>
inline constexpr bool __has_contiguous_traversal =
    __has_iterator_category_convertible_to<Iter, contiguous_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, contiguous_iterator_tag>;

template <class Iter, class = void>
inline constexpr bool __has_member_iterator_concept = false;

template <class Iter>
inline constexpr bool __has_member_iterator_concept<Iter, void_t<typename Iter::iterator_concept>> = true;

// C++20 iterators do not always carry a C++17-compatible iterator_category;
// deduce the effective category from the maximum of iterator_concept and
// iterator_category, mirroring __iterator_traits_category_or_concept.
template <class Iter>
CANN_ASC_STL_API constexpr auto __iterator_traits_category_or_concept() noexcept
{
    if constexpr (!__has_member_iterator_concept<Iter>) {
        return typename iterator_traits<Iter>::iterator_category{};
    } else if constexpr (__has_contiguous_traversal<Iter>) {
        return contiguous_iterator_tag{};
    } else if constexpr (__has_random_access_traversal<Iter>) {
        return random_access_iterator_tag{};
    } else if constexpr (__has_bidirectional_traversal<Iter>) {
        return bidirectional_iterator_tag{};
    } else if constexpr (__has_forward_traversal<Iter>) {
        return forward_iterator_tag{};
    } else if constexpr (__has_input_traversal<Iter>) {
        return input_iterator_tag{};
    } else {
        return typename Iter::iterator_category{};
    }
}

template <class Iter>
using __iterator_traits_category_or_concept_t = decltype(__iterator_traits_category_or_concept<Iter>());

// Local equivalent of __has_const_arrow: satisfied by pointers and by types
// exposing a const operator->.
template <class Iter, class = void>
inline constexpr bool __has_const_arrow_operator = false;

template <class Iter>
inline constexpr bool
    __has_const_arrow_operator<Iter, void_t<decltype(::asc::std::declval<const Iter&>().operator->())>> = true;

template <class Iter>
inline constexpr bool __has_const_arrow = is_pointer_v<Iter> || __has_const_arrow_operator<Iter>;

}  // namespace __reverse_iterator_detail

// iter_move remains the element move customization point. The namespace-scope
// iter_swap overload below preserves the underlying iterator's ADL customization
// after decrementing copies of both bases.

template <class Iter, class Iter2, class = void>
inline constexpr bool __noexcept_rev_iter_convertible = false;

template <class Iter, class Iter2>
inline constexpr bool __noexcept_rev_iter_convertible<Iter, Iter2, enable_if_t<is_convertible_v<const Iter&, Iter2>>> =
    noexcept(Iter2(::asc::std::declval<const Iter&>()));

template <class Iter>
class reverse_iterator {
public:
    static_assert(__reverse_iterator_detail::__has_bidirectional_traversal<Iter> || bidirectional_iterator<Iter>,
        "reverse_iterator<It> requires It to be a bidirectional iterator.");

    using iterator_type = Iter;
    using iterator_category = conditional_t<__reverse_iterator_detail::__has_random_access_traversal<Iter>,
        random_access_iterator_tag, __reverse_iterator_detail::__iterator_traits_category_or_concept_t<Iter>>;
    using pointer = typename iterator_traits<Iter>::pointer;
    using iterator_concept =
        conditional_t<random_access_iterator<Iter>, random_access_iterator_tag, bidirectional_iterator_tag>;
    using value_type = iter_value_t<Iter>;
    using difference_type = iter_difference_t<Iter>;
    using reference = iter_reference_t<Iter>;

    template <class It = Iter, enable_if_t<is_default_constructible_v<It>, int> = 0>
    CANN_ASC_STL_API constexpr reverse_iterator() noexcept(is_nothrow_default_constructible_v<It>) : current()
    {}

    CANN_ASC_STL_API constexpr explicit reverse_iterator(Iter value) noexcept(is_nothrow_copy_constructible_v<Iter>)
        : current(value)
    {}
    template <class Other, enable_if_t<!is_same_v<Other, Iter> && is_convertible_v<const Other&, Iter>, int> = 0>
    CANN_ASC_STL_API constexpr reverse_iterator(const reverse_iterator<Other>& other) noexcept(
        __noexcept_rev_iter_convertible<Other, Iter>)
        : current(other.base())
    {}
    template <class Other,
        enable_if_t<!is_same_v<Other, Iter> && is_convertible_v<const Other&, Iter> &&
                is_assignable_v<Iter&, const Other&>,
            int> = 0>
    CANN_ASC_STL_API constexpr reverse_iterator& operator=(const reverse_iterator<Other>& other) noexcept(
        is_nothrow_assignable_v<Iter&, const Other&>)
    {
        current = other.base();
        return *this;
    }
    CANN_ASC_STL_API constexpr Iter base() const noexcept(is_nothrow_copy_constructible_v<Iter>)
    {
        return current;
    }
    CANN_ASC_STL_API constexpr reference operator*() const
    {
        return *::asc::std::prev(current);
    }
    template <class It = Iter, enable_if_t<__reverse_iterator_detail::__has_const_arrow<It>, int> = 0>
    CANN_ASC_STL_API constexpr pointer operator->() const
    {
        if constexpr (is_pointer_v<It>) {
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
        reverse_iterator old(*this);
        --current;
        return old;
    }
    CANN_ASC_STL_API constexpr reverse_iterator& operator--()
    {
        ++current;
        return *this;
    }
    CANN_ASC_STL_API constexpr reverse_iterator operator--(int)
    {
        reverse_iterator old(*this);
        ++current;
        return old;
    }
    CANN_ASC_STL_API constexpr reverse_iterator operator+(difference_type count) const
    {
        return reverse_iterator(current - count);
    }
    CANN_ASC_STL_API friend constexpr reverse_iterator operator+(difference_type count, const reverse_iterator& value)
    {
        return reverse_iterator(value.base() - count);
    }
    CANN_ASC_STL_API constexpr reverse_iterator& operator+=(difference_type count)
    {
        current -= count;
        return *this;
    }
    CANN_ASC_STL_API constexpr reverse_iterator operator-(difference_type count) const
    {
        return reverse_iterator(current + count);
    }
    template <class Iter2>
    CANN_ASC_STL_API friend constexpr auto operator-(const reverse_iterator& left,
        const reverse_iterator<Iter2>& right) -> decltype(::asc::std::declval<const Iter2&>() -
                                                  ::asc::std::declval<const Iter&>())
    {
        return right.base() - left.base();
    }
    CANN_ASC_STL_API constexpr reverse_iterator& operator-=(difference_type count)
    {
        current += count;
        return *this;
    }
    CANN_ASC_STL_API constexpr reference operator[](difference_type count) const
    {
        return *(*this + count);
    }
    template <class Iter2>
    CANN_ASC_STL_API friend constexpr auto operator==(const reverse_iterator& left,
        const reverse_iterator<Iter2>& right) noexcept(noexcept(static_cast<bool>(::asc::std::declval<const Iter&>() ==
        ::asc::std::declval<const Iter2&>()))) -> decltype(static_cast<bool>(::asc::std::declval<const Iter&>() ==
                                                   ::asc::std::declval<const Iter2&>()))
    {
        return left.base() == right.base();
    }
    template <class Iter2>
    CANN_ASC_STL_API friend constexpr auto operator!=(const reverse_iterator& left,
        const reverse_iterator<Iter2>& right) noexcept(noexcept(static_cast<bool>(::asc::std::declval<const Iter&>() !=
        ::asc::std::declval<const Iter2&>()))) -> decltype(static_cast<bool>(::asc::std::declval<const Iter&>() !=
                                                   ::asc::std::declval<const Iter2&>()))
    {
        return left.base() != right.base();
    }
    // Relational comparisons expose the reversed ordering: the exposed < compares
    // the underlying iterators via >.
    template <class Iter2>
    CANN_ASC_STL_API friend constexpr auto operator<(const reverse_iterator& left, const reverse_iterator<Iter2>& right)
        -> decltype(static_cast<bool>(::asc::std::declval<const Iter&>() > ::asc::std::declval<const Iter2&>()))
    {
        return left.base() > right.base();
    }
    template <class Iter2>
    CANN_ASC_STL_API friend constexpr auto operator>(const reverse_iterator& left, const reverse_iterator<Iter2>& right)
        -> decltype(static_cast<bool>(::asc::std::declval<const Iter&>() < ::asc::std::declval<const Iter2&>()))
    {
        return left.base() < right.base();
    }
    template <class Iter2>
    CANN_ASC_STL_API friend constexpr auto operator>=(const reverse_iterator& left,
        const reverse_iterator<Iter2>& right) -> decltype(static_cast<bool>(::asc::std::declval<const Iter&>() <=
                                                  ::asc::std::declval<const Iter2&>()))
    {
        return left.base() <= right.base();
    }
    template <class Iter2>
    CANN_ASC_STL_API friend constexpr auto operator<=(const reverse_iterator& left,
        const reverse_iterator<Iter2>& right) -> decltype(static_cast<bool>(::asc::std::declval<const Iter&>() >=
                                                  ::asc::std::declval<const Iter2&>()))
    {
        return left.base() >= right.base();
    }

private:
    Iter current{};
};

template <class Iter1, class Iter2>
inline constexpr bool disable_sized_sentinel_for<reverse_iterator<Iter1>, reverse_iterator<Iter2>> =
    !sized_sentinel_for<Iter1, Iter2>;

namespace __reverse_iterator_detail {
template <class Iter1, class Iter2, class = void>
inline constexpr bool __can_iter_swap = false;
template <class Iter1, class Iter2>
inline constexpr bool __can_iter_swap<Iter1, Iter2,
    void_t<decltype(--::asc::std::declval<Iter1&>()), decltype(--::asc::std::declval<Iter2&>()),
        decltype(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(
            --::asc::std::declval<Iter1&>(), --::asc::std::declval<Iter2&>()))>> = indirectly_swappable<Iter1, Iter2>;
}  // namespace __reverse_iterator_detail

CANN_ASC_STL_DETAIL_TEMPLATE(class Iter1, class Iter2)
CANN_ASC_STL_DETAIL_REQUIRES(__reverse_iterator_detail::__can_iter_swap<Iter1, Iter2>)
CANN_ASC_STL_API constexpr void iter_swap(const reverse_iterator<Iter1>& left,
    const reverse_iterator<Iter2>& right) noexcept(is_nothrow_copy_constructible_v<Iter1> &&
    is_nothrow_copy_constructible_v<Iter2> &&
    noexcept(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(
        --::asc::std::declval<Iter1&>(), --::asc::std::declval<Iter2&>())))
{
    auto first = left.base();
    auto second = right.base();
    ::asc::std::ranges::__iter_swap::__iter_swap_fn{}(--first, --second);
}

template <class Iter>
CANN_ASC_STL_API constexpr reverse_iterator<Iter> make_reverse_iterator(Iter value) noexcept(
    is_nothrow_copy_constructible_v<Iter>)
{
    return reverse_iterator<Iter>(value);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_REVERSE_ITERATOR_H
