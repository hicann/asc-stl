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

#include <asc/std/__fwd/fp.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][fp] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Verify __fp_format is an enum type in asc::std namespace
    expect_true("std::is_enum<asc::std::__fp_format>::value", std::is_enum<asc::std::__fp_format>::value);

    // Verify the forward-declared enum is usable as an incomplete type (pointer declaration)
    asc::std::__fp_format* fmt_ptr = nullptr;
    expect_true("__fp_format pointer is null", fmt_ptr == nullptr);

    // Verify __asc_fp template is declared in asc::std by naming a specialization in a non-instantiating context.
    // __fp_format has no enumerators defined in this forward-declaration header,
    // so use a zero-valued converted constant expression as the template argument.
    using fp_template_alias = asc::std::__asc_fp<static_cast<asc::std::__fp_format>(0)>;
    (void)sizeof(fp_template_alias*);  // pointer to incomplete specialization -- compiles if template is declared
    expect_true("__asc_fp template is declared", true);

    return g_failures == 0 ? 0 : 1;
}
