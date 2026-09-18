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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_COMP_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_COMP_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

struct __equal_to {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _T1& __lhs, const _T2& __rhs) const
        noexcept(noexcept(__lhs == __rhs))
    {
        return __lhs == __rhs;
    }
};

struct __less {
    template <class _Tp, class _Up>
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __lhs, const _Up& __rhs) const
        noexcept(noexcept(__lhs < __rhs))
    {
        return __lhs < __rhs;
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_COMP_H
