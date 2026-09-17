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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_FIND_IF_NOT_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_FIND_IF_NOT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/ranges_find_if.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__find_if_not)
template <class _Pred>
struct __not_pred {
    CANN_ASC_STL_API constexpr __not_pred(_Pred& __pred) noexcept : __pred_(__pred)
    {}

    _Pred& __pred_;

    template <class _Tp>
    CANN_ASC_STL_API constexpr auto operator()(_Tp&& __e) const
    {
        return !::asc::std::invoke(__pred_, ::asc::std::forward<_Tp>(__e));
    }
};

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip, class _Sp, class _Pred, class _Proj = identity)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        input_iterator<_Ip> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sp, _Ip> CANN_ASC_STL_DETAIL_ACCL_AND
            indirect_unary_predicate<_Pred, projected<_Ip, _Proj>>)
    [[nodiscard]] CANN_ASC_STL_API constexpr _Ip operator()(
        _Ip __first, _Sp __last, _Pred __pred, _Proj __proj = {}) const
    {
        return ::asc::std::ranges::find_if(
            ::asc::std::move(__first), ::asc::std::move(__last), __not_pred{__pred}, ::asc::std::move(__proj));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp, class _Pred, class _Proj = identity)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_range<_Rp> CANN_ASC_STL_DETAIL_ACCL_AND
            indirect_unary_predicate<_Pred, projected<iterator_t<_Rp>, _Proj>>)
    [[nodiscard]] CANN_ASC_STL_API constexpr borrowed_iterator_t<_Rp> operator()(
        _Rp&& __r, _Pred __pred, _Proj __proj = {}) const
    {
        return ::asc::std::ranges::find_if(::asc::std::forward<_Rp>(__r), __not_pred{__pred},
            ::asc::std::move(__proj));  // NOLINT(build/include_what_you_use)
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto find_if_not = __find_if_not::__fn{};
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_FIND_IF_NOT_H
