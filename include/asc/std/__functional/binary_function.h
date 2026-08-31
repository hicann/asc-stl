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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BINARY_FUNCTION_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BINARY_FUNCTION_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION)

template <class _Arg1, class _Arg2, class _Result>
struct ASC_DEPRECATED binary_function {
    using first_argument_type = _Arg1;
    using second_argument_type = _Arg2;
    using result_type = _Result;
};

#endif  // defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION)

template <class _Arg1, class _Arg2, class _Result>
struct __binary_function_keep_layout_base {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using first_argument_type ASC_DEPRECATED = _Arg1;
    using second_argument_type ASC_DEPRECATED = _Arg2;
    using result_type ASC_DEPRECATED = _Result;
#endif  // CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS
};

#if defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION)
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
template <class _Arg1, class _Arg2, class _Result>
using __binary_function = binary_function<_Arg1, _Arg2, _Result>;  // NOLINT(build/include_what_you_use)
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP
#else
template <class _Arg1, class _Arg2, class _Result>
using __binary_function = __binary_function_keep_layout_base<_Arg1, _Arg2, _Result>;
#endif  // !CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BINARY_FUNCTION_H
