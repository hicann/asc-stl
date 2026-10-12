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
#include <asc/std/__type_traits/enable_if.h>
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
// ASC 设备侧无断言机制
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#elif defined(ASC_ENABLE_HOST_ASSERTIONS)
#ifdef NDEBUG
// NDEBUG 下 <assert.h> 未必已包含，手工补声明
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

// 迭代器/哨兵可用的整数类约束（基座 __iterator/concepts.h 无此内部件，按 dev 语义就地内联）。
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class T>
concept __integer_like = integral<T> && !same_as<T, bool>;

template <class T>
concept __signed_integer_like = signed_integral<T>;

template <class T>
concept __integer_like_with_usable_difference_type =
    __signed_integer_like<T> || (__integer_like<T> && weakly_incrementable<T>);

#else  // ^^^ concepts ^^^ / vvv !concepts vvv

// 非概念路径：用 trait 等价式表达（usable_difference_type 检查降为整型判定，与基座同级）。
template <class T>
inline constexpr bool __integer_like = is_integral_v<T> && !is_same_v<T, bool>;

template <class T>
inline constexpr bool __signed_integer_like = is_integral_v<T> && is_signed_v<T>;

template <class T>
inline constexpr bool __integer_like_with_usable_difference_type = __integer_like<T>;

#endif  // !concepts

// _IotaDiffT 等价：有符号整型即自身；否则取 ptrdiff_t 与该类型的公共类型。
template <class T>
using __repeat_view_iterator_difference_t =
    conditional_t<__signed_integer_like<T>, T, common_type_t<__PTRDIFF_TYPE__, T>>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <move_constructible T, semiregular Bound = __PTRDIFF_TYPE__>
    requires(is_object_v<T> && is_same_v<T, remove_cv_t<T>> &&
        (__integer_like_with_usable_difference_type<Bound> || is_same_v<Bound, unreachable_sentinel_t>))
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
// 设备编译下 concept 约束求值不可用（纯 SIMT 后端），非概念路径保持与基座同级的无约束形状。
// Bound 默认值与无界构造入口按产品冻结合同保持基座形状（有界 __PTRDIFF_TYPE__；views::repeat 仅双参，
// 单参无界形态为负向边界用例显式排除）。
template <class T, class Bound = __PTRDIFF_TYPE__>
#endif  // !concepts
class repeat_view : public view_interface<repeat_view<T, Bound>> {
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
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
    CANN_ASC_STL_API constexpr repeat_view() = default;
#endif  // !concepts

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class T2 = T>
        requires(!same_as<T2, repeat_view> && copy_constructible<T2>)
    CANN_ASC_STL_API constexpr explicit repeat_view(const T2& value, Bound bound_sentinel)
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
    CANN_ASC_STL_API constexpr explicit repeat_view(const T& value, Bound bound_sentinel)
#endif  // !concepts
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        : value_(in_place_t{}, value), bound_(bound_sentinel)
#else
        : value_(value), bound_(bound_sentinel)
#endif
    {
        if constexpr (!is_same_v<Bound, unreachable_sentinel_t> && is_signed_v<Bound>) {
            CANN_ASC_STL_DETAIL_ASSERT(bound_ >= 0, "The value of bound must be greater than or equal to 0");
        }
    }

    CANN_ASC_STL_API constexpr explicit repeat_view(T&& value, Bound bound_sentinel)
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        : value_(in_place_t{}, ::asc::std::move(value)), bound_(bound_sentinel)
#else
        : value_(::asc::std::move(value)), bound_(bound_sentinel)
#endif
    {
        if constexpr (!is_same_v<Bound, unreachable_sentinel_t> && is_signed_v<Bound>) {
            CANN_ASC_STL_DETAIL_ASSERT(bound_ >= 0, "The value of bound must be greater than or equal to 0");
        }
    }

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class... TArgs, class... BoundArgs>
        requires(constructible_from<T, TArgs...> && constructible_from<Bound, BoundArgs...>)
    CANN_ASC_STL_API constexpr explicit repeat_view(piecewise_construct_t, tuple<TArgs...> value_args,
        tuple<BoundArgs...> bound_args)  // NOLINT(build/include_what_you_use)
#else                                    // ^^^ concepts ^^^ / vvv !concepts vvv
    template <class... TArgs, class... BoundArgs>
    CANN_ASC_STL_API constexpr explicit repeat_view(piecewise_construct_t, tuple<TArgs...> value_args,
        tuple<BoundArgs...> bound_args)  // NOLINT(build/include_what_you_use)
#endif                                   // !concepts
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        : value_(in_place_t{}, ::asc::std::make_from_tuple<T>(::asc::std::move(value_args))),
          bound_(::asc::std::make_from_tuple<Bound>(::asc::std::move(bound_args)))
#else
        : value_(::asc::std::make_from_tuple<T>(::asc::std::move(value_args))),
          bound_(::asc::std::make_from_tuple<Bound>(::asc::std::move(bound_args)))
#endif
    {
        if constexpr (!is_same_v<Bound, unreachable_sentinel_t> && is_signed_v<Bound>) {
            CANN_ASC_STL_DETAIL_ASSERT(
                bound_, "The behavior is undefined if Bound is not unreachable_sentinel_t and bound is negative");
        }
    }

    CANN_ASC_STL_API constexpr iterator begin() const
    {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return iterator(::asc::std::addressof(*value_));
#else
        return iterator(::asc::std::addressof(value_));
#endif
    }
    CANN_ASC_STL_API constexpr auto end() const noexcept(is_nothrow_copy_constructible_v<Bound>)
    {
        if constexpr (is_same_v<Bound, unreachable_sentinel_t>) {
            return unreachable_sentinel;
        } else {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
            return iterator(::asc::std::addressof(*value_), bound_);
#else
            return iterator(::asc::std::addressof(value_), bound_);
#endif
        }
    }

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class Bound2 = Bound>
        requires(!same_as<Bound2, unreachable_sentinel_t>)
    CANN_ASC_STL_API constexpr auto size() const
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
    template <class Bound2 = Bound, enable_if_t<!is_same_v<Bound2, unreachable_sentinel_t>, int> = 0>
    CANN_ASC_STL_API constexpr auto size() const
#endif  // !concepts
    {
        return ::asc::std::__to_unsigned_like(bound_);
    }

private:
    // 概念路径用 __movable_box 支持仅可移动元素；非概念路径（C++17 与设备编译）保持
    // 基座惯用的平凡成员形状（基座 __movable_box 仅在 C++20 下提供）。
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __movable_box<T> value_;
#else
    T value_{};
#endif
    CANN_ASC_STL_NO_UNIQUE_ADDRESS Bound bound_ = Bound();
};

template <class T, class Bound>
repeat_view(T, Bound) -> repeat_view<T, Bound>;

namespace views {
// 按产品冻结合同仅提供双参有界形态；单参无界 repeat 为负向边界用例显式排除，不提供入口。
struct __repeat_fn {
    template <class T, class Bound>
    CANN_ASC_STL_API constexpr repeat_view<remove_cvref_t<T>, remove_cvref_t<Bound>> operator()(
        T&& value, Bound&& bound_sentinel) const
    {
        return repeat_view<remove_cvref_t<T>, remove_cvref_t<Bound>>(::asc::std::forward<T>(value),
            ::asc::std::forward<Bound>(bound_sentinel));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __repeat_fn repeat{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_REPEAT_VIEW_H
