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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_POINTER_TO_BINARY_FUNCTION_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_POINTER_TO_BINARY_FUNCTION_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/binary_function.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS)

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH

template <class _Arg1, class _Arg2, class _Result>
class ASC_DEPRECATED pointer_to_binary_function : public __binary_function<_Arg1, _Arg2, _Result> {
    _Result (*__f_)(_Arg1, _Arg2);

public:
    CANN_ASC_STL_API explicit pointer_to_binary_function(_Result (*__f)(_Arg1, _Arg2)) : __f_(__f)
    {}
    CANN_ASC_STL_API _Result operator()(_Arg1 __x, _Arg2 __y) const
    {
        return __f_(__x, __y);
    }
};

template <class _Arg1, class _Arg2, class _Result>
ASC_DEPRECATED CANN_ASC_STL_API pointer_to_binary_function<_Arg1, _Arg2, _Result> ptr_fun(_Result (*__f)(_Arg1, _Arg2))
{
    return pointer_to_binary_function<_Arg1, _Arg2, _Result>(__f);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

#endif  // defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_POINTER_TO_BINARY_FUNCTION_H
