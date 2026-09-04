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

#include <asc/std/expected>
#include <iostream>

using E = asc::std::expected<int, int>;
using VE = asc::std::expected<void, int>;

static int g_failures = 0;

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][expected] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_bool(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][expected] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_part1()
{
    // === expected<int,int>: construction ===

    // default construction
    {
        E e{};
        expect_bool("default has_value", e.has_value(), true);
        expect_eq("default value", *e, 0);
    }

    // in_place construction
    {
        E e{asc::std::in_place, 42};
        expect_bool("in_place has_value", e.has_value(), true);
        expect_eq("in_place value", *e, 42);
    }

    // unexpect construction
    {
        E e{asc::std::unexpect, 42};
        expect_bool("unexpect has_value", e.has_value(), false);
        expect_eq("unexpect error", e.error(), 42);
    }

    // unexpect zero initialization
    {
        E e{asc::std::unexpect};
        expect_bool("unexpect default has_value", e.has_value(), false);
        expect_eq("unexpect default error", e.error(), 0);
    }

    // value construction
    {
        E e{42};
        expect_bool("value ctor has_value", e.has_value(), true);
        expect_eq("value ctor value", *e, 42);
    }
}

static void check_part2()
{
    // value() method
    {
        E e{42};
        expect_eq("value()", e.value(), 42);
    }

    // operator bool
    {
        E ev{42};
        E ee{asc::std::unexpect, 7};
        expect_bool("operator bool (value)", static_cast<bool>(ev), true);
        expect_bool("operator bool (error)", static_cast<bool>(ee), false);
    }

    // === expected<int,int>: copy/move ===

    // copy construction
    {
        E input{42};
        E dest{input};
        expect_bool("copy has_value", dest.has_value(), true);
        expect_eq("copy value", *dest, 42);
    }

    // move construction
    {
        E input{42};
        E dest{asc::std::move(input)};
        expect_bool("move has_value", dest.has_value(), true);
        expect_eq("move value", *dest, 42);
    }

    // === expected<int,int>: assignment ===

    // assignment: value to value
    {
        E input{42};
        E dest{1337};
        dest = input;
        expect_eq("assign val->val", *dest, 42);
    }
}

static void check_part3()
{
    // assignment: value to empty
    {
        E input{42};
        E dest{};
        dest = input;
        expect_eq("assign val->empty", *dest, 42);
    }

    // assignment: empty to value
    {
        E input{};
        E dest{1337};
        dest = input;
        expect_eq("assign empty->val", *dest, 0);
    }

    // assignment: error to value
    {
        E input{asc::std::unexpect, 42};
        E dest{1337};
        dest = input;
        expect_bool("assign err->val has_value", dest.has_value(), false);
        expect_eq("assign err->val error", dest.error(), 42);
    }

    // assignment: value to error
    {
        E input{42};
        E dest{asc::std::unexpect, 1337};
        dest = input;
        expect_bool("assign val->err has_value", dest.has_value(), true);
        expect_eq("assign val->err value", *dest, 42);
    }
}

static void check_part4()
{
    // assignment: error to error
    {
        E input{asc::std::unexpect, 42};
        E dest{asc::std::unexpect, 1337};
        dest = input;
        expect_eq("assign err->err error", dest.error(), 42);
    }

    // assignment: direct value to error
    {
        E e{asc::std::unexpect, 7};
        e = 42;
        expect_bool("assign value direct has_value", e.has_value(), true);
        expect_eq("assign value direct", *e, 42);
    }

    // === expected<int,int>: comparison ===

    // comparison with expected (different values)
    {
        E lhs{42};
        E rhs{1337};
        expect_bool("lhs==rhs (diff val)", lhs == rhs, false);
        expect_bool("lhs!=rhs (diff val)", lhs != rhs, true);
    }

    // comparison with expected (same values)
    {
        E lhs{42};
        E rhs{42};
        expect_bool("lhs==rhs (same val)", lhs == rhs, true);
        expect_bool("lhs!=rhs (same val)", lhs != rhs, false);
    }

    // comparison with expected (different errors)
    {
        E lhs{asc::std::unexpect, 42};
        E rhs{asc::std::unexpect, 1337};
        expect_bool("lhs==rhs (diff err)", lhs == rhs, false);
        expect_bool("lhs!=rhs (diff err)", lhs != rhs, true);
    }
}

static void check_part5()
{
    // comparison with value
    {
        E e{42};
        expect_bool("e==42", e == 42, true);
        expect_bool("42==e", 42 == e, true);
        expect_bool("e!=1337", e != 1337, true);
        expect_bool("1337!=e", 1337 != e, true);
    }

    // comparison with unexpected
    {
        E e{asc::std::unexpect, 42};
        expect_bool("e==unexpected(42)", e == asc::std::unexpected<int>{42}, true);
        expect_bool("unexpected(42)==e", asc::std::unexpected<int>{42} == e, true);
        expect_bool("e!=unexpected(1337)", e != asc::std::unexpected<int>{1337}, true);
        expect_bool("unexpected(1337)!=e", asc::std::unexpected<int>{1337} != e, true);
    }

    // === expected<int,int>: value_or ===

    {
        E e{42};
        expect_eq("value_or(has value)", e.value_or(99), 42);
    }
    {
        E e{asc::std::unexpect, 7};
        expect_eq("value_or(has error)", e.value_or(99), 99);
    }

    // === expected<int,int>: swap ===

    // member swap (both value)
    {
        E lhs{42};
        E rhs{1337};
        lhs.swap(rhs);
        expect_eq("member swap lhs", *lhs, 1337);
        expect_eq("member swap rhs", *rhs, 42);
    }
}

static void check_part6()
{
    // free swap (both value)
    {
        E lhs{42};
        E rhs{1337};
        swap(lhs, rhs);
        expect_eq("free swap lhs", *lhs, 1337);
        expect_eq("free swap rhs", *rhs, 42);
    }

    // swap cross error (value <-> error)
    {
        E lhs{42};
        E rhs{asc::std::unexpect, 1337};
        lhs.swap(rhs);
        expect_bool("cross swap lhs has_value", lhs.has_value(), false);
        expect_eq("cross swap lhs error", lhs.error(), 1337);
        expect_bool("cross swap rhs has_value", rhs.has_value(), true);
        expect_eq("cross swap rhs value", *rhs, 42);
    }

    // === unexpected<int> tests ===

    {
        asc::std::unexpected<int> u{42};
        expect_eq("unexpected error()", u.error(), 42);
    }
    {
        asc::std::unexpected<int> u1{42};
        asc::std::unexpected<int> u2{42};
        expect_bool("unexpected == (same)", u1 == u2, true);
    }
    {
        asc::std::unexpected<int> u1{42};
        asc::std::unexpected<int> u2{1337};
        expect_bool("unexpected == (diff)", u1 == u2, false);
    }
}

static void check_part7()
{
    // === expected<void,int> tests ===

    // default construction
    {
        VE e{};
        expect_bool("void default has_value", e.has_value(), true);
    }

    // in_place construction
    {
        VE e{asc::std::in_place};
        expect_bool("void in_place has_value", e.has_value(), true);
    }

    // unexpect construction
    {
        VE e{asc::std::unexpect, 42};
        expect_bool("void unexpect has_value", e.has_value(), false);
        expect_eq("void unexpect error", e.error(), 42);
    }

    // unexpect default
    {
        VE e{asc::std::unexpect};
        expect_bool("void unexpect default has_value", e.has_value(), false);
        expect_eq("void unexpect default error", e.error(), 0);
    }

    // copy construction
    {
        VE input{asc::std::in_place};
        VE dest{input};
        expect_bool("void copy has_value", dest.has_value(), true);
    }

    // move construction
    {
        VE input{asc::std::in_place};
        VE dest{asc::std::move(input)};
        expect_bool("void move has_value", dest.has_value(), true);
    }
}

static void check_part8()
{
    // assignment: value to value
    {
        VE input{asc::std::in_place};
        VE dest{asc::std::in_place};
        dest = input;
        expect_bool("void assign val->val has_value", dest.has_value(), true);
    }

    // assignment: value to empty
    {
        VE input{asc::std::in_place};
        VE dest{};
        dest = input;
        expect_bool("void assign val->empty has_value", dest.has_value(), true);
    }

    // assignment: empty to value
    {
        VE input{};
        VE dest{asc::std::in_place};
        dest = input;
        expect_bool("void assign empty->val has_value", dest.has_value(), true);
    }

    // assignment: error to value
    {
        VE input{asc::std::unexpect, 42};
        VE dest{asc::std::in_place};
        dest = input;
        expect_bool("void assign err->val has_value", dest.has_value(), false);
        expect_eq("void assign err->val error", dest.error(), 42);
    }
}

static void check_part9()
{
    // assignment: value to error
    {
        VE input{asc::std::in_place};
        VE dest{asc::std::unexpect, 1337};
        dest = input;
        expect_bool("void assign val->err has_value", dest.has_value(), true);
    }

    // assignment: error to error
    {
        VE input{asc::std::unexpect, 42};
        VE dest{asc::std::unexpect, 1337};
        dest = input;
        expect_eq("void assign err->err error", dest.error(), 42);
    }

    // comparison: both value
    {
        VE lhs{asc::std::in_place};
        VE rhs{asc::std::in_place};
        expect_bool("void lhs==rhs (both val)", lhs == rhs, true);
        expect_bool("void lhs!=rhs (both val)", lhs != rhs, false);
    }

    // comparison: both error (different)
    {
        VE lhs{asc::std::unexpect, 42};
        VE rhs{asc::std::unexpect, 1337};
        expect_bool("void lhs==rhs (diff err)", lhs == rhs, false);
        expect_bool("void lhs!=rhs (diff err)", lhs != rhs, true);
    }

    // comparison with unexpected
    {
        VE e{asc::std::unexpect, 42};
        expect_bool("void e==unexpected(42)", e == asc::std::unexpected<int>{42}, true);
        expect_bool("void unexpected(42)==e", asc::std::unexpected<int>{42} == e, true);
        expect_bool("void e!=unexpected(1337)", e != asc::std::unexpected<int>{1337}, true);
    }
}

static void check_part10()
{
    // member swap (both error)
    {
        VE lhs{asc::std::unexpect, 42};
        VE rhs{asc::std::unexpect, 1337};
        lhs.swap(rhs);
        expect_eq("void member swap lhs error", lhs.error(), 1337);
        expect_eq("void member swap rhs error", rhs.error(), 42);
    }

    // free swap (both error)
    {
        VE lhs{asc::std::unexpect, 42};
        VE rhs{asc::std::unexpect, 1337};
        swap(lhs, rhs);  // NOLINT(build/include_what_you_use)
        expect_eq("void free swap lhs error", lhs.error(), 1337);
        expect_eq("void free swap rhs error", rhs.error(), 42);
    }

    // swap cross error (value <-> error)
    {
        VE lhs{asc::std::in_place};
        VE rhs{asc::std::unexpect, 1337};
        lhs.swap(rhs);
        expect_bool("void cross swap lhs has_value", lhs.has_value(), false);
        expect_eq("void cross swap lhs error", lhs.error(), 1337);
        expect_bool("void cross swap rhs has_value", rhs.has_value(), true);
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();
    check_part4();
    check_part5();
    check_part6();
    check_part7();
    check_part8();
    check_part9();
    check_part10();

    return g_failures == 0 ? 0 : 1;
}
