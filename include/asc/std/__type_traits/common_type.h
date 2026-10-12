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

template <class... _Tp>
struct common_type;

template <class... _Tp>
using common_type_t = typename common_type<_Tp...>::type;

template <class _Tp, class _Up>
using __cond_type = decltype(false ? declval<_Tp>() : declval<_Up>());

template <class _Tp, class _Up, class = void>
struct __common_type_extended_floating_point {};

template <class _Tp, class _Up>
struct __common_type_extended_floating_point<_Tp, _Up,
    enable_if_t<__is_extended_floating_point_v<remove_cvref_t<_Tp>> && is_arithmetic_v<remove_cvref_t<_Up>>>> {
    using type = common_type_t<__copy_cvref_t<_Tp, float>, _Up>;
};

template <class _Tp, class _Up>
struct __common_type_extended_floating_point<_Tp, _Up,
    enable_if_t<is_arithmetic_v<remove_cvref_t<_Tp>> && __is_extended_floating_point_v<remove_cvref_t<_Up>>>> {
    using type = common_type_t<_Tp, __copy_cvref_t<_Up, float>>;
};

template <class _Tp, class _Up, class = void>
struct __common_type3 : __common_type_extended_floating_point<_Tp, _Up> {};

#if CANN_ASC_STL_DETAIL_HAS_CXX20()
template <class _Tp, class _Up>
struct __common_type3<_Tp, _Up, void_t<__cond_type<const _Tp&, const _Up&>>> {
    using type = remove_cvref_t<__cond_type<const _Tp&, const _Up&>>;
};
#endif

template <class _Tp, class _Up, class = void>
struct __common_type2_imp : __common_type3<_Tp, _Up> {};

template <class _Tp, class _Up>
using __msvc_declval_workaround =
#if CANN_ASC_STL_DETAIL_COMPILER_MSVC
    enable_if_t<is_same_v<__cond_type<_Tp, _Up>, __cond_type<_Up, _Tp>>>;
#else
    void;
#endif

template <class _Tp, class _Up>
struct __common_type2_imp<_Tp, _Up, void_t<__cond_type<_Tp, _Up>, __msvc_declval_workaround<_Tp, _Up>>> {
    using type = decay_t<__cond_type<_Tp, _Up>>;
};

template <class, class = void>
struct __common_type_impl {};

template <class... _Tp>
struct __common_types;

template <class _Tp, class _Up>
struct __common_type_impl<__common_types<_Tp, _Up>, void_t<common_type_t<_Tp, _Up>>> {
    using type = common_type_t<_Tp, _Up>;
};

template <class _Tp, class _Up, class _Vp, class... _Rest>
struct __common_type_impl<__common_types<_Tp, _Up, _Vp, _Rest...>, void_t<common_type_t<_Tp, _Up>>>
    : __common_type_impl<__common_types<common_type_t<_Tp, _Up>, _Vp, _Rest...>> {};

template <>
struct common_type<> {};

template <class _Tp>
struct common_type<_Tp> : public common_type<_Tp, _Tp> {};

template <class _Tp, class _Up, class _D1 = decay_t<_Tp>, class _D2 = decay_t<_Up>>
struct __common_type2 : common_type<_D1, _D2> {};

template <class _Tp, class _Up>
struct __common_type2<_Tp, _Up, _Tp, _Up> : __common_type2_imp<_Tp, _Up> {};

template <class _Tp, class _Up>
struct common_type<_Tp, _Up> : __common_type2<_Tp, _Up> {};

template <class _Tp, class _Up, class _Vp, class... _Rest>
struct common_type<_Tp, _Up, _Vp, _Rest...> : __common_type_impl<__common_types<_Tp, _Up, _Vp, _Rest...>> {};

template <class, class, class = void>
inline constexpr bool __has_common_type = false;

template <class _Tp, class _Up>
inline constexpr bool __has_common_type<_Tp, _Up, void_t<common_type_t<_Tp, _Up>>> = true;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COMMON_TYPE_H
