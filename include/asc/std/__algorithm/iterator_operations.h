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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_ITERATOR_OPERATIONS_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_ITERATOR_OPERATIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/iter_swap.h>
#include <asc/std/__algorithm/ranges_iterator_concept.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__iterator/prev.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

struct __classic_algorithm_iterator_operations {
    template <class Iterator>
    CANN_ASC_STL_API static constexpr decltype(auto) iter_move(Iterator&& iterator) noexcept(
        noexcept(::asc::std::move(*::asc::std::forward<Iterator>(iterator))))
    {
        return ::asc::std::move(                        // NOLINT(build/include_what_you_use)
            *::asc::std::forward<Iterator>(iterator));  // NOLINT(build/include_what_you_use)
    }

    template <class Iterator1, class Iterator2>
    CANN_ASC_STL_API static constexpr void iter_swap(Iterator1 left, Iterator2 right) noexcept(
        noexcept(::asc::std::iter_swap(left, right)))
    {
        ::asc::std::iter_swap(left, right);
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_ITERATOR_OPERATIONS_H
