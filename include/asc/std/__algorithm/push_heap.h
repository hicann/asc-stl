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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_PUSH_HEAP_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_PUSH_HEAP_H

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
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _AlgPolicy, class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __sift_up(_RandomAccessIterator __first, _RandomAccessIterator __last,
    _Compare&& __comp, typename iterator_traits<_RandomAccessIterator>::difference_type __len)
{
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;

    if (__len > 1) {
        __len = (__len - 2) / 2;
        _RandomAccessIterator __ptr = __first + __len;

        if (__comp(*__ptr, *--__last)) {
            value_type __t(_AlgPolicy::iter_move(__last));
            do {
                *__last = _AlgPolicy::iter_move(__ptr);
                __last = __ptr;
                if (__len == 0) {
                    break;
                }
                __len = (__len - 1) / 2;
                __ptr = __first + __len;
            } while (__comp(*__ptr, __t));

            *__last = ::asc::std::move(__t);
        }
    }
}

template <class _AlgPolicy, class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr void __push_heap(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare& __comp)
{
    typename iterator_traits<_RandomAccessIterator>::difference_type __len = __last - __first;
    ::asc::std::__sift_up<_AlgPolicy, __comp_ref_type<_Compare>>(
        ::asc::std::move(__first), ::asc::std::move(__last), __comp, __len);
}

template <class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr void push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    static_assert(::asc::std::is_copy_constructible_v<_RandomAccessIterator>, "Iterators must be copy constructible.");
    static_assert(::asc::std::is_copy_assignable_v<_RandomAccessIterator>, "Iterators must be copy assignable.");

    ::asc::std::__push_heap<__classic_algorithm_iterator_operations>(
        ::asc::std::move(__first), ::asc::std::move(__last), __comp);
}

template <class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    ::asc::std::push_heap(  // NOLINT(build/include_what_you_use)
                            // NOLINTNEXTLINE(build/include_what_you_use)
        ::asc::std::move(__first), ::asc::std::move(__last), __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_PUSH_HEAP_H
