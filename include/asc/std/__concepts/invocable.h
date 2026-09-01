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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_INVOCABLE_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_INVOCABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/invoke.h>
#include <asc/std/__type_traits/is_valid_expansion.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Fn, class... _Args>
concept invocable = requires(_Fn&& __fn, _Args&&... __args) {
    ::asc::std::invoke(::asc::std::forward<_Fn>(__fn), ::asc::std::forward<_Args>(__args)...);
};
template <class _Fn, class... _Args>
concept regular_invocable = invocable<_Fn, _Args...>;
template <class _Fun, class... _Args>
concept __invoke_constructible = requires(_Fun&& __fun, _Args&&... __args) {
    static_cast<remove_cvref_t<invoke_result_t<_Fun, _Args...>>>(::asc::std::invoke(::asc::std::forward<_Fun>(__fun),
        ::asc::std::forward<_Args>(__args)...));  // NOLINT(build/include_what_you_use)
};
#else
template <class _Fn, class... _Args>
using __invocable_result_t = invoke_result_t<_Fn, _Args...>;

template <class _Fun, class... _Args>
using __invoke_constructible_result_t = decltype(static_cast<remove_cvref_t<invoke_result_t<_Fun, _Args...>>>(
    ::asc::std::invoke(::asc::std::declval<_Fun>(), ::asc::std::declval<_Args>()...)));

template <class _Fn, class... _Args>
inline constexpr bool invocable = _IsValidExpansion<__invocable_result_t, _Fn, _Args...>::value;
template <class _Fn, class... _Args>
inline constexpr bool regular_invocable = invocable<_Fn, _Args...>;
template <class _Fun, class... _Args>
inline constexpr bool __invoke_constructible =
    _IsValidExpansion<__invoke_constructible_result_t, _Fun, _Args...>::value;
#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD
#endif
