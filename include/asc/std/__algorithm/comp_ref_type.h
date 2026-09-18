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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_COMP_REF_TYPE_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_COMP_REF_TYPE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Compare>
struct __debug_less {
    _Compare& __comp_;
    CANN_ASC_STL_API constexpr __debug_less(_Compare& __c) : __comp_(__c)
    {}

    template <class _Tp, class _Up>
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Up& __y)
    {
        bool __r = __comp_(__x, __y);
        if (__r) {
            __do_compare_assert(0, __y, __x);
        }
        return __r;
    }

    template <class _Tp, class _Up>
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Tp& __x, _Up& __y)
    {
        bool __r = __comp_(__x, __y);
        if (__r) {
            __do_compare_assert(0, __y, __x);
        }
        return __r;
    }

    template <class _LHS, class _RHS>
    CANN_ASC_STL_API constexpr decltype((void)declval<_Compare&>()(declval<_LHS&>(), declval<_RHS&>()))
    __do_compare_assert(int, [[maybe_unused]] _LHS& __l, [[maybe_unused]] _RHS& __r)
    {
        CANN_ASC_STL_DETAIL_ASSERT(!__comp_(__l, __r), "Comparator does not induce a strict weak ordering");
    }

    template <class _LHS, class _RHS>
    CANN_ASC_STL_API constexpr void __do_compare_assert(long, _LHS&, _RHS&)
    {}
};

// Pass the comparator by lvalue reference. Or in debug mode, using a
// debugging wrapper that stores a reference.
#ifdef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
template <class _Comp>
using __comp_ref_type = __debug_less<_Comp>;
#else   // ^^^ CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE ^^^ / vvv !CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE vvv
template <class _Comp>
using __comp_ref_type = _Comp&;
#endif  // !CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_COMP_REF_TYPE_H
