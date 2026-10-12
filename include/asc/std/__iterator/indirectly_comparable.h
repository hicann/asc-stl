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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_INDIRECTLY_COMPARABLE_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_INDIRECTLY_COMPARABLE_H

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
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

CANN_ASC_STL_BEGIN_NAMESPACE

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class _Iter1, class _Iter2, class _BinaryPred, class _Proj1 = identity, class _Proj2 = identity>
concept indirectly_comparable =
    indirect_binary_predicate<_BinaryPred, projected<_Iter1, _Proj1>, projected<_Iter2, _Proj2>>;
#else
// 设备编译下 projected 链的约束求值不可靠（iter_reference_t 硬错误），采用不经 projected 的等价公式。
template <class _Iter1, class _Iter2, class _BinaryPred, class _Proj1 = identity, class _Proj2 = identity>
concept indirectly_comparable = indirectly_readable<_Iter1> && indirectly_readable<_Iter2> &&
    copy_constructible<_BinaryPred> && copy_constructible<_Proj1> && copy_constructible<_Proj2> &&
    predicate<_BinaryPred&, indirect_result_t<_Proj1&, _Iter1>, indirect_result_t<_Proj2&, _Iter2>>;
#endif

CANN_ASC_STL_END_NAMESPACE

#endif

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_INDIRECTLY_COMPARABLE_H
