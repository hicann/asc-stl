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

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/nat.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__make_unsigned)

template <class T>
using make_unsigned_t = __make_unsigned(T);

#else

using __unsigned_types = __type_list<unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;

template <class T, bool = is_integral_v<T> || is_enum_v<T>>
struct __make_unsigned_impl {};

template <class T>
struct __make_unsigned_impl<T, true> {
    struct __size_greater_equal_fn {
        template <class U>
        using __call = bool_constant<(sizeof(T) <= sizeof(U))>;
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

// CCE aicore rejects a device function signature that expands the
// decltype(__apply_cvref<...>) detection of __copy_cvref_t, so the _t helper
// is routed through a class member instead of a pure alias chain.
template <class T>
struct __make_unsigned_result {
    using type = __copy_cvref_t<T, typename __make_unsigned_impl<remove_cv_t<T>>::type>;
};

template <class T>
using make_unsigned_t = typename __make_unsigned_result<T>::type;

#endif

template <class T>
struct make_unsigned {
    using type = make_unsigned_t<T>;
};

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr make_unsigned_t<T> __to_unsigned_like(T x) noexcept
{
    return static_cast<make_unsigned_t<T>>(x);
}

template <class T, class U>
using __copy_unsigned_t = conditional_t<is_unsigned_v<T>, make_unsigned_t<U>, U>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_H
