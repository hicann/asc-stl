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

#ifndef CANN_ASC_STL_ASC_STD___FUNCTIONAL_PERFECT_FORWARD_H
#define CANN_ASC_STL_ASC_STD___FUNCTIONAL_PERFECT_FORWARD_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
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

CANN_ASC_STL_BEGIN_NAMESPACE

// True when INVOKE(op, args...) is well-formed; inlined is_invocable_v equivalent.
template <class Op, class Void, class... Args>
inline constexpr bool __perfect_forward_invocable_impl = false;

template <class Op, class... Args>
inline constexpr bool __perfect_forward_invocable_impl<Op,
    void_t<decltype(::asc::std::invoke(::asc::std::declval<Op>(), ::asc::std::declval<Args>()...))>, Args...> = true;

template <class Op, class... Args>
inline constexpr bool __perfect_forward_invocable = __perfect_forward_invocable_impl<Op, void, Args...>;

template <class Op, class Indices, class... BoundArgs>
class __perfect_forward_impl;
template <class Op, size_t... Indices, class... BoundArgs>
class __perfect_forward_impl<Op, index_sequence<Indices...>, BoundArgs...> {
    tuple<BoundArgs...> bound_;

public:
    template <class... Args, enable_if_t<is_constructible_v<tuple<BoundArgs...>, Args&&...>, int> = 0>
    CANN_ASC_STL_API explicit constexpr __perfect_forward_impl(Args&&... args) noexcept(
        is_nothrow_constructible_v<tuple<BoundArgs...>, Args&&...>)  // NOLINT(build/include_what_you_use)
        : bound_(::asc::std::forward<Args>(args)...)
    {}
    __perfect_forward_impl(const __perfect_forward_impl&) = default;
    __perfect_forward_impl(__perfect_forward_impl&&) = default;
    __perfect_forward_impl& operator=(const __perfect_forward_impl&) = default;
    __perfect_forward_impl& operator=(__perfect_forward_impl&&) = default;

    template <class... Args, enable_if_t<__perfect_forward_invocable<Op, BoundArgs&..., Args...>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Args&&... args) & noexcept(
        noexcept(Op{}(::asc::std::get<Indices>(bound_)..., ::asc::std::forward<Args>(args)...)))
        -> decltype(Op{}(::asc::std::get<Indices>(bound_)..., ::asc::std::forward<Args>(args)...))
    {
        return Op{}(::asc::std::get<Indices>(bound_)..., ::asc::std::forward<Args>(args)...);
    }
    template <class... Args, enable_if_t<!__perfect_forward_invocable<Op, BoundArgs&..., Args...>, int> = 0>
    void operator()(Args&&...) & = delete;
    template <class... Args, enable_if_t<__perfect_forward_invocable<Op, const BoundArgs&..., Args...>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Args&&... args) const& noexcept(
        noexcept(Op{}(::asc::std::get<Indices>(bound_)..., ::asc::std::forward<Args>(args)...)))
        -> decltype(Op{}(::asc::std::get<Indices>(bound_)..., ::asc::std::forward<Args>(args)...))
    {
        return Op{}(::asc::std::get<Indices>(bound_)..., ::asc::std::forward<Args>(args)...);
    }
    template <class... Args, enable_if_t<!__perfect_forward_invocable<Op, const BoundArgs&..., Args...>, int> = 0>
    void operator()(Args&&...) const& = delete;
    template <class... Args, enable_if_t<__perfect_forward_invocable<Op, BoundArgs..., Args...>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Args&&... args) && noexcept(
        noexcept(Op{}(::asc::std::get<Indices>(::asc::std::move(bound_))..., ::asc::std::forward<Args>(args)...)))
        -> decltype(Op{}(::asc::std::get<Indices>(::asc::std::move(bound_))..., ::asc::std::forward<Args>(args)...))
    {
        return Op{}(::asc::std::get<Indices>(::asc::std::move(bound_))...,
            ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
    }
    template <class... Args, enable_if_t<!__perfect_forward_invocable<Op, BoundArgs..., Args...>, int> = 0>
    void operator()(Args&&...) && = delete;
    template <class... Args, enable_if_t<__perfect_forward_invocable<Op, const BoundArgs..., Args...>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Args&&... args) const&& noexcept(
        noexcept(Op{}(::asc::std::get<Indices>(::asc::std::move(bound_))..., ::asc::std::forward<Args>(args)...)))
        -> decltype(Op{}(::asc::std::get<Indices>(::asc::std::move(bound_))..., ::asc::std::forward<Args>(args)...))
    {
        return Op{}(::asc::std::get<Indices>(::asc::std::move(bound_))...,
            ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
    }
    template <class... Args, enable_if_t<!__perfect_forward_invocable<Op, const BoundArgs..., Args...>, int> = 0>
    void operator()(Args&&...) const&& = delete;
};
template <class Op, class... Args>
using __perfect_forward = __perfect_forward_impl<Op, index_sequence_for<Args...>, Args...>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FUNCTIONAL_PERFECT_FORWARD_H
