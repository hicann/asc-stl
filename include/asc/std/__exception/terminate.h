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

#ifndef CANN_ASC_STL_STD_DETAIL_EXCEPTION_TERMINATE_H
#define CANN_ASC_STL_STD_DETAIL_EXCEPTION_TERMINATE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/cassert>

// 序言内联等价语义：基座 __config 未提供 hosted 门（参见
// __string/constexpr_c_functions.h 的同形内联定义，#ifndef 守卫以便未来集中定义胜出）。
#ifndef CANN_ASC_STL_DETAIL_HOSTED
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_HOSTED() 0
#else
#define CANN_ASC_STL_DETAIL_HOSTED() 1
#endif
#endif  // CANN_ASC_STL_DETAIL_HOSTED

#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <exception>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

// The Device branches follow the delivered fail-fast trap mechanism
// (`asc/std/__atomic/backend.h` and `asc/std/__variant/get.h`): the compiler
// builtin lowers to the same trap entrypoint that the CANN wrappers
// `__asc_simt_vf::__trap` and `AscendC::Trap` reach on this toolchain, keeps
// the debug-assertion adapter out of release semantics, and never returns.
// The Host branch delegates to the currently installed terminate handler.
// The freestanding Host compiler path (no C runtime, no terminate handler)
// falls back to the same fail-fast trap.
#if defined(__CCE__) || defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-noreturn"
#endif

CANN_ASC_STL_NORETURN CANN_ASC_STL_API void terminate() noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    __builtin_trap();
    for (;;) {
    }
#elif CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    ::std::terminate();
#else  // 独立环境的宿主编译器路径：无 C 运行时，直接 fail-fast
    __builtin_trap();
#endif
}

#if defined(__CCE__) || defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#pragma clang diagnostic pop
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_EXCEPTION_TERMINATE_H
