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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_DANGLING_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_DANGLING_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__ranges/concepts.h>
#include <asc/std/__type_traits/enable_if.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

struct dangling {
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI dangling() = default;
    template <class... _Args>
    CANN_ASC_STL_API constexpr dangling(_Args&&...) noexcept
    {}
};

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <range _Rp>
using borrowed_iterator_t = _If<borrowed_range<_Rp>, iterator_t<_Rp>, dangling>;
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
template <class _Rp>
using borrowed_iterator_t = enable_if_t<range<_Rp>, _If<borrowed_range<_Rp>, iterator_t<_Rp>, dangling> >;
#endif  // !concepts

// borrowed_subrange_t defined in <__ranges/subrange.h>

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_DANGLING_H
