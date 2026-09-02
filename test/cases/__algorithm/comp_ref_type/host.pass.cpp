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

#include <asc/std/__algorithm/comp_ref_type.h>
#include <iostream>
#include <functional>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][comp_ref_type] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][comp_ref_type] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

static void check_part1()
{
    // Test __debug_less delegates correctly to underlying lambda comparator
    {
        auto less = [](int a, int b) { return a < b; };
        asc::std::__debug_less<decltype(less)> dbg_less(less);

        expect_true("__debug_less(1, 2)", dbg_less(1, 2));
        expect_false("__debug_less(2, 1)", dbg_less(2, 1));
        expect_false("__debug_less(1, 1)", dbg_less(1, 1));
    }

    // Test with std::less
    {
        std::less<int> comp;
        asc::std::__debug_less<std::less<int>> dbg_less(comp);

        expect_true("__debug_less(std::less)(3, 5)", dbg_less(3, 5));
        expect_false("__debug_less(std::less)(5, 3)", dbg_less(5, 3));
        expect_false("__debug_less(std::less)(4, 4)", dbg_less(4, 4));
    }

    // Test with negative values
    {
        auto less = [](int a, int b) { return a < b; };
        asc::std::__debug_less<decltype(less)> dbg_less(less);

        expect_true("__debug_less(-5, -3)", dbg_less(-5, -3));
        expect_false("__debug_less(-3, -5)", dbg_less(-3, -5));
        expect_true("__debug_less(-10, 0)", dbg_less(-10, 0));
    }

    // Test __comp_ref_type type alias resolves correctly
    {
        using Comp = std::less<int>;
        using RefType = asc::std::__comp_ref_type<Comp>;

#ifdef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
        expect_true("is_same<__comp_ref_type, __debug_less<Comp>> (debug mode)",
            std::is_same<RefType, asc::std::__debug_less<Comp>>::value);
#else
        expect_true("is_same<__comp_ref_type, Comp&> (non-debug mode)", std::is_same<RefType, Comp&>::value);
#endif
    }
}

static void check_part2()
{
    // Test __comp_ref_type used as a comparator
    {
        std::less<int> comp;
        asc::std::__comp_ref_type<std::less<int>> ref_comp = comp;

        expect_true("__comp_ref_type(1, 2)", ref_comp(1, 2));
        expect_false("__comp_ref_type(2, 1)", ref_comp(2, 1));
        expect_false("__comp_ref_type(3, 3)", ref_comp(3, 3));
    }

    // Test with greater comparator via __debug_less
    {
        auto greater = [](int a, int b) { return a > b; };
        asc::std::__debug_less<decltype(greater)> dbg_greater(greater);

        expect_true("__debug_less(greater)(5, 3)", dbg_greater(5, 3));
        expect_false("__debug_less(greater)(3, 5)", dbg_greater(3, 5));
        expect_false("__debug_less(greater)(4, 4)", dbg_greater(4, 4));
    }

    // Test __debug_less with float comparator
    {
        auto less = [](float a, float b) { return a < b; };
        asc::std::__debug_less<decltype(less)> dbg_less(less);

        expect_true("__debug_less(float)(1.5f, 2.5f)", dbg_less(1.5f, 2.5f));
        expect_false("__debug_less(float)(2.5f, 1.5f)", dbg_less(2.5f, 1.5f));
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
