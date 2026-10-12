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
#include <asc/std/__functional/invoke.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/unreachable.h>
#include <asc/std/__variant/get.h>
#include <asc/std/__variant/variant.h>
#include <asc/std/__variant/variant_access.h>
#include <asc/std/__variant/variant_visit.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// 无值变体进入分派前在此终止（基座变体不引入 bad_variant_access，以 trap 兜底，
// 与 get.h 的越界处理同构）。
template <class... Variants>
CANN_ASC_STL_API constexpr void __visit_check_valueless(const Variants&... variants)
{
    ((variants.valueless_by_exception() ? __builtin_trap() : static_cast<void>(0)), ...);
}

// 逐层绑定已确定备选的访问器：visitor(已绑定备选..., 后续实参...)。
template <class Visitor, class Alternative>
struct __visit_bound_visitor {
    Visitor& visitor;
    Alternative& alternative;

    template <class... Args>
    CANN_ASC_STL_API constexpr decltype(auto) operator()(Args&&... args) const
    {
        return visitor(alternative, ::asc::std::forward<Args>(args)...);
    }
};

// 单变元：全部备选按实参值类别调用 visitor 的结果会合类型。
template <class Visitor, class Variant, size_t... Indices>
CANN_ASC_STL_API auto __visit_common_last(__tuple_indices<Indices...>)
    -> common_type_t<
        __invoke_result_t<Visitor, decltype(__variant_get_alt<Indices>(::asc::std::declval<Variant>()))>...>;

// 多变元递归层：首变元逐备选绑定后，对余下变元递归求会合类型。
template <class Visitor, class Variant, class... Rest>
struct __visit_common;

template <class Visitor, class Variant, class... Rest, size_t... Indices>
CANN_ASC_STL_API auto __visit_common_step(__tuple_indices<Indices...>)
    -> common_type_t<
        typename __visit_common<__visit_bound_visitor<Visitor, variant_alternative_t<Indices, remove_cvref_t<Variant>>>,
            remove_cvref_t<Rest>&...>::type...>;

template <class Visitor, class Variant, class... Rest>
struct __visit_common {
    using type = decltype(::asc::std::__visit_common_step<Visitor, Variant, Rest...>(
        __make_indices_imp<variant_size_v<remove_cvref_t<Variant>>, 0>{}));
};

template <class Visitor, class Variant>
struct __visit_common<Visitor, Variant> {
    using type = decltype(::asc::std::__visit_common_last<Visitor, Variant>(
        __make_indices_imp<variant_size_v<remove_cvref_t<Variant>>, 0>{}));
};

// 双变元专用：两侧备选均按实参值类别参与，两重展开求会合类型。
template <class Visitor, class Left, class Right, size_t LeftIndex, size_t... RightIndices>
CANN_ASC_STL_API auto __visit_common_row(__tuple_indices<RightIndices...>)
    -> common_type_t<__invoke_result_t<Visitor, decltype(__variant_get_alt<LeftIndex>(::asc::std::declval<Left>())),
        decltype(__variant_get_alt<RightIndices>(::asc::std::declval<Right>()))>...>;

template <class Visitor, class Left, class Right, size_t... LeftIndices>
CANN_ASC_STL_API auto __visit_common_two(__tuple_indices<LeftIndices...>)
    -> common_type_t<decltype(::asc::std::__visit_common_row<Visitor, Left, Right, LeftIndices>(
        __make_indices_imp<variant_size_v<remove_cvref_t<Right>>, 0>{}))...>;

template <class Result, __SIZE_TYPE__ Index, class Visitor, class Variant>
CANN_ASC_STL_API constexpr Result __visit_one(Visitor&& visitor, Variant&& value)
{
    if (value.index() == Index) {
        return static_cast<Result>(::asc::std::__variant_visit_at<Index>(
            ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Variant>(value)));
    }
    if constexpr (Index + 1 < variant_size_v<remove_cvref_t<Variant>>) {
        return ::asc::std::__visit_one<Result, Index + 1>(
            ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Variant>(value));
    } else {
        return static_cast<Result>(::asc::std::__variant_visit_at<Index>(
            ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Variant>(value)));
    }
}

template <class Result, __SIZE_TYPE__ LeftIndex, __SIZE_TYPE__ RightIndex, class Visitor, class Left, class Right>
CANN_ASC_STL_API constexpr Result __visit_two(Visitor&& visitor, Left&& left, Right&& right)
{
    if (left.index() == LeftIndex && right.index() == RightIndex) {
        return static_cast<Result>(::asc::std::forward<Visitor>(visitor)(
            ::asc::std::forward<Left>(left).template __get<LeftIndex>(),  // NOLINT(build/include_what_you_use)
            ::asc::std::forward<Right>(right).template __get<RightIndex>()));
    }
    if constexpr (RightIndex + 1 < variant_size_v<remove_cvref_t<Right>>) {
        return ::asc::std::__visit_two<Result, LeftIndex, RightIndex + 1>(
            ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Left>(left), ::asc::std::forward<Right>(right));
    } else if constexpr (LeftIndex + 1 < variant_size_v<remove_cvref_t<Left>>) {
        return ::asc::std::__visit_two<Result, LeftIndex + 1, 0>(
            ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Left>(left), ::asc::std::forward<Right>(right));
    } else {
        return static_cast<Result>(::asc::std::forward<Visitor>(visitor)(
            ::asc::std::forward<Left>(left).template __get<LeftIndex>(),  // NOLINT(build/include_what_you_use)
            ::asc::std::forward<Right>(right).template __get<RightIndex>()));
    }
}

// 三元及以上：每层消解一个变元的活跃备选，余下变元递归分派。
template <class Result, __SIZE_TYPE__ Index, class Visitor, class Variant, class... Rest>
CANN_ASC_STL_API constexpr Result __visit_n(Visitor&& visitor, Variant&& value, Rest&&... rest)
{
    if (value.index() == Index) {
        __visit_bound_visitor<remove_cvref_t<Visitor>, variant_alternative_t<Index, remove_cvref_t<Variant>>> bound{
            visitor, ::asc::std::forward<Variant>(value).template __get<Index>()};
        if constexpr (sizeof...(Rest) == 0) {
            return static_cast<Result>(bound());
        } else {
            return ::asc::std::__visit_n<Result, 0>(bound, ::asc::std::forward<Rest>(rest)...);
        }
    }
    if constexpr (Index + 1 < variant_size_v<remove_cvref_t<Variant>>) {
        return ::asc::std::__visit_n<Result, Index + 1>(::asc::std::forward<Visitor>(visitor),
            ::asc::std::forward<Variant>(value), ::asc::std::forward<Rest>(rest)...);
    } else {
        // 无值变体已在入口拦截，正常流程不会抵达此处
        CANN_ASC_STL_DETAIL_UNREACHABLE();
    }
}

template <class Visitor, class Variant>
CANN_ASC_STL_API constexpr decltype(auto) visit(Visitor&& visitor, Variant&& value)
{
    ::asc::std::__visit_check_valueless(value);
    using __result = typename __visit_common<remove_cvref_t<Visitor>, Variant>::type;
    return ::asc::std::__visit_one<__result, 0>(
        ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Variant>(value));
}
template <class Visitor, class Left, class Right>
CANN_ASC_STL_API constexpr decltype(auto) visit(Visitor&& visitor, Left&& left, Right&& right)
{
    ::asc::std::__visit_check_valueless(left, right);
    using __result = decltype(::asc::std::__visit_common_two<remove_cvref_t<Visitor>, Left, Right>(
        __make_indices_imp<variant_size_v<remove_cvref_t<Left>>, 0>{}));
    return ::asc::std::__visit_two<__result, 0, 0>(
        ::asc::std::forward<Visitor>(visitor), ::asc::std::forward<Left>(left), ::asc::std::forward<Right>(right));
}
template <class Visitor, class First, class Second, class... Rest, enable_if_t<sizeof...(Rest) >= 1, int> = 0>
CANN_ASC_STL_API constexpr auto visit(Visitor&& visitor, First&& first, Second&& second,
    Rest&&... rest) -> decltype(::asc::std::__visit_common_step<remove_cvref_t<Visitor>, remove_cvref_t<First>&,
                        remove_cvref_t<Second>&, remove_cvref_t<Rest>&...>(
                        __make_indices_imp<variant_size_v<remove_cvref_t<First>>, 0>{}))
{
    ::asc::std::__visit_check_valueless(first, second, rest...);
    using __result = decltype(::asc::std::__visit_common_step<remove_cvref_t<Visitor>, remove_cvref_t<First>&,
        remove_cvref_t<Second>&, remove_cvref_t<Rest>&...>(
        __make_indices_imp<variant_size_v<remove_cvref_t<First>>, 0>{}));
    return ::asc::std::__visit_n<__result, 0>(::asc::std::forward<Visitor>(visitor), ::asc::std::forward<First>(first),
        ::asc::std::forward<Second>(second), ::asc::std::forward<Rest>(rest)...);
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
