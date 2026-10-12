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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_LOWER_BOUND_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_LOWER_BOUND_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/half_positive.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__type_traits/remove_reference.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _AlgPolicy, class _Iter, class _Sent, class _Type, class _Proj, class _Comp>
CANN_ASC_STL_API constexpr _Iter __lower_bound(
    _Iter __first, _Sent __last, const _Type& __value, _Comp& __comp, _Proj& __proj)
{
    auto __len = _AlgPolicy::distance(__first, __last);

    while (__len != 0) {
        auto __l2 = ::asc::std::__half_positive(__len);
        _Iter __m = __first;
        _AlgPolicy::advance(__m, __l2);
        if (::asc::std::invoke(__comp, ::asc::std::invoke(__proj, *__m), __value)) {
            __first = ++__m;
            __len -= __l2 + 1;
        } else {
            __len = __l2;
        }
    }
    return __first;
}

template <class _ForwardIterator, class _Tp, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator lower_bound(
    _ForwardIterator __first, _ForwardIterator __last, const _Tp& __value, _Compare __comp)
{
    static_assert(__is_callable<_Compare, decltype(*__first), const _Tp&>::value, "The comparator has to be callable");
    auto __proj = ::asc::std::identity();
    return ::asc::std::__lower_bound<__classic_algorithm_iterator_operations>(__first, __last, __value, __comp, __proj);
}

template <class _ForwardIterator, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator lower_bound(
    _ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
{
    return ::asc::std::lower_bound(__first, __last, __value, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_LOWER_BOUND_H
