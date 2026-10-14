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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_ITER_SWAP_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_ITER_SWAP_H

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
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/swap.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#ifndef CANN_ASC_STL_DETAIL_ITER_SWAP_DEFINED
#define CANN_ASC_STL_DETAIL_ITER_SWAP_DEFINED
template <class ForwardIterator1, class ForwardIterator2>
CANN_ASC_STL_API constexpr void iter_swap(ForwardIterator1 left, ForwardIterator2 right) noexcept(
    noexcept(swap(*left, *right)))
{
    using ::asc::std::swap;
    swap(*left, *right);  // NOLINT(build/include_what_you_use)
}
#endif

// Customization-point form (ranges CPO): prefer ADL iter_swap(a, b), otherwise
// fall back to swap(*a, *b). The nested namespace keeps the CPO body from
// clashing with the classic asc::std::iter_swap function (the classic function
// stays; the definition under the same guard in __iterator/iter_swap.h keeps
// coexisting).
namespace ranges {
namespace __iter_swap {

template <class _ForwardIterator1, class _ForwardIterator2, class = void>
inline constexpr bool __unqualified_iter_swap = false;

template <class _ForwardIterator1, class _ForwardIterator2>
inline constexpr bool __unqualified_iter_swap<_ForwardIterator1, _ForwardIterator2,
    void_t<decltype(iter_swap(::asc::std::declval<_ForwardIterator1>(), ::asc::std::declval<_ForwardIterator2>()))>> =
    true;

template <class _ForwardIterator1, class _ForwardIterator2, class = void>
inline constexpr bool __readable_swappable = false;

template <class _ForwardIterator1, class _ForwardIterator2>
inline constexpr bool __readable_swappable<_ForwardIterator1, _ForwardIterator2,
    void_t<decltype(swap(*::asc::std::declval<_ForwardIterator1>(), *::asc::std::declval<_ForwardIterator2>()))>> =
    !__unqualified_iter_swap<_ForwardIterator1, _ForwardIterator2>;

template <class _ForwardIterator1, class _ForwardIterator2, class = void>
inline constexpr bool __movable_exchangeable = false;

template <class _ForwardIterator1, class _ForwardIterator2>
inline constexpr bool __movable_exchangeable<_ForwardIterator1, _ForwardIterator2,
    void_t<decltype(::asc::std::iter_move(::asc::std::declval<_ForwardIterator1>())),
        decltype(*::asc::std::declval<_ForwardIterator2>() =
                     ::asc::std::iter_move(::asc::std::declval<_ForwardIterator1>())),
        decltype(*::asc::std::declval<_ForwardIterator1>() =
                     ::asc::std::iter_move(::asc::std::declval<_ForwardIterator2>()))>> =
    !__unqualified_iter_swap<_ForwardIterator1, _ForwardIterator2> &&
    !__readable_swappable<_ForwardIterator1, _ForwardIterator2>;

struct __iter_swap_fn {
    template <class _ForwardIterator1, class _ForwardIterator2,
        enable_if_t<__unqualified_iter_swap<_ForwardIterator1, _ForwardIterator2>, int> = 0>
    CANN_ASC_STL_API constexpr void operator()(_ForwardIterator1&& __a, _ForwardIterator2&& __b) const noexcept(
        noexcept(iter_swap(::asc::std::declval<_ForwardIterator1>(), ::asc::std::declval<_ForwardIterator2>())))
    {
        (void)iter_swap(::asc::std::forward<_ForwardIterator1>(__a), ::asc::std::forward<_ForwardIterator2>(__b));
    }

    template <class _ForwardIterator1, class _ForwardIterator2,
        enable_if_t<__readable_swappable<_ForwardIterator1, _ForwardIterator2>, int> = 0>
    CANN_ASC_STL_API constexpr void operator()(_ForwardIterator1&& __a, _ForwardIterator2&& __b) const
        noexcept(noexcept(swap(*::asc::std::declval<_ForwardIterator1>(), *::asc::std::declval<_ForwardIterator2>())))
    {
        swap(*__a, *__b);  // NOLINT(build/include_what_you_use)
    }

    template <class _ForwardIterator1, class _ForwardIterator2,
        enable_if_t<__movable_exchangeable<_ForwardIterator1, _ForwardIterator2>, int> = 0>
    CANN_ASC_STL_API constexpr void operator()(_ForwardIterator1&& __a, _ForwardIterator2&& __b) const
        noexcept(noexcept(*::asc::std::declval<_ForwardIterator1>() = ::asc::std::iter_move(
                              ::asc::std::declval<_ForwardIterator2>())) &&
            noexcept(*::asc::std::declval<_ForwardIterator2>() = ::asc::std::iter_move(
                         ::asc::std::declval<_ForwardIterator1>())))
    {
        auto __tmp = ::asc::std::iter_move(__a);
        *__a = ::asc::std::iter_move(__b);
        *__b = ::asc::std::move(__tmp);  // NOLINT(build/include_what_you_use)
    }
};

}  // namespace __iter_swap

inline constexpr __iter_swap::__iter_swap_fn iter_swap{};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_ITER_SWAP_H
