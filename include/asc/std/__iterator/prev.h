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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_PREV_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_PREV_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/enable_if.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class InputIterator>
CANN_ASC_STL_API constexpr InputIterator prev(
    InputIterator value, typename iterator_traits<InputIterator>::difference_type count = 1)
{
    CANN_ASC_STL_DETAIL_ASSERT(count <= 0 || __advance_detail::__has_bidirectional_traversal<InputIterator>,
        "Attempt to prev(it, +n) on a non-bidirectional iterator");

    ::asc::std::advance(value, -count);
    return value;
}

CANN_ASC_STL_END_NAMESPACE

// [range.iter.op.prev]

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

namespace __prev {
struct __fn {
    template <class _Ip, enable_if_t<bidirectional_iterator<_Ip>, int> = 0>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _Ip operator()(_Ip __x) const
    {
        --__x;
        return __x;
    }

    template <class _Ip, enable_if_t<bidirectional_iterator<_Ip>, int> = 0>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _Ip operator()(_Ip __x, iter_difference_t<_Ip> __n) const
    {
        ::asc::std::ranges::__advance_cpo{}(__x, -__n);
        return __x;
    }

    template <class _Ip, enable_if_t<bidirectional_iterator<_Ip>, int> = 0>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _Ip operator()(
        _Ip __x, iter_difference_t<_Ip> __n, _Ip __bound_iter) const
    {
        ::asc::std::ranges::__advance_cpo{}(__x, -__n, __bound_iter);
        return __x;
    }
};
}  // namespace __prev

inline namespace __cpo {
inline constexpr auto prev = __prev::__fn{};

// Avoid using the public CPO internally so lookup stays constrained to this implementation.
using __prev_cpo = __prev::__fn;
}  // namespace __cpo

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_PREV_H
