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

#include <asc/std/__fwd/format.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void check(const char* expr, bool got, bool expected)
{
    const bool ok = (got == expected);
    std::cout << "[host][fwd.format] " << expr << ": " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_header_guard()
{
    check("CANN_ASC_STL_STD_DETAIL_FWD_FORMAT_H is defined",
#ifdef CANN_ASC_STL_STD_DETAIL_FWD_FORMAT_H
        true,
#else
        false,
#endif
        true);
}

static void test_parse_context_aliases()
{
    check("format_parse_context aliases basic_format_parse_context<char>",
        (std::is_same_v<asc::std::format_parse_context, asc::std::basic_format_parse_context<char>>), true);
#if CANN_ASC_STL_DETAIL_HAS_WCHAR_T()
    check("wformat_parse_context aliases basic_format_parse_context<wchar_t>",
        (std::is_same_v<asc::std::wformat_parse_context, asc::std::basic_format_parse_context<wchar_t>>), true);
#endif
}

static void test_format_args_aliases()
{
    check("format_args aliases basic_format_args<format_context>",
        (std::is_same_v<asc::std::format_args, asc::std::basic_format_args<asc::std::format_context>>), true);
#if CANN_ASC_STL_DETAIL_HAS_WCHAR_T()
    check("wformat_args aliases basic_format_args<wformat_context>",
        (std::is_same_v<asc::std::wformat_args, asc::std::basic_format_args<asc::std::wformat_context>>), true);
#endif
}

static void test_incomplete_types_usable()
{
    // The forward-declared formatting components must be usable as incomplete
    // types in declaration-only contexts.
    using asc::std::basic_format_arg;
    using asc::std::basic_format_context;
    using asc::std::basic_format_parse_context;

    const basic_format_arg<asc::std::format_context>* null_arg = nullptr;
    const basic_format_context<void*, char>* null_ctx = nullptr;
    const basic_format_parse_context<char>* null_parse = nullptr;
    check("pointers to incomplete format components are null",
        null_arg == nullptr && null_ctx == nullptr && null_parse == nullptr, true);
}

int main()
{
    test_header_guard();
    test_parse_context_aliases();
    test_format_args_aliases();
    test_incomplete_types_usable();

    return g_failures == 0 ? 0 : 1;
}
