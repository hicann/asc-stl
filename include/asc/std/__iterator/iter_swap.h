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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_ITER_SWAP_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_ITER_SWAP_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__concepts/swappable.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#ifndef CANN_ASC_STL_DETAIL_ITER_SWAP_DEFINED
#define CANN_ASC_STL_DETAIL_ITER_SWAP_DEFINED
template <class I1, class I2>
CANN_ASC_STL_API constexpr void iter_swap(I1 left, I2 right) noexcept(
    noexcept(*left = ::asc::std::iter_move(right)) && noexcept(*right = ::asc::std::iter_move(left)))
{
    auto temporary = ::asc::std::iter_move(left);
    *left = ::asc::std::iter_move(right);
    *right = ::asc::std::move(temporary);  // NOLINT(build/include_what_you_use)
}
#endif

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class I1, class I2 = I1>
concept indirectly_swappable =
    indirectly_readable<I1> && indirectly_readable<I2> && requires(const I1 left, const I2 right) {
        ::asc::std::iter_swap(left, left);
        ::asc::std::iter_swap(right, right);
        ::asc::std::iter_swap(left, right);
        ::asc::std::iter_swap(right, left);
    };
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_ITER_SWAP_H
