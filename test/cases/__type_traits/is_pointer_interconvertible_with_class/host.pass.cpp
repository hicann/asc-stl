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

#include <asc/std/__type_traits/is_pointer_interconvertible_with_class.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_pointer_interconvertible_with_class] " << expr << " = " << (got ? "true" : "false")
              << " (expected " << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Standard layout struct: first member is pointer-interconvertible with the class
struct StandardLayout {
    int a;
    int b;
};

// Single member struct: the sole member is pointer-interconvertible
struct SingleMember {
    double x;
};

// Struct with a char member first, then a larger type
struct MixedLayout {
    char c;
    double d;
};

int main()
{
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS)
    // First member of a standard layout class is pointer-interconvertible
    expect_eq("is_pointer_interconvertible_with_class(&StandardLayout::a)",
        asc::std::is_pointer_interconvertible_with_class(&StandardLayout::a), true);
    // Second member is NOT pointer-interconvertible (non-zero offset)
    expect_eq("is_pointer_interconvertible_with_class(&StandardLayout::b)",
        asc::std::is_pointer_interconvertible_with_class(&StandardLayout::b), false);
    // Single member of a class is pointer-interconvertible
    expect_eq("is_pointer_interconvertible_with_class(&SingleMember::x)",
        asc::std::is_pointer_interconvertible_with_class(&SingleMember::x), true);
    // First member (char) of MixedLayout is pointer-interconvertible
    expect_eq("is_pointer_interconvertible_with_class(&MixedLayout::c)",
        asc::std::is_pointer_interconvertible_with_class(&MixedLayout::c), true);
    // Second member (double) of MixedLayout is NOT pointer-interconvertible
    expect_eq("is_pointer_interconvertible_with_class(&MixedLayout::d)",
        asc::std::is_pointer_interconvertible_with_class(&MixedLayout::d), false);
#else
    std::cout << "[host][is_pointer_interconvertible_with_class] builtin not available, skipping tests" << std::endl;
#endif
    return g_failures == 0 ? 0 : 1;
}
