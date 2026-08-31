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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_FORMAT_H
#define CANN_ASC_STL_STD_DETAIL_FWD_FORMAT_H

#include <asc/std/detail/__config>

#include <asc/std/__fwd/iterator.h>

#if __cpp_lib_format >= 201907L

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD

template <class, class>
struct formatter;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD

#endif  // __cpp_lib_format >= 201907L

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _CharT>
class basic_format_parse_context;

using format_parse_context = basic_format_parse_context<char>;
#if CANN_ASC_STL_DETAIL_HAS_WCHAR_T()
using wformat_parse_context = basic_format_parse_context<wchar_t>;
#endif  // CANN_ASC_STL_DETAIL_HAS_WCHAR_T()

template <class _CharT>
class __fmt_output_buffer;

template <class _Context>
class basic_format_arg;

template <class _OutIt, class _CharT>
class basic_format_context;

using format_context = basic_format_context<__back_insert_iterator<__fmt_output_buffer<char>>, char>;
#if CANN_ASC_STL_DETAIL_HAS_WCHAR_T()
using wformat_context = basic_format_context<__back_insert_iterator<__fmt_output_buffer<wchar_t>>, wchar_t>;
#endif  // CANN_ASC_STL_DETAIL_HAS_WCHAR_T()

template <class _Context>
class basic_format_args;

using format_args = basic_format_args<format_context>;
#if CANN_ASC_STL_DETAIL_HAS_WCHAR_T()
using wformat_args = basic_format_args<wformat_context>;
#endif  // CANN_ASC_STL_DETAIL_HAS_WCHAR_T()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_FORMAT_H
