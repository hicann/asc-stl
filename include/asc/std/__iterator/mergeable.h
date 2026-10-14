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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_MERGEABLE_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_MERGEABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Input1, class _Input2, class _Output, class _Comp = ::asc::std::ranges::less, class _Proj1 = identity,
    class _Proj2 = identity>
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
concept mergeable = input_iterator<_Input1> && input_iterator<_Input2> && weakly_incrementable<_Output> &&
    indirectly_copyable<_Input1, _Output> && indirectly_copyable<_Input2, _Output> &&
    indirect_strict_weak_order<_Comp, projected<_Input1, _Proj1>, projected<_Input2, _Proj2>>;
#else
// Constraint evaluation through the projected chain is unreliable under device
// compilation, so use an equivalent formulation that bypasses projected.
concept mergeable = input_iterator<_Input1> && input_iterator<_Input2> && weakly_incrementable<_Output> &&
    indirectly_copyable<_Input1, _Output> && indirectly_copyable<_Input2, _Output> && copy_constructible<_Comp> &&
    copy_constructible<_Proj1> && copy_constructible<_Proj2> &&
    predicate<_Comp&, indirect_result_t<_Proj1&, _Input1>, indirect_result_t<_Proj2&, _Input2>>;
#endif

CANN_ASC_STL_END_NAMESPACE

#endif

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_MERGEABLE_H
