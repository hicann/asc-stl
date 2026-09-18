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

#ifndef CANN_ASC_STL_STD_DETAIL_OPTIONAL_HASH_H
#define CANN_ASC_STL_STD_DETAIL_OPTIONAL_HASH_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/hash.h>
#include <asc/std/__optional/optional.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <>
struct hash<long> {
    CANN_ASC_STL_API size_t operator()(long __v) const
    {
        return static_cast<size_t>(__v);
    }
};

template <class _Tp>
struct hash<optional<_Tp>> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using argument_type ASC_DEPRECATED = optional<_Tp>;
    using result_type ASC_DEPRECATED = size_t;
#endif

    CANN_ASC_STL_API size_t operator()(const optional<_Tp>& __opt) const
    {
        return static_cast<bool>(__opt) ? hash<remove_const_t<_Tp>>()(*__opt) : 0;
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_OPTIONAL_HASH_H
