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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_IN_FUN_RESULT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_IN_FUN_RESULT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

template <bool Enabled, class T>
struct __in_fun_enable {};
template <class T>
struct __in_fun_enable<true, T> {
    using type = T;
};

template <class _InIter1, class _Func1>
struct in_fun_result {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _InIter1 in;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Func1 fun;

    template <class _InIter2, class _Func2,
        typename __in_fun_enable<is_convertible_v<const _InIter1&, _InIter2> && is_convertible_v<const _Func1&, _Func2>,
            int>::type = 0>
    CANN_ASC_STL_API constexpr operator in_fun_result<_InIter2, _Func2>() const&
    {
        return {in, fun};
    }

    template <class _InIter2, class _Func2,
        typename __in_fun_enable<is_convertible_v<_InIter1, _InIter2> && is_convertible_v<_Func1, _Func2>, int>::type =
            0>
    CANN_ASC_STL_API constexpr operator in_fun_result<_InIter2, _Func2>() &&
    {
        return {::asc::std::move(in), ::asc::std::move(fun)};  // NOLINT(build/include_what_you_use)
    }
};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_IN_FUN_RESULT_H
