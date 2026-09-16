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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_MASK_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_MASK_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__floating_point/properties.h>
#include <asc/std/__floating_point/storage.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <__fp_format Fmt>
inline constexpr auto __fp_sign_mask_v =
    static_cast<__fp_storage_t<Fmt>>(__fp_storage_t<Fmt>(1) << (__fp_exp_nbits_v<Fmt> + __fp_mant_nbits_v<Fmt>));
template <class T>
inline constexpr auto __fp_sign_mask_of_v = __fp_sign_mask_v<__fp_format_of_v<T>>;

template <__fp_format Fmt>
inline constexpr auto __fp_exp_mask_v =
    static_cast<__fp_storage_t<Fmt>>(((__fp_storage_t<Fmt>(1) << __fp_exp_nbits_v<Fmt>)-1) << __fp_mant_nbits_v<Fmt>);
template <class T>
inline constexpr auto __fp_exp_mask_of_v = __fp_exp_mask_v<__fp_format_of_v<T>>;
template <__fp_format Fmt>
inline constexpr auto __fp_inv_exp_mask_v = static_cast<__fp_storage_t<Fmt>>(~__fp_exp_mask_v<Fmt>);
template <class T>
inline constexpr auto __fp_inv_exp_mask_of_v = __fp_inv_exp_mask_v<__fp_format_of_v<T>>;

template <__fp_format Fmt>
inline constexpr auto __fp_mant_mask_v =
    static_cast<__fp_storage_t<Fmt>>((__fp_storage_t<Fmt>(1) << __fp_mant_nbits_v<Fmt>)-1);
template <class T>
inline constexpr auto __fp_mant_mask_of_v = __fp_mant_mask_v<__fp_format_of_v<T>>;
template <__fp_format Fmt>
inline constexpr auto __fp_exp_mant_mask_v =
    static_cast<__fp_storage_t<Fmt>>(__fp_exp_mask_v<Fmt> | __fp_mant_mask_v<Fmt>);
template <class T>
inline constexpr auto __fp_exp_mant_mask_of_v = __fp_exp_mant_mask_v<__fp_format_of_v<T>>;

template <__fp_format Fmt>
inline constexpr auto __fp_explicit_bit_mask_v =
    static_cast<__fp_storage_t<Fmt>>(static_cast<__fp_storage_t<Fmt>>(!__fp_has_implicit_bit_v<Fmt>)
        << (__fp_mant_nbits_v<Fmt> - !__fp_has_implicit_bit_v<Fmt>));
template <class T>
inline constexpr auto __fp_explicit_bit_mask_of_v = __fp_explicit_bit_mask_v<__fp_format_of_v<T>>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_MASK_H
