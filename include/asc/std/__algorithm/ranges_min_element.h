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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_MIN_ELEMENT_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_MIN_ELEMENT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/min_element.h>
#include <asc/std/__config>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__min_element)
struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(
        class _Ip, class _Sp, class _Proj = identity, class _Comp = ::asc::std::ranges::less)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        forward_iterator<_Ip> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sp, _Ip> CANN_ASC_STL_DETAIL_ACCL_AND
            indirect_strict_weak_order<_Comp, projected<_Ip, _Proj>>)
    [[nodiscard]] CANN_ASC_STL_API constexpr _Ip operator()(
        _Ip __first, _Sp __last, _Comp __comp = {}, _Proj __proj = {}) const
    {
        return ::asc::std::__min_element(__first, __last, __comp, __proj);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp, class _Proj = identity, class _Comp = ::asc::std::ranges::less)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(forward_range<_Rp> CANN_ASC_STL_DETAIL_ACCL_AND
            indirect_strict_weak_order<_Comp, projected<iterator_t<_Rp>, _Proj>>)
    [[nodiscard]] CANN_ASC_STL_API constexpr borrowed_iterator_t<_Rp> operator()(
        _Rp&& __r, _Comp __comp = {}, _Proj __proj = {}) const
    {
        return ::asc::std::__min_element(
            ::asc::std::ranges::__begin_cpo{}(__r), ::asc::std::ranges::__end_cpo{}(__r), __comp, __proj);
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto min_element = __min_element::__fn{};
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_MIN_ELEMENT_H
