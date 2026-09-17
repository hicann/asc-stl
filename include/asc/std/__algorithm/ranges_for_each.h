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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_FOR_EACH_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_FOR_EACH_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/in_fun_result.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

template <class _Iter, class _Func>
using for_each_result = in_fun_result<_Iter, _Func>;

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__for_each)
struct __fn {
private:
    template <class _Iter, class _Sent, class _Proj, class _Func>
    CANN_ASC_STL_API constexpr static for_each_result<_Iter, _Func> __for_each_impl(
        _Iter __first, _Sent __last, _Func& __func, _Proj& __proj)
    {
        for (; __first != __last; ++__first) {
            ::asc::std::invoke(__func, ::asc::std::invoke(__proj, *__first));
        }
        return {::asc::std::move(__first), ::asc::std::move(__func)};
    }

public:
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Iter, class _Sent, class _Func, class _Proj = identity)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        input_iterator<_Iter> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sent, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND
            indirectly_unary_invocable<_Func, projected<_Iter, _Proj>>)
    CANN_ASC_STL_API constexpr for_each_result<_Iter, _Func> operator()(
        _Iter __first, _Sent __last, _Func __func, _Proj __proj = {}) const
    {
        return __for_each_impl(
            ::asc::std::move(__first), ::asc::std::move(__last), __func, __proj);  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range, class _Func, class _Proj = identity)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_range<_Range> CANN_ASC_STL_DETAIL_ACCL_AND
            indirectly_unary_invocable<_Func, projected<iterator_t<_Range>, _Proj>>)
    CANN_ASC_STL_API constexpr for_each_result<borrowed_iterator_t<_Range>, _Func> operator()(
        _Range&& __range, _Func __func, _Proj __proj = {}) const
    {
        return __for_each_impl(
            ::asc::std::ranges::__begin_cpo{}(__range), ::asc::std::ranges::__end_cpo{}(__range), __func, __proj);
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto for_each = __for_each::__fn{};
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_FOR_EACH_H
