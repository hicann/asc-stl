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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_ADVANCE_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_ADVANCE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/convert_to_integral.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __advance_detail {
template <class Iter, class Difference>
CANN_ASC_STL_API constexpr void call(Iter& iter, Difference n, input_iterator_tag)
{
    while (n > 0) {
        --n;
        ++iter;
    }
}
template <class Iter, class Difference>
CANN_ASC_STL_API constexpr void call(Iter& iter, Difference n, bidirectional_iterator_tag)
{
    while (n > 0) {
        --n;
        ++iter;
    }
    while (n < 0) {
        ++n;
        --iter;
    }
}
template <class Iter, class Difference>
CANN_ASC_STL_API constexpr void call(Iter& iter, Difference n, random_access_iterator_tag)
{
    iter += n;
}
}  // namespace __advance_detail

template <class InputIter, class Distance>
CANN_ASC_STL_API constexpr void advance(InputIter& iter, Distance original)
{
    using difference_type = typename iterator_traits<InputIter>::difference_type;
    const difference_type count = static_cast<difference_type>(::asc::std::__convert_to_integral(original));
    __advance_detail::call(iter, count, typename iterator_traits<InputIter>::iterator_category{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_ADVANCE_H
