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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_ITER_SWAP_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_ITER_SWAP_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/swap.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__iter_swap)

template <class _ForwardIterator1, class _ForwardIterator2>
void iter_swap(_ForwardIterator1, _ForwardIterator2) = delete;

template <class _ForwardIterator1, class _ForwardIterator2, class = void>
inline constexpr bool __unqualified_iter_swap_impl = false;

template <class _ForwardIterator1, class _ForwardIterator2>
inline constexpr bool __unqualified_iter_swap_impl<_ForwardIterator1, _ForwardIterator2,
    void_t<decltype(iter_swap(::asc::std::declval<_ForwardIterator1>(), ::asc::std::declval<_ForwardIterator2>()))>> =
    true;

template <class _ForwardIterator1, class _ForwardIterator2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __unqualified_iter_swap =
    __unqualified_iter_swap_impl<_ForwardIterator1, _ForwardIterator2>;

template <class _ForwardIterator1, class _ForwardIterator2, class = void>
inline constexpr bool __readable_swappable_impl = false;

template <class _ForwardIterator1, class _ForwardIterator2>
inline constexpr bool __readable_swappable_impl<_ForwardIterator1, _ForwardIterator2,
    void_t<decltype(swap(*::asc::std::declval<_ForwardIterator1>(), *::asc::std::declval<_ForwardIterator2>()))>> =
    !__unqualified_iter_swap<_ForwardIterator1, _ForwardIterator2>;

template <class _ForwardIterator1, class _ForwardIterator2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __readable_swappable = __readable_swappable_impl<_ForwardIterator1, _ForwardIterator2>;

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _ForwardIterator1, class _ForwardIterator2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__unqualified_iter_swap<_ForwardIterator1, _ForwardIterator2>)
    CANN_ASC_STL_API constexpr void operator()(_ForwardIterator1&& __a, _ForwardIterator2&& __b) const noexcept(
        noexcept(iter_swap(::asc::std::declval<_ForwardIterator1>(), ::asc::std::declval<_ForwardIterator2>())))
    {
        (void)iter_swap(::asc::std::forward<_ForwardIterator1>(__a), ::asc::std::forward<_ForwardIterator2>(__b));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _ForwardIterator1, class _ForwardIterator2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__readable_swappable<_ForwardIterator1, _ForwardIterator2>)
    CANN_ASC_STL_API constexpr void operator()(_ForwardIterator1&& __a, _ForwardIterator2&& __b) const
        noexcept(noexcept(swap(*::asc::std::declval<_ForwardIterator1>(), *::asc::std::declval<_ForwardIterator2>())))
    {
        swap(*__a, *__b);  // NOLINT(build/include_what_you_use)
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto iter_swap = __iter_swap::__fn{};
using __iter_swap_cpo = __iter_swap::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_ITER_SWAP_H
