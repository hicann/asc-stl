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

#include <asc/__utility/immovable.h>
#include <iostream>
#include <type_traits>
#include <utility>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][immovable] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][immovable] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

// A class that inherits from asc::__immovable to become immovable
struct DerivedImmovable : asc::__immovable {
    int value;
    explicit DerivedImmovable(int v) : value(v)
    {}
};

// A class using the CANN_ASC_STL_DETAIL_ACCL_IMMOVABLE macro directly
struct MacroImmovable {
    MacroImmovable() = default;
    CANN_ASC_STL_DETAIL_ACCL_IMMOVABLE(MacroImmovable);
    int data = 0;
};

// A normal movable type for contrast
struct MovableType {
    MovableType() = default;
    MovableType(MovableType&&) noexcept = default;
    int value = 0;
};

static void test_asc_immovable_default_constructible()
{
    // Test 1: asc::__immovable is default constructible
    {
        asc::__immovable obj;
        (void)obj;
        std::cout << "[host][immovable] asc::__immovable default-constructed OK" << std::endl;
    }
}

static void test_asc_immovable_copy_constructible()
{
    // Test 2: asc::__immovable is not copy constructible
    // (user-declared move ctor suppresses implicit copy ctor)
    expect_false("std::is_copy_constructible_v<asc::__immovable>", std::is_copy_constructible<asc::__immovable>::value);
}

static void test_asc_immovable_move_constructibility()
{
    // Test 3: asc::__immovable move constructibility is compiler-dependent
    // On GCC: move ctor is declared but not defined (linker error if ODR-used)
    // On non-GCC: move ctor is deleted
#if CANN_ASC_STL_DETAIL_COMPILER(GCC)
    expect_true("std::is_move_constructible_v<asc::__immovable> (GCC: declared-not-defined)",
        std::is_move_constructible<asc::__immovable>::value);
#else
    expect_false("std::is_move_constructible_v<asc::__immovable> (non-GCC: deleted)",
        std::is_move_constructible<asc::__immovable>::value);
#endif
}

static void test_inheriting_asc_immovable_makes()
{
    // Test 4: Inheriting from asc::__immovable makes a class immovable
    expect_false("std::is_copy_constructible_v<DerivedImmovable>", std::is_copy_constructible<DerivedImmovable>::value);

#if CANN_ASC_STL_DETAIL_COMPILER(GCC)
    expect_true("std::is_move_constructible_v<DerivedImmovable> (GCC: declared-not-defined)",
        std::is_move_constructible<DerivedImmovable>::value);
#else
    expect_false("std::is_move_constructible_v<DerivedImmovable> (non-GCC: deleted)",
        std::is_move_constructible<DerivedImmovable>::value);
#endif

    {
        DerivedImmovable d(42);
        expect_true("DerivedImmovable(42).value == 42", d.value == 42);
    }
}

static void test_accl_immovable_custom_class()
{
    // Test 5: CANN_ASC_STL_DETAIL_ACCL_IMMOVABLE macro on a custom class
    expect_false("std::is_copy_constructible_v<MacroImmovable>", std::is_copy_constructible<MacroImmovable>::value);

#if CANN_ASC_STL_DETAIL_COMPILER(GCC)
    expect_true("std::is_move_constructible_v<MacroImmovable> (GCC: declared-not-defined)",
        std::is_move_constructible<MacroImmovable>::value);
#else
    expect_false("std::is_move_constructible_v<MacroImmovable> (non-GCC: deleted)",
        std::is_move_constructible<MacroImmovable>::value);
#endif

    {
        MacroImmovable mc;
        mc.data = 99;
        expect_true("MacroImmovable.data == 99 after set", mc.data == 99);
    }
}

static void test_contrast_movable_type()
{
    // Test 6: Contrast with a movable type
    expect_true("std::is_move_constructible_v<MovableType>", std::is_move_constructible<MovableType>::value);

    {
        MovableType a;
        a.value = 10;
        MovableType b(std::move(a));
        expect_true("MovableType moved: b.value == 10", b.value == 10);
    }
}

int main()
{
    test_asc_immovable_default_constructible();
    test_asc_immovable_copy_constructible();
    test_asc_immovable_move_constructibility();
    test_inheriting_asc_immovable_makes();
    test_accl_immovable_custom_class();
    test_contrast_movable_type();

    return g_failures == 0 ? 0 : 1;
}
