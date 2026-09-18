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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_GET_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_GET_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/get.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__tuple_dir/get.h>
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__variant/bad_variant_access.h>
#include <asc/std/__variant/variant.h>
#include <asc/std/__variant/variant_access.h>
#include <asc/std/__variant/variant_match.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <size_t _Ip, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr bool __holds_alternative(const variant<_Types...>& __v) noexcept
{
    return __v.index() == _Ip;
}

template <class _Tp, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr bool holds_alternative(const variant<_Types...>& __v) noexcept
{
    return ::asc::std::__holds_alternative<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

template <size_t _Ip, class _Vp>
[[nodiscard]] CANN_ASC_STL_API constexpr auto&& __generic_get(_Vp&& __v)
{
    using __variant_detail::__access::__variant;
    if (!::asc::std::__holds_alternative<_Ip>(__v)) {
        ::asc::std::__throw_bad_variant_access();
    }
    return __variant::__get_alt<_Ip>(::asc::std::forward<_Vp>(__v)).__value;
}

template <size_t _Ip, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr variant_alternative_t<_Ip, variant<_Types...>>& get(variant<_Types...>& __v)
{
    static_assert(_Ip < sizeof...(_Types));
    static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
    return ::asc::std::__generic_get<_Ip>(__v);
}

template <size_t _Ip, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr variant_alternative_t<_Ip, variant<_Types...>>&& get(variant<_Types...>&& __v)
{
    static_assert(_Ip < sizeof...(_Types));
    static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
    return ::asc::std::__generic_get<_Ip>(::asc::std::move(__v));
}

template <size_t _Ip, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr const variant_alternative_t<_Ip, variant<_Types...>>& get(
    const variant<_Types...>& __v)
{
    static_assert(_Ip < sizeof...(_Types));
    static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
    return ::asc::std::__generic_get<_Ip>(__v);
}

template <size_t _Ip, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr const variant_alternative_t<_Ip, variant<_Types...>>&& get(
    const variant<_Types...>&& __v)
{
    static_assert(_Ip < sizeof...(_Types));
    static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
    return ::asc::std::__generic_get<_Ip>(::asc::std::move(__v));
}

template <class _Tp, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp& get(variant<_Types...>& __v)
{
    static_assert(!is_void_v<_Tp>);
    return ::asc::std::get<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

template <class _Tp, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp&& get(variant<_Types...>&& __v)
{
    static_assert(!is_void_v<_Tp>);
    return ::asc::std::get<__find_exactly_one_t<_Tp, _Types...>::value>(::asc::std::move(__v));
}

template <class _Tp, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr const _Tp& get(const variant<_Types...>& __v)
{
    static_assert(!is_void_v<_Tp>);
    return ::asc::std::get<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

template <class _Tp, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr const _Tp&& get(const variant<_Types...>&& __v)
{
    static_assert(!is_void_v<_Tp>);
    return ::asc::std::get<__find_exactly_one_t<_Tp, _Types...>::value>(::asc::std::move(__v));
}

template <size_t _Ip, class _Vp>
[[nodiscard]] CANN_ASC_STL_API constexpr auto* __generic_get_if(_Vp* __v) noexcept
{
    using __variant_detail::__access::__variant;
    return __v && ::asc::std::__holds_alternative<_Ip>(*__v) ?
        ::asc::std::addressof(__variant::__get_alt<_Ip>(*__v).__value) :
        nullptr;
}

template <size_t _Ip, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr add_pointer_t<variant_alternative_t<_Ip, variant<_Types...>>> get_if(
    variant<_Types...>* __v) noexcept
{
    static_assert(_Ip < sizeof...(_Types));
    static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
    return ::asc::std::__generic_get_if<_Ip>(__v);
}

template <size_t _Ip, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr add_pointer_t<const variant_alternative_t<_Ip, variant<_Types...>>> get_if(
    const variant<_Types...>* __v) noexcept
{
    static_assert(_Ip < sizeof...(_Types));
    static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
    return ::asc::std::__generic_get_if<_Ip>(__v);
}

template <class _Tp, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr add_pointer_t<_Tp> get_if(variant<_Types...>* __v) noexcept
{
    static_assert(!is_void_v<_Tp>);
    return ::asc::std::get_if<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

template <class _Tp, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr add_pointer_t<const _Tp> get_if(const variant<_Types...>* __v) noexcept
{
    static_assert(!is_void_v<_Tp>);
    return ::asc::std::get_if<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

// __unchecked_get is the same as ::asc::std::get, except, it is UB to use it
// with the wrong type whereas ::asc::std::get will throw or returning nullptr.
// This makes it faster than ::asc::std::get.
template <size_t _Ip, class _Vp>
[[nodiscard]] CANN_ASC_STL_API constexpr auto&& __unchecked_get(_Vp&& __v) noexcept
{
    using __variant_detail::__access::__variant;
    return __variant::__get_alt<_Ip>(::asc::std::forward<_Vp>(__v)).__value;  // NOLINT(build/include_what_you_use)
}

template <class _Tp, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr auto&& __unchecked_get(const variant<_Types...>& __v) noexcept
{
    return ::asc::std::__unchecked_get<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

template <class _Tp, class... _Types>
[[nodiscard]] CANN_ASC_STL_API constexpr auto&& __unchecked_get(variant<_Types...>& __v) noexcept
{
    return ::asc::std::__unchecked_get<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_GET_H
