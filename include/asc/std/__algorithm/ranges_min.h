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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_MIN_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_MIN_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/min_element.h>
#include <asc/std/__config>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__min)

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Proj = identity, class _Comp = ::asc::std::ranges::less)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(indirect_strict_weak_order<_Comp, projected<const _Tp*, _Proj>>)
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Tp& operator()(
        const _Tp& __a, const _Tp& __b, _Comp __comp = {}, _Proj __proj = {}) const
    {
        return ::asc::std::invoke(__comp, ::asc::std::invoke(__proj, __b), ::asc::std::invoke(__proj, __a)) ? __b : __a;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Proj = identity, class _Comp = ::asc::std::ranges::less)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(indirect_strict_weak_order<_Comp, projected<const _Tp*, _Proj>>)
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(
        initializer_list<_Tp> __il, _Comp __comp = {}, _Proj __proj = {}) const
    {
        CANN_ASC_STL_DETAIL_ASSERT(__il.begin() != __il.end(), "initializer_list must contain at least one element");
        return *::asc::std::__min_element(__il.begin(), __il.end(), __comp, __proj);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp, class _Proj = identity, class _Comp = ::asc::std::ranges::less)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_range<_Rp> CANN_ASC_STL_DETAIL_ACCL_AND
            indirect_strict_weak_order<_Comp, projected<iterator_t<_Rp>, _Proj>>
                CANN_ASC_STL_DETAIL_ACCL_AND indirectly_copyable_storable<iterator_t<_Rp>, range_value_t<_Rp>*>)
    [[nodiscard]] CANN_ASC_STL_API constexpr range_value_t<_Rp> operator()(
        _Rp&& __r, _Comp __comp = {}, _Proj __proj = {}) const
    {
        auto __first = ::asc::std::ranges::__begin_cpo{}(__r);
        auto __last = ::asc::std::ranges::__end_cpo{}(__r);

        CANN_ASC_STL_DETAIL_ASSERT(__first != __last, "range must contain at least one element");

        if constexpr (forward_range<_Rp>) {
            return *::asc::std::__min_element(__first, __last, __comp, __proj);
        } else {
            range_value_t<_Rp> __result = *__first;
            while (++__first != __last) {
                if (::asc::std::invoke(
                        __comp, ::asc::std::invoke(__proj, *__first), ::asc::std::invoke(__proj, __result))) {
                    __result = *__first;
                }
            }
            return __result;
        }
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto min = __min::__fn{};
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_MIN_H
