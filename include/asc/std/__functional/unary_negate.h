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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_UNARY_NEGATE_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_UNARY_NEGATE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/unary_function.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_NEGATORS)

template <class _Predicate>
class ASC_DEPRECATED unary_negate : public __unary_function<typename _Predicate::argument_type, bool> {
    _Predicate __pred_;

public:
    CANN_ASC_STL_API explicit constexpr unary_negate(const _Predicate& __pred) : __pred_(__pred)
    {}

    constexpr CANN_ASC_STL_API bool operator()(const typename _Predicate::argument_type& __x) const
    {
        return !__pred_(__x);
    }
};

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
template <class _Predicate>
ASC_DEPRECATED CANN_ASC_STL_API constexpr unary_negate<_Predicate> not1(const _Predicate& __pred)
{
    return unary_negate<_Predicate>(__pred);  // NOLINT(build/include_what_you_use)
}
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_NEGATORS)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_UNARY_NEGATE_H
