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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COMMON_TYPE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COMMON_TYPE_H

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
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class... Tp>
struct common_type;

template <class... Tp>
using common_type_t = typename common_type<Tp...>::type;

template <class Tp, class Up>
using __cond_type = decltype(false ? declval<Tp>() : declval<Up>());

template <class Tp, class Up, class = void>
struct __common_type_extended_floating_point {};

template <class Tp, class Up>
struct __common_type_extended_floating_point<Tp, Up,
    enable_if_t<__is_extended_floating_point_v<remove_cvref_t<Tp>> && is_arithmetic_v<remove_cvref_t<Up>>>> {
    using type = common_type_t<__copy_cvref_t<Tp, float>, Up>;
};

template <class Tp, class Up>
struct __common_type_extended_floating_point<Tp, Up,
    enable_if_t<is_arithmetic_v<remove_cvref_t<Tp>> && __is_extended_floating_point_v<remove_cvref_t<Up>>>> {
    using type = common_type_t<Tp, __copy_cvref_t<Up, float>>;
};

template <class Tp, class Up, class = void>
struct __common_type3 : __common_type_extended_floating_point<Tp, Up> {};

// The approved common-reference conditional-expression fallback is provided
// in both supported language modes.
template <class Tp, class Up>
struct __common_type3<Tp, Up, void_t<__cond_type<const Tp&, const Up&>>> {
    using type = remove_cvref_t<__cond_type<const Tp&, const Up&>>;
};

template <class Tp, class Up, class = void>
struct __common_type2_imp : __common_type3<Tp, Up> {};

template <class Tp, class Up>
struct __common_type2_imp<Tp, Up, void_t<__cond_type<Tp, Up>>> {
    using type = decay_t<__cond_type<Tp, Up>>;
};

template <class, class = void>
struct __common_type_impl {};

template <class... Tp>
struct __common_types;

template <class Tp, class Up>
struct __common_type_impl<__common_types<Tp, Up>, void_t<common_type_t<Tp, Up>>> {
    using type = common_type_t<Tp, Up>;
};

template <class Tp, class Up, class Vp, class... Rest>
struct __common_type_impl<__common_types<Tp, Up, Vp, Rest...>, void_t<common_type_t<Tp, Up>>>
    : __common_type_impl<__common_types<common_type_t<Tp, Up>, Vp, Rest...>> {};

template <>
struct common_type<> {};

template <class Tp>
struct common_type<Tp> : public common_type<Tp, Tp> {};

template <class Tp, class Up, class D1 = decay_t<Tp>, class D2 = decay_t<Up>>
struct __common_type2 : common_type<D1, D2> {};

template <class Tp, class Up>
struct __common_type2<Tp, Up, Tp, Up> : __common_type2_imp<Tp, Up> {};

template <class Tp, class Up>
struct common_type<Tp, Up> : __common_type2<Tp, Up> {};

template <class Tp, class Up, class Vp, class... Rest>
struct common_type<Tp, Up, Vp, Rest...> : __common_type_impl<__common_types<Tp, Up, Vp, Rest...>> {};

template <class, class, class = void>
inline constexpr bool __has_common_type = false;

template <class Tp, class Up>
inline constexpr bool __has_common_type<Tp, Up, void_t<common_type_t<Tp, Up>>> = true;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COMMON_TYPE_H
