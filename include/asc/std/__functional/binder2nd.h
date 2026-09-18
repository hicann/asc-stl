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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BINDER2ND_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BINDER2ND_H

#include <asc/std/detail/__config>

#include <asc/std/__functional/unary_function.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS)

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH

template <class __Operation>
class ASC_DEPRECATED binder2nd
    : public __unary_function<typename __Operation::first_argument_type, typename __Operation::result_type> {
protected:
    __Operation op;
    typename __Operation::second_argument_type value;

public:
    CANN_ASC_STL_API binder2nd(const __Operation& __x, const typename __Operation::second_argument_type __y)
        : op(__x), value(__y)
    {}
    CANN_ASC_STL_API typename __Operation::result_type operator()(typename __Operation::first_argument_type& __x) const
    {
        return op(__x, value);
    }
    CANN_ASC_STL_API typename __Operation::result_type operator()(
        const typename __Operation::first_argument_type& __x) const
    {
        return op(__x, value);
    }
};

template <class __Operation, class _Tp>
ASC_DEPRECATED CANN_ASC_STL_API binder2nd<__Operation> bind2nd(const __Operation& __op, const _Tp& __x)
{
    return binder2nd<__Operation>(__op, __x);
}

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

#endif  // defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BINDER2ND_H
