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

#include <asc/std/__type_traits/is_complete.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_complete] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Complete user-defined types
struct CompleteType {
    int x;
};
class CompleteClass {
public:
    int y;
};
enum CompleteEnum { EA, EB, EC };

// Incomplete type: forward-declared, never defined in this TU
struct IncompleteType;

int main()
{
    // --- Fundamental complete types ---
    expect_eq("__is_complete_v<int>", asc::std::__is_complete_v<int>, true);
    expect_eq("__is_complete_v<char>", asc::std::__is_complete_v<char>, true);
    expect_eq("__is_complete_v<double>", asc::std::__is_complete_v<double>, true);
    expect_eq("__is_complete_v<bool>", asc::std::__is_complete_v<bool>, true);
    expect_eq("__is_complete_v<const int>", asc::std::__is_complete_v<const int>, true);

    // --- User-defined complete types ---
    expect_eq("__is_complete_v<CompleteType>", asc::std::__is_complete_v<CompleteType>, true);
    expect_eq("__is_complete_v<CompleteClass>", asc::std::__is_complete_v<CompleteClass>, true);
    expect_eq("__is_complete_v<CompleteEnum>", asc::std::__is_complete_v<CompleteEnum>, true);

    // --- Pointer types are always complete (even to incomplete pointee) ---
    expect_eq("__is_complete_v<int*>", asc::std::__is_complete_v<int*>, true);
    expect_eq("__is_complete_v<IncompleteType*>", asc::std::__is_complete_v<IncompleteType*>, true);

    // --- Bounded array of complete element type ---
    expect_eq("__is_complete_v<int[10]>", asc::std::__is_complete_v<int[10]>, true);

    // --- Incomplete types ---
    expect_eq("__is_complete_v<void>", asc::std::__is_complete_v<void>, false);
    expect_eq("__is_complete_v<IncompleteType>", asc::std::__is_complete_v<IncompleteType>, false);
    expect_eq("__is_complete_v<int[]>", asc::std::__is_complete_v<int[]>, false);

    return g_failures == 0 ? 0 : 1;
}
