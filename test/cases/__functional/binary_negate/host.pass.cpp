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

#include <asc/std/__functional/binary_negate.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][binary_negate] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct LessThan {
    typedef int first_argument_type;
    typedef int second_argument_type;
    bool operator()(const int& x, const int& y) const
    {
        return x < y;
    }
};

struct GreaterThan {
    typedef int first_argument_type;
    typedef int second_argument_type;
    bool operator()(const int& x, const int& y) const
    {
        return x > y;
    }
};

struct EqualTo {
    typedef int first_argument_type;
    typedef int second_argument_type;
    bool operator()(const int& x, const int& y) const
    {
        return x == y;
    }
};

struct OverloadChoice {
    typedef int first_argument_type;
    typedef int second_argument_type;
    bool operator()(const int&, const int&) const
    {
        return true;
    }
    bool operator()(const short&, const short&) const
    {
        return false;
    }
};

int main()
{
    // Test binary_negate direct construction with LessThan
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
    asc::std::binary_negate<LessThan> neg_less{LessThan{}};
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

    expect_eq("neg_less(3, 5)", neg_less(3, 5), false);  // LessThan(3,5)=true  -> negated=false
    expect_eq("neg_less(5, 3)", neg_less(5, 3), true);   // LessThan(5,3)=false -> negated=true
    expect_eq("neg_less(3, 3)", neg_less(3, 3), true);   // LessThan(3,3)=false -> negated=true

    // Test not2 helper with LessThan
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
    auto neg_less2 = asc::std::not2(LessThan());
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

    expect_eq("not2(LessThan)(3, 5)", neg_less2(3, 5), false);
    expect_eq("not2(LessThan)(5, 3)", neg_less2(5, 3), true);
    expect_eq("not2(LessThan)(3, 3)", neg_less2(3, 3), true);

    // Test not2 with GreaterThan
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
    auto neg_gt = asc::std::not2(GreaterThan());
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

    expect_eq("not2(GreaterThan)(3, 5)", neg_gt(3, 5), true);   // GreaterThan(3,5)=false -> negated=true
    expect_eq("not2(GreaterThan)(5, 3)", neg_gt(5, 3), false);  // GreaterThan(5,3)=true  -> negated=false
    expect_eq("not2(GreaterThan)(3, 3)", neg_gt(3, 3), true);   // GreaterThan(3,3)=false -> negated=true

    // Test not2 with EqualTo
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
    auto neg_eq = asc::std::not2(EqualTo());
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

    expect_eq("not2(EqualTo)(3, 3)", neg_eq(3, 3), false);  // EqualTo(3,3)=true  -> negated=false
    expect_eq("not2(EqualTo)(3, 5)", neg_eq(3, 5), true);   // EqualTo(3,5)=false -> negated=true
    expect_eq("not2(EqualTo)(5, 3)", neg_eq(5, 3), true);   // EqualTo(5,3)=false -> negated=true

    // The adaptor contract fixes its parameters to Predicate::argument_type.
    // A templated adaptor operator would incorrectly select the short overload.
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
    auto neg_overload = asc::std::not2(OverloadChoice());
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP
    expect_eq("not2(OverloadChoice)(short, short)", neg_overload(short{1}, short{2}), false);

    // Verify the returned type of not2 is binary_negate<LessThan>
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
    using RetType = decltype(asc::std::not2(LessThan()));
    bool is_binary_negate = std::is_same<RetType, asc::std::binary_negate<LessThan>>::value;
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP
    std::cout << "[host][binary_negate] not2 returns binary_negate<LessThan> = "
              << (is_binary_negate ? "true" : "false") << " (expected true) " << (is_binary_negate ? "OK" : "FAIL")
              << std::endl;
    if (!is_binary_negate)
        ++g_failures;

    return g_failures == 0 ? 0 : 1;
}
