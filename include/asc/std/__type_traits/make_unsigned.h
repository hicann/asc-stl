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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/type_list.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// 见 make_signed.h: 类型列表路径不依赖编译器版本差异,
// 避免依赖 BiSheng 编译器尚不满足的条件。
using __unsigned_types = __type_list<unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long
#if CANN_ASC_STL_DETAIL_HAS_INT128()
    ,
    __uint128_t
#endif
    >;

template <class _Tp, bool = is_integral_v<_Tp> || is_enum_v<_Tp>>
struct __make_unsigned_impl {};

template <class _Tp>
struct __make_unsigned_impl<_Tp, true> {
    struct __size_greater_equal_fn {
        template <class _Up>
        using __call = bool_constant<(sizeof(_Tp) <= sizeof(_Up))>;
    };

    using type = __type_front<__type_find_if<__unsigned_types, __size_greater_equal_fn>>;
};

template <>
struct __make_unsigned_impl<bool, true> {};
template <>
struct __make_unsigned_impl<signed short, true> {
    using type = unsigned short;
};
template <>
struct __make_unsigned_impl<unsigned short, true> {
    using type = unsigned short;
};
template <>
struct __make_unsigned_impl<signed int, true> {
    using type = unsigned int;
};
template <>
struct __make_unsigned_impl<unsigned int, true> {
    using type = unsigned int;
};
template <>
struct __make_unsigned_impl<signed long, true> {
    using type = unsigned long;
};
template <>
struct __make_unsigned_impl<unsigned long, true> {
    using type = unsigned long;
};
template <>
struct __make_unsigned_impl<signed long long, true> {
    using type = unsigned long long;
};
template <>
struct __make_unsigned_impl<unsigned long long, true> {
    using type = unsigned long long;
};
#if CANN_ASC_STL_DETAIL_HAS_INT128()
template <>
struct __make_unsigned_impl<__int128_t, true> {
    using type = __uint128_t;
};
template <>
struct __make_unsigned_impl<__uint128_t, true> {
    using type = __uint128_t;
};
#endif

template <class _Tp>
using make_unsigned_t = __copy_cvref_t<_Tp, typename __make_unsigned_impl<remove_cv_t<_Tp>>::type>;

template <class _Tp>
struct make_unsigned {
    using type = make_unsigned_t<_Tp>;
};

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr make_unsigned_t<_Tp> __to_unsigned_like(_Tp __x) noexcept
{
    return static_cast<make_unsigned_t<_Tp>>(__x);
}

template <class _Tp, class _Up>
using __copy_unsigned_t = conditional_t<is_unsigned_v<_Tp>, make_unsigned_t<_Up>, _Up>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_H
