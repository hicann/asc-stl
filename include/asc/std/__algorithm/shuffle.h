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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SHUFFLE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SHUFFLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__random/uniform_int_distribution.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _AlgPolicy, class _RandomAccessIterator, class _Sentinel, class _UniformRandomNumberGenerator>
CANN_ASC_STL_API _RandomAccessIterator __shuffle(
    _RandomAccessIterator __first, _Sentinel __last_sentinel, _UniformRandomNumberGenerator&& __g)
{
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    using _Dp = uniform_int_distribution<ptrdiff_t>;
    using _Pp = typename _Dp::param_type;

    auto __original_last = __first;
    while (__original_last != __last_sentinel) {
        ++__original_last;
    }
    auto __last = __original_last;
    difference_type __d = __last - __first;
    if (__d > 1) {
        _Dp __uid;
        for (--__last, (void)--__d; __first < __last; ++__first, (void)--__d) {
            difference_type __i = __uid(__g, _Pp(0, __d));
            if (__i != difference_type(0)) {
                _AlgPolicy::iter_swap(__first, __first + __i);
            }
        }
    }

    return __original_last;
}

template <class _RandomAccessIterator, class _UniformRandomNumberGenerator>
CANN_ASC_STL_API void shuffle(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _UniformRandomNumberGenerator&& __g)
{
    (void)::asc::std::__shuffle<__classic_algorithm_iterator_operations>(  // NOLINT(build/include_what_you_use)
                                                                           // NOLINTNEXTLINE(build/include_what_you_use)
        ::asc::std::move(__first), ::asc::std::move(__last), ::asc::std::forward<_UniformRandomNumberGenerator>(__g));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SHUFFLE_H
