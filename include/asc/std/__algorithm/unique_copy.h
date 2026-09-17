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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNIQUE_COPY_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNIQUE_COPY_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __unique_copy_tags {
struct __reread_from_input_tag {};
struct __reread_from_output_tag {};
struct __read_from_tmp_value_tag {};
}  // namespace __unique_copy_tags
template <class _AlgPolicy, class _BinaryPredicate, class _InputIterator, class _Sent, class _OutputIterator>
constexpr CANN_ASC_STL_API pair<_InputIterator, _OutputIterator> __unique_copy(_InputIterator __first, _Sent __last,
    _OutputIterator __result, _BinaryPredicate&& __pred, __unique_copy_tags::__read_from_tmp_value_tag)
{
    if (__first != __last) {
        typename _IterOps<_AlgPolicy>::template __value_type<_InputIterator> __t(*__first);
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
constexpr CANN_ASC_STL_API pair<_ForwardIterator, _OutputIterator> __unique_copy(_ForwardIterator __first, _Sent __last,
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
constexpr CANN_ASC_STL_API pair<_InputIterator, _InputAndOutputIterator> __unique_copy(_InputIterator __first,
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
    using __algo_tag = conditional_t<is_base_of_v<forward_iterator_tag, __iterator_category_type<_InputIterator>>,
        __unique_copy_tags::__reread_from_input_tag,
        conditional_t<is_base_of_v<forward_iterator_tag, __iterator_category_type<_OutputIterator>> &&
                is_same_v<__iter_value_type<_InputIterator>, __iter_value_type<_OutputIterator>>,
            __unique_copy_tags::__reread_from_output_tag, __unique_copy_tags::__read_from_tmp_value_tag>>;
    return ::asc::std::__unique_copy<_ClassicAlgPolicy>(
        ::asc::std::move(__first), ::asc::std::move(__last), ::asc::std::move(__result), __pred, __algo_tag())
        .second;
}
template <class _InputIterator, class _OutputIterator>
CANN_ASC_STL_API constexpr _OutputIterator unique_copy(
    _InputIterator __first, _InputIterator __last, _OutputIterator __result)
{
    return ::asc::std::unique_copy(::asc::std::move(__first), ::asc::std::move(__last),
        ::asc::std::move(__result),  // NOLINT(build/include_what_you_use)
        __equal_to{});               // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNIQUE_COPY_H
