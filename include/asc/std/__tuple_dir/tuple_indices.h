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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_INDICES_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_INDICES_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <size_t _Ep, size_t _Sp = 0>
struct __make_tuple_indices {
    static_assert(_Sp <= _Ep, "__make_tuple_indices input error");
    using type = __make_indices_imp<_Ep, _Sp>;
};

template <size_t _Ep, size_t _Sp = 0>
using __make_tuple_indices_t = typename __make_tuple_indices<_Ep, _Sp>::type;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_INDICES_H
