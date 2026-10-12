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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_ITERATOR_CONCEPT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_ITERATOR_CONCEPT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/remove_cvref.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
// 按 concept 链（contiguous -> random_access -> bidirectional -> forward -> input）推导迭代器标签，
// 与上游参考实现一致且 constexpr。CCE 铁律1：设备编译下禁用 concept 约束求值，回退到基座 SFINAE 探测版。
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class _IterMaybeQualified>
CANN_ASC_STL_API constexpr auto __get_iterator_concept()
{
    using _Iter = remove_cvref_t<_IterMaybeQualified>;

    if constexpr (requires { typename iterator_traits<_Iter>::iterator_concept; }) {
        return typename iterator_traits<_Iter>::iterator_concept();
    } else if constexpr (contiguous_iterator<_Iter>) {
        return contiguous_iterator_tag();
    } else if constexpr (random_access_iterator<_Iter>) {
        return random_access_iterator_tag();
    } else if constexpr (bidirectional_iterator<_Iter>) {
        return bidirectional_iterator_tag();
    } else if constexpr (forward_iterator<_Iter>) {
        return forward_iterator_tag();
    } else if constexpr (input_iterator<_Iter>) {
        return input_iterator_tag();
    } else {
        return typename iterator_traits<_Iter>::iterator_category();
    }
}

template <class _Iter>
using __iterator_concept = decltype(__get_iterator_concept<_Iter>());
#else
template <class Iter, class = void>
struct __iterator_concept_impl {
    using type = typename iterator_traits<Iter>::iterator_category;
};
template <class Iter>
struct __iterator_concept_impl<Iter, decltype(void(sizeof(typename iterator_traits<Iter>::iterator_concept)))> {
    using type = typename iterator_traits<Iter>::iterator_concept;
};
template <class Iter>
using __iterator_concept = typename __iterator_concept_impl<Iter>::type;
template <class Iter>
CANN_ASC_STL_API auto __get_iterator_concept() -> __iterator_concept<Iter>
{
    return {};
}
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_ITERATOR_CONCEPT_H
