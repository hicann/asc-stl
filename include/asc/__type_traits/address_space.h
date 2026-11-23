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

#ifndef CANN_ASC_STL_ASC___TYPE_TRAITS_ADDRESS_SPACE_H
#define CANN_ASC_STL_ASC___TYPE_TRAITS_ADDRESS_SPACE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_reference.h>

namespace asc {
namespace detail {

// Internal identity shared with memory's space-value mapping. Only the direct
// pointee is examined; this does not classify a pointer's runtime value.
enum class native_memory_space { unqualified, global, unified_buffer };

template <class T>
struct native_pointer_space : asc::std::integral_constant<native_memory_space, native_memory_space::unqualified> {};

// The mixed frontend retains address spaces in both its control code and SIMT
// VFs. In pure SIMT, these spellings are declaration attributes, not type
// qualifiers; defining these specializations there would redefine T* twice.
#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION() && defined(__NPU_ARCH__) && __NPU_ARCH__ == 3510 && \
    defined(__BISHENG_CCEC__) && __clang_major__ == 15
template <class T>
struct native_pointer_space<__gm__ T*> : asc::std::integral_constant<native_memory_space, native_memory_space::global> {
};

template <class T>
struct native_pointer_space<__ubuf__ T*>
    : asc::std::integral_constant<native_memory_space, native_memory_space::unified_buffer> {};
#endif

template <class T>
using normalized_native_pointer_space = native_pointer_space<asc::std::remove_cv_t<asc::std::remove_reference_t<T>>>;

}  // namespace detail
}  // namespace asc

#endif  // CANN_ASC_STL_ASC___TYPE_TRAITS_ADDRESS_SPACE_H
