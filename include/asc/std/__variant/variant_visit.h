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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_VISIT_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_VISIT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/invoke.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/unreachable.h>
#include <asc/std/__variant/variant_access.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __variant_detail::__visitation {
struct __variant {
    // We need to guard against the final invocation where we have processed all variants
    template <size_t _Remaining, size_t _CurrentVariant, class... _Variants, enable_if_t<_Remaining == 0, int> = 0>
    [[nodiscard]] CANN_ASC_STL_API static constexpr size_t __get_runtime_index(const _Variants&...) noexcept
    {
        return 0;
    }

    template <size_t _Remaining, size_t _CurrentVariant, class _Variant, class... _OtherVariants,
        enable_if_t<(_Remaining != 0) && (_CurrentVariant == 0), int> = 0>
    [[nodiscard]] CANN_ASC_STL_API static constexpr size_t __get_runtime_index(
        const _Variant& __v, const _OtherVariants&...) noexcept
    {
        return __v.__impl_.index();
    }

    template <size_t _Remaining, size_t _CurrentVariant, class _Variant, class... _OtherVariants,
        enable_if_t<(_Remaining != 0) && (_CurrentVariant != 0), int> = 0>
    [[nodiscard]] CANN_ASC_STL_API static constexpr size_t __get_runtime_index(
        const _Variant&, const _OtherVariants&... __vs) noexcept
    {
        return __get_runtime_index<_Remaining, _CurrentVariant - 1>(__vs...);
    }

    // Terminal function call with all indexes determined
    template <class _Visitor, class... _Vs, size_t... _ProcessedIndices>
    [[nodiscard]] CANN_ASC_STL_API static constexpr decltype(auto) __visit_impl(index_sequence<_ProcessedIndices...>,
        integer_sequence<size_t>, const size_t, _Visitor&& __visitor, _Vs&&... __vs)
    {
        return ::asc::std::__invoke(::asc::std::forward<_Visitor>(__visitor),
            __access::__base::__get_alt<_ProcessedIndices>(::asc::std::forward<_Vs>(__vs).__impl_)...);
    }

    template <size_t _CurrentIndex, class _Visitor, class... _Vs, size_t... _ProcessedIndices,
        size_t... _UnprocessedIndices, enable_if_t<_CurrentIndex != 0, int> = 0>
    [[nodiscard]] CANN_ASC_STL_API static constexpr decltype(auto) __visit_impl(index_sequence<_ProcessedIndices...>,
        index_sequence<_CurrentIndex, _UnprocessedIndices...>, const size_t __current_index, _Visitor&& __visitor,
        _Vs&&... __vs)
    {
        // We found the right index, move to the next variant
        if (__current_index == _CurrentIndex) {
            const size_t __next_index =
                __get_runtime_index<sizeof...(_UnprocessedIndices), sizeof...(_ProcessedIndices) + 1>(__vs...);
            return __visit_impl(index_sequence<_ProcessedIndices..., _CurrentIndex>{},
                index_sequence<_UnprocessedIndices...>{}, __next_index, ::asc::std::forward<_Visitor>(__visitor),
                ::asc::std::forward<_Vs>(__vs)...);
        }

        return __visit_impl(index_sequence<_ProcessedIndices...>{},
            index_sequence<_CurrentIndex - 1, _UnprocessedIndices...>{}, __current_index,
            ::asc::std::forward<_Visitor>(__visitor), ::asc::std::forward<_Vs>(__vs)...);
    }

    // This overload is needed to tell the compiler that the recursion is indeed limited
    template <class _Visitor, class... _Vs, size_t... _ProcessedIndices, size_t... _UnprocessedIndices>
    [[nodiscard]] CANN_ASC_STL_API static constexpr decltype(auto) __visit_impl(index_sequence<_ProcessedIndices...>,
        index_sequence<0, _UnprocessedIndices...>, const size_t __current_index, _Visitor&& __visitor, _Vs&&... __vs)
    {
        // We found the right index, move to the next variant
        if (__current_index == 0) {
            const size_t __next_index =
                __get_runtime_index<sizeof...(_UnprocessedIndices), sizeof...(_ProcessedIndices) + 1>(__vs...);
            return __visit_impl(index_sequence<_ProcessedIndices..., 0>{}, index_sequence<_UnprocessedIndices...>{},
                __next_index, ::asc::std::forward<_Visitor>(__visitor), ::asc::std::forward<_Vs>(__vs)...);
        }
        ::asc::std::unreachable();
    }

    template <class _Visitor, class... _Vs>
    [[nodiscard]] CANN_ASC_STL_API static constexpr decltype(auto) __visit_value(_Visitor&& __visitor, _Vs&&... __vs)
    {
        // NOTE: We use a recursive implementation strategy here. That means we can omit the manual return type checks
        // from the common function pointer implementation, as the compiler will abort if the return types do not match.
        const size_t __first_index = __get_runtime_index<sizeof...(_Vs), 0>(__vs...);
        return __visit_impl(integer_sequence<size_t>{}, index_sequence<(remove_cvref_t<_Vs>::__size() - 1)...>{},
            __first_index, __make_value_visitor(::asc::std::forward<_Visitor>(__visitor)),
            ::asc::std::forward<_Vs>(__vs)...);
    }

    template <class _Rp, class _Visitor, class... _Vs>
    [[nodiscard]] CANN_ASC_STL_API static constexpr _Rp __visit_value(_Visitor&& __visitor, _Vs&&... __vs)
    {
        const size_t __first_index = __get_runtime_index<sizeof...(_Vs), 0>(__vs...);
        return __visit_impl(integer_sequence<size_t>{}, index_sequence<(remove_cvref_t<_Vs>::__size() - 1)...>{},
            __first_index, __make_value_visitor<_Rp>(::asc::std::forward<_Visitor>(__visitor)),
            ::asc::std::forward<_Vs>(__vs)...);
    }

    template <class _Visitor, class... _Values>
    CANN_ASC_STL_API static constexpr void __accl_visit_exhaustive_visitor_check()
    {
        static_assert(is_invocable_v<_Visitor, _Values...>, "`std::visit` requires the visitor to be exhaustive.");
    }

    template <class _Visitor>
    struct __value_visitor {
        template <class... _Alts>
        [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) operator()(_Alts&&... __alts) const
        {
            __accl_visit_exhaustive_visitor_check<_Visitor,
                decltype((::asc::std::forward<_Alts>(__alts).__value))...>();
            return ::asc::std::__invoke(
                ::asc::std::forward<_Visitor>(__visitor), ::asc::std::forward<_Alts>(__alts).__value...);
        }
        _Visitor&& __visitor;
    };

    template <class _Rp, class _Visitor>
    struct __value_visitor_return_type {
        template <class... _Alts>
        [[nodiscard]] CANN_ASC_STL_API constexpr _Rp operator()(_Alts&&... __alts) const
        {
            __accl_visit_exhaustive_visitor_check<_Visitor,
                decltype((::asc::std::forward<_Alts>(__alts).__value))...>();
            return ::asc::std::__invoke(
                ::asc::std::forward<_Visitor>(__visitor), ::asc::std::forward<_Alts>(__alts).__value...);
        }
        _Visitor&& __visitor;
    };

    template <class _Visitor>
    struct __value_visitor_return_type<void, _Visitor> {
        template <class... _Alts>
        CANN_ASC_STL_API constexpr void operator()(_Alts&&... __alts) const
        {
            __accl_visit_exhaustive_visitor_check<_Visitor,
                decltype((::asc::std::forward<_Alts>(__alts).__value))...>();
            ::asc::std::__invoke(
                ::asc::std::forward<_Visitor>(__visitor), ::asc::std::forward<_Alts>(__alts).__value...);
        }
        _Visitor&& __visitor;
    };

    template <class _Visitor>
    [[nodiscard]] CANN_ASC_STL_API static constexpr auto __make_value_visitor(_Visitor&& __visitor)
    {
        return __value_visitor<_Visitor>{::asc::std::forward<_Visitor>(__visitor)};
    }

    template <class _Rp, class _Visitor>
    [[nodiscard]] CANN_ASC_STL_API static constexpr auto __make_value_visitor(_Visitor&& __visitor)
    {
        return __value_visitor_return_type<_Rp, _Visitor>{
            ::asc::std::forward<_Visitor>(__visitor)};  // NOLINT(build/include_what_you_use)
    }
};
}  // namespace __variant_detail::__visitation

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_VISIT_H
