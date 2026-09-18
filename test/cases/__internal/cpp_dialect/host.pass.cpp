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

#define ASC_IGNORE_DEPRECATED_CPP_DIALECT
#include <asc/std/__internal/cpp_dialect.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][cpp_dialect] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
#if defined(ASC_STL_COMP_DEPR_IMPL)
    expect_true("defined(ASC_STL_COMP_DEPR_IMPL)", true);
#else
    expect_true("defined(ASC_STL_COMP_DEPR_IMPL)", false);
#endif

#if defined(ASC_STL_DIALECT_DEPRECATION)
    expect_true("defined(ASC_STL_DIALECT_DEPRECATION)", true);
#else
    expect_true("defined(ASC_STL_DIALECT_DEPRECATION)", false);
#endif

    expect_true("CANN_ASC_STL_DETAIL_STD_VER >= 2017", CANN_ASC_STL_DETAIL_STD_VER >= 2017);

#if defined(ASC_IGNORE_DEPRECATED_CPP_DIALECT)
    expect_true("ASC_IGNORE_DEPRECATED_CPP_DIALECT remains defined", true);
#else
    expect_true("ASC_IGNORE_DEPRECATED_CPP_DIALECT remains defined", false);
#endif

#if defined(ASC_STL_IGNORE_DEPRECATED_CPP_DIALECT)
    expect_true("ASC dialect alias defines ASC_STL_IGNORE_DEPRECATED_CPP_DIALECT", true);
#else
    expect_true("ASC dialect alias defines ASC_STL_IGNORE_DEPRECATED_CPP_DIALECT", false);
#endif

    return g_failures == 0 ? 0 : 1;
}
