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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_COMPARISON_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_COMPARISON_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/operations.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__variant/variant.h>
#include <asc/std/__variant/visit.h>

// [variant.syn]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Operator>
struct __convert_to_bool {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_T1&& __t1, _T2&& __t2) const
    {
        static_assert(
            is_convertible_v<decltype(_Operator{}(::asc::std::forward<_T1>(__t1), ::asc::std::forward<_T2>(__t2))),
                bool>,
            "the relational operator does not return a type which is "
            "implicitly convertible to bool");
        return _Operator{}(
            ::asc::std::forward<_T1>(__t1), ::asc::std::forward<_T2>(__t2));  // NOLINT(build/include_what_you_use)
    }
};

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator==(
    const variant<_Types...>& __lhs, const variant<_Types...>& __rhs)
{
    const auto __index_ = __lhs.index();
    if (__index_ != __rhs.index()) {
        return false;
    }
    if (__lhs.valueless_by_exception()) {
        return true;
    }

    return __variant_binary_visitor::__visit(__index_, __convert_to_bool<equal_to<>>{}, __lhs, __rhs);
}

#if CANN_ASC_STL_DETAIL_ACCL_HAS_SPACESHIP_OPERATOR()

template <class... _Types>
    requires(three_way_comparable<_Types> && ...)
[[nodiscard]] CANN_ASC_STL_API constexpr common_comparison_category_t<compare_three_way_result_t<_Types>...>
operator<=>(const variant<_Types...>& __lhs, const variant<_Types...>& __rhs)
{
    using __result_t = common_comparison_category_t<compare_three_way_result_t<_Types>...>;
    if (__lhs.valueless_by_exception() && __rhs.valueless_by_exception()) {
        return strong_ordering::equal;
    }
    if (__lhs.valueless_by_exception()) {
        return strong_ordering::less;
    }
    if (__rhs.valueless_by_exception()) {
        return strong_ordering::greater;
    }
    if (auto __c = __lhs.index() <=> __rhs.index(); __c != 0) {
        return __c;
    }
    auto __three_way = []<class _Type>(const _Type& __v, const _Type& __w) -> __result_t { return __v <=> __w; };
    return __variant_binary_visitor::__visit(__lhs.index(), __three_way, __lhs, __rhs);
}

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_COMPARISON_H

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator!=(
    const variant<_Types...>& __lhs, const variant<_Types...>& __rhs)
{
    if (__lhs.index() != __rhs.index()) {
        return true;
    }
    if (__lhs.valueless_by_exception()) {
        return false;
    }
    return __variant_binary_visitor::__visit(__lhs.index(), __convert_to_bool<not_equal_to<>>{}, __lhs, __rhs);
}

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator<(
    const variant<_Types...>& __lhs, const variant<_Types...>& __rhs)
{
    if (__rhs.valueless_by_exception()) {
        return false;
    }
    if (__lhs.valueless_by_exception()) {
        return true;
    }
    if (__lhs.index() < __rhs.index()) {
        return true;
    }
    if (__lhs.index() > __rhs.index()) {
        return false;
    }
    return __variant_binary_visitor::__visit(__lhs.index(), __convert_to_bool<less<>>{}, __lhs, __rhs);
}

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator>(
    const variant<_Types...>& __lhs, const variant<_Types...>& __rhs)
{
    if (__lhs.valueless_by_exception()) {
        return false;
    }
    if (__rhs.valueless_by_exception()) {
        return true;
    }
    if (__lhs.index() > __rhs.index()) {
        return true;
    }
    if (__lhs.index() < __rhs.index()) {
        return false;
    }
    return __variant_binary_visitor::__visit(__lhs.index(), __convert_to_bool<greater<>>{}, __lhs, __rhs);
}

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator<=(
    const variant<_Types...>& __lhs, const variant<_Types...>& __rhs)
{
    if (__lhs.valueless_by_exception()) {
        return true;
    }
    if (__rhs.valueless_by_exception()) {
        return false;
    }
    if (__lhs.index() < __rhs.index()) {
        return true;
    }
    if (__lhs.index() > __rhs.index()) {
        return false;
    }
    return __variant_binary_visitor::__visit(__lhs.index(), __convert_to_bool<less_equal<>>{}, __lhs, __rhs);
}

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator>=(
    const variant<_Types...>& __lhs, const variant<_Types...>& __rhs)
{
    if (__rhs.valueless_by_exception()) {
        return true;
    }
    if (__lhs.valueless_by_exception()) {
        return false;
    }
    if (__lhs.index() > __rhs.index()) {
        return true;
    }
    if (__lhs.index() < __rhs.index()) {
        return false;
    }
    return __variant_binary_visitor::__visit(
        __lhs.index(), __convert_to_bool<greater_equal<>>{}, __lhs, __rhs);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_COMPARISON_H
