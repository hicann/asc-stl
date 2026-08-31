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

#include <asc/std/__type_traits/remove_pointer.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

#define EXPECT_SAME(expr, T1, T2)                                                                                      \
    do {                                                                                                               \
        bool ok = std::is_same<T1, T2>::value;                                                                         \
        std::cout << "[host][remove_pointer] " << expr << " => " << (ok ? "same" : "DIFFERENT") << " (expected same) " \
                  << (ok ? "OK" : "FAIL") << std::endl;                                                                \
        if (!ok)                                                                                                       \
            ++g_failures;                                                                                              \
    } while (0)

int main()
{
    // Basic: pointer to non-pointer
    EXPECT_SAME("remove_pointer<int*>::type", asc::std::remove_pointer<int*>::type, int);
    EXPECT_SAME("remove_pointer<int* const>::type", asc::std::remove_pointer<int* const>::type, int);
    EXPECT_SAME("remove_pointer<int* volatile>::type", asc::std::remove_pointer<int* volatile>::type, int);
    EXPECT_SAME("remove_pointer<int* const volatile>::type", asc::std::remove_pointer<int* const volatile>::type, int);

    // Non-pointer type: unchanged
    EXPECT_SAME("remove_pointer<int>::type", asc::std::remove_pointer<int>::type, int);
    EXPECT_SAME("remove_pointer<char>::type", asc::std::remove_pointer<char>::type, char);

    // _t alias
    EXPECT_SAME("remove_pointer_t<int*>", asc::std::remove_pointer_t<int*>, int);
    EXPECT_SAME("remove_pointer_t<int* const>", asc::std::remove_pointer_t<int* const>, int);
    EXPECT_SAME("remove_pointer_t<int* volatile>", asc::std::remove_pointer_t<int* volatile>, int);
    EXPECT_SAME("remove_pointer_t<int* const volatile>", asc::std::remove_pointer_t<int* const volatile>, int);
    EXPECT_SAME("remove_pointer_t<int>", asc::std::remove_pointer_t<int>, int);

    // Multi-level pointer: only one level removed
    EXPECT_SAME("remove_pointer<int**>::type", asc::std::remove_pointer<int**>::type, int*);
    EXPECT_SAME("remove_pointer<int***>::type", asc::std::remove_pointer<int***>::type, int**);
    EXPECT_SAME("remove_pointer_t<int**>", asc::std::remove_pointer_t<int**>, int*);

    // Pointer to const
    EXPECT_SAME("remove_pointer<const int*>::type", asc::std::remove_pointer<const int*>::type, const int);
    EXPECT_SAME("remove_pointer_t<const int*>", asc::std::remove_pointer_t<const int*>, const int);

    // Pointer to function
    using FuncPtr = int (*)(double);
    EXPECT_SAME("remove_pointer<FuncPtr>::type", asc::std::remove_pointer<FuncPtr>::type,
        int(double));  // NOLINT(readability/casting)

    // Void pointer
    EXPECT_SAME("remove_pointer<void*>::type", asc::std::remove_pointer<void*>::type, void);
    EXPECT_SAME("remove_pointer_t<void*>", asc::std::remove_pointer_t<void*>, void);

    // Reference is not a pointer
    EXPECT_SAME("remove_pointer<int&>::type", asc::std::remove_pointer<int&>::type, int&);

    // const volatile pointer combos
    EXPECT_SAME("remove_pointer<const int* const>::type", asc::std::remove_pointer<const int* const>::type, const int);
    EXPECT_SAME("remove_pointer_t<const int* volatile>", asc::std::remove_pointer_t<const int* volatile>, const int);

    return g_failures == 0 ? 0 : 1;
}
