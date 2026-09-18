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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_COMMON_ITERATOR_H
#define CANN_ASC_STL_STD_DETAIL_FWD_COMMON_ITERATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__type_traits/enable_if.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_ACCL_BEGIN_HIDDEN_FRIEND_NAMESPACE

// Normally this would be defined in __fwd/iterator.h, but that leads to partial include cycles
// with __is_primary_std_template since that would now transitively include __fwd/iterator.h
// (through __concepts/concepts.h). To break that cycle, we need a separate forward declaration
// for this class.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator _Iter, sentinel_for<_Iter> _Sent>
    requires(!same_as<_Iter, _Sent> && copyable<_Iter>)
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Iter, class _Sent, enable_if_t<input_or_output_iterator<_Iter>, int> = 0,
    enable_if_t<sentinel_for<_Sent, _Iter>, int> = 0, enable_if_t<(!same_as<_Iter, _Sent> && copyable<_Iter>), int> = 0>
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
class common_iterator;

CANN_ASC_STL_DETAIL_ACCL_END_HIDDEN_FRIEND_NAMESPACE(common_iterator)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD
#endif  // CANN_ASC_STL_STD_DETAIL_FWD_COMMON_ITERATOR_H
