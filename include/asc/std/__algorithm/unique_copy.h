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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_UNIQUE_COPY_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_UNIQUE_COPY_H

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
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __unique_copy_tags {
struct __reread_from_input_tag {};
struct __reread_from_output_tag {};
struct __read_from_tmp_value_tag {};
}  // namespace __unique_copy_tags

template <class _AlgPolicy, class _BinaryPredicate, class _InputIterator, class _Sent, class _OutputIterator>
CANN_ASC_STL_API constexpr pair<_InputIterator, _OutputIterator> __unique_copy(_InputIterator __first, _Sent __last,
    _OutputIterator __result, _BinaryPredicate&& __pred, __unique_copy_tags::__read_from_tmp_value_tag)
{
    if (__first != __last) {
        typename iterator_traits<_InputIterator>::value_type __t(*__first);
        *__result = __t;
        ++__result;
        while (++__first != __last) {
            if (!__pred(__t, *__first)) {
                __t = *__first;
                *__result = __t;
                ++__result;
            }
        }
    }
    return pair<_InputIterator, _OutputIterator>(::asc::std::move(__first), ::asc::std::move(__result));
}

template <class _AlgPolicy, class _BinaryPredicate, class _ForwardIterator, class _Sent, class _OutputIterator>
CANN_ASC_STL_API constexpr pair<_ForwardIterator, _OutputIterator> __unique_copy(_ForwardIterator __first, _Sent __last,
    _OutputIterator __result, _BinaryPredicate&& __pred, __unique_copy_tags::__reread_from_input_tag)
{
    if (__first != __last) {
        _ForwardIterator __i = __first;
        *__result = *__i;
        ++__result;
        while (++__first != __last) {
            if (!__pred(*__i, *__first)) {
                *__result = *__first;
                ++__result;
                __i = __first;
            }
        }
    }
    return pair<_ForwardIterator, _OutputIterator>(::asc::std::move(__first), ::asc::std::move(__result));
}

template <class _AlgPolicy, class _BinaryPredicate, class _InputIterator, class _Sent, class _InputAndOutputIterator>
CANN_ASC_STL_API constexpr pair<_InputIterator, _InputAndOutputIterator> __unique_copy(_InputIterator __first,
    _Sent __last, _InputAndOutputIterator __result, _BinaryPredicate&& __pred,
    __unique_copy_tags::__reread_from_output_tag)
{
    if (__first != __last) {
        *__result = *__first;
        while (++__first != __last) {
            if (!__pred(*__result, *__first)) {
                *++__result = *__first;
            }
        }
        ++__result;
    }
    return pair<_InputIterator, _InputAndOutputIterator>(::asc::std::move(__first), ::asc::std::move(__result));
}

template <class _InputIterator, class _OutputIterator, class _BinaryPredicate>
CANN_ASC_STL_API constexpr _OutputIterator unique_copy(
    _InputIterator __first, _InputIterator __last, _OutputIterator __result, _BinaryPredicate __pred)
{
    using __algo_tag =
        conditional_t<is_base_of_v<forward_iterator_tag, typename iterator_traits<_InputIterator>::iterator_category>,
            __unique_copy_tags::__reread_from_input_tag,
            conditional_t<
                is_base_of_v<forward_iterator_tag, typename iterator_traits<_OutputIterator>::iterator_category> &&
                    is_same_v<typename iterator_traits<_InputIterator>::value_type,
                        typename iterator_traits<_OutputIterator>::value_type>,
                __unique_copy_tags::__reread_from_output_tag, __unique_copy_tags::__read_from_tmp_value_tag>>;
    return ::asc::std::__unique_copy<__classic_algorithm_iterator_operations>(
        ::asc::std::move(__first), ::asc::std::move(__last), ::asc::std::move(__result), __pred, __algo_tag())
        .second;
}

template <class _InputIterator, class _OutputIterator>
CANN_ASC_STL_API constexpr _OutputIterator unique_copy(
    _InputIterator __first, _InputIterator __last, _OutputIterator __result)
{
    return ::asc::std::unique_copy(::asc::std::move(__first), ::asc::std::move(__last),
        ::asc::std::move(__result),  // NOLINT(build/include_what_you_use)
        __equal_to{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_UNIQUE_COPY_H
