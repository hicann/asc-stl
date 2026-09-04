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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_STATIC_FOR_H
#define CANN_ASC_STL_DETAIL_UTILITY_STATIC_FOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/integer_sequence.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <typename _SizeType, _SizeType _Start, _SizeType _Step, typename _Operator, _SizeType... _Indices,
    typename... _TArgs>
CANN_ASC_STL_API constexpr void __static_for_impl(
    _Operator __op, ::asc::std::integer_sequence<_SizeType, _Indices...>, _TArgs&&... __args) noexcept((true && ... &&
    noexcept(__op(::asc::std::integral_constant<_SizeType, (_Indices * _Step + _Start)>{}, __args...))))
{
    (__op(::asc::std::integral_constant<_SizeType, (_Indices * _Step + _Start)>{}, __args...), ...);
}

template <typename _Tp, _Tp _Size, typename _Operator, typename... _TArgs>
CANN_ASC_STL_API constexpr void static_for(_Operator __op, _TArgs&&... __args) noexcept(
    noexcept(::asc::__static_for_impl<_Tp, 0, 1>(
        __op, ::asc::std::make_integer_sequence<_Tp, _Size>{}, ::asc::std::forward<_TArgs>(__args)...)))
{
    ::asc::__static_for_impl<_Tp, 0, 1>(
        __op, ::asc::std::make_integer_sequence<_Tp, _Size>{}, ::asc::std::forward<_TArgs>(__args)...);
}

template <typename _Tp, _Tp _Start, _Tp _End, _Tp _Step = 1, typename _Operator, typename... _TArgs>
CANN_ASC_STL_API constexpr void static_for(_Operator __op, _TArgs&&... __args) noexcept(
    noexcept(::asc::__static_for_impl<_Tp, _Start, _Step>(__op,
        ::asc::std::make_integer_sequence<_Tp, (_End - _Start) / _Step>{}, ::asc::std::forward<_TArgs>(__args)...)))
{
    ::asc::__static_for_impl<_Tp, _Start, _Step>(__op,
        ::asc::std::make_integer_sequence<_Tp, (_End - _Start) / _Step>{}, ::asc::std::forward<_TArgs>(__args)...);
}

template <auto _Size, typename _Operator, typename... _TArgs>
CANN_ASC_STL_API constexpr void static_for(_Operator __op, _TArgs&&... __args) noexcept(
    noexcept(::asc::static_for<decltype(_Size), _Size>(__op, ::asc::std::forward<_TArgs>(__args)...)))
{
    ::asc::static_for<decltype(_Size), _Size>(__op, ::asc::std::forward<_TArgs>(__args)...);
}

template <auto _Start, decltype(_Start) _End, decltype(_Start) _Step = decltype(_Start){1}, typename _Operator,
    typename... _TArgs>
CANN_ASC_STL_API constexpr void static_for(_Operator __op, _TArgs&&... __args) noexcept(
    noexcept(::asc::static_for<decltype(_Start), _Start, _End, _Step>(__op, ::asc::std::forward<_TArgs>(__args)...)))
{
    ::asc::static_for<decltype(_Start), _Start, _End, _Step>(
        __op, ::asc::std::forward<_TArgs>(__args)...);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_STATIC_FOR_H
