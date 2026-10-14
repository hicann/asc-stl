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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_BACKEND_H
#define CANN_ASC_STL_ASC_STD___CMATH_BACKEND_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#include <simt_api/math_functions.h>
#define CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(function, builtin, arguments) ::function arguments
#else
#define CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(function, builtin, arguments) builtin arguments
#endif

// Functions routed through FLOAT_MATH_CALL to libm/simt_api are not
// constant-evaluable on the device side, so the constexpr marker is
// host-only.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR
#else
#define CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR constexpr
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __cmath_backend {
inline constexpr bool simt_available = CANN_ASC_STL_DETAIL_SIMT_COMPILATION() != 0;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_BACKEND_H
