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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SAMPLE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SAMPLE_H

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
#include <asc/std/__algorithm/min.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__random/uniform_int_distribution.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _PopulationIterator, class _SampleIterator, class _Distance, class _UniformRandomNumberGenerator>
CANN_ASC_STL_API _SampleIterator __sample(_PopulationIterator __first, _PopulationIterator __last,
    _SampleIterator __output_iter, _Distance __n, _UniformRandomNumberGenerator& __g, input_iterator_tag)
{
    _Distance __k = 0;
    for (; __first != __last && __k < __n; ++__first, (void)++__k) {
        __output_iter[__k] = *__first;
    }
    _Distance __sz = __k;
    for (; __first != __last; ++__first, (void)++__k) {
        _Distance __r = ::asc::std::uniform_int_distribution<_Distance>(0, __k)(__g);
        if (__r < __sz) {
            __output_iter[__r] = *__first;
        }
    }
    return __output_iter + ::asc::std::min(__n, __k);
}

template <class _PopulationIterator, class _SampleIterator, class _Distance, class _UniformRandomNumberGenerator>
CANN_ASC_STL_API _SampleIterator __sample(_PopulationIterator __first, _PopulationIterator __last,
    _SampleIterator __output_iter, _Distance __n, _UniformRandomNumberGenerator& __g, forward_iterator_tag)
{
    _Distance __unsampled_sz = ::asc::std::distance(__first, __last);
    for (__n = ::asc::std::min(__n, __unsampled_sz);  // NOLINT(build/include_what_you_use)
         __n != 0; ++__first) {
        _Distance __r = ::asc::std::uniform_int_distribution<_Distance>(0, --__unsampled_sz)(__g);
        if (__r < __n) {
            *__output_iter++ = *__first;
            --__n;
        }
    }
    return __output_iter;
}

template <class _PopulationIterator, class _SampleIterator, class _Distance, class _UniformRandomNumberGenerator>
CANN_ASC_STL_API _SampleIterator __sample(_PopulationIterator __first, _PopulationIterator __last,
    _SampleIterator __output_iter, _Distance __n, _UniformRandomNumberGenerator& __g)
{
    using _PopCategory = typename iterator_traits<_PopulationIterator>::iterator_category;
    using _Difference = typename iterator_traits<_PopulationIterator>::difference_type;
    using _CommonType = typename common_type<_Distance, _Difference>::type;
    return ::asc::std::__sample(__first, __last, __output_iter, _CommonType(__n), __g, _PopCategory());
}

template <class _PopulationIterator, class _SampleIterator, class _Distance, class _UniformRandomNumberGenerator>
CANN_ASC_STL_API _SampleIterator sample(_PopulationIterator __first, _PopulationIterator __last,
    _SampleIterator __output_iter, _Distance __n, _UniformRandomNumberGenerator&& __g)
{
    return ::asc::std::__sample(__first, __last, __output_iter, __n, __g);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SAMPLE_H
