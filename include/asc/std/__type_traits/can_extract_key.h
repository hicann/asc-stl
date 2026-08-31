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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_CAN_EXTRACT_KEY_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_CAN_EXTRACT_KEY_H

#include <asc/std/detail/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__fwd/pair.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_const_ref.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// These tags select the key-extraction path used by __tree and __hash_table.
struct __extract_key_fail_tag {};
struct __extract_key_self_tag {};
struct __extract_key_first_tag {};

template <class _ValTy, class _Key, class _RawValTy = __remove_const_ref_t<_ValTy>>
struct __can_extract_key : conditional_t<is_same_v<_RawValTy, _Key>, __extract_key_self_tag, __extract_key_fail_tag> {};

template <class _Pair, class _Key, class _First, class _Second>
struct __can_extract_key<_Pair, _Key, pair<_First, _Second>>  // NOLINT(build/include_what_you_use)
    : conditional_t<is_same_v<remove_const_t<_First>, _Key>, __extract_key_first_tag, __extract_key_fail_tag> {};

template <class _ValTy, class _Key, class _ContainerValueTy, class _RawValTy = __remove_const_ref_t<_ValTy>>
struct __can_extract_map_key : integral_constant<bool, is_same_v<_RawValTy, _Key>> {};

template <class _ValTy, class _Key, class _RawValTy>
struct __can_extract_map_key<_ValTy, _Key, _Key, _RawValTy> : false_type {};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_CAN_EXTRACT_KEY_H
