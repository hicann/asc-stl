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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_STRING_H
#define CANN_ASC_STL_STD_DETAIL_FWD_STRING_H

#include <asc/std/detail/__config>

#include <asc/std/__fwd/allocator.h>
#include <asc/std/__fwd/char_traits.h>

// std:: forward declarations

#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD

// libstdc++ puts basic_string to inline cxx11 namespace
#if CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX) && _GLIBCXX_USE_CXX11_ABI
inline _GLIBCXX_BEGIN_NAMESPACE_CXX11
#endif  // CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX) && _GLIBCXX_USE_CXX11_ABI

    template <class _CharT, class _Traits, class _Alloc>
    class basic_string;

#if CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX) && _GLIBCXX_USE_CXX11_ABI
_GLIBCXX_END_NAMESPACE_CXX11
#endif  // CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX) && _GLIBCXX_USE_CXX11_ABI

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

// asc::std:: forward declarations

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
inline constexpr bool __is_std_basic_string_v = false;
#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
template <class _CharT, class _Traits, class _Alloc>
using _Std_basic_string_t = ::std::basic_string<_CharT, _Traits, _Alloc>;  // NOLINT(build/include_what_you_use)

template <class _CharT, class _Traits, class _Alloc>
inline constexpr bool __is_std_basic_string_v<_Std_basic_string_t<_CharT, _Traits, _Alloc>> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_STRING_H
