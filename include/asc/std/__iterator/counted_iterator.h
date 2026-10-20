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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_COUNTED_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_COUNTED_ITERATOR_H

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
#include <asc/std/__concepts/common_with.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/default_sentinel.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/exception_guard.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __counted_iterator_detail {

// Traversal probes built on the base _ITER_CONCEPT tag ladder (pointer ->
// iterator_traits::iterator_concept -> iterator_traits::iterator_category),
// usable in every compilation mode; probes live in their own partial
// specializations so a missing tag stays SFINAE-friendly. (Same family of
// probes as in advance.h / move_iterator.h.)
template <class Iter, class = void>
inline constexpr bool __has_forward_traversal = false;

template <class Iter>
inline constexpr bool __has_forward_traversal<Iter, void_t<_ITER_CONCEPT<Iter>>> =
    is_convertible_v<_ITER_CONCEPT<Iter>, forward_iterator_tag>;

template <class Iter, class = void>
inline constexpr bool __has_bidirectional_traversal = false;

template <class Iter>
inline constexpr bool __has_bidirectional_traversal<Iter, void_t<_ITER_CONCEPT<Iter>>> =
    is_convertible_v<_ITER_CONCEPT<Iter>, bidirectional_iterator_tag>;

template <class Iter, class = void>
inline constexpr bool __has_random_access_traversal = false;

template <class Iter>
inline constexpr bool __has_random_access_traversal<Iter, void_t<_ITER_CONCEPT<Iter>>> =
    is_convertible_v<_ITER_CONCEPT<Iter>, random_access_iterator_tag>;

template <class Iter, class = void>
inline constexpr bool __has_contiguous_traversal = false;

template <class Iter>
inline constexpr bool __has_contiguous_traversal<Iter, void_t<_ITER_CONCEPT<Iter>>> =
    is_convertible_v<_ITER_CONCEPT<Iter>, contiguous_iterator_tag>;

// Probes for conditional availability of nested types: pure output iterators
// have no iter_value_t/iterator_category, so these members must be presented
// conditionally rather than defined unconditionally.
template <class Iter, class = void>
inline constexpr bool __has_iter_value = false;

template <class Iter>
inline constexpr bool __has_iter_value<Iter, void_t<iter_value_t<Iter>>> = true;

template <class Iter, class = void>
inline constexpr bool __has_iter_reference = false;

template <class Iter>
inline constexpr bool __has_iter_reference<Iter, void_t<iter_reference_t<Iter>>> = true;

}  // namespace __counted_iterator_detail

// Conditional nested-type carriers: iterator_concept forwards Iter's member
// of the same name, iterator_category follows the
// iterator_traits<Iter>::iterator_category semantics (staying visible for
// pointers as well), and value_type/reference/pointer appear only when the
// corresponding deduction is valid.
template <class Iter, class = void>
struct __counted_iterator_concept {};

template <class Iter>
struct __counted_iterator_concept<Iter, void_t<typename Iter::iterator_concept>> {
    using iterator_concept = typename Iter::iterator_concept;
};

template <class Iter, class = void>
struct __counted_iterator_category {};

template <class Iter>
struct __counted_iterator_category<Iter, void_t<typename iterator_traits<Iter>::iterator_category>> {
    using iterator_category = typename iterator_traits<Iter>::iterator_category;
};

template <class Iter, class = void>
struct __counted_iterator_value_type {};

template <class Iter>
struct __counted_iterator_value_type<Iter, enable_if_t<__counted_iterator_detail::__has_iter_value<Iter>>> {
    using value_type = iter_value_t<Iter>;
};

template <class Iter, class = void>
struct __counted_iterator_reference {};

template <class Iter>
struct __counted_iterator_reference<Iter, enable_if_t<__counted_iterator_detail::__has_iter_reference<Iter>>> {
    using reference = iter_reference_t<Iter>;
    using pointer = add_pointer_t<iter_reference_t<Iter>>;
};

template <class Iter>
class counted_iterator : public __counted_iterator_concept<Iter>,
                         public __counted_iterator_category<Iter>,
                         public __counted_iterator_value_type<Iter>,
                         public __counted_iterator_reference<Iter> {
public:
    using iterator_type = Iter;
    using difference_type = iter_difference_t<Iter>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr counted_iterator()
        requires is_default_constructible_v<Iter>
    = default;
#else   // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())
    template <class I2 = Iter, enable_if_t<is_default_constructible_v<I2>, int> = 0>
    CANN_ASC_STL_API constexpr counted_iterator()
    {}
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

    CANN_ASC_STL_API constexpr counted_iterator(Iter value, difference_type count) noexcept(
        is_nothrow_move_constructible_v<Iter>)
        : current_(::asc::std::move(value)), count_(count)
    {
        CANN_ASC_STL_DETAIL_ASSERT(count >= 0, "count must not be negative.");
    }
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class I2>
        requires convertible_to<const I2&, Iter>
    CANN_ASC_STL_API constexpr counted_iterator(const counted_iterator<I2>& other) noexcept(
        is_nothrow_constructible_v<Iter, const I2&>)
        : current_(other.base()), count_(other.count())
    {}
    template <class I2>
        requires assignable_from<Iter&, const I2&>
    CANN_ASC_STL_API constexpr counted_iterator& operator=(const counted_iterator<I2>& other) noexcept(
        is_nothrow_assignable_v<Iter&, const I2&>)
    {
        current_ = other.base();
        count_ = other.count();
        return *this;
    }
#else   // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())
    template <class I2, enable_if_t<is_convertible_v<const I2&, Iter>, int> = 0>
    CANN_ASC_STL_API constexpr counted_iterator(const counted_iterator<I2>& other) noexcept(
        is_nothrow_constructible_v<Iter, const I2&>)
        : current_(other.base()), count_(other.count())
    {}
    template <class I2, enable_if_t<assignable_from<Iter&, const I2&>, int> = 0>
    CANN_ASC_STL_API constexpr counted_iterator& operator=(const counted_iterator<I2>& other) noexcept(
        is_nothrow_assignable_v<Iter&, const I2&>)
    {
        current_ = other.base();
        count_ = other.count();
        return *this;
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

    CANN_ASC_STL_API constexpr const Iter& base() const& noexcept
    {
        return current_;
    }
    CANN_ASC_STL_API constexpr Iter base() &&
    {
        return ::asc::std::move(current_);  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API constexpr difference_type count() const noexcept
    {
        return count_;
    }
    CANN_ASC_STL_API constexpr decltype(auto) operator*()
    {
        CANN_ASC_STL_DETAIL_ASSERT(count_ > 0, "Iterator is equal to or past end.");
        return *current_;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr decltype(auto) operator*() const
    {
        CANN_ASC_STL_DETAIL_ASSERT(count_ > 0, "Iterator is equal to or past end.");
        return *current_;
    }
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class I2 = Iter>
        requires contiguous_iterator<I2>
    CANN_ASC_STL_API constexpr auto operator->() const noexcept
    {
        return ::asc::std::to_address(current_);
    }
#else   // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())
    template <class I2 = Iter, enable_if_t<contiguous_iterator<I2>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator->() const noexcept
    {
        return ::asc::std::to_address(current_);
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

    CANN_ASC_STL_API constexpr counted_iterator& operator++()
    {
        CANN_ASC_STL_DETAIL_ASSERT(count_ > 0, "Iterator already at or past end.");
        ++current_;
        --count_;
        return *this;
    }
    // Forward iterators return a copy of the old counted_iterator; non-forward
    // iterators return the old underlying iterator as the standard requires,
    // and the host exception path rolls the count back before rethrowing
    // (under C++17, a try block is incompatible with constexpr, so the
    // function degrades to a non-constant expression).
#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && !CANN_ASC_STL_DETAIL_HAS_CXX20()
    template <class I2 = Iter>
    CANN_ASC_STL_API auto operator++(int)
#else
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr auto operator++(int)
#endif
    {
        CANN_ASC_STL_DETAIL_ASSERT(count_ > 0, "Iterator already at or past end.");
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        if constexpr (forward_iterator<I2>) {
#else
        if constexpr (forward_iterator<I2>) {
#endif
            counted_iterator old(*this);
            ++*this;
            return old;
        } else {
            --count_;
#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()
            try {
                return current_++;
            } catch (...) {
                ++count_;
                throw;
            }
#else
            return current_++;
#endif
        }
    }
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class I2 = Iter>
        requires bidirectional_iterator<I2>
    CANN_ASC_STL_API constexpr counted_iterator& operator--()
    {
        --current_;
        ++count_;
        return *this;
    }
    template <class I2 = Iter>
        requires bidirectional_iterator<I2>
    CANN_ASC_STL_API constexpr counted_iterator operator--(int)
    {
        counted_iterator old(*this);
        --*this;
        return old;
    }
    template <class I2 = Iter>
        requires random_access_iterator<I2>
    CANN_ASC_STL_API constexpr counted_iterator& operator+=(iter_difference_t<I2> count)
    {
        CANN_ASC_STL_DETAIL_ASSERT(count <= count_, "Cannot advance iterator past end.");
        current_ += count;
        count_ -= count;
        return *this;
    }
    template <class I2 = Iter>
        requires random_access_iterator<I2>
    CANN_ASC_STL_API constexpr counted_iterator& operator-=(iter_difference_t<I2> count)
    {
        CANN_ASC_STL_DETAIL_ASSERT(-count <= count_,
            "Attempt to subtract too large of a size: counted_iterator would be decremented before "
            "the first element of its range.");
        current_ -= count;
        count_ += count;
        return *this;
    }
    template <class I2 = Iter>
        requires random_access_iterator<I2>
    CANN_ASC_STL_API constexpr counted_iterator operator+(iter_difference_t<I2> count) const
    {
        return counted_iterator(current_ + count, count_ - count);
    }
    template <class I2 = Iter>
        requires random_access_iterator<I2>
    CANN_ASC_STL_API constexpr counted_iterator operator-(iter_difference_t<I2> count) const
    {
        return counted_iterator(current_ - count, count_ + count);
    }
    template <class I2 = Iter>
        requires random_access_iterator<I2>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](iter_difference_t<I2> count) const
    {
        CANN_ASC_STL_DETAIL_ASSERT(count < count_, "Subscript argument must be less than size.");
        return current_[count];
    }
#else   // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())
    template <class I2 = Iter, enable_if_t<bidirectional_iterator<I2>, int> = 0>
    CANN_ASC_STL_API constexpr counted_iterator& operator--()
    {
        --current_;
        ++count_;
        return *this;
    }
    template <class I2 = Iter, enable_if_t<bidirectional_iterator<I2>, int> = 0>
    CANN_ASC_STL_API constexpr counted_iterator operator--(int)
    {
        counted_iterator old(*this);
        --*this;
        return old;
    }
    template <class I2 = Iter, enable_if_t<random_access_iterator<I2>, int> = 0>
    CANN_ASC_STL_API constexpr counted_iterator& operator+=(iter_difference_t<I2> count)
    {
        CANN_ASC_STL_DETAIL_ASSERT(count <= count_, "Cannot advance iterator past end.");
        current_ += count;
        count_ -= count;
        return *this;
    }
    template <class I2 = Iter, enable_if_t<random_access_iterator<I2>, int> = 0>
    CANN_ASC_STL_API constexpr counted_iterator& operator-=(iter_difference_t<I2> count)
    {
        CANN_ASC_STL_DETAIL_ASSERT(-count <= count_,
            "Attempt to subtract too large of a size: counted_iterator would be decremented before "
            "the first element of its range.");
        current_ -= count;
        count_ += count;
        return *this;
    }
    template <class I2 = Iter, enable_if_t<random_access_iterator<I2>, int> = 0>
    CANN_ASC_STL_API constexpr counted_iterator operator+(iter_difference_t<I2> count) const
    {
        return counted_iterator(current_ + count, count_ - count);
    }
    template <class I2 = Iter, enable_if_t<random_access_iterator<I2>, int> = 0>
    CANN_ASC_STL_API constexpr counted_iterator operator-(iter_difference_t<I2> count) const
    {
        return counted_iterator(current_ - count, count_ + count);
    }
    template <class I2 = Iter, enable_if_t<random_access_iterator<I2>, int> = 0>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](iter_difference_t<I2> count) const
    {
        CANN_ASC_STL_DETAIL_ASSERT(count < count_, "Subscript argument must be less than size.");
        return current_[count];
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

private:
    Iter current_{};
    difference_type count_{};
};

CANN_ASC_STL_DETAIL_CTAD_SUPPORTED_FOR_TYPE(counted_iterator);

template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator==(const counted_iterator<I1>& left, const counted_iterator<I2>& right)
{
    return left.count() == right.count();
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator!=(const counted_iterator<I1>& left, const counted_iterator<I2>& right)
{
    return !(left == right);
}
template <class Iter>
CANN_ASC_STL_API constexpr bool operator==(const counted_iterator<Iter>& value, default_sentinel_t) noexcept
{
    return value.count() == 0;
}
template <class Iter>
CANN_ASC_STL_API constexpr bool operator==(default_sentinel_t, const counted_iterator<Iter>& value) noexcept
{
    return value.count() == 0;
}
template <class Iter>
CANN_ASC_STL_API constexpr bool operator!=(const counted_iterator<Iter>& value, default_sentinel_t sentinel) noexcept
{
    return !(value == sentinel);
}
template <class Iter>
CANN_ASC_STL_API constexpr bool operator!=(default_sentinel_t sentinel, const counted_iterator<Iter>& value) noexcept
{
    return !(sentinel == value);
}
// Sign convention (matching the standard): the distance from iterator
// to sentinel is negative, and from sentinel to iterator positive.
template <class Iter>
CANN_ASC_STL_API constexpr iter_difference_t<Iter> operator-(
    default_sentinel_t, const counted_iterator<Iter>& value) noexcept
{
    return value.count();
}
template <class Iter>
CANN_ASC_STL_API constexpr iter_difference_t<Iter> operator-(
    const counted_iterator<Iter>& value, default_sentinel_t) noexcept
{
    return -value.count();
}

// Relational comparisons order by remaining count as the standard specifies
// (same basis as operator==, pure count semantics).
#define CANN_ASC_STL_DETAIL_COUNTED_ITERATOR_COMPARE(op)                              \
    template <class I1, class I2>                                                     \
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool operator op(               \
        const counted_iterator<I1>& left, const counted_iterator<I2>& right) noexcept \
    {                                                                                 \
        return left.count() op right.count();                                         \
    }

CANN_ASC_STL_DETAIL_COUNTED_ITERATOR_COMPARE(<)  // NOLINT(whitespace/operators)
CANN_ASC_STL_DETAIL_COUNTED_ITERATOR_COMPARE(>)  // NOLINT(whitespace/operators)
CANN_ASC_STL_DETAIL_COUNTED_ITERATOR_COMPARE(<=)
CANN_ASC_STL_DETAIL_COUNTED_ITERATOR_COMPARE(>=)

#undef CANN_ASC_STL_DETAIL_COUNTED_ITERATOR_COMPARE

template <class Iter>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr counted_iterator<Iter> operator+(
    typename counted_iterator<Iter>::difference_type count, const counted_iterator<Iter>& value)
{
    return value + count;
}

template <class I1, class I2>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr iter_difference_t<I2> operator-(
    const counted_iterator<I1>& left, const counted_iterator<I2>& right)
{
    return right.count() - left.count();
}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class I1, class I2>
    requires indirectly_swappable<I2, I1>
CANN_ASC_STL_API constexpr auto iter_swap(const counted_iterator<I1>& left, const counted_iterator<I2>& right) noexcept(
    noexcept(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left.base(),
        right.base()))) -> decltype(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left.base(), right.base()))
{
    CANN_ASC_STL_DETAIL_ASSERT(left.count() > 0 && right.count() > 0, "Iterators must not be past end of range.");
    return ::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left.base(), right.base());
}
#else   // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())
namespace __counted_iterator_detail {
template <class I1, class I2, class = void>
inline constexpr bool __iter_swappable_probe = false;

template <class I1, class I2>
inline constexpr bool __iter_swappable_probe<I1, I2,
    void_t<decltype(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(
               ::asc::std::declval<const I1&>(), ::asc::std::declval<const I2&>())),
        decltype(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(
            ::asc::std::declval<const I2&>(), ::asc::std::declval<const I1&>()))>> = true;
}  // namespace __counted_iterator_detail

template <class I1, class I2, enable_if_t<indirectly_swappable<I2, I1>, int> = 0>
CANN_ASC_STL_API constexpr auto iter_swap(const counted_iterator<I1>& left, const counted_iterator<I2>& right) noexcept(
    noexcept(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left.base(),
        right.base()))) -> decltype(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left.base(), right.base()))
{
    CANN_ASC_STL_DETAIL_ASSERT(left.count() > 0 && right.count() > 0, "Iterators must not be past end of range.");
    return ::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left.base(), right.base());
}
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

// Note: a hidden-friend iter_move cannot be declared here:
// asc::std::iter_move is a customization-point object (a namespace-scope
// variable), and a same-named function at asc::std scope would be redeclared
// as a different kind of entity. The equivalent behavior is provided by the
// customization point itself: iter_move(ci) dispatches to *ci, which already
// yields the element-wise move of the underlying iterator.

// iterator_traits specialization: passes the underlying traits through when
// the underlying trait is available (non-empty primary template) and corrects
// the pointer member for contiguous underlying iterators; pure output
// iterators fall back to the member-probing primary path.
template <class Iter>
struct iterator_traits<counted_iterator<Iter>, void_t<typename iterator_traits<Iter>::iterator_category>>
    : iterator_traits<Iter> {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    using pointer = _If<contiguous_iterator<Iter>, add_pointer_t<iter_reference_t<Iter>>, void>;
#else   // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())
    using pointer = _If<contiguous_iterator<Iter>, add_pointer_t<iter_reference_t<Iter>>, void>;
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_COUNTED_ITERATOR_H
