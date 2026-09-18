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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp, _Tp __v>
struct integral_constant {
    static constexpr const _Tp value = __v;
    using value_type = _Tp;
    using type = integral_constant;
    CANN_ASC_STL_API constexpr operator value_type() const noexcept
    {
        return value;
    }
    CANN_ASC_STL_API constexpr value_type operator()() const noexcept
    {
        return value;
    }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <bool __b>
using bool_constant = integral_constant<bool, __b>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_H
