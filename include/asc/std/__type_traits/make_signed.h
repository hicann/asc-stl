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

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/nat.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/type_list.h>

// Feature macro inlined from the dev dialect layer (not present in the base config).
#ifndef CANN_ASC_STL_DETAIL_HAS_INT128
#if !defined(ASC_DISABLE_INT128_SUPPORT) && defined(__linux__) && defined(__SIZEOF_INT128__)
#define CANN_ASC_STL_DETAIL_HAS_INT128() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_INT128() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128

CANN_ASC_STL_BEGIN_NAMESPACE

// 统一走类型列表实现：编译器家族不提供稳定的 __make_signed 类型变换内建，
// Host 与设备语义一致，含枚举与目标门控的 128 位扩展。
using __signed_types = __type_list<signed char, signed short, signed int, signed long, signed long long
#if CANN_ASC_STL_DETAIL_HAS_INT128()
    ,
    __int128_t
#endif
    >;

template <class T, bool = is_integral_v<T> || is_enum_v<T>>
struct __make_signed_impl {};

template <class T>
struct __make_signed_impl<T, true> {
    struct __size_greater_equal_fn {
        template <class U>
        using __call = bool_constant<(sizeof(T) <= sizeof(U))>;
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
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()

// CCE aicore rejects a device function signature that expands the
// decltype(__apply_cvref<...>) detection of __copy_cvref_t, so the _t helper
// is routed through a class member instead of a pure alias chain.
template <class T>
struct __make_signed_result {
    using type = __copy_cvref_t<T, typename __make_signed_impl<remove_cv_t<T>>::type>;
};

template <class T>
using make_signed_t = typename __make_signed_result<T>::type;

template <class T>
struct make_signed {
    using type = make_signed_t<T>;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_SIGNED_H
