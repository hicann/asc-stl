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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_COMMON_ITERATOR_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_COMMON_ITERATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__fwd/common_iterator.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__iterator/variant_like.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_ACCL_BEGIN_HIDDEN_FRIEND_NAMESPACE

template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __postfix_can_reference =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Iter), _Iter& __it)(_Satisfies(__can_reference) * __it++);

template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __use_postfix_proxy =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Iter), )(  // NOLINT(whitespace/parens)
        requires(!__postfix_can_reference<_Iter>), requires(indirectly_readable<_Iter>),
        requires(constructible_from<iter_value_t<_Iter>, iter_reference_t<_Iter>>),
        requires(move_constructible<iter_value_t<_Iter>>));

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator _Iter, sentinel_for<_Iter> _Sent>
    requires(!same_as<_Iter, _Sent> && copyable<_Iter>)
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Iter, class _Sent, enable_if_t<input_or_output_iterator<_Iter>, int>,
    enable_if_t<sentinel_for<_Sent, _Iter>, int>, enable_if_t<(!same_as<_Iter, _Sent> && copyable<_Iter>), int>>
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
class common_iterator {
public:
    // These should be private but older compilers (gcc-7 and clang-14) complain about implicitly
    // naming private types in decltype or auto expressions.
    struct __proxy {
        iter_value_t<_Iter> __value_;

        [[nodiscard]] CANN_ASC_STL_API constexpr const iter_value_t<_Iter>* operator->() const noexcept
        {
            return ::asc::std::addressof(__value_);
        }
    };

    struct __postfix_proxy {
        iter_value_t<_Iter> __value_;

        [[nodiscard]] CANN_ASC_STL_API constexpr const iter_value_t<_Iter>& operator*() const noexcept
        {
            return __value_;
        }
    };

    __variant_like<_Iter, _Sent> __hold_;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr common_iterator() noexcept(is_nothrow_default_constructible_v<_Iter>)
        requires default_initializable<_Iter>
    = default;
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(default_initializable<_I2>)
    CANN_ASC_STL_API constexpr common_iterator() noexcept(is_nothrow_default_constructible_v<_I2>)
    {}
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr common_iterator(const common_iterator&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr common_iterator& operator=(const common_iterator&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr common_iterator(common_iterator&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr common_iterator& operator=(common_iterator&&) = default;

    CANN_ASC_STL_API constexpr common_iterator(_Iter __i) noexcept(is_nothrow_move_constructible_v<_Iter>)
        : __hold_{__construct_first{}, ::asc::std::move(__i)}
    {}

    CANN_ASC_STL_API constexpr common_iterator(_Sent __s) noexcept(is_nothrow_move_constructible_v<_Sent>)
        : __hold_{__construct_second{}, ::asc::std::move(__s)}  // NOLINT(build/include_what_you_use)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2, class _S2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        convertible_to<const _I2&, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND convertible_to<const _S2&, _Sent>)
    CANN_ASC_STL_API constexpr common_iterator(const common_iterator<_I2, _S2>& __other) noexcept(
        is_nothrow_constructible_v<_Iter, const _I2&> && is_nothrow_constructible_v<_Sent, const _S2&>)
        : __hold_{__other.__get_hold()}
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2, class _S2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        convertible_to<const _I2&, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND convertible_to<const _S2&, _Sent>
            CANN_ASC_STL_DETAIL_ACCL_AND assignable_from<_Iter&, const _I2&>
                CANN_ASC_STL_DETAIL_ACCL_AND assignable_from<_Sent&, const _S2&>)
    CANN_ASC_STL_API constexpr common_iterator& operator=(const common_iterator<_I2, _S2>& __other)
    {
        __hold_ = __other.__get_hold();
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) operator*()
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __hold_.__holds_first(), "Attempted to dereference a non-dereferenceable common_iterator");
        return *__hold_.__first_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__dereferenceable<const _I2>)
    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) operator*() const
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __hold_.__holds_first(), "Attempted to dereference a non-dereferenceable common_iterator");
        return *__hold_.__first_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        indirectly_readable<const _I2> CANN_ASC_STL_DETAIL_ACCL_AND(__has_const_arrow<_I2> ||
            is_reference_v<iter_reference_t<_I2>> || constructible_from<iter_value_t<_I2>, iter_reference_t<_I2>>))
    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) operator->() const
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __hold_.__holds_first(), "Attempted to dereference a non-dereferenceable common_iterator");
        if constexpr (__has_const_arrow<_Iter>) {
            return __hold_.__first_;
        } else if constexpr (is_reference_v<iter_reference_t<_Iter>>) {
            auto&& __tmp = *__hold_.__first_;

            return ::asc::std::addressof(__tmp);
        } else {
            return __proxy{*__hold_.__first_};
        }
        CANN_ASC_STL_DETAIL_UNREACHABLE();
    }

    CANN_ASC_STL_API constexpr common_iterator& operator++()
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __hold_.__holds_first(), "Attempted to increment a non-dereferenceable common_iterator");
        ++__hold_.__first_;
        return *this;
    }

    CANN_ASC_STL_API constexpr decltype(auto) operator++(int)
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __hold_.__holds_first(), "Attempted to increment a non-dereferenceable common_iterator");
        if constexpr (forward_iterator<_Iter>) {
            auto __tmp = *this;

            ++*this;
            return __tmp;
        } else if constexpr (__use_postfix_proxy<_Iter>) {
            auto __p = __postfix_proxy{**this};

            ++*this;
            return __p;
        } else {
            return __hold_.__first_++;
        }
        CANN_ASC_STL_DETAIL_UNREACHABLE();
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2, class _S2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        sentinel_for<_S2, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sent, _I2> CANN_ASC_STL_DETAIL_ACCL_AND(
            !equality_comparable_with<_Iter, _I2>))
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const common_iterator& __x, const common_iterator<_I2, _S2>& __y)
    {
        const auto& __y_hold = __y.__get_hold();

        CANN_ASC_STL_DETAIL_ASSERT(
            !__x.__hold_.__valueless_by_exception(), "Attempted to compare a valueless common_iterator");
        CANN_ASC_STL_DETAIL_ASSERT(
            !__y_hold.__valueless_by_exception(), "Attempted to compare a valueless common_iterator");

        const auto __x_contains = __x.__hold_.__contains_;
        const auto __y_contains = __y_hold.__contains_;

        if (__x_contains == __y_contains) {
            return true;
        }

        if (__x_contains == __variant_like_state::__holds_first) {
            return __x.__hold_.__first_ == __y_hold.__second_;
        }

        return __x.__hold_.__second_ == __y_hold.__first_;
    }

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!equality_comparable<_I2>))
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const common_iterator& __x, const common_iterator& __y)
    {
        const auto& __y_hold = __y.__get_hold();

        CANN_ASC_STL_DETAIL_ASSERT(
            !__x.__hold_.__valueless_by_exception(), "Attempted to compare a valueless common_iterator");
        CANN_ASC_STL_DETAIL_ASSERT(
            !__y_hold.__valueless_by_exception(), "Attempted to compare a valueless common_iterator");

        const auto __x_contains = __x.__hold_.__contains_;
        const auto __y_contains = __y_hold.__contains_;

        if (__x_contains == __y_contains) {
            return true;
        }

        if (__x_contains == __variant_like_state::__holds_first) {
            return __x.__hold_.__first_ == __y_hold.__second_;
        }

        return __x.__hold_.__second_ == __y_hold.__first_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!equality_comparable<_I2>))
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const common_iterator& __x, const common_iterator& __y)
    {
        return !(__x == __y);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2, class _S2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        sentinel_for<_S2, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sent, _I2> CANN_ASC_STL_DETAIL_ACCL_AND(
            !equality_comparable_with<_Iter, _I2>))
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const common_iterator& __x, const common_iterator<_I2, _S2>& __y)
    {
        return !(__x == __y);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2, class _S2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        sentinel_for<_S2, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sent, _I2> CANN_ASC_STL_DETAIL_ACCL_AND
            equality_comparable_with<_Iter, _I2>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const common_iterator& __x, const common_iterator<_I2, _S2>& __y)
    {
        const auto& __y_hold = __y.__get_hold();

        CANN_ASC_STL_DETAIL_ASSERT(
            !__x.__hold_.__valueless_by_exception(), "Attempted to compare a valueless common_iterator");
        CANN_ASC_STL_DETAIL_ASSERT(
            !__y_hold.__valueless_by_exception(), "Attempted to compare a valueless common_iterator");

        if (__x.__hold_.__holds_second() && __y_hold.__holds_second()) {
            return true;
        }

        if (__x.__hold_.__holds_first() && __y_hold.__holds_first()) {
            return __x.__hold_.__first_ == __y_hold.__first_;
        }

        if (__x.__hold_.__holds_first()) {
            return __x.__hold_.__first_ == __y_hold.__second_;
        }

        return __x.__hold_.__second_ == __y_hold.__first_;
    }
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(equality_comparable<_I2>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const common_iterator& __x, const common_iterator& __y)
    {
        const auto& __y_hold = __y.__get_hold();

        CANN_ASC_STL_DETAIL_ASSERT(
            !__x.__hold_.__valueless_by_exception(), "Attempted to compare a valueless common_iterator");
        CANN_ASC_STL_DETAIL_ASSERT(
            !__y_hold.__valueless_by_exception(), "Attempted to compare a valueless common_iterator");

        if (__x.__hold_.__holds_second() && __y_hold.__holds_second()) {
            return true;
        }

        if (__x.__hold_.__holds_first() && __y_hold.__holds_first()) {
            return __x.__hold_.__first_ == __y_hold.__first_;
        }

        if (__x.__hold_.__holds_first()) {
            return __x.__hold_.__first_ == __y_hold.__second_;
        }

        return __x.__hold_.__second_ == __y_hold.__first_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(equality_comparable<_I2>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const common_iterator& __x, const common_iterator& __y)
    {
        return !(__x == __y);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2, class _S2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        sentinel_for<_S2, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sent, _I2> CANN_ASC_STL_DETAIL_ACCL_AND
            equality_comparable_with<_Iter, _I2>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const common_iterator& __x, const common_iterator<_I2, _S2>& __y)
    {
        return !(__x == __y);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2, class _S2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        sized_sentinel_for<_I2, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND sized_sentinel_for<_S2, _Iter>
            CANN_ASC_STL_DETAIL_ACCL_AND sized_sentinel_for<_Sent, _I2>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_difference_t<_I2> operator-(
        const common_iterator& __x, const common_iterator<_I2, _S2>& __y)
    {
        const auto& __y_hold = __y.__get_hold();

        CANN_ASC_STL_DETAIL_ASSERT(
            !__x.__hold_.__valueless_by_exception(), "Attempted to subtract from a valueless common_iterator");
        CANN_ASC_STL_DETAIL_ASSERT(
            !__y_hold.__valueless_by_exception(), "Attempted to subtract a valueless common_iterator");

        if (__x.__hold_.__holds_second() && __y_hold.__holds_second()) {
            return 0;
        }

        if (__x.__hold_.__holds_first() && __y_hold.__holds_first()) {
            return __x.__hold_.__first_ - __y_hold.__first_;
        }

        if (__x.__hold_.__holds_first()) {
            return __x.__hold_.__first_ - __y_hold.__second_;
        }

        return __x.__hold_.__second_ - __y_hold.__first_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Iter2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_iterator<_Iter2>)
    CANN_ASC_STL_API friend constexpr iter_rvalue_reference_t<_Iter2> iter_move(const common_iterator& __i) noexcept(
        noexcept(::asc::std::ranges::__iter_move_cpo{}(declval<const _Iter&>())))
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __i.__hold_.__holds_first(), "Attempted to iter_move a non-dereferenceable common_iterator");
        return ::asc::std::ranges::__iter_move_cpo{}(__i.__hold_.__first_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2, class _S2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(indirectly_swappable<_I2, _Iter>)
    CANN_ASC_STL_API friend constexpr void
    iter_swap(const common_iterator& __x, const common_iterator<_I2, _S2>& __y) noexcept(noexcept(
        ::asc::std::ranges::__iter_swap_cpo{}(::asc::std::declval<const _Iter&>(), ::asc::std::declval<const _I2&>())))
    {
        const auto& __y_hold = __y.__get_hold();

        CANN_ASC_STL_DETAIL_ASSERT(
            __x.__hold_.__holds_first(), "Attempted to iter_swap a non-dereferenceable common_iterator");
        CANN_ASC_STL_DETAIL_ASSERT(
            __y_hold.__holds_first(), "Attempted to iter_swap a non-dereferenceable common_iterator");
        return ::asc::std::ranges::__iter_swap_cpo{}(__x.__hold_.__first_, __y_hold.__first_);
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr __variant_like<_Iter, _Sent>& __get_hold() noexcept
    {
        return __hold_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const __variant_like<_Iter, _Sent>& __get_hold() const noexcept
    {
        return __hold_;
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_HIDDEN_FRIEND_NAMESPACE(common_iterator)

template <class _Iter, class _Sent>
struct incrementable_traits<common_iterator<_Iter, _Sent>> {
    using difference_type = iter_difference_t<_Iter>;
};

#if CANN_ASC_STL_DETAIL_COMPILER(GCC)  // GCC breaks with a circular definition here
template <class _Iter, class _Sent>
struct __is_primary_std_template<common_iterator<_Iter, _Sent>> : true_type {};
#endif  // CANN_ASC_STL_DETAIL_COMPILER(GCC)

template <class _Iter, class _Sent>
struct iterator_traits<common_iterator<_Iter, _Sent>, enable_if_t<input_iterator<_Iter>>> {
    using iterator_concept = conditional_t<forward_iterator<_Iter>, forward_iterator_tag, input_iterator_tag>;
    using iterator_category = conditional_t<__has_iterator_category_convertible_to<_Iter, forward_iterator_tag>,
        forward_iterator_tag, input_iterator_tag>;
    using pointer = __iterator_traits_member_pointer_or_arrow_or_void<common_iterator<_Iter, _Sent>>;
    using value_type = iter_value_t<_Iter>;
    using difference_type = iter_difference_t<_Iter>;
    using reference = iter_reference_t<_Iter>;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD
#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_COMMON_ITERATOR_H
