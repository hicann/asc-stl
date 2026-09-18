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

#ifndef CANN_ASC_STL_DETAIL_FWD_COMPLEX_H
#define CANN_ASC_STL_DETAIL_FWD_COMPLEX_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <class _Tp>
class complex;

// __is_asc_complex_v

template <class _Tp>
inline constexpr bool __is_asc_complex_v = false;
template <class _Tp>
inline constexpr bool __is_asc_complex_v<const _Tp> = __is_asc_complex_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_asc_complex_v<volatile _Tp> = __is_asc_complex_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_asc_complex_v<const volatile _Tp> = __is_asc_complex_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_asc_complex_v<complex<_Tp>> = true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_FWD_COMPLEX_H
