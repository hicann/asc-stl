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

#ifndef CANN_ASC_STL_DETAIL_FUNCTIONAL_ALWAYS_TRUE_FALSE_H
#define CANN_ASC_STL_DETAIL_FUNCTIONAL_ALWAYS_TRUE_FALSE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//! @brief Function object that always returns \c true regardless of the arguments passed.
struct always_true {
    template <typename... _Ts>
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Ts&&...) const noexcept
    {
        return true;
    }
};

//! @brief Function object that always returns \c false regardless of the arguments passed.
struct always_false {
    template <typename... _Ts>
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Ts&&...) const noexcept
    {
        return false;
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_FUNCTIONAL_ALWAYS_TRUE_FALSE_H
