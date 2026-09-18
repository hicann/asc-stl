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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_VIRTUAL_FUNCTIONS_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_VIRTUAL_FUNCTIONS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/std/__algorithm/max.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_member_function_pointer.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/maybe_const.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/__utility/typeid.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//!
//! __override_tag
//!
template <class _Tp, auto _Override>
struct __override_tag_;

template <class _Tp, auto _Override>
using __override_tag = __override_tag_<_Tp, _Override>*;

CANN_ASC_STL_DETAIL_DIAG_PUSH
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_GCC("-Wstrict-aliasing")

template <class _Fn, class _Cp>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __class_of_(_Fn _Cp::*) -> _Cp;

template <class _Fn>
using __class_of = decltype(::asc::__class_of_(_Fn()));

//! We use a C-style cast instead of a static_cast because a C-style cast will
//! ignore accessibility, letting us cast to a private base class.
template <class _DstPtr, class _Src>
CANN_ASC_STL_DETAIL_NODEBUG_API auto __c_style_cast(_Src* __ptr) noexcept -> _DstPtr
{
    static_assert(::asc::std::is_pointer_v<_DstPtr>);
    static_assert(
        ::asc::std::is_base_of_v<::asc::std::remove_pointer_t<_DstPtr>, _Src>, "invalid C-style cast detected");
    return (_DstPtr)__ptr;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
}

// Helper function to not use a function pointer as a template parameter, which breaks MSVC in some cases.
template <class _Tp, class _FnType, class _Ret, bool _IsConst, bool _IsNothrow, class... _Args>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __override_fn_dispatch_impl([[maybe_unused]] _FnType __fn,
    [[maybe_unused]] ::asc::std::__maybe_const<_IsConst, void>* __pv,
    [[maybe_unused]] _Args... __args) noexcept(_IsNothrow) -> _Ret
{
    using __value_type = ::asc::std::__maybe_const<_IsConst, _Tp>;

    if constexpr (::asc::std::is_same_v<_Tp, void>) {
        // This instantiation is created only during the computation of the vtable
        // type. It is never actually called.
        CANN_ASC_STL_DETAIL_UNREACHABLE();
    } else if constexpr (::asc::std::is_member_function_pointer_v<_FnType>) {
        // _Fn may be a pointer to a member function of a private base of _Tp. So
        // after static_cast-ing to _Tp*, we need to use a C-style cast to get a
        // pointer to the correct base class.
        using __class_type = ::asc::std::__maybe_const<_IsConst, __class_of<_FnType>>;
        __class_type& __obj = *::asc::__c_style_cast<__class_type*>(static_cast<__value_type*>(__pv));
        return (__obj.*__fn)(static_cast<_Args&&>(__args)...);
    } else {
        __value_type& __obj = *static_cast<__value_type*>(__pv);
        return (*__fn)(__obj, static_cast<_Args&&>(__args)...);
    }
}

template <class _Tp, auto _Fn, class _Ret, bool _IsConst, bool _IsNothrow, class... _Args>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __override_fn_(
    [[maybe_unused]] ::asc::std::__maybe_const<_IsConst, void>* __pv,
    [[maybe_unused]] _Args... __args) noexcept(_IsNothrow) -> _Ret
{
    return __override_fn_dispatch_impl<_Tp, decltype(_Fn), _Ret, _IsConst, _IsNothrow, _Args...>(
        _Fn, __pv, static_cast<_Args&&>(__args)...);
}

CANN_ASC_STL_DETAIL_DIAG_POP

template <class _Fn, class _Tp = void, auto _Override = 0>
extern ::asc::std::__undefined<_Fn> __virtual_override_fn;

template <class _Tp, auto _Override, class _Ret, class _Cp, class... _Args>
inline constexpr ::asc::std::type_identity_t<_Ret (*)(void*, _Args...)>  //
    __virtual_override_fn<_Ret (*)(_Cp&, _Args...), _Tp, _Override> =    //
    &__override_fn_<_Tp, _Override, _Ret, false, false, _Args...>;

template <class _Tp, auto _Override, class _Ret, class _Cp, class... _Args>
inline constexpr ::asc::std::type_identity_t<_Ret (*)(void const*, _Args...)>
    __virtual_override_fn<_Ret (*)(_Cp const&, _Args...), _Tp, _Override> =
        &__override_fn_<_Tp, _Override, _Ret, true, false, _Args...>;

template <class _Tp, auto _Override, class _Ret, class _Cp, class... _Args>
inline constexpr ::asc::std::type_identity_t<_Ret (*)(void*, _Args...) noexcept>
    __virtual_override_fn<_Ret (*)(_Cp&, _Args...) noexcept, _Tp, _Override> =
        &__override_fn_<_Tp, _Override, _Ret, false, true, _Args...>;

template <class _Tp, auto _Override, class _Ret, class _Cp, class... _Args>
inline constexpr ::asc::std::type_identity_t<_Ret (*)(void const*, _Args...) noexcept>
    __virtual_override_fn<_Ret (*)(_Cp const&, _Args...) noexcept, _Tp, _Override> =
        &__override_fn_<_Tp, _Override, _Ret, true, true, _Args...>;

// TODO: Add support for member functions with reference qualifiers.

template <class _Tp, auto _Override, class _Ret, class _Cp, class... _Args>
inline constexpr ::asc::std::type_identity_t<_Ret (*)(void*, _Args...)>  //
    __virtual_override_fn<_Ret (_Cp::*)(_Args...), _Tp, _Override> =     //
    &__override_fn_<_Tp, _Override, _Ret, false, false, _Args...>;

template <class _Tp, auto _Override, class _Ret, class _Cp, class... _Args>
inline constexpr ::asc::std::type_identity_t<_Ret (*)(void const*, _Args...)>  //
    __virtual_override_fn<_Ret (_Cp::*)(_Args...) const, _Tp, _Override> =
        &__override_fn_<_Tp, _Override, _Ret, true, false, _Args...>;

template <class _Tp, auto _Override, class _Ret, class _Cp, class... _Args>
inline constexpr ::asc::std::type_identity_t<_Ret (*)(void*, _Args...) noexcept>
    __virtual_override_fn<_Ret (_Cp::*)(_Args...) noexcept, _Tp, _Override> =
        &__override_fn_<_Tp, _Override, _Ret, false, true, _Args...>;

template <class _Tp, auto _Override, class _Ret, class _Cp, class... _Args>
inline constexpr ::asc::std::type_identity_t<_Ret (*)(void const*, _Args...) noexcept>
    __virtual_override_fn<_Ret (_Cp::*)(_Args...) const noexcept, _Tp, _Override> =
        &__override_fn_<_Tp, _Override, _Ret, true, true, _Args...>;

template <class _Ret, class... _Args>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_virtual_result(_Ret (*)(_Args...)) -> _Ret;

template <class _Ret, class... _Args>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_virtual_result(_Ret (*)(_Args...) noexcept) noexcept -> _Ret;

template <class _Ret, class... _Args>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __is_virtual_const(_Ret (*)(void*, _Args...)) -> ::asc::std::false_type;

template <class _Ret, class... _Args>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __is_virtual_const(_Ret (*)(void const*, _Args...)) -> ::asc::std::true_type;

//!
//! __virtual_fn
//!
template <auto _Fn>
struct __virtual_fn {
    using __function_t = decltype(__virtual_override_fn<decltype(_Fn)>);
    using __result_t = decltype(__get_virtual_result(__function_t{}));

    static constexpr bool __const_fn = decltype(::asc::__is_virtual_const(__function_t{}))::value;
    static constexpr bool __nothrow_fn = noexcept(::asc::__get_virtual_result(__function_t{}));

    template <class _Tp, auto _Override>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr __virtual_fn(__override_tag<_Tp, _Override>) noexcept
        : __fn_(__virtual_override_fn<decltype(_Fn), _Tp, _Override>)
    {}

    __function_t __fn_;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC
#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_VIRTUAL_FUNCTIONS_H
