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

#ifndef CANN_ASC_STL_ASC_STD___VARIANT_VISIT_H
#define CANN_ASC_STL_ASC_STD___VARIANT_VISIT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/unreachable.h>
#include <asc/std/__variant/get.h>
#include <asc/std/__variant/variant.h>
#include <asc/std/__variant/variant_visit.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <size_t Index, class Visitor, class Variant>
CANN_ASC_STL_API constexpr decltype(auto) __visit_one(Visitor&& visitor, Variant&& value)
{
    if (value.index() == Index) {
        return ::asc::std::__variant_visit_at<Index>(
            ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Variant>(value));
    }
    if constexpr (Index + 1 < variant_size_v<remove_cvref_t<Variant>>) {
        return ::asc::std::__visit_one<Index + 1>(
            ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Variant>(value));
    } else {
        return ::asc::std::__variant_visit_at<Index>(
            ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Variant>(value));
    }
}
template <size_t LeftIndex, size_t RightIndex, class Visitor, class Left, class Right>
CANN_ASC_STL_API constexpr decltype(auto) __visit_two(Visitor&& visitor, Left&& left, Right&& right)
{
    if (left.index() == LeftIndex && right.index() == RightIndex) {
        return ::asc::std::forward<Visitor>(visitor)(::asc::std::forward<Left>(left).template __get<LeftIndex>(),
            ::asc::std::forward<Right>(right).template __get<RightIndex>());
    }
    if constexpr (RightIndex + 1 < variant_size_v<remove_cvref_t<Right>>) {
        return ::asc::std::__visit_two<LeftIndex, RightIndex + 1>(
            ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Left>(left), ::asc::std::forward<Right>(right));
    } else if constexpr (LeftIndex + 1 < variant_size_v<remove_cvref_t<Left>>) {
        return ::asc::std::__visit_two<LeftIndex + 1, 0>(
            ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Left>(left), ::asc::std::forward<Right>(right));
    } else {
        return ::asc::std::forward<Visitor>(visitor)(::asc::std::forward<Left>(left).template __get<LeftIndex>(),
            ::asc::std::forward<Right>(right).template __get<RightIndex>());
    }
}
template <class Visitor, class Variant>
CANN_ASC_STL_API constexpr decltype(auto) visit(Visitor&& visitor, Variant&& value)
{
    return ::asc::std::__visit_one<0>(::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Variant>(value));
}
template <class Visitor, class Left, class Right>
CANN_ASC_STL_API constexpr decltype(auto) visit(Visitor&& visitor, Left&& left, Right&& right)
{
    return ::asc::std::__visit_two<0, 0>(
        ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Left>(left), ::asc::std::forward<Right>(right));
}
template <class Result, class Visitor, class... Variants>
CANN_ASC_STL_API constexpr Result visit(Visitor&& visitor, Variants&&... variants)
{
    return static_cast<Result>(
        ::asc::std::visit(::asc::std::forward<Visitor>(visitor),  // NOLINT(build/include_what_you_use)
            ::asc::std::forward<Variants>(variants)...));         // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_VISIT_H
