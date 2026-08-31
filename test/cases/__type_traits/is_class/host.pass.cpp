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

#include <asc/std/__type_traits/is_class.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_class] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Test types
struct EmptyClass {};
struct ClassWithMembers {
    int x;
    double y;
};
class PrivateClass {
private:
    int z;
};
union UnionType {
    int a;
    float b;
};
enum EnumType { A, B, C };
enum class ScopedEnum { X, Y, Z };

int main()
{
    // is_class<struct> should be true
    expect_true("is_class<EmptyClass>::value", asc::std::is_class<EmptyClass>::value, true);
    expect_true("is_class<ClassWithMembers>::value", asc::std::is_class<ClassWithMembers>::value, true);
    expect_true("is_class<PrivateClass>::value", asc::std::is_class<PrivateClass>::value, true);

    // is_class_v convenience variable
    expect_true("is_class_v<EmptyClass>", asc::std::is_class_v<EmptyClass>, true);
    expect_true("is_class_v<ClassWithMembers>", asc::std::is_class_v<ClassWithMembers>, true);

    // Non-class types should be false
    expect_true("is_class<int>::value", asc::std::is_class<int>::value, false);
    expect_true("is_class<double>::value", asc::std::is_class<double>::value, false);
    expect_true("is_class<void>::value", asc::std::is_class<void>::value, false);
    expect_true("is_class<int*>::value", asc::std::is_class<int*>::value, false);
    expect_true("is_class<int&>::value", asc::std::is_class<int&>::value, false);
    expect_true("is_class<UnionType>::value", asc::std::is_class<UnionType>::value, false);
    expect_true("is_class<EnumType>::value", asc::std::is_class<EnumType>::value, false);
    expect_true("is_class<ScopedEnum>::value", asc::std::is_class<ScopedEnum>::value, false);

    // is_class_v for non-class types
    expect_true("is_class_v<int>", asc::std::is_class_v<int>, false);
    expect_true("is_class_v<UnionType>", asc::std::is_class_v<UnionType>, false);

    // integral_constant inheritance: is_class derives from integral_constant<bool, ...>
    // so is_class<T>::value should be usable as bool_constant
    static_assert(asc::std::is_class<EmptyClass>::value == true, "");
    static_assert(asc::std::is_class<int>::value == false, "");

    // Test that the trait type itself is a class
    expect_true("is_class<is_class<int>>::value", asc::std::is_class<asc::std::is_class<int>>::value, true);

    return g_failures == 0 ? 0 : 1;
}
