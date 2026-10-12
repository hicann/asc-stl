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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_ADVANCE_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_ADVANCE_H

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
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/convert_to_integral.h>
#include <asc/std/__utility/move.h>

// dev 版 <asc/std/__asc/assert.h> 断言链的最小等价内联（规则册条款5，#ifndef 守卫防重）：
// debug 构建（_DEBUG/DEBUG）启用 ENABLE_DEBUG_MODE，进而启用宿主断言；设备侧无断言机制，恒为 no-op。
#ifndef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#if defined(_DEBUG) || defined(DEBUG)
#define CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // defined(_DEBUG) || defined(DEBUG)
#endif  // !CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE

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

#ifndef CANN_ASC_STL_DETAIL_ASSERT
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// ASC 设备侧无断言机制
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#elif defined(ASC_ENABLE_HOST_ASSERTIONS)
#ifdef NDEBUG
// NDEBUG 下 <assert.h> 未必已包含，按 dev 版做法手工补声明
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
#endif  // ASC_ENABLE_HOST_ASSERTIONS
#endif  // !CANN_ASC_STL_DETAIL_ASSERT

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __advance_detail {

// 本文件内联的遍历探测（与 __iterator/distance.h 的同名探测同形）：对
// iterator_traits<Iter>::iterator_category 与成员 iterator_concept 各做一次 SFINAE 友好的
// tag 可转换性探测，用于 if constexpr 分派以支持指向不完整类型的指针。
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
inline constexpr bool __has_bidirectional_traversal =
    __has_iterator_category_convertible_to<Iter, bidirectional_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, bidirectional_iterator_tag>;

template <class Iter>
inline constexpr bool __has_random_access_traversal =
    __has_iterator_category_convertible_to<Iter, random_access_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, random_access_iterator_tag>;

}  // namespace __advance_detail

template <class InputIter, class Distance>
CANN_ASC_STL_API constexpr void advance(InputIter& __i, Distance __orig_n)
{
    using difference_type = typename iterator_traits<InputIter>::difference_type;
    difference_type __n = static_cast<difference_type>(::asc::std::__convert_to_integral(__orig_n));
    // To support pointers to incomplete types
    if constexpr (__advance_detail::__has_random_access_traversal<InputIter>) {
        __i += __n;
    } else if constexpr (__advance_detail::__has_bidirectional_traversal<InputIter>) {
        if (__n >= 0) {
            for (; __n > 0; --__n) {
                ++__i;
            }
        } else {
            for (; __n < 0; ++__n) {
                --__i;
            }
        }
    } else {
        CANN_ASC_STL_DETAIL_ASSERT(
            __n >= 0, "Attempt to advance(it, n) with negative n on a non-bidirectional iterator");
        for (; __n > 0; --__n) {
            ++__i;
        }
    }
}

CANN_ASC_STL_END_NAMESPACE

// [range.iter.op.advance]

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

namespace __advance {
struct __fn {
private:
    template <class _IterDifference>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr auto __magnitude_geq(
        _IterDifference __a, _IterDifference __b) noexcept
    {
        return __a == 0 ? __b == 0 :  //
            __a > 0 ? __a >= __b :
                      __a <= __b;
    }

public:
    // Preconditions: If `I` does not model `bidirectional_iterator`, `n` is not negative.

    template <class _Ip, enable_if_t<input_or_output_iterator<_Ip>, int> = 0>
    CANN_ASC_STL_API constexpr void operator()(_Ip& __i, iter_difference_t<_Ip> __n) const
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __n >= 0 || bidirectional_iterator<_Ip>, "If `n < 0`, then `bidirectional_iterator<I>` must be true.");

        // If `I` models `random_access_iterator`, equivalent to `i += n`.
        if constexpr (random_access_iterator<_Ip>) {
            __i += __n;
            return;
        } else if constexpr (bidirectional_iterator<_Ip>) {
            // Otherwise, if `n` is non-negative, increments `i` by `n`.
            while (__n > 0) {
                --__n;
                ++__i;
            }
            // Otherwise, decrements `i` by `-n`.
            while (__n < 0) {
                ++__n;
                --__i;
            }
            return;
        } else {
            // Otherwise, if `n` is non-negative, increments `i` by `n`.
            while (__n > 0) {
                --__n;
                ++__i;
            }
            return;
        }
    }

    template <class _Ip, class _Sp, enable_if_t<input_or_output_iterator<_Ip> && sentinel_for<_Sp, _Ip>, int> = 0>
    CANN_ASC_STL_API constexpr void operator()(_Ip& __i, _Sp __bound_sentinel) const
    {
        // If `I` and `S` model `assignable_from<I&, S>`, equivalent to `i = std::move(bound_sentinel)`.
        if constexpr (assignable_from<_Ip&, _Sp>) {
            __i = ::asc::std::move(__bound_sentinel);  // NOLINT(build/include_what_you_use)
        }
        // Otherwise, if `S` and `I` model `sized_sentinel_for<S, I>`,
        // equivalent to `ranges::advance(i, bound_sentinel - i)`.
        else if constexpr (sized_sentinel_for<_Sp, _Ip>) {  // NOLINT(whitespace/newline)
            (*this)(__i, __bound_sentinel - __i);
        }
        // Otherwise, while `bool(i != bound_sentinel)` is true, increments `i`.
        else {  // NOLINT(whitespace/newline)
            while (__i != __bound_sentinel) {
                ++__i;
            }
        }
    }

    // Preconditions:
    //   * If `n > 0`, [i, bound_sentinel) denotes a range.
    //   * If `n == 0`, [i, bound_sentinel) or [bound_sentinel, i) denotes a range.
    //   * If `n < 0`, [bound_sentinel, i) denotes a range, `I` models `bidirectional_iterator`,
    //     and `I` and `S` model `same_as<I, S>`.
    // Returns: `n - M`, where `M` is the difference between the ending and starting position.

    template <class _Ip, class _Sp, enable_if_t<input_or_output_iterator<_Ip> && sentinel_for<_Sp, _Ip>, int> = 0>
    CANN_ASC_STL_API constexpr iter_difference_t<_Ip> operator()(
        _Ip& __i, iter_difference_t<_Ip> __n, _Sp __bound_sentinel) const
    {
        CANN_ASC_STL_DETAIL_ASSERT((__n >= 0) || (bidirectional_iterator<_Ip> && same_as<_Ip, _Sp>),
            "If `n < 0`, then `bidirectional_iterator<I> && same_as<I, S>` must be true.");
        // If `S` and `I` model `sized_sentinel_for<S, I>`:
        if constexpr (sized_sentinel_for<_Sp, _Ip>) {
            // If |n| >= |bound_sentinel - i|, equivalent to `ranges::advance(i, bound_sentinel)`.
            // __magnitude_geq(a, b) returns |a| >= |b|, assuming they have the same sign.
            const auto __M = __bound_sentinel - __i;
            if (__magnitude_geq(__n, __M)) {
                (*this)(__i, __bound_sentinel);
                return __n - __M;
            }

            // Otherwise, equivalent to `ranges::advance(i, n)`.
            (*this)(__i, __n);
            return 0;
        } else {
            // Otherwise, if `n` is non-negative, while `bool(i != bound_sentinel)` is true, increments `i` but at
            // most `n` times.
            while (__i != __bound_sentinel && __n > 0) {
                ++__i;
                --__n;
            }

            // Otherwise, while `bool(i != bound_sentinel)` is true, decrements `i` but at most `-n` times.
            if constexpr (bidirectional_iterator<_Ip> && same_as<_Ip, _Sp>) {
                while (__i != __bound_sentinel && __n < 0) {
                    --__i;
                    ++__n;
                }
            }
            return __n;
        }
    }
};
}  // namespace __advance

inline namespace __cpo {
inline constexpr auto advance = __advance::__fn{};

// Avoid using the public CPO internally so lookup stays constrained to this implementation.
using __advance_cpo = __advance::__fn;
}  // namespace __cpo

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_ADVANCE_H
