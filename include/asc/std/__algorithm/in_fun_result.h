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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_IN_FUN_RESULT_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_IN_FUN_RESULT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

template <class _InIter1, class _Func1>
struct in_fun_result {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _InIter1 in;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Func1 fun;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _InIter2, class _Func2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        convertible_to<const _InIter1&, _InIter2> CANN_ASC_STL_DETAIL_ACCL_AND convertible_to<const _Func1&, _Func2>)
    CANN_ASC_STL_API constexpr operator in_fun_result<_InIter2, _Func2>() const&
    {
        return {in, fun};
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _InIter2, class _Func2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        convertible_to<_InIter1, _InIter2> CANN_ASC_STL_DETAIL_ACCL_AND convertible_to<_Func1, _Func2>)
    CANN_ASC_STL_API constexpr operator in_fun_result<_InIter2, _Func2>() &&
    {
        return {::asc::std::move(in), ::asc::std::move(fun)};  // NOLINT(build/include_what_you_use)
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_IN_FUN_RESULT_H
