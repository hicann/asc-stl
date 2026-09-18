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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_SIGNED_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_SIGNED_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/type_list.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// BiSheng does not provide a stable __make_signed type-transform builtin.
// 源库的类型列表回退路径, Host 与设备语义一致
// AICore, including enums and the target-gated 128-bit extension.
using __signed_types = __type_list<signed char, signed short, signed int, signed long, signed long long
#if CANN_ASC_STL_DETAIL_HAS_INT128()
    ,
    __int128_t
#endif
    >;

template <class _Tp, bool = is_integral_v<_Tp> || is_enum_v<_Tp>>
struct __make_signed_impl {};

template <class _Tp>
struct __make_signed_impl<_Tp, true> {
    struct __size_greater_equal_fn {
        template <class _Up>
        using __call = bool_constant<(sizeof(_Tp) <= sizeof(_Up))>;
    };

    using type = __type_front<__type_find_if<__signed_types, __size_greater_equal_fn>>;
};

template <>
struct __make_signed_impl<bool, true> {};
template <>
struct __make_signed_impl<signed short, true> {
    using type = short;
};
template <>
struct __make_signed_impl<unsigned short, true> {
    using type = short;
};
template <>
struct __make_signed_impl<signed int, true> {
    using type = int;
};
template <>
struct __make_signed_impl<unsigned int, true> {
    using type = int;
};
template <>
struct __make_signed_impl<signed long, true> {
    using type = long;
};
template <>
struct __make_signed_impl<unsigned long, true> {
    using type = long;
};
template <>
struct __make_signed_impl<signed long long, true> {
    using type = long long;
};
template <>
struct __make_signed_impl<unsigned long long, true> {
    using type = long long;
};
#if CANN_ASC_STL_DETAIL_HAS_INT128()
template <>
struct __make_signed_impl<__int128_t, true> {
    using type = __int128_t;
};
template <>
struct __make_signed_impl<__uint128_t, true> {
    using type = __int128_t;
};
#endif

template <class _Tp>
using make_signed_t = __copy_cvref_t<_Tp, typename __make_signed_impl<remove_cv_t<_Tp>>::type>;

template <class _Tp>
struct make_signed {
    using type = make_signed_t<_Tp>;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_SIGNED_H
