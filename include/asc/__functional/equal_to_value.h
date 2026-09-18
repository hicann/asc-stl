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

#ifndef CANN_ASC_STL_DETAIL_FUNCTIONAL_EQUAL_TO_VALUE_H
#define CANN_ASC_STL_DETAIL_FUNCTIONAL_EQUAL_TO_VALUE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_comparable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//! @brief `equal_to_value` is a function object that checks if a value is equal to a stored value.
//! @tparam _Tp The type of the value to be compared.
template <typename _Tp>
struct equal_to_value {
    _Tp __value_;

    CANN_ASC_STL_API explicit constexpr equal_to_value(const _Tp& __value) noexcept(
        ::asc::std::is_nothrow_copy_constructible_v<_Tp>)
        : __value_(__value)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(::asc::std::__is_cpp17_equality_comparable_v<_Tp, _Up>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Up& __lhs) const
        noexcept(::asc::std::__is_cpp17_nothrow_equality_comparable_v<_Tp, _Up>)
    {
        return static_cast<bool>(__lhs == __value_);
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_FUNCTIONAL_EQUAL_TO_VALUE_H
