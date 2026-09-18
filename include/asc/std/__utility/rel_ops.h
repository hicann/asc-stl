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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_REL_OPS_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_REL_OPS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace rel_ops {
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20 CANN_ASC_STL_API bool operator!=(const _Tp& __x, const _Tp& __y)
{
    return !(__x == __y);
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20 CANN_ASC_STL_API bool operator>(const _Tp& __x, const _Tp& __y)
{
    return __y < __x;
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20 CANN_ASC_STL_API bool operator<=(const _Tp& __x, const _Tp& __y)
{
    return !(__y < __x);
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20 CANN_ASC_STL_API bool operator>=(const _Tp& __x, const _Tp& __y)
{
    return !(__x < __y);
}
}  // namespace rel_ops

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_REL_OPS_H
