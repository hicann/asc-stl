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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MISMATCH_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MISMATCH_H

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
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<_InputIterator1, _InputIterator2> mismatch(
    _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _BinaryPredicate __pred)
{
    for (; __first1 != __last1; ++__first1, (void)++__first2) {
        if (!__pred(*__first1, *__first2)) {
            break;
        }
    }
    return pair<_InputIterator1, _InputIterator2>{__first1, __first2};
}

template <class _InputIterator1, class _InputIterator2>
// NOLINTNEXTLINE(build/include_what_you_use)
[[nodiscard]] CANN_ASC_STL_API constexpr pair<_InputIterator1, _InputIterator2> mismatch(
    _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2)
{
    return ::asc::std::mismatch(__first1, __last1, __first2, __equal_to{});
}

template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<_InputIterator1, _InputIterator2> mismatch(_InputIterator1 __first1,
    _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2, _BinaryPredicate __pred)
{
    for (; __first1 != __last1 && __first2 != __last2; ++__first1, (void)++__first2) {
        if (!__pred(*__first1, *__first2)) {
            break;
        }
    }
    return pair<_InputIterator1, _InputIterator2>{__first1, __first2};
}

template <class _InputIterator1, class _InputIterator2>
// NOLINTNEXTLINE(build/include_what_you_use)
[[nodiscard]] CANN_ASC_STL_API constexpr pair<_InputIterator1, _InputIterator2> mismatch(
    _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2)
{
    return ::asc::std::mismatch(  // NOLINT(build/include_what_you_use)
        __first1, __last1, __first2, __last2, __equal_to{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MISMATCH_H
