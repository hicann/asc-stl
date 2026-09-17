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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_VISIT_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_VISIT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/unreachable.h>
#include <asc/std/__variant/bad_variant_access.h>
#include <asc/std/__variant/get.h>
#include <asc/std/__variant/variant.h>
#include <asc/std/__variant/variant_visit.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

struct __variant_binary_visitor {
    template <class _BinaryOp, class _LeftVariant, class _RightVariant>
    [[nodiscard]] CANN_ASC_STL_API static constexpr auto __visit(
        const size_t __index_, _BinaryOp&& __op, const _LeftVariant& __lhs, const _RightVariant& __rhs)
    {
        return __visit(integral_constant<size_t, variant_size_v<_LeftVariant> - 1>{}, __index_,
            ::asc::std::forward<_BinaryOp>(__op), __lhs, __rhs);
    }

private:
    template <size_t _CurrentIndex, class _BinaryOp, class _LeftVariant, class _RightVariant>
    [[nodiscard]] CANN_ASC_STL_API static constexpr auto __visit(integral_constant<size_t, _CurrentIndex>,
        const size_t __index_, _BinaryOp&& __op, const _LeftVariant& __lhs, const _RightVariant& __rhs)
    {
        if (__index_ == _CurrentIndex) {
            return __op(::asc::std::get<_CurrentIndex>(__lhs), ::asc::std::get<_CurrentIndex>(__rhs));
        }
        return __visit(integral_constant<size_t, _CurrentIndex - 1>{}, __index_, ::asc::std::forward<_BinaryOp>(__op),
            __lhs, __rhs);
    }

    template <class _BinaryOp, class _LeftVariant, class _RightVariant>
    [[nodiscard]] CANN_ASC_STL_API static constexpr auto __visit(integral_constant<size_t, 0>, const size_t __index_,
        _BinaryOp&& __op, const _LeftVariant& __lhs, const _RightVariant& __rhs)
    {
        if (__index_ == 0) {
            return __op(::asc::std::get<0>(__lhs), ::asc::std::get<0>(__rhs));
        }
        // We already checked that every variant has a value, so we should never reach this line
#if 0  // MSVC-only workaround, not applicable
    ::asc::std::unreachable();
#else  // ^^^ CANN_ASC_STL_DETAIL_COMPILER(MSVC) ^^^ / vvv !CANN_ASC_STL_DETAIL_COMPILER(MSVC) vvv
        CANN_ASC_STL_DETAIL_UNREACHABLE();
#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_VISIT_H
    }
};

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr variant<_Types...>& __as_variant(variant<_Types...>& __vs) noexcept
{
    return __vs;
}

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr const variant<_Types...>& __as_variant(const variant<_Types...>& __vs) noexcept
{
    return __vs;
}

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr variant<_Types...>&& __as_variant(variant<_Types...>&& __vs) noexcept
{
    return ::asc::std::move(__vs);
}

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr const variant<_Types...>&& __as_variant(
    const variant<_Types...>&& __vs) noexcept
{
    return ::asc::std::move(__vs);
}

template <class... _Vs>
CANN_ASC_STL_API constexpr void __throw_if_valueless(_Vs&&... __vs)
{
    [[maybe_unused]] int __unused[] = {
        (::asc::std::__as_variant(__vs).valueless_by_exception() ? ::asc::std::__throw_bad_variant_access() : void(),
            0)...,
        0};
}

template <class _Visitor, class... _Vs,
    typename = void_t<decltype(::asc::std::__as_variant(::asc::std::declval<_Vs>()))...>>
CANN_ASC_STL_API constexpr decltype(auto) visit(_Visitor&& __visitor, _Vs&&... __vs)
{
    using __variant_detail::__visitation::__variant;
    ::asc::std::__throw_if_valueless(::asc::std::forward<_Vs>(__vs)...);
    return __variant::__visit_value(::asc::std::forward<_Visitor>(__visitor), ::asc::std::forward<_Vs>(__vs)...);
}

template <class _Rp, class _Visitor, class... _Vs,
    typename = void_t<decltype(::asc::std::__as_variant(::asc::std::declval<_Vs>()))...>>
CANN_ASC_STL_API constexpr _Rp visit(_Visitor&& __visitor, _Vs&&... __vs)
{
    using __variant_detail::__visitation::__variant;
    ::asc::std::__throw_if_valueless(::asc::std::forward<_Vs>(__vs)...);
    return __variant::__visit_value<_Rp>(::asc::std::forward<_Visitor>(__visitor),
        ::asc::std::forward<_Vs>(__vs)...);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_VISIT_H
