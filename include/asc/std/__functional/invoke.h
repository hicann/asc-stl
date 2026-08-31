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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_INVOKE_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_INVOKE_H

#include <asc/std/detail/__config>

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__fwd/reference_wrapper.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_core_convertible.h>
#include <asc/std/__type_traits/is_member_function_pointer.h>
#include <asc/std/__type_traits/is_member_object_pointer.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _DecayedFp>
struct __member_pointer_class_type {};

template <class _Ret, class _ClassType>
struct __member_pointer_class_type<_Ret _ClassType::*> {
    using type = _ClassType;
};

template <class _DecayedFp>
using __member_pointer_class_type_t = typename __member_pointer_class_type<_DecayedFp>::type;

template <class _Fp, class _A0, class _DecayFp = decay_t<_Fp>, class _DecayA0 = decay_t<_A0>,
    class _ClassT = __member_pointer_class_type_t<_DecayFp>>
using __enable_if_bullet1 = enable_if_t<is_member_function_pointer_v<_DecayFp> && is_base_of_v<_ClassT, _DecayA0>>;

template <class _Fp, class _A0, class _DecayFp = decay_t<_Fp>, class _DecayA0 = decay_t<_A0>>
using __enable_if_bullet2 =
    enable_if_t<is_member_function_pointer_v<_DecayFp> && __is_asc_std_reference_wrapper_v<_DecayA0>>;

template <class _Fp, class _A0, class _DecayFp = decay_t<_Fp>, class _DecayA0 = decay_t<_A0>,
    class _ClassT = __member_pointer_class_type_t<_DecayFp>>
using __enable_if_bullet3 = enable_if_t<is_member_function_pointer_v<_DecayFp> && !is_base_of_v<_ClassT, _DecayA0> &&
    !__is_asc_std_reference_wrapper_v<_DecayA0>>;

template <class _Fp, class _A0, class _DecayFp = decay_t<_Fp>, class _DecayA0 = decay_t<_A0>,
    class _ClassT = __member_pointer_class_type_t<_DecayFp>>
using __enable_if_bullet4 = enable_if_t<is_member_object_pointer_v<_DecayFp> && is_base_of_v<_ClassT, _DecayA0>>;

template <class _Fp, class _A0, class _DecayFp = decay_t<_Fp>, class _DecayA0 = decay_t<_A0>>
using __enable_if_bullet5 =
    enable_if_t<is_member_object_pointer_v<_DecayFp> && __is_asc_std_reference_wrapper_v<_DecayA0>>;

template <class _Fp, class _A0, class _DecayFp = decay_t<_Fp>, class _DecayA0 = decay_t<_A0>,
    class _ClassT = __member_pointer_class_type_t<_DecayFp>>
using __enable_if_bullet6 = enable_if_t<is_member_object_pointer_v<_DecayFp> && !is_base_of_v<_ClassT, _DecayA0> &&
    !__is_asc_std_reference_wrapper_v<_DecayA0>>;

template <class _Fp, class _A0, class... _Args, class = __enable_if_bullet1<_Fp, _A0>>
CANN_ASC_STL_API constexpr decltype((::asc::std::declval<_A0>().*::asc::std::declval<_Fp>())(
    ::asc::std::declval<_Args>()...))
__invoke(_Fp&& __f, _A0&& __a0, _Args&&... __args) noexcept(
    noexcept((static_cast<_A0&&>(__a0).*__f)(static_cast<_Args&&>(__args)...)))
{
    return (static_cast<_A0&&>(__a0).*__f)(static_cast<_Args&&>(__args)...);
}

template <class _Fp, class _A0, class... _Args, class = __enable_if_bullet2<_Fp, _A0>>
CANN_ASC_STL_API constexpr decltype((::asc::std::declval<_A0>().get().*::asc::std::declval<_Fp>())(
    ::asc::std::declval<_Args>()...))
__invoke(_Fp&& __f, _A0&& __a0, _Args&&... __args) noexcept(
    noexcept((__a0.get().*__f)(static_cast<_Args&&>(__args)...)))
{
    return (__a0.get().*__f)(static_cast<_Args&&>(__args)...);
}

template <class _Fp, class _A0, class... _Args, class = __enable_if_bullet3<_Fp, _A0>>
CANN_ASC_STL_API constexpr decltype(((*::asc::std::declval<_A0>()).*::asc::std::declval<_Fp>())(
    ::asc::std::declval<_Args>()...))
__invoke(_Fp&& __f, _A0&& __a0, _Args&&... __args) noexcept(
    noexcept(((*static_cast<_A0&&>(__a0)).*__f)(static_cast<_Args&&>(__args)...)))
{
    return ((*static_cast<_A0&&>(__a0)).*__f)(static_cast<_Args&&>(__args)...);
}

template <class _Fp, class _A0, class = __enable_if_bullet4<_Fp, _A0>>
CANN_ASC_STL_API constexpr decltype(::asc::std::declval<_A0>().*::asc::std::declval<_Fp>()) __invoke(
    _Fp&& __f, _A0&& __a0) noexcept(noexcept(static_cast<_A0&&>(__a0).*__f))
{
    return static_cast<_A0&&>(__a0).*__f;
}

template <class _Fp, class _A0, class = __enable_if_bullet5<_Fp, _A0>>
CANN_ASC_STL_API constexpr decltype(::asc::std::declval<_A0>().get().*::asc::std::declval<_Fp>()) __invoke(
    _Fp&& __f, _A0&& __a0) noexcept(noexcept(__a0.get().*__f))
{
    return __a0.get().*__f;
}

template <class _Fp, class _A0, class = __enable_if_bullet6<_Fp, _A0>>
CANN_ASC_STL_API constexpr decltype((*::asc::std::declval<_A0>()).*::asc::std::declval<_Fp>()) __invoke(
    _Fp&& __f, _A0&& __a0) noexcept(noexcept((*static_cast<_A0&&>(__a0)).*__f))
{
    return (*static_cast<_A0&&>(__a0)).*__f;
}

template <class _Fp, class... _Args>
CANN_ASC_STL_API constexpr decltype(::asc::std::declval<_Fp>()(::asc::std::declval<_Args>()...)) __invoke(
    _Fp&& __f, _Args&&... __args) noexcept(noexcept(static_cast<_Fp&&>(__f)(static_cast<_Args&&>(__args)...)))
{
    return static_cast<_Fp&&>(__f)(static_cast<_Args&&>(__args)...);
}

template <class _Fp, class... _Args>
using __invoke_result_t = decltype(::asc::std::__invoke(::asc::std::declval<_Fp>(), ::asc::std::declval<_Args>()...));

template <class _Fp, class _Void, class... _Args>
struct __is_invocable_impl : false_type {};

template <class _Fp, class... _Args>
struct __is_invocable_impl<_Fp, void_t<__invoke_result_t<_Fp, _Args...>>, _Args...> : true_type {};

template <class _Fp, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __is_invocable = __is_invocable_impl<_Fp, void, _Args...>::value;

template <class _Ret, class _Fp, class _Void, class... _Args>
struct __is_invocable_r_impl : false_type {};

template <class _Ret, class _Fp, class... _Args>
struct __is_invocable_r_impl<_Ret, _Fp, void_t<__invoke_result_t<_Fp, _Args...>>, _Args...>
    : bool_constant<is_void_v<_Ret> || __is_core_convertible<__invoke_result_t<_Fp, _Args...>, _Ret>::value> {};

template <class _Ret, class _Fp, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __is_invocable_r = __is_invocable_r_impl<_Ret, _Fp, void, _Args...>::value;

template <class _Fp, class _Void, class... _Args>
struct __invoke_result_impl {};

template <class _Fp, class... _Args>
struct __invoke_result_impl<_Fp, void_t<__invoke_result_t<_Fp, _Args...>>, _Args...> {
    using type = __invoke_result_t<_Fp, _Args...>;
};

template <class _Fp, class... _Args>
struct invoke_result : __invoke_result_impl<_Fp, void, _Args...> {};

template <class _Fn, class... _Args>
struct is_invocable : bool_constant<__is_invocable<_Fn, _Args...>> {};

template <class _Ret, class _Fn, class... _Args>
struct is_invocable_r : bool_constant<__is_invocable_r<_Ret, _Fn, _Args...>> {};

template <class _Fn, class... _Args>
inline constexpr bool is_invocable_v = __is_invocable<_Fn, _Args...>;

template <class _Ret, class _Fn, class... _Args>
inline constexpr bool is_invocable_r_v = __is_invocable_r<_Ret, _Fn, _Args...>;

template <class _Tp>
CANN_ASC_STL_API constexpr void __accl_test_noexcept_conversion(_Tp) noexcept;

template <bool _IsInvocable, bool _IsCVVoid, class _Ret, class _Fp, class... _Args>
inline constexpr bool __nothrow_invocable_r_imp = false;

template <class _Ret, class _Fp, class... _Args>
inline constexpr bool __nothrow_invocable_r_imp<true, false, _Ret, _Fp, _Args...> =
    noexcept(::asc::std::__accl_test_noexcept_conversion<_Ret>(
        ::asc::std::__invoke(declval<_Fp>(), ::asc::std::declval<_Args>()...)));

template <class _Ret, class _Fp, class... _Args>
inline constexpr bool __nothrow_invocable_r_imp<true, true, _Ret, _Fp, _Args...> =
    noexcept(::asc::std::__invoke(::asc::std::declval<_Fp>(), ::asc::std::declval<_Args>()...));

template <class _Fp, class... _Args>
inline constexpr bool is_nothrow_invocable_v =
    __nothrow_invocable_r_imp<__is_invocable<_Fp, _Args...>, true, void, _Fp, _Args...>;

template <class _Ret, class _Fp, class... _Args>
inline constexpr bool is_nothrow_invocable_r_v =
    __nothrow_invocable_r_imp<__is_invocable_r<_Ret, _Fp, _Args...>, is_void_v<_Ret>, _Ret, _Fp, _Args...>;

template <class _Fn, class... _Args>
struct is_nothrow_invocable : bool_constant<is_nothrow_invocable_v<_Fn, _Args...>> {};

template <class _Ret, class _Fn, class... _Args>
struct is_nothrow_invocable_r : bool_constant<is_nothrow_invocable_r_v<_Ret, _Fn, _Args...>> {};

template <class _Fn, class... _Args>
using invoke_result_t = typename invoke_result<_Fn, _Args...>::type;

template <class _Fn, class... _Args>
CANN_ASC_STL_API constexpr invoke_result_t<_Fn, _Args...> invoke(_Fn&& __f, _Args&&... __args) noexcept(
    is_nothrow_invocable_v<_Fn, _Args...>)
{
    return ::asc::std::__invoke(::asc::std::forward<_Fn>(__f), ::asc::std::forward<_Args>(__args)...);
}

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ret, class _Fn, class... _Args)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_invocable_r_v<_Ret, _Fn, _Args...>)
CANN_ASC_STL_API constexpr _Ret invoke_r(_Fn&& __f, _Args&&... __args) noexcept(
    is_nothrow_invocable_r_v<_Ret, _Fn, _Args...>)
{
    if constexpr (is_void_v<_Ret>) {
        ::asc::std::__invoke(::asc::std::forward<_Fn>(__f), ::asc::std::forward<_Args>(__args)...);
    } else {
        return ::asc::std::__invoke(::asc::std::forward<_Fn>(__f),
            ::asc::std::forward<_Args>(__args)...);  // NOLINT(build/include_what_you_use)
    }
}

template <typename _Invocable, typename _InputT, typename _InitT = _InputT>
using __accumulator_t = decay_t<invoke_result_t<_Invocable, _InitT, _InputT>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_INVOKE_H
