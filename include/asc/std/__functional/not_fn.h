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

#ifndef CANN_ASC_STL_ASC_STD___FUNCTIONAL_NOT_FN_H
#define CANN_ASC_STL_ASC_STD___FUNCTIONAL_NOT_FN_H

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
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// True when INVOKE(f, args...) is well-formed and its result can be negated.
template <class F, class Void, class... Args>
inline constexpr bool __can_invoke_and_negate_impl = false;

template <class F, class... Args>
inline constexpr bool __can_invoke_and_negate_impl<F,
    void_t<decltype(!::asc::std::invoke(::asc::std::declval<F>(), ::asc::std::declval<Args>()...))>, Args...> = true;

template <class F, class... Args>
inline constexpr bool __can_invoke_and_negate = __can_invoke_and_negate_impl<F, void, Args...>;

template <class F>
class __not_fn_t {
    F function_;

public:
    template <class... Args, enable_if_t<is_constructible_v<F, Args&&...>, int> = 0>
    CANN_ASC_STL_API explicit constexpr __not_fn_t(Args&&... args) noexcept(is_nothrow_constructible_v<F, Args&&...>)
        : function_(::asc::std::forward<Args>(args)...)
    {}

    template <class... Args, enable_if_t<__can_invoke_and_negate<F&, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Args&&... args) & noexcept(noexcept(
        !::asc::std::invoke(function_, ::asc::std::forward<Args>(args)...))) -> decltype(!::asc::std::invoke(function_,
                                                                                 ::asc::std::forward<Args>(args)...))
    {
        return !::asc::std::invoke(function_, ::asc::std::forward<Args>(args)...);
    }

    template <class... Args, enable_if_t<!__can_invoke_and_negate<F&, Args...>, int> = 0>
    void operator()(Args&&...) & = delete;

    template <class... Args, enable_if_t<__can_invoke_and_negate<const F&, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Args&&... args) const& noexcept(noexcept(
        !::asc::std::invoke(function_, ::asc::std::forward<Args>(args)...))) -> decltype(!::asc::std::invoke(function_,
                                                                                 ::asc::std::forward<Args>(args)...))
    {
        return !::asc::std::invoke(function_, ::asc::std::forward<Args>(args)...);
    }

    template <class... Args, enable_if_t<!__can_invoke_and_negate<const F&, Args...>, int> = 0>
    void operator()(Args&&...) const& = delete;

    template <class... Args, enable_if_t<__can_invoke_and_negate<F, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Args&&... args) && noexcept(
        noexcept(!::asc::std::invoke(::asc::std::move(function_), ::asc::std::forward<Args>(args)...)))
        -> decltype(!::asc::std::invoke(::asc::std::move(function_), ::asc::std::forward<Args>(args)...))
    {
        return !::asc::std::invoke(::asc::std::move(function_), ::asc::std::forward<Args>(args)...);
    }

    template <class... Args, enable_if_t<!__can_invoke_and_negate<F, Args...>, int> = 0>
    void operator()(Args&&...) && = delete;

    template <class... Args, enable_if_t<__can_invoke_and_negate<const F, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Args&&... args) const&& noexcept(
        noexcept(!::asc::std::invoke(::asc::std::move(function_), ::asc::std::forward<Args>(args)...)))
        -> decltype(!::asc::std::invoke(::asc::std::move(function_), ::asc::std::forward<Args>(args)...))
    {
        return !::asc::std::invoke(::asc::std::move(function_), ::asc::std::forward<Args>(args)...);
    }

    template <class... Args, enable_if_t<!__can_invoke_and_negate<const F, Args...>, int> = 0>
    void operator()(Args&&...) const&& = delete;
};

template <class F, class Result = decay_t<F>,
    class = enable_if_t<is_constructible_v<Result, F&&> && is_move_constructible_v<Result>>>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto not_fn(F&& function)
{
    return __not_fn_t<Result>(::asc::std::forward<F>(function));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FUNCTIONAL_NOT_FN_H
