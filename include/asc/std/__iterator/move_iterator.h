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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_MOVE_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_MOVE_ITERATOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/move_sentinel.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_convertible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __move_iterator_detail {

// SFINAE-friendly traversal probes against iterator_traits::iterator_category
// and a member iterator_concept, usable in every compilation mode.
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
inline constexpr bool __has_iter_category = false;

template <class Iter>
inline constexpr bool __has_iter_category<Iter, void_t<typename iterator_traits<Iter>::iterator_category>> = true;

template <class Iter, class = void>
inline constexpr bool __has_member_iterator_concept = false;

template <class Iter>
inline constexpr bool __has_member_iterator_concept<Iter, void_t<typename Iter::iterator_concept>> = true;

// Deduce the effective category from the maximum of iterator_concept and
// iterator_category, mirroring the category-or-concept mapping of
// iterator_traits.
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
        return typename iterator_traits<Iter>::iterator_category{};
    }
}

template <class Iter>
using __iterator_traits_category_or_concept_t = decltype(__iterator_traits_category_or_concept<Iter>());

template <class Iter>
inline constexpr bool __is_random_access_or_better =
    is_convertible_v<__iterator_traits_category_or_concept_t<Iter>, random_access_iterator_tag>;

}  // namespace __move_iterator_detail

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class Iter, class = void>
struct __move_iter_category_base {};

template <class Iter>
    requires requires { typename iterator_traits<Iter>::iterator_category; }
struct __move_iter_category_base<Iter> {
    using iterator_category = _If<
        derived_from<__move_iterator_detail::__iterator_traits_category_or_concept_t<Iter>, random_access_iterator_tag>,
        random_access_iterator_tag, __move_iterator_detail::__iterator_traits_category_or_concept_t<Iter>>;
};

template <class Iter, class Sentinel>
concept __move_iter_comparable = requires {
    { declval<const Iter&>() == declval<Sentinel>() } -> convertible_to<bool>;
};

#else  // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())

template <class Iter, class = void>
struct __move_iter_category_base {};

template <class Iter>
struct __move_iter_category_base<Iter, enable_if_t<__move_iterator_detail::__has_iter_category<Iter>>> {
    using iterator_category = _If<__move_iterator_detail::__is_random_access_or_better<Iter>,
        random_access_iterator_tag, __move_iterator_detail::__iterator_traits_category_or_concept_t<Iter>>;
};

template <class Iter, class Sentinel, class = void>
struct __move_iter_comparable_impl : false_type {};

template <class Iter, class Sentinel>
struct __move_iter_comparable_impl<Iter, Sentinel,
    void_t<decltype(::asc::std::declval<const Iter&>() == ::asc::std::declval<Sentinel>())>>
    : bool_constant<
          is_convertible_v<decltype(::asc::std::declval<const Iter&>() == ::asc::std::declval<Sentinel>()), bool>> {};

template <class Iter, class Sentinel>
inline constexpr bool __move_iter_comparable = __move_iter_comparable_impl<Iter, Sentinel>::value;

template <class Iter, class Sentinel, class = void>
struct __move_iter_sized_impl : false_type {};

template <class Iter, class Sentinel>
struct __move_iter_sized_impl<Iter, Sentinel,
    void_t<decltype(::asc::std::declval<const Sentinel&>() - ::asc::std::declval<const Iter&>())>>
    : is_convertible<decltype(::asc::std::declval<const Sentinel&>() - ::asc::std::declval<const Iter&>()),
          iter_difference_t<Iter>> {};

template <class Iter, class Sentinel>
inline constexpr bool __move_iter_sized_sentinel = __move_iter_sized_impl<Iter, Sentinel>::value;

#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class Iter>
inline constexpr bool __noexcept_move_iter_iter_move =
    noexcept(::asc::std::iter_move(::asc::std::declval<const Iter&>()));

// Note: a hidden-friend iter_move cannot be declared here:
// asc::std::iter_move is a customization-point object (a namespace-scope
// variable), and a same-named friend function in an asc::std class is
// ill-formed ("redeclared as a different kind of entity"). The equivalent
// behavior is provided by the customization point itself: iter_move(mi)
// dispatches to *mi, which already yields iter_rvalue_reference_t<Iter>,
// i.e. the element-wise move of the underlying iterator.
// iter_swap keeps full underlying-element semantics through the
// namespace-scope overload declared below the class.

template <class Iter>
class move_iterator : public __move_iter_category_base<Iter> {
private:
    template <class>
    friend class move_iterator;

    Iter current_;

    CANN_ASC_STL_API static constexpr auto __mi_get_iter_concept()
    {
        if constexpr (random_access_iterator<Iter>) {
            return random_access_iterator_tag{};
        } else if constexpr (bidirectional_iterator<Iter>) {
            return bidirectional_iterator_tag{};
        } else if constexpr (forward_iterator<Iter>) {
            return forward_iterator_tag{};
        } else {
            return input_iterator_tag{};
        }
    }

public:
    using iterator_type = Iter;
    using iterator_concept = decltype(__mi_get_iter_concept());

    // iterator_category is inherited from __move_iter_category_base and is
    // not always present.
    using value_type = iter_value_t<Iter>;
    using difference_type = iter_difference_t<Iter>;
    using pointer = Iter;
    using reference = iter_rvalue_reference_t<Iter>;

    CANN_ASC_STL_API constexpr explicit move_iterator(Iter iterator) noexcept(is_nothrow_move_constructible_v<Iter>)
        : current_(::asc::std::move(iterator))
    {}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class It = Iter>
        requires is_default_constructible_v<It>
    CANN_ASC_STL_API constexpr move_iterator() noexcept(is_nothrow_default_constructible_v<It>) : current_()
    {}

    template <class Other>
        requires(!is_same_v<Other, Iter> && convertible_to<const Other&, Iter>)
    CANN_ASC_STL_API constexpr move_iterator(const move_iterator<Other>& other) noexcept(
        is_nothrow_convertible_v<const Other&, Iter>)
        : current_(other.base())
    {}

    template <class Other>
        requires(!is_same_v<Other, Iter> && convertible_to<const Other&, Iter> && assignable_from<Iter&, const Other&>)
    CANN_ASC_STL_API constexpr move_iterator& operator=(const move_iterator<Other>& other) noexcept(
        is_nothrow_assignable_v<Iter&, const Other&>)
    {
        current_ = other.base();
        return *this;
    }
#else
    template <class It = Iter, enable_if_t<is_default_constructible_v<It>, int> = 0>
    CANN_ASC_STL_API constexpr move_iterator() noexcept(is_nothrow_default_constructible_v<It>) : current_()
    {}
    template <class Other, enable_if_t<!is_same_v<Other, Iter> && convertible_to<const Other&, Iter>, int> = 0>
    CANN_ASC_STL_API constexpr move_iterator(const move_iterator<Other>& other) noexcept(
        is_nothrow_convertible_v<const Other&, Iter>)
        : current_(other.base())
    {}
    template <class Other,
        enable_if_t<!is_same_v<Other, Iter> && convertible_to<const Other&, Iter> &&
                assignable_from<Iter&, const Other&>,
            int> = 0>
    CANN_ASC_STL_API constexpr move_iterator& operator=(const move_iterator<Other>& other) noexcept(
        noexcept(current_ = other.base()))
    {
        current_ = other.base();
        return *this;
    }
#endif

    CANN_ASC_STL_API constexpr const Iter& base() const& noexcept
    {
        return current_;
    }
    CANN_ASC_STL_API constexpr Iter base() &&
    {
        return ::asc::std::move(current_);
    }
    CANN_ASC_STL_API constexpr reference operator*() const
    {
        return ::asc::std::iter_move(current_);
    }
    CANN_ASC_STL_API constexpr pointer operator->() const
    {
        return current_;
    }
    CANN_ASC_STL_API constexpr reference operator[](difference_type count) const
    {
        return ::asc::std::iter_move(current_ + count);
    }
    CANN_ASC_STL_API constexpr move_iterator& operator++()
    {
        ++current_;
        return *this;
    }
    CANN_ASC_STL_API constexpr auto operator++(int)
    {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        if constexpr (forward_iterator<Iter>) {
#else
        if constexpr (forward_iterator<Iter>) {
#endif
            move_iterator tmp(*this);
            ++current_;
            return tmp;
        } else {
            ++current_;
        }
    }
    CANN_ASC_STL_API constexpr move_iterator& operator--()
    {
        --current_;
        return *this;
    }

    CANN_ASC_STL_API constexpr move_iterator operator--(int)
    {
        move_iterator tmp(*this);
        --current_;
        return tmp;
    }
    CANN_ASC_STL_API constexpr move_iterator operator+(difference_type count) const
    {
        return move_iterator(current_ + count);
    }
    CANN_ASC_STL_API constexpr move_iterator operator-(difference_type count) const
    {
        return move_iterator(current_ - count);
    }
    CANN_ASC_STL_API constexpr move_iterator& operator+=(difference_type count)
    {
        current_ += count;
        return *this;
    }
    CANN_ASC_STL_API constexpr move_iterator& operator-=(difference_type count)
    {
        current_ -= count;
        return *this;
    }
};

template <class Iter>
CANN_ASC_STL_API constexpr move_iterator<Iter> operator+(
    typename move_iterator<Iter>::difference_type count, const move_iterator<Iter>& iterator)
{
    return iterator + count;
}

template <class Left, class Right>
CANN_ASC_STL_API constexpr auto operator-(
    const move_iterator<Left>& left, const move_iterator<Right>& right) -> decltype(left.base() - right.base())
{
    return left.base() - right.base();
}

#define CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(op)                                                               \
    template <class Left, class Right>                                                                              \
    CANN_ASC_STL_API constexpr auto operator op(const move_iterator<Left>& left, const move_iterator<Right>& right) \
        ->decltype(static_cast<bool>(left.base() op right.base()))                                                  \
    {                                                                                                               \
        return left.base() op right.base();                                                                         \
    }

CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(==)
CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(!=)
CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(<)  // NOLINT(whitespace/operators)
CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(>)  // NOLINT(whitespace/operators)
CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(<=)
CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(>=)

#undef CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE

template <class Iter, class Sentinel>
CANN_ASC_STL_API constexpr bool operator==(const move_iterator<Iter>& iterator, const move_sentinel<Sentinel>& sentinel)
{
    return iterator.base() == sentinel.base();
}
template <class Iter, class Sentinel>
CANN_ASC_STL_API constexpr bool operator!=(const move_iterator<Iter>& iterator, const move_sentinel<Sentinel>& sentinel)
{
    return !(iterator == sentinel);
}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class Iter, class Sentinel>
    requires(sentinel_for<Sentinel, Iter> && __move_iter_comparable<Iter, Sentinel>)
CANN_ASC_STL_API constexpr bool operator==(const move_sentinel<Sentinel>& sentinel, const move_iterator<Iter>& iterator)
{
    return sentinel.base() == iterator.base();
}

template <class Iter, class Sentinel>
    requires(sized_sentinel_for<Sentinel, Iter>)
CANN_ASC_STL_API constexpr iter_difference_t<Iter> operator-(
    const move_sentinel<Sentinel>& sentinel, const move_iterator<Iter>& iterator)
{
    return sentinel.base() - iterator.base();
}

template <class Iter, class Sentinel>
    requires(sized_sentinel_for<Sentinel, Iter>)
CANN_ASC_STL_API constexpr iter_difference_t<Iter> operator-(
    const move_iterator<Iter>& iterator, const move_sentinel<Sentinel>& sentinel)
{
    return iterator.base() - sentinel.base();
}
#else
template <class Iter, class Sentinel,
    enable_if_t<sentinel_for<Sentinel, Iter> && __move_iter_comparable<Iter, Sentinel>, int> = 0>
CANN_ASC_STL_API constexpr bool operator==(const move_sentinel<Sentinel>& sentinel, const move_iterator<Iter>& iterator)
{
    return sentinel.base() == iterator.base();
}

template <class Iter, class Sentinel,
    enable_if_t<sentinel_for<Sentinel, Iter> && __move_iter_comparable<Iter, Sentinel>, int> = 0>
CANN_ASC_STL_API constexpr bool operator!=(const move_sentinel<Sentinel>& sentinel, const move_iterator<Iter>& iterator)
{
    return !(sentinel == iterator);
}

template <class Iter, class Sentinel, enable_if_t<sized_sentinel_for<Sentinel, Iter>, int> = 0>
CANN_ASC_STL_API constexpr auto operator-(const move_sentinel<Sentinel>& sentinel,
    const move_iterator<Iter>& iterator) -> decltype(sentinel.base() - iterator.base())
{
    return sentinel.base() - iterator.base();
}

template <class Iter, class Sentinel, enable_if_t<sized_sentinel_for<Sentinel, Iter>, int> = 0>
CANN_ASC_STL_API constexpr auto operator-(const move_iterator<Iter>& iterator,
    const move_sentinel<Sentinel>& sentinel) -> decltype(iterator.base() - sentinel.base())
{
    return iterator.base() - sentinel.base();
}
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

// Swaps the elements denoted by the two underlying iterators. Declared at
// namespace scope (instead of as a hidden friend) because asc::std::iter_swap
// is a function template here; this overload wins partial ordering for
// move_iterator argument pairs and delegates to the base-level swap.
template <class Iter, class Iter2>
CANN_ASC_STL_API constexpr auto iter_swap(const move_iterator<Iter>& left, const move_iterator<Iter2>& right) noexcept(
    noexcept(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left.base(),
        right.base()))) -> decltype(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left.base(), right.base()))
{
    return ::asc::std::ranges::__iter_swap::__iter_swap_fn{}(
        left.base(), right.base());  // NOLINT(build/include_what_you_use)
}

template <class Iter>
CANN_ASC_STL_API constexpr move_iterator<Iter> make_move_iterator(Iter iterator) noexcept(
    is_nothrow_move_constructible_v<Iter>)
{
    return move_iterator<Iter>(::asc::std::move(iterator));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_MOVE_ITERATOR_H
