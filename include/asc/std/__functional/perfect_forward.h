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

// -*- C++ -*-
#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_PERFECT_FORWARD_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_PERFECT_FORWARD_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/move.h>
#include <asc/std/tuple>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Op, class _Indices, class... _BoundArgs>
struct __perfect_forward_impl;

template <class _Op, size_t... _Idx, class... _BoundArgs>
struct __perfect_forward_impl<_Op, index_sequence<_Idx...>, _BoundArgs...> {
private:
    tuple<_BoundArgs...> __bound_args_;

    template <class... _Args>
    static constexpr bool __noexcept_constructible = is_nothrow_constructible_v<tuple<_BoundArgs...>, _Args&&...>;

public:
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_constructible_v<tuple<_BoundArgs...>, _Args&&...>)  // NOLINT(build/include_what_you_use)
    CANN_ASC_STL_API explicit constexpr __perfect_forward_impl(_Args&&... __bound_args) noexcept(
        __noexcept_constructible<_Args...>)
        : __bound_args_(::asc::std::forward<_Args>(__bound_args)...)
    {}

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __perfect_forward_impl(__perfect_forward_impl const&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __perfect_forward_impl(__perfect_forward_impl&&) = default;

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __perfect_forward_impl& operator=(__perfect_forward_impl const&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __perfect_forward_impl& operator=(__perfect_forward_impl&&) = default;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_invocable_v<_Op, _BoundArgs&..., _Args...>)
    CANN_ASC_STL_API constexpr auto operator()(_Args&&... __args) & noexcept(
        noexcept(_Op()(::asc::std::get<_Idx>(__bound_args_)..., ::asc::std::forward<_Args>(__args)...)))
        -> decltype(_Op()(::asc::std::get<_Idx>(__bound_args_)..., ::asc::std::forward<_Args>(__args)...))
    {
        return _Op()(::asc::std::get<_Idx>(__bound_args_)..., ::asc::std::forward<_Args>(__args)...);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_invocable_v<_Op, _BoundArgs&..., _Args...>))
    CANN_ASC_STL_API auto operator()(_Args&&...) & = delete;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_invocable_v<_Op, _BoundArgs const&..., _Args...>)
    CANN_ASC_STL_API constexpr auto operator()(_Args&&... __args) const& noexcept(
        noexcept(_Op()(::asc::std::get<_Idx>(__bound_args_)..., ::asc::std::forward<_Args>(__args)...)))
        -> decltype(_Op()(::asc::std::get<_Idx>(__bound_args_)..., ::asc::std::forward<_Args>(__args)...))
    {
        return _Op()(::asc::std::get<_Idx>(__bound_args_)..., ::asc::std::forward<_Args>(__args)...);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_invocable_v<_Op, _BoundArgs const&..., _Args...>))
    CANN_ASC_STL_API auto operator()(_Args&&...) const& = delete;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_invocable_v<_Op, _BoundArgs..., _Args...>)
    CANN_ASC_STL_API constexpr auto operator()(_Args&&... __args) && noexcept(noexcept(
        _Op()(::asc::std::get<_Idx>(::asc::std::move(__bound_args_))..., ::asc::std::forward<_Args>(__args)...)))
        -> decltype(_Op()(
            ::asc::std::get<_Idx>(::asc::std::move(__bound_args_))..., ::asc::std::forward<_Args>(__args)...))
    {
        return _Op()(::asc::std::get<_Idx>(::asc::std::move(__bound_args_))..., ::asc::std::forward<_Args>(__args)...);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_invocable_v<_Op, _BoundArgs..., _Args...>))
    CANN_ASC_STL_API auto operator()(_Args&&...) && = delete;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_invocable_v<_Op, _BoundArgs const..., _Args...>)
    CANN_ASC_STL_API constexpr auto operator()(_Args&&... __args) const&& noexcept(noexcept(
        _Op()(::asc::std::get<_Idx>(::asc::std::move(__bound_args_))..., ::asc::std::forward<_Args>(__args)...)))
        -> decltype(_Op()(
            ::asc::std::get<_Idx>(::asc::std::move(__bound_args_))..., ::asc::std::forward<_Args>(__args)...))
    {
        return _Op()(::asc::std::get<_Idx>(::asc::std::move(__bound_args_))...,
            ::asc::std::forward<_Args>(__args)...);  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_invocable_v<_Op, _BoundArgs const..., _Args...>))
    CANN_ASC_STL_API auto operator()(_Args&&...) const&& = delete;
};

// __perfect_forward implements a perfect-forwarding call wrapper as explained in [func.require].
template <class _Op, class... _Args>
using __perfect_forward = __perfect_forward_impl<_Op, index_sequence_for<_Args...>, _Args...>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_PERFECT_FORWARD_H
