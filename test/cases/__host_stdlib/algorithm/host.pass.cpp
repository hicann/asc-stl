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

#include <asc/std/__host_stdlib/algorithm>
#include <iostream>

static int g_failures = 0;

int main()
{
    // This header is a passthrough/umbrella wrapper with no callable symbols.
    // The only verifiable contract is that it compiles cleanly and the header
    // guard macro is defined.
    bool guard_defined = false;
#ifdef CANN_ASC_STL_STD_DETAIL_HOST_STDLIB_ALGORITHM
    guard_defined = true;
#endif
    std::cout << "[host][algorithm] Header guard CANN_ASC_STL_STD_DETAIL_HOST_STDLIB_ALGORITHM defined = "
              << (guard_defined ? "true" : "false") << " (expected true) " << (guard_defined ? "OK" : "FAIL")
              << std::endl;
    if (!guard_defined)
        ++g_failures;

    std::cout << "[host][algorithm] Header asc/std/__host_stdlib/algorithm included OK" << std::endl;

    return g_failures == 0 ? 0 : 1;
}
