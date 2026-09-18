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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_ADVANCE_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_ADVANCE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/convert_to_integral.h>
#include <asc/std/__utility/move.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _InputIter, class _Distance,
    class _IntegralDistance = decltype(::asc::std::__convert_to_integral(::asc::std::declval<_Distance>())),
    class = enable_if_t<is_integral_v<_IntegralDistance>>>
CANN_ASC_STL_API constexpr void advance(_InputIter& __i, _Distance __orig_n)
{
    using _Difference = typename iterator_traits<_InputIter>::difference_type;
    _Difference __n = static_cast<_Difference>(::asc::std::__convert_to_integral(__orig_n));
    if constexpr (__has_random_access_traversal<_InputIter>)  // To support pointers to incomplete types
    {
        __i += __n;
    } else if constexpr (__has_bidirectional_traversal<_InputIter>) {
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

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

// [range.iter.op.advance]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__advance)
struct __fn {
private:
    template <class _Iter_difference>
    [[nodiscard]] CANN_ASC_STL_API static constexpr auto __magnitude_geq(
        _Iter_difference __a, _Iter_difference __b) noexcept
    {
        return __a == 0 ? __b == 0 :  //
            __a > 0 ? __a >= __b :
                      __a <= __b;
    }

public:
    // Preconditions: If `I` does not model `bidirectional_iterator`, `n` is not negative.

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_or_output_iterator<_Ip>)
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

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip, class _Sp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_or_output_iterator<_Ip> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sp, _Ip>)
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

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip, class _Sp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_or_output_iterator<_Ip> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sp, _Ip>)
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
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto advance = __advance::__fn{};

// Avoid using the public CPO internally so lookup stays constrained to this implementation.
using __advance_cpo = __advance::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES
#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_ADVANCE_H
