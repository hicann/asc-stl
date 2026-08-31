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

#include <asc/std/__type_traits/disjunction.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][disjunction] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][disjunction] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

// Custom trait for testing
template <int N>
struct is_positive : asc::std::bool_constant<(N > 0)> {};

// Trait that fails to compile if instantiated — tests short-circuit evaluation
template <typename T>
struct fail_if_instantiated {
    static_assert(sizeof(T) != sizeof(T), "should not be instantiated");
};

// Compile-time checks
static_assert(!asc::std::disjunction<>::value, "");
static_assert(asc::std::disjunction<asc::std::true_type>::value, "");
static_assert(!asc::std::disjunction<asc::std::false_type>::value, "");
static_assert(asc::std::disjunction<asc::std::true_type, asc::std::false_type>::value, "");
static_assert(!asc::std::disjunction<asc::std::false_type, asc::std::false_type>::value, "");
static_assert(!asc::std::disjunction_v<>, "");
static_assert(asc::std::disjunction_v<asc::std::true_type>, "");
static_assert(asc::std::disjunction_v<asc::std::false_type, asc::std::true_type>, "");

// Result type checks
static_assert(std::is_same_v<typename asc::std::disjunction<asc::std::true_type, asc::std::false_type>::type,
                  asc::std::true_type>,
    "");
static_assert(std::is_same_v<typename asc::std::disjunction<asc::std::false_type, asc::std::true_type>::type,
                  asc::std::true_type>,
    "");
static_assert(std::is_same_v<typename asc::std::disjunction<asc::std::false_type, asc::std::false_type>::type,
                  asc::std::false_type>,
    "");

// Short-circuit: fail_if_instantiated<int> must NOT be instantiated
static_assert(asc::std::disjunction<asc::std::true_type, fail_if_instantiated<int>>::value, "");

int main()
{
    // Empty disjunction → false
    expect_false("disjunction<>::value", asc::std::disjunction<>::value);

    // Single argument
    expect_true("disjunction<true_type>::value", asc::std::disjunction<asc::std::true_type>::value);
    expect_false("disjunction<false_type>::value", asc::std::disjunction<asc::std::false_type>::value);

    // Two arguments
    expect_true("disjunction<true_type, false_type>::value",
        asc::std::disjunction<asc::std::true_type, asc::std::false_type>::value);
    expect_true("disjunction<false_type, true_type>::value",
        asc::std::disjunction<asc::std::false_type, asc::std::true_type>::value);
    expect_false("disjunction<false_type, false_type>::value",
        asc::std::disjunction<asc::std::false_type, asc::std::false_type>::value);

    // disjunction_v
    expect_false("disjunction_v<>", asc::std::disjunction_v<>);
    expect_true("disjunction_v<true_type>", asc::std::disjunction_v<asc::std::true_type>);
    expect_true(
        "disjunction_v<false_type, true_type>", asc::std::disjunction_v<asc::std::false_type, asc::std::true_type>);
    expect_false(
        "disjunction_v<false_type, false_type>", asc::std::disjunction_v<asc::std::false_type, asc::std::false_type>);

    // Custom traits
    expect_true("disjunction<is_positive<5>>::value", asc::std::disjunction<is_positive<5>>::value);
    expect_false("disjunction<is_positive<-3>>::value", asc::std::disjunction<is_positive<-3>>::value);
    expect_true("disjunction<is_positive<-3>, is_positive<5>>::value",
        asc::std::disjunction<is_positive<-3>, is_positive<5>>::value);
    expect_false("disjunction<is_positive<-3>, is_positive<-7>>::value",
        asc::std::disjunction<is_positive<-3>, is_positive<-7>>::value);

    // Short-circuit: fail_if_instantiated<int> must NOT be instantiated
    expect_true("disjunction<true_type, fail_if_instantiated<int>>::value (short-circuit)",
        asc::std::disjunction<asc::std::true_type, fail_if_instantiated<int>>::value);

    // Three arguments
    expect_true("disjunction<false_type, true_type, false_type>::value",
        asc::std::disjunction<asc::std::false_type, asc::std::true_type, asc::std::false_type>::value);
    expect_false("disjunction<false_type, false_type, false_type>::value",
        asc::std::disjunction<asc::std::false_type, asc::std::false_type, asc::std::false_type>::value);

    return g_failures == 0 ? 0 : 1;
}
