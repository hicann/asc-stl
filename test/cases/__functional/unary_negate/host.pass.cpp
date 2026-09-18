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

#define CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_NEGATORS
#include <asc/std/__functional/unary_negate.h>
#include <iostream>

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][unary_negate] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct IsEven {
    using argument_type = int;
    bool operator()(int x) const
    {
        return x % 2 == 0;
    }
};

struct IsPositive {
    using argument_type = int;
    bool operator()(int x) const
    {
        return x > 0;
    }
};

int main()
{
    // Test unary_negate with IsEven: negates "is even" -> "is odd"
    {
        asc::std::unary_negate<IsEven> neg(IsEven{});
        expect_eq("unary_negate<IsEven>(4)", neg(4), false);
        expect_eq("unary_negate<IsEven>(3)", neg(3), true);
        expect_eq("unary_negate<IsEven>(0)", neg(0), false);
        expect_eq("unary_negate<IsEven>(-2)", neg(-2), false);
        expect_eq("unary_negate<IsEven>(-1)", neg(-1), true);
    }

    // Test not1 helper with IsEven
    {
        auto neg = asc::std::not1(IsEven{});
        expect_eq("not1(IsEven)(4)", neg(4), false);
        expect_eq("not1(IsEven)(3)", neg(3), true);
        expect_eq("not1(IsEven)(0)", neg(0), false);
        expect_eq("not1(IsEven)(-1)", neg(-1), true);
    }

    // Test unary_negate with IsPositive: negates "is positive" -> "is not positive"
    {
        asc::std::unary_negate<IsPositive> neg(IsPositive{});
        expect_eq("unary_negate<IsPositive>(5)", neg(5), false);
        expect_eq("unary_negate<IsPositive>(-3)", neg(-3), true);
        expect_eq("unary_negate<IsPositive>(0)", neg(0), true);
    }

    // Test not1 helper with IsPositive
    {
        auto neg = asc::std::not1(IsPositive{});
        expect_eq("not1(IsPositive)(5)", neg(5), false);
        expect_eq("not1(IsPositive)(-3)", neg(-3), true);
        expect_eq("not1(IsPositive)(0)", neg(0), true);
    }

    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

    return g_failures == 0 ? 0 : 1;
}
