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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_MAKE_PROJECTED_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_MAKE_PROJECTED_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_member_pointer.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Pred, class _Proj>
struct _ProjectedPred {
    _Pred& __pred;
    _Proj& __proj;

    CANN_ASC_STL_API constexpr _ProjectedPred(_Pred& __pred_arg, _Proj& __proj_arg)
        : __pred(__pred_arg), __proj(__proj_arg)
    {}

    template <class _Tp>
    CANN_ASC_STL_API constexpr invoke_result_t<_Pred&, invoke_result_t<_Proj&, _Tp>> operator()(_Tp&& __v) const
    {
        return ::asc::std::invoke(__pred, ::asc::std::invoke(__proj, ::asc::std::forward<_Tp>(__v)));
    }

    template <class _T1, class _T2>
    CANN_ASC_STL_API invoke_result_t<_Pred&, invoke_result_t<_Proj&, _T1>, invoke_result_t<_Proj&, _T2>> operator()(
        _T1&& __lhs, _T2&& __rhs) const
    {
        return ::asc::std::invoke(__pred, ::asc::std::invoke(__proj, ::asc::std::forward<_T1>(__lhs)),
            ::asc::std::invoke(__proj, ::asc::std::forward<_T2>(__rhs)));  // NOLINT(build/include_what_you_use)
    }
};

template <class _Pred, class _Proj,
    enable_if_t<!(!is_member_pointer_v<decay_t<_Pred>> && __is_identity_v<decay_t<_Proj>>), int> = 0>
CANN_ASC_STL_API constexpr _ProjectedPred<_Pred, _Proj> __make_projected(_Pred& __pred, _Proj& __proj)
{
    return _ProjectedPred<_Pred, _Proj>(__pred, __proj);
}

template <class _Pred, class _Proj,
    enable_if_t<!is_member_pointer_v<decay_t<_Pred>> && __is_identity_v<decay_t<_Proj>>, int> = 0>
CANN_ASC_STL_API constexpr _Pred& __make_projected(_Pred& __pred, _Proj&)
{
    return __pred;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_MAKE_PROJECTED_H
