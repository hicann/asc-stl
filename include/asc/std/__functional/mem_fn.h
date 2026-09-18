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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_MEM_FN_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_MEM_FN_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/binary_function.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/weak_result_type.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
class __mem_fn : public __weak_result_type<_Tp> {
public:
    // types
    using type = _Tp;

private:
    type __f_;

public:
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __mem_fn(type __f) noexcept : __f_(__f)
    {}

    // invoke
    template <class... _ArgTypes>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 invoke_result_t<type, _ArgTypes...> operator()(
        _ArgTypes&&... __args) const
    {
        return ::asc::std::__invoke(__f_,
            ::asc::std::forward<_ArgTypes>(__args)...);  // NOLINT(build/include_what_you_use)
    }
};

template <class _Rp, class _Tp>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __mem_fn<_Rp _Tp::*> mem_fn(_Rp _Tp::*__pm) noexcept
{
    return __mem_fn<_Rp _Tp::*>(__pm);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_MEM_FN_H
