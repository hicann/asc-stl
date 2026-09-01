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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_NOT_FN_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_NOT_FN_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/invoke.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Fn, class _Void, class... _Args>
inline constexpr bool __can_invoke_and_negate_impl = false;

template <class _Fn, class... _Args>
inline constexpr bool __can_invoke_and_negate_impl<_Fn,
    void_t<decltype(!::asc::std::invoke(::asc::std::declval<_Fn>(), ::asc::std::declval<_Args>()...))>, _Args...> =
    true;

template <class _Fn, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __can_invoke_and_negate = __can_invoke_and_negate_impl<_Fn, void, _Args...>;

template <class _Fn>
struct __not_fn_t {
    _Fn __f;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Fn, _Args&&...>)
    CANN_ASC_STL_API explicit constexpr __not_fn_t(_Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Fn, _Args&&...>)
        : __f(::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_invoke_and_negate<_Fn&, _Args...>)
    CANN_ASC_STL_API constexpr auto operator()(_Args&&... __args) & noexcept(noexcept(
        !::asc::std::invoke(__f, ::asc::std::forward<_Args>(__args)...))) -> decltype(!::asc::std::invoke(__f,
                                                                              ::asc::std::forward<_Args>(__args)...))
    {
        return !::asc::std::invoke(__f, ::asc::std::forward<_Args>(__args)...);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__can_invoke_and_negate<_Fn&, _Args...>))
    void operator()(_Args&&...) & = delete;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_invoke_and_negate<const _Fn&, _Args...>)
    CANN_ASC_STL_API constexpr auto operator()(_Args&&... __args) const& noexcept(noexcept(
        !::asc::std::invoke(__f, ::asc::std::forward<_Args>(__args)...))) -> decltype(!::asc::std::invoke(__f,
                                                                              ::asc::std::forward<_Args>(__args)...))
    {
        return !::asc::std::invoke(__f, ::asc::std::forward<_Args>(__args)...);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__can_invoke_and_negate<const _Fn&, _Args...>))
    void operator()(_Args&&...) const& = delete;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_invoke_and_negate<_Fn, _Args...>)
    CANN_ASC_STL_API constexpr auto operator()(_Args&&... __args) && noexcept(
        noexcept(!::asc::std::invoke(::asc::std::move(__f), ::asc::std::forward<_Args>(__args)...)))
        -> decltype(!::asc::std::invoke(::asc::std::move(__f), ::asc::std::forward<_Args>(__args)...))
    {
        return !::asc::std::invoke(::asc::std::move(__f), ::asc::std::forward<_Args>(__args)...);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__can_invoke_and_negate<_Fn, _Args...>))
    void operator()(_Args&&...) && = delete;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_invoke_and_negate<const _Fn, _Args...>)
    CANN_ASC_STL_API constexpr auto operator()(_Args&&... __args) const&& noexcept(
        noexcept(!::asc::std::invoke(::asc::std::move(__f), ::asc::std::forward<_Args>(__args)...)))
        -> decltype(!::asc::std::invoke(::asc::std::move(__f), ::asc::std::forward<_Args>(__args)...))
    {
        return !::asc::std::invoke(::asc::std::move(__f), ::asc::std::forward<_Args>(__args)...);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__can_invoke_and_negate<const _Fn, _Args...>))
    void operator()(_Args&&...) const&& = delete;
};

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fn)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
    is_constructible_v<decay_t<_Fn>, _Fn> CANN_ASC_STL_DETAIL_ACCL_AND is_move_constructible_v<decay_t<_Fn>>)
[[nodiscard]] CANN_ASC_STL_API constexpr auto not_fn(_Fn&& __f)
{
    return __not_fn_t<decay_t<_Fn>>(::asc::std::forward<_Fn>(__f));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_NOT_FN_H
