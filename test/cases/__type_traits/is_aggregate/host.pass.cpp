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

#include <asc/std/__type_traits/is_aggregate.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_aggregate] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_aggregate] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

// Test types
struct EmptyAggregate {};
struct AggregateWithMembers {
    int a;
    double b;
};
struct AggregateWithBase : EmptyAggregate {
    int x;
};
struct NonAggregate {
    NonAggregate()
    {}
    int v;
};
struct HasUserCtor {
    HasUserCtor(int)  // NOLINT(readability/casting,runtime/explicit)
    {}
    int v;
};
struct HasPrivateMember {
private:
    int v;

public:
    int w;
};
struct DerivedNonAgg : NonAggregate {
    int extra;
};
struct AggWithArray {
    int arr[4];
};
struct AggNested {
    AggregateWithMembers inner;
    int x;
};
enum E1 { A, B, C };
union U1 {
    int a;
    float b;
};

int main()
{
    // --- is_aggregate_v tests ---

    // Aggregates
    expect_true("is_aggregate_v<EmptyAggregate>", asc::std::is_aggregate_v<EmptyAggregate>);
    expect_true("is_aggregate_v<AggregateWithMembers>", asc::std::is_aggregate_v<AggregateWithMembers>);
    expect_true("is_aggregate_v<AggWithArray>", asc::std::is_aggregate_v<AggWithArray>);
    expect_true("is_aggregate_v<AggNested>", asc::std::is_aggregate_v<AggNested>);
    expect_true("is_aggregate_v<AggregateWithBase>", asc::std::is_aggregate_v<AggregateWithBase>);

    // Non-aggregates
    expect_false("is_aggregate_v<NonAggregate>", asc::std::is_aggregate_v<NonAggregate>);
    expect_false("is_aggregate_v<HasUserCtor>", asc::std::is_aggregate_v<HasUserCtor>);
    expect_false("is_aggregate_v<HasPrivateMember>", asc::std::is_aggregate_v<HasPrivateMember>);
    // In C++17 a derived class may still be an aggregate even when its base is
    // not an aggregate; the base is initialized as one aggregate element.
    expect_true("is_aggregate_v<DerivedNonAgg>", asc::std::is_aggregate_v<DerivedNonAgg>);

    // Fundamental types are not aggregates
    expect_false("is_aggregate_v<int>", asc::std::is_aggregate_v<int>);
    expect_false("is_aggregate_v<double>", asc::std::is_aggregate_v<double>);
    expect_false("is_aggregate_v<float>", asc::std::is_aggregate_v<float>);

    // Enum and union
    expect_false("is_aggregate_v<E1>", asc::std::is_aggregate_v<E1>);
    expect_true("is_aggregate_v<U1>", asc::std::is_aggregate_v<U1>);

    // Arrays of aggregates and non-aggregates are aggregates
    expect_true("is_aggregate_v<int[4]>", asc::std::is_aggregate_v<int[4]>);
    expect_true("is_aggregate_v<AggregateWithMembers[3]>", asc::std::is_aggregate_v<AggregateWithMembers[3]>);

    // References are not aggregates
    expect_false("is_aggregate_v<int&>", asc::std::is_aggregate_v<int&>);

    // --- is_aggregate (struct) tests ---

    expect_true("is_aggregate<EmptyAggregate>::value", asc::std::is_aggregate<EmptyAggregate>::value);
    expect_false("is_aggregate<int>::value", asc::std::is_aggregate<int>::value);
    expect_true("is_aggregate<AggregateWithMembers>::value", asc::std::is_aggregate<AggregateWithMembers>::value);
    expect_false("is_aggregate<NonAggregate>::value", asc::std::is_aggregate<NonAggregate>::value);

    // --- Inherited from bool_constant / integral_constant ---
    static_assert(asc::std::is_aggregate<EmptyAggregate>::value == true, "");
    static_assert(asc::std::is_aggregate<int>::value == false, "");
    static_assert(asc::std::is_aggregate_v<EmptyAggregate> == true, "");
    static_assert(asc::std::is_aggregate_v<int> == false, "");

    // Verify it works as a compile-time constant
    if constexpr (asc::std::is_aggregate_v<EmptyAggregate>) {
        expect_true("constexpr if is_aggregate_v<EmptyAggregate>", true);
    } else {
        expect_true("constexpr if is_aggregate_v<EmptyAggregate>", false);
    }

    // Test the inherited member types from integral_constant
    static_assert(std::is_same_v<asc::std::is_aggregate<int>::value_type, bool>, "");

    return g_failures == 0 ? 0 : 1;
}
