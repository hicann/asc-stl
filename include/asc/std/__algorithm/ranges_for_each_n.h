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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_FOR_EACH_N_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_FOR_EACH_N_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/in_fun_result.h>
#include <asc/std/__config>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

template <class _Iter, class _Func>
using for_each_n_result = in_fun_result<_Iter, _Func>;

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__for_each_n)

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Iter, class _Func, class _Proj = identity)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        input_iterator<_Iter> CANN_ASC_STL_DETAIL_ACCL_AND indirectly_unary_invocable<_Func, projected<_Iter, _Proj>>)
    CANN_ASC_STL_API constexpr for_each_n_result<_Iter, _Func> operator()(
        _Iter __first, iter_difference_t<_Iter> __count, _Func __func, _Proj __proj = {}) const
    {
        while (__count-- > 0) {
            ::asc::std::invoke(__func, ::asc::std::invoke(__proj, *__first));
            ++__first;
        }
        return {::asc::std::move(__first), ::asc::std::move(__func)};  // NOLINT(build/include_what_you_use)
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto for_each_n = __for_each_n::__fn{};
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_FOR_EACH_N_H
