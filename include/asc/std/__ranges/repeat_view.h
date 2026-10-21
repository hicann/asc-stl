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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_REPEAT_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_REPEAT_VIEW_H

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
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__concepts/arithmetic.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__concepts/semiregular.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/unreachable_sentinel.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/iota_view.h>
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/piecewise_construct.h>
#include <asc/std/tuple>

#ifndef CANN_ASC_STL_DETAIL_ASSERT
#ifndef ASC_ENABLE_ASSERTIONS
#ifdef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#define ASC_ENABLE_ASSERTIONS
#endif  // CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // !ASC_ENABLE_ASSERTIONS

#ifndef ASC_ENABLE_HOST_ASSERTIONS
#ifdef ASC_ENABLE_ASSERTIONS
#define ASC_ENABLE_HOST_ASSERTIONS
#endif  // ASC_ENABLE_ASSERTIONS
#endif  // !ASC_ENABLE_HOST_ASSERTIONS

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// ASC device side has no assertion mechanism
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#elif defined(ASC_ENABLE_HOST_ASSERTIONS)
#ifdef NDEBUG
// <assert.h> is not necessarily included under NDEBUG; declare the prototype manually
extern "C" {
void __assert_fail(const char* __assertion, const char* __file, unsigned int __line, const char* __function) noexcept
    __attribute__((__noreturn__));
}  // extern "C"
#else
#include <assert.h>
#endif  // NDEBUG
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    __builtin_expect(static_cast<bool>(expression), 1) ? (void)0 : __assert_fail(message, __FILE__, __LINE__, __func__)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#endif  // CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#endif  // !CANN_ASC_STL_DETAIL_ASSERT

namespace asc::std::ranges {

// Integer-like constraints for iterators/sentinels, inlined here because
// __iterator/concepts.h does not provide these internals.

template <class T>
CANN_ASC_STL_DETAIL_CONCEPT __integer_like = integral<T> && !same_as<T, bool>;

template <class T>
CANN_ASC_STL_DETAIL_CONCEPT __signed_integer_like = signed_integral<T>;

template <class T>
CANN_ASC_STL_DETAIL_CONCEPT __integer_like_with_usable_difference_type =
    __signed_integer_like<T> || (__integer_like<T> && weakly_incrementable<T>);

// Equivalent of _IotaDiffT: a signed-integer-like type maps to itself; otherwise
// take the common type of ptrdiff_t and T.
template <class T>
using __repeat_view_iterator_difference_t =
    conditional_t<__signed_integer_like<T>, T, common_type_t<__PTRDIFF_TYPE__, T>>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <move_constructible T, semiregular Bound = __PTRDIFF_TYPE__>
    requires(is_object_v<T> && is_same_v<T, remove_cv_t<T>> &&
        (__integer_like_with_usable_difference_type<Bound> || is_same_v<Bound, unreachable_sentinel_t>))
#else
template <class T, class Bound = __PTRDIFF_TYPE__>
#endif
class repeat_view : public view_interface<repeat_view<T, Bound>> {
    static_assert(move_constructible<T> && semiregular<Bound> &&
            ((is_object_v<T> && is_same_v<T, remove_cv_t<T>> &&
                (__integer_like_with_usable_difference_type<Bound> || is_same_v<Bound, unreachable_sentinel_t>))),
        "range view constraints are not satisfied");

    class iterator {
    public:
        using iterator_concept = random_access_iterator_tag;
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = __repeat_view_iterator_difference_t<
            conditional_t<is_same_v<Bound, unreachable_sentinel_t>, __PTRDIFF_TYPE__, Bound>>;
        using reference = const T&;
        using pointer = const T*;

        CANN_ASC_STL_API constexpr iterator() = default;
        CANN_ASC_STL_API constexpr explicit iterator(const T* value,
            conditional_t<is_same_v<Bound, unreachable_sentinel_t>, __PTRDIFF_TYPE__, Bound> bound_sentinel =
                conditional_t<is_same_v<Bound, unreachable_sentinel_t>, __PTRDIFF_TYPE__,
                    Bound>{}) noexcept(is_nothrow_copy_constructible_v<conditional_t<is_same_v<Bound,
                                                                                         unreachable_sentinel_t>,
                __PTRDIFF_TYPE__, Bound>>)
            : value_(value), current_(bound_sentinel)
        {}

        CANN_ASC_STL_API constexpr const T& operator*() const noexcept
        {
            return *value_;
        }
        CANN_ASC_STL_API constexpr iterator& operator++()
        {
            ++current_;
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator operator++(int)
        {
            auto tmp = *this;
            ++*this;
            return tmp;
        }
        CANN_ASC_STL_API constexpr iterator& operator--()
        {
            if constexpr (!is_same_v<Bound, unreachable_sentinel_t>) {
                CANN_ASC_STL_DETAIL_ASSERT(current_ > 0, "The value of bound must be greater than or equal to 0");
            }
            --current_;
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator operator--(int)
        {
            auto tmp = *this;
            --*this;
            return tmp;
        }
        CANN_ASC_STL_API constexpr iterator& operator+=(difference_type value)
        {
            if constexpr (!is_same_v<Bound, unreachable_sentinel_t>) {
                CANN_ASC_STL_DETAIL_ASSERT(
                    current_ + value >= 0, "The value of bound must be greater than or equal to 0");
            }
            current_ += static_cast<decltype(current_)>(value);
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator& operator-=(difference_type value)
        {
            if constexpr (!is_same_v<Bound, unreachable_sentinel_t>) {
                CANN_ASC_STL_DETAIL_ASSERT(
                    current_ - value >= 0, "The value of bound must be greater than or equal to 0");
            }
            current_ -= static_cast<decltype(current_)>(value);
            return *this;
        }
        CANN_ASC_STL_API constexpr const T& operator[](difference_type value) const noexcept
        {
            return *(*this + value);
        }
        friend CANN_ASC_STL_API constexpr bool operator==(iterator left, iterator right)
        {
            return left.current_ == right.current_;
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(iterator left, iterator right)
        {
            return !(left == right);
        }
        friend CANN_ASC_STL_API constexpr bool operator<(iterator left, iterator right)
        {
            return left.current_ < right.current_;
        }
        friend CANN_ASC_STL_API constexpr bool operator<=(iterator left, iterator right)
        {
            return left.current_ <= right.current_;
        }
        friend CANN_ASC_STL_API constexpr bool operator>(iterator left, iterator right)
        {
            return left.current_ > right.current_;
        }
        friend CANN_ASC_STL_API constexpr bool operator>=(iterator left, iterator right)
        {
            return left.current_ >= right.current_;
        }
        friend CANN_ASC_STL_API constexpr iterator operator+(iterator iter, difference_type value)
        {
            iter += value;
            return iter;
        }
        friend CANN_ASC_STL_API constexpr iterator operator+(difference_type value, iterator iter)
        {
            iter += value;
            return iter;
        }
        friend CANN_ASC_STL_API constexpr iterator operator-(iterator iter, difference_type value)
        {
            iter -= value;
            return iter;
        }
        friend CANN_ASC_STL_API constexpr difference_type operator-(iterator left, iterator right)
        {
            return static_cast<difference_type>(left.current_) - static_cast<difference_type>(right.current_);
        }

    private:
        const T* value_ = nullptr;
        conditional_t<is_same_v<Bound, unreachable_sentinel_t>, __PTRDIFF_TYPE__, Bound> current_{};
    };

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr repeat_view()
        requires default_initializable<T>
    = default;
#else
    template <bool __asc_enabled = true, enable_if_t<__asc_enabled && (default_initializable<T>), int> = 0>
    CANN_ASC_STL_API constexpr repeat_view()
    {}
#endif

    CANN_ASC_STL_DETAIL_TEMPLATE(class T2 = T)
    CANN_ASC_STL_DETAIL_REQUIRES(((!same_as<T2, repeat_view> && copy_constructible<T2>)))
    CANN_ASC_STL_API constexpr explicit repeat_view(const T2& value, Bound bound_sentinel)
        : value_(in_place_t{}, value), bound_(bound_sentinel)
    {
        if constexpr (!is_same_v<Bound, unreachable_sentinel_t> && is_signed_v<Bound>) {
            CANN_ASC_STL_DETAIL_ASSERT(bound_ >= 0, "The value of bound must be greater than or equal to 0");
        }
    }

    CANN_ASC_STL_API constexpr explicit repeat_view(T&& value, Bound bound_sentinel)
        : value_(in_place_t{}, ::asc::std::move(value)), bound_(bound_sentinel)
    {
        if constexpr (!is_same_v<Bound, unreachable_sentinel_t> && is_signed_v<Bound>) {
            CANN_ASC_STL_DETAIL_ASSERT(bound_ >= 0, "The value of bound must be greater than or equal to 0");
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class... TArgs, class... BoundArgs)
    CANN_ASC_STL_DETAIL_REQUIRES(((constructible_from<T, TArgs...> && constructible_from<Bound, BoundArgs...>)))
    CANN_ASC_STL_API constexpr explicit repeat_view(piecewise_construct_t, tuple<TArgs...> value_args,
        tuple<BoundArgs...> bound_args)  // NOLINT(build/include_what_you_use)
        : value_(in_place_t{}, ::asc::std::make_from_tuple<T>(::asc::std::move(value_args))),
          bound_(::asc::std::make_from_tuple<Bound>(::asc::std::move(bound_args)))
    {
        if constexpr (!is_same_v<Bound, unreachable_sentinel_t> && is_signed_v<Bound>) {
            CANN_ASC_STL_DETAIL_ASSERT(
                bound_ >= 0, "The behavior is undefined if Bound is not unreachable_sentinel_t and bound is negative");
        }
    }

    CANN_ASC_STL_API constexpr iterator begin() const
    {
        return iterator(::asc::std::addressof(*value_));
    }
    CANN_ASC_STL_API constexpr auto end() const noexcept(is_nothrow_copy_constructible_v<Bound>)
    {
        if constexpr (is_same_v<Bound, unreachable_sentinel_t>) {
            return unreachable_sentinel;
        } else {
            return iterator(::asc::std::addressof(*value_), bound_);
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Bound2 = Bound)
    CANN_ASC_STL_DETAIL_REQUIRES(((!same_as<Bound2, unreachable_sentinel_t>)))
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::__to_unsigned_like(bound_);
    }

private:
    // The shared movable box reconstructs a non-assignable stored value.
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __movable_box<T> value_;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS Bound bound_ = Bound();
};

template <class T, class Bound>
CANN_ASC_STL_HOST_DEVICE repeat_view(T, Bound) -> repeat_view<T, Bound>;

namespace views {
// Only the two-argument bounded form is provided; the single-argument unbounded
// repeat is deliberately excluded and has no entry point.
struct __repeat_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class T, class Bound, class Stored = remove_cvref_t<T>, class Count = remove_cvref_t<Bound>)
    CANN_ASC_STL_DETAIL_REQUIRES(
        is_object_v<Stored>&& move_constructible<Stored>&& same_as<Stored, remove_cv_t<Stored>>&& semiregular<Count> &&
        (__integer_like_with_usable_difference_type<Count> || same_as<Count, unreachable_sentinel_t>) &&
        constructible_from<Stored, T> && constructible_from<Count, Bound>)
    CANN_ASC_STL_API constexpr repeat_view<Stored, Count> operator()(T&& value, Bound&& bound_sentinel) const
    {
        return repeat_view<remove_cvref_t<T>, remove_cvref_t<Bound>>(::asc::std::forward<T>(value),
            ::asc::std::forward<Bound>(bound_sentinel));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __repeat_fn repeat{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_REPEAT_VIEW_H
