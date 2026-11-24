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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_EQUAL_RANGE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_EQUAL_RANGE_H

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
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__algorithm/half_positive.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/lower_bound.h>
#include <asc/std/__algorithm/upper_bound.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _AlgPolicy, class _Compare, class _Iter, class _Sent, class _Tp, class _Proj>
CANN_ASC_STL_API constexpr pair<_Iter, _Iter> __equal_range(
    _Iter __first, _Sent __last, const _Tp& __value, _Compare&& __comp, _Proj&& __proj)
{
    auto __len = ::asc::std::distance(__first, __last);
    _Iter __end = _AlgPolicy::next(__first, __last);
    while (__len != 0) {
        auto __half_len = ::asc::std::__half_positive(__len);
        _Iter __mid = ::asc::std::next(__first, __half_len);
        if (::asc::std::invoke(__comp, ::asc::std::invoke(__proj, *__mid), __value)) {
            __first = ++__mid;
            __len -= __half_len + 1;
        } else if (::asc::std::invoke(__comp, __value, ::asc::std::invoke(__proj, *__mid))) {
            __end = __mid;
            __len = __half_len;
        } else {
            _Iter __mp1 = __mid;
            return pair<_Iter, _Iter>(::asc::std::__lower_bound<_AlgPolicy>(__first, __mid, __value, __comp, __proj),
                ::asc::std::__upper_bound<_AlgPolicy>(++__mp1, __end, __value, __comp, __proj));
        }
    }
    return pair<_Iter, _Iter>(__first, __first);
}

template <class _ForwardIterator, class _Tp, class _Compare>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr pair<_ForwardIterator, _ForwardIterator> equal_range(
    _ForwardIterator __first, _ForwardIterator __last, const _Tp& __value, _Compare __comp)
{
    static_assert(__is_callable<_Compare, decltype(*__first), const _Tp&>::value, "The comparator has to be callable");
    static_assert(is_copy_constructible_v<_ForwardIterator>, "Iterator has to be copy constructible");
    return ::asc::std::__equal_range<__classic_algorithm_iterator_operations>(::asc::std::move(__first),
        ::asc::std::move(__last), __value, static_cast<__comp_ref_type<_Compare>>(__comp), ::asc::std::identity());
}

template <class _ForwardIterator, class _Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr pair<_ForwardIterator, _ForwardIterator> equal_range(
    _ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
{
    return ::asc::std::equal_range(
        ::asc::std::move(__first), ::asc::std::move(__last), __value, __less{});  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_EQUAL_RANGE_H
