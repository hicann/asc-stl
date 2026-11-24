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

#ifndef CANN_ASC_STL_ASC___ITERATOR_SUPPORT_H
#define CANN_ASC_STL_ASC___ITERATOR_SUPPORT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/functional>
#include <asc/std/iterator>
#include <asc/std/limits>
#include <asc/std/optional>
#include <asc/std/tuple>
#include <asc/std/type_traits>
#include <asc/std/utility>

namespace asc::detail::iterator_detail {

template <class T>
inline constexpr bool integer_v = ::asc::std::is_integral_v<T> && !::asc::std::is_same_v<T, bool> &&
    ::asc::std::is_same_v<T, ::asc::std::remove_cv_t<T>>;

template <class F>
inline constexpr bool stored_callable_v = ::asc::std::is_copy_constructible_v<::asc::std::decay_t<F>> &&
    ::asc::std::is_move_constructible_v<::asc::std::decay_t<F>> &&
    ::asc::std::is_nothrow_destructible_v<::asc::std::decay_t<F>> &&
    ::asc::std::is_constructible_v<::asc::std::decay_t<F>, F>;

CANN_ASC_STL_API constexpr void require(bool condition) noexcept
{
    if (!condition) {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        CANN_ASC_STL_DETAIL_BUILTIN_ASSUME_UNREACHABLE();
#else
        CANN_ASC_STL_DETAIL_BUILTIN_TRAP();
#endif
    }
}

template <class D>
CANN_ASC_STL_API constexpr D add(D position, D offset) noexcept
{
    static_assert(integer_v<D> && ::asc::std::is_signed_v<D>, "iterator difference must be a signed integer");
    if (offset > 0) {
        require(position <= (::asc::std::numeric_limits<D>::max)() - offset);
    } else if (offset < 0) {
        require(position >= (::asc::std::numeric_limits<D>::lowest)() - offset);
    }
    return static_cast<D>(position + offset);
}

template <class D>
CANN_ASC_STL_API constexpr D subtract(D position, D offset) noexcept
{
    if (offset > 0) {
        require(position >= (::asc::std::numeric_limits<D>::lowest)() + offset);
    } else if (offset < 0) {
        require(position <= (::asc::std::numeric_limits<D>::max)() + offset);
    }
    return static_cast<D>(position - offset);
}

template <class T>
CANN_ASC_STL_API constexpr bool negative(T value) noexcept
{
    if constexpr (::asc::std::is_signed_v<T>) {
        return value < 0;
    }
    return false;
}

template <class U, class T>
CANN_ASC_STL_API constexpr U magnitude(T value) noexcept
{
    return negative(value) ? static_cast<U>(-(value + 1)) + U{1} : static_cast<U>(value);
}

// Work with signs and unsigned magnitudes, never with an overflowing common
// signed intermediate or with a negation of the minimum difference value.
template <class V, class D>
CANN_ASC_STL_API constexpr V offset_value(V first, D position) noexcept
{
    static_assert(integer_v<V> && integer_v<D> && ::asc::std::is_signed_v<D>);
    using U = ::asc::std::common_type_t<::asc::std::make_unsigned_t<V>, ::asc::std::make_unsigned_t<D>>;
    const U left = magnitude<U>(first);
    const U right = magnitude<U>(position);
    const bool first_negative = negative(first);
    const bool position_negative = position < 0;
    bool result_negative = first_negative;
    U result = 0;
    if (first_negative == position_negative) {
        const U bound = first_negative ? magnitude<U>((::asc::std::numeric_limits<V>::lowest)()) :
                                         static_cast<U>((::asc::std::numeric_limits<V>::max)());
        require(left <= bound && right <= bound - left);
        result = left + right;
    } else {
        result_negative = left < right ? position_negative : first_negative;
        result = left < right ? right - left : left - right;
    }
    if (result == 0) {
        return V{0};
    }
    if (result_negative) {
        require(::asc::std::is_signed_v<V>);
        const U bound = magnitude<U>((::asc::std::numeric_limits<V>::lowest)());
        require(result <= bound);
        return result == bound ? (::asc::std::numeric_limits<V>::lowest)() : static_cast<V>(-static_cast<V>(result));
    }
    require(result <= static_cast<U>((::asc::std::numeric_limits<V>::max)()));
    return static_cast<V>(result);
}

template <class D, class Index>
CANN_ASC_STL_API constexpr D index_offset(Index index) noexcept
{
    static_assert(integer_v<Index> && integer_v<D> && ::asc::std::is_signed_v<D>);
    using U = ::asc::std::common_type_t<::asc::std::make_unsigned_t<Index>, ::asc::std::make_unsigned_t<D>>;
    require(!negative(index));
    require(static_cast<U>(index) <= static_cast<U>((::asc::std::numeric_limits<D>::max)()));
    return static_cast<D>(index);
}

template <class T>
class state_box {
public:
    CANN_ASC_STL_API constexpr state_box() noexcept = default;
    CANN_ASC_STL_API constexpr state_box(const state_box&) = default;
    CANN_ASC_STL_API constexpr state_box(state_box&&) = default;

    template <class U, ::asc::std::enable_if_t<::asc::std::is_constructible_v<T, U>, int> = 0>
    CANN_ASC_STL_API constexpr explicit state_box(::asc::std::in_place_t, U&& value) noexcept(
        ::asc::std::is_nothrow_constructible_v<T, U>)
        : value_(::asc::std::in_place, ::asc::std::forward<U>(value))
    {}

    CANN_ASC_STL_API constexpr state_box& operator=(const state_box& other) noexcept(
        ::asc::std::is_nothrow_copy_constructible_v<T> &&
        (!::asc::std::is_copy_assignable_v<T> || ::asc::std::is_nothrow_copy_assignable_v<T>))
    {
        if (this != ::asc::std::addressof(other)) {
            if (!other.value_) {
                value_.reset();
            } else if constexpr (::asc::std::is_copy_assignable_v<T>) {
                if (value_) {
                    *value_ = *other.value_;
                } else {
                    value_.emplace(*other.value_);
                }
            } else {
                value_.emplace(*other.value_);
            }
        }
        return *this;
    }

    CANN_ASC_STL_API constexpr state_box& operator=(state_box&& other) noexcept(
        ::asc::std::is_nothrow_move_constructible_v<T> &&
        (!::asc::std::is_move_assignable_v<T> || ::asc::std::is_nothrow_move_assignable_v<T>))
    {
        if (this != ::asc::std::addressof(other)) {
            if (!other.value_) {
                value_.reset();
            } else if constexpr (::asc::std::is_move_assignable_v<T>) {
                if (value_) {
                    *value_ = ::asc::std::move(*other.value_);
                } else {
                    value_.emplace(::asc::std::move(*other.value_));
                }
            } else {
                value_.emplace(::asc::std::move(*other.value_));
            }
        }
        return *this;
    }

    CANN_ASC_STL_API constexpr bool bound() const noexcept
    {
        return value_.has_value();
    }
    CANN_ASC_STL_API constexpr T& get() noexcept
    {
        return *value_;
    }
    CANN_ASC_STL_API constexpr const T& get() const noexcept
    {
        return *value_;
    }

private:
    ::asc::std::optional<T> value_;
};

template <class T, class U>
CANN_ASC_STL_API constexpr state_box<T> convert_box(const state_box<U>& source) noexcept(
    ::asc::std::is_nothrow_constructible_v<T, const U&>)
{
    return source.bound() ? state_box<T>(::asc::std::in_place, source.get()) : state_box<T>();
}

template <class I, class = void>
struct category {
    using type = ::asc::std::output_iterator_tag;
};
template <class I>
struct category<I, ::asc::std::void_t<typename ::asc::std::iterator_traits<I>::iterator_category>> {
    using type = typename ::asc::std::iterator_traits<I>::iterator_category;
};
template <class I, class = void>
struct concept_tag : category<I> {};
template <class I>
struct concept_tag<I, ::asc::std::void_t<typename I::iterator_concept>> {
    using type = typename I::iterator_concept;
};
template <class I, class = void>
struct navigation {
    using tag = typename concept_tag<I>::type;
    static constexpr int value = ::asc::std::is_base_of_v<::asc::std::random_access_iterator_tag, tag> ? 3 :
        ::asc::std::is_base_of_v<::asc::std::bidirectional_iterator_tag, tag>                          ? 2 :
        ::asc::std::is_base_of_v<::asc::std::forward_iterator_tag, tag>                                ? 1 :
                                                                                                         0;
};
template <class I>
struct navigation<I, ::asc::std::void_t<decltype(I::__iterator_rank)>> {
    static constexpr int value = I::__iterator_rank;
};
template <int Rank>
using navigation_tag = ::asc::std::conditional_t<(Rank >= 3), ::asc::std::random_access_iterator_tag,
    ::asc::std::conditional_t<(Rank >= 2), ::asc::std::bidirectional_iterator_tag,
        ::asc::std::conditional_t<(Rank >= 1), ::asc::std::forward_iterator_tag, ::asc::std::input_iterator_tag>>>;

template <class I, class = void>
struct equality : ::asc::std::false_type {};
template <class I>
struct equality<I,
    ::asc::std::void_t<decltype(static_cast<bool>(::asc::std::declval<const I&>() == ::asc::std::declval<const I&>()))>>
    : ::asc::std::true_type {};
template <class I, class = void>
struct readable : ::asc::std::false_type {};
template <class I>
struct readable<I, ::asc::std::void_t<::asc::std::iter_value_t<I>, ::asc::std::iter_reference_t<I>>>
    : ::asc::std::bool_constant<!::asc::std::is_void_v<::asc::std::iter_value_t<I>>> {};

template <class I, class = void>
struct difference {
    using type = ::asc::std::ptrdiff_t;
};
template <class I>
struct difference<I, ::asc::std::void_t<::asc::std::iter_difference_t<I>>> {
    using raw = ::asc::std::iter_difference_t<I>;
    using type = ::asc::std::conditional_t<::asc::std::is_void_v<raw>, ::asc::std::ptrdiff_t, raw>;
};
template <class I>
using difference_t = typename difference<I>::type;

template <class T>
class arrow_value {
public:
    template <class U>
    CANN_ASC_STL_API constexpr explicit arrow_value(U&& value) noexcept(::asc::std::is_nothrow_constructible_v<T, U>)
        : value_(::asc::std::forward<U>(value))
    {}
    CANN_ASC_STL_API constexpr const T* operator->() const noexcept
    {
        return ::asc::std::addressof(value_);
    }

private:
    T value_;
};

template <class R>
using arrow_type = ::asc::std::conditional_t<::asc::std::is_reference_v<R>,
    ::asc::std::add_pointer_t<::asc::std::remove_reference_t<R>>, arrow_value<::asc::std::remove_cvref_t<R>>>;

template <class R>
CANN_ASC_STL_API constexpr arrow_type<R> arrow(R&& value) noexcept(
    ::asc::std::is_reference_v<R> || ::asc::std::is_nothrow_constructible_v<::asc::std::remove_cvref_t<R>, R>)
{
    if constexpr (::asc::std::is_reference_v<R>) {
        return ::asc::std::addressof(value);
    } else {
        return arrow_type<R>(::asc::std::forward<R>(value));
    }
}

template <class R>
using moved_reference =
    ::asc::std::conditional_t<::asc::std::is_lvalue_reference_v<R>, ::asc::std::remove_reference_t<R>&&, R>;

template <class V>
class postfix_value {
public:
    template <class R>
    CANN_ASC_STL_API constexpr explicit postfix_value(R&& value) noexcept(::asc::std::is_nothrow_constructible_v<V, R>)
        : value_(::asc::std::forward<R>(value))
    {}
    CANN_ASC_STL_API constexpr V operator*() && noexcept(::asc::std::is_nothrow_move_constructible_v<V>)
    {
        // NOLINTNEXTLINE(build/include_what_you_use)
        return ::asc::std::move(value_);
    }
    template <class T = V, ::asc::std::enable_if_t<::asc::std::is_copy_constructible_v<T>, int> = 0>
    CANN_ASC_STL_API constexpr V operator*() const& noexcept(::asc::std::is_nothrow_copy_constructible_v<V>)
    {
        return value_;
    }

private:
    V value_;
};

template <class I>
CANN_ASC_STL_API constexpr I old_position(I& current) noexcept(::asc::std::is_nothrow_copy_constructible_v<I> &&
    ::asc::std::is_nothrow_move_constructible_v<I> && noexcept(++current))
{
    I old(current);
    ++current;
    return old;
}

template <class I>
CANN_ASC_STL_API constexpr bool read_postfix_nothrow() noexcept
{
    if constexpr (I::__iterator_rank >= 1) {
        return noexcept(old_position(::asc::std::declval<I&>()));
    } else if constexpr (::asc::std::is_constructible_v<typename I::value_type, typename I::reference>) {
        return noexcept(postfix_value<typename I::value_type>(*::asc::std::declval<I&>())) &&
            noexcept(++::asc::std::declval<I&>()) &&
            ::asc::std::is_nothrow_move_constructible_v<typename I::value_type>;
    } else {
        return noexcept(++::asc::std::declval<I&>());
    }
}

template <class I>
CANN_ASC_STL_API constexpr auto read_postfix(I& current) noexcept(read_postfix_nothrow<I>())
{
    if constexpr (I::__iterator_rank >= 1) {
        return old_position(current);
    } else if constexpr (::asc::std::is_constructible_v<typename I::value_type, typename I::reference>) {
        postfix_value<typename I::value_type> old(*current);
        ++current;
        return old;
    } else {
        static_assert(CANN_ASC_STL_DETAIL_HAS_CXX20() || !::asc::std::is_same_v<I, I>,
            "C++17 single-pass input must preserve its old value");
        ++current;
    }
}

// Position operations are shared, but availability follows the underlying
// navigation protocol, independently of the legacy readable/output category.
template <class Derived, class D>
class position_facade {
    static_assert(integer_v<D> && ::asc::std::is_signed_v<D>, "iterator difference must be a signed integer");
    CANN_ASC_STL_API constexpr Derived& self() noexcept
    {
        return static_cast<Derived&>(*this);
    }

public:
    template <class T = Derived>
    CANN_ASC_STL_API constexpr Derived& operator++() noexcept(noexcept(::asc::std::declval<T&>().__increment()))
    {
        self().__increment();
        return self();
    }
    template <class T = Derived>
    CANN_ASC_STL_API constexpr auto operator++(int) noexcept(
        noexcept(::asc::std::declval<T&>().__postfix())) -> decltype(::asc::std::declval<T&>().__postfix())
    {
        return self().__postfix();
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 2), int> = 0>
    CANN_ASC_STL_API constexpr Derived& operator--() noexcept(noexcept(::asc::std::declval<T&>().__decrement()))
    {
        self().__decrement();
        return self();
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 2), int> = 0>
    CANN_ASC_STL_API constexpr Derived operator--(int) noexcept(::asc::std::is_nothrow_copy_constructible_v<T> &&
        ::asc::std::is_nothrow_move_constructible_v<T> && noexcept(::asc::std::declval<T&>().__decrement()))
    {
        Derived old(self());
        --self();
        return old;
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API constexpr Derived& operator+=(D n) noexcept(noexcept(::asc::std::declval<T&>().__advance(n)))
    {
        self().__advance(n);
        return self();
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API constexpr Derived& operator-=(D n) noexcept(noexcept(::asc::std::declval<T&>().__retreat(n)))
    {
        self().__retreat(n);
        return self();
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API constexpr auto operator[](D n) const noexcept(noexcept(::asc::std::declval<const T&>().__at(n))) ->
        typename T::reference
    {
        return static_cast<const Derived&>(*this).__at(n);
    }

    template <class T = Derived, ::asc::std::enable_if_t<T::__iterator_equality, int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator==(const Derived& a, const Derived& b) noexcept(
        noexcept(a.__equal(b)))
    {
        return a.__is_bound() == b.__is_bound() && (!a.__is_bound() || a.__equal(b));
    }
    template <class T = Derived, ::asc::std::enable_if_t<T::__iterator_equality, int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator!=(const Derived& a, const Derived& b) noexcept(noexcept(a == b))
    {
        return !(a == b);
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API friend constexpr D operator-(const Derived& a, const Derived& b) noexcept(
        noexcept(a.__distance(b)))
    {
        require(a.__is_bound() && b.__is_bound());
        return a.__distance(b);
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator<(const Derived& a, const Derived& b) noexcept(noexcept(a.__less(b)))
    {
        require(a.__is_bound() && b.__is_bound());
        return a.__less(b);
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator>(const Derived& a, const Derived& b) noexcept(noexcept(b < a))
    {
        return b < a;
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator<=(const Derived& a, const Derived& b) noexcept(noexcept(b < a))
    {
        return !(b < a);
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator>=(const Derived& a, const Derived& b) noexcept(noexcept(a < b))
    {
        return !(a < b);
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API friend constexpr Derived operator+(const Derived& a, D n) noexcept(
        ::asc::std::is_nothrow_copy_constructible_v<T> && ::asc::std::is_nothrow_move_constructible_v<T> &&
        noexcept(::asc::std::declval<T&>() += n))
    {
        Derived result(a);
        result += n;
        return result;
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API friend constexpr Derived operator+(D n, const Derived& a) noexcept(noexcept(a + n))
    {
        return a + n;
    }
    template <class T = Derived, ::asc::std::enable_if_t<(T::__iterator_rank >= 3), int> = 0>
    CANN_ASC_STL_API friend constexpr Derived operator-(const Derived& a, D n) noexcept(
        ::asc::std::is_nothrow_copy_constructible_v<T> && ::asc::std::is_nothrow_move_constructible_v<T> &&
        noexcept(::asc::std::declval<T&>() -= n))
    {
        Derived result(a);
        result -= n;
        return result;
    }
};

template <class Derived, class D>
class logical_position : public position_facade<Derived, D> {
public:
    static_assert(integer_v<D> && ::asc::std::is_signed_v<D>, "iterator difference must be a signed integer");
    static constexpr int __iterator_rank = 3;
    static constexpr bool __iterator_equality = true;
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return bound_;
    }
    CANN_ASC_STL_API constexpr D index() const noexcept
    {
        return position_;
    }
    CANN_ASC_STL_API constexpr void __advance(D n) noexcept
    {
        require(static_cast<const Derived&>(*this).__is_bound());
        position_ = add(position_, n);
    }
    CANN_ASC_STL_API constexpr void __retreat(D n) noexcept
    {
        require(static_cast<const Derived&>(*this).__is_bound());
        position_ = subtract(position_, n);
    }
    CANN_ASC_STL_API constexpr void __increment() noexcept
    {
        __advance(D{1});
    }
    CANN_ASC_STL_API constexpr void __decrement() noexcept
    {
        __retreat(D{1});
    }
    CANN_ASC_STL_API constexpr bool __equal(const Derived& other) const noexcept
    {
        return position_ == other.index();
    }
    CANN_ASC_STL_API constexpr bool __less(const Derived& other) const noexcept
    {
        return position_ < other.index();
    }
    CANN_ASC_STL_API constexpr D __distance(const Derived& other) const noexcept
    {
        return subtract(position_, other.index());
    }
    template <class S = Derived>
    CANN_ASC_STL_API constexpr S __postfix() noexcept(noexcept(old_position(::asc::std::declval<S&>())))
    {
        return old_position(static_cast<Derived&>(*this));
    }

protected:
    CANN_ASC_STL_API constexpr logical_position() noexcept = default;
    CANN_ASC_STL_API constexpr logical_position(bool bound, D position) noexcept : position_(position), bound_(bound)
    {}
    D position_ = 0;
    bool bound_ = false;
};

}  // namespace asc::detail::iterator_detail

#endif  // CANN_ASC_STL_ASC___ITERATOR_SUPPORT_H
