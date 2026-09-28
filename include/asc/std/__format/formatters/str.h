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

#ifndef CANN_ASC_STL_ASC_STD___FORMAT_FORMATTERS_STR_H
#define CANN_ASC_STL_ASC_STD___FORMAT_FORMATTERS_STR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__string/char_traits.h>
#include <asc/std/__type_traits/is_null_pointer.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__utility/to_underlying.h>
#include <asc/std/string_view>

#if CANN_ASC_STL_DETAIL_HAS_CXX20()

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __format_detail {
struct string_formatter_tag {};
}  // namespace __format_detail

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_DETAIL_HAS_CXX20()

#endif  // CANN_ASC_STL_ASC_STD___FORMAT_FORMATTERS_STR_H
