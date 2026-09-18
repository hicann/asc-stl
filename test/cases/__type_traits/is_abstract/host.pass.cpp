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

#include <asc/std/__type_traits/is_abstract.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got)
{
    bool ok = got;
    std::cout << "[host][is_abstract] " << expr << " = " << (got ? "true" : "false") << " (expected true) "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_false(const char* expr, bool got)
{
    bool ok = !got;
    std::cout << "[host][is_abstract] " << expr << " = " << (got ? "true" : "false") << " (expected false) "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Abstract class: has a pure virtual function
struct Abstract {
    virtual void f() = 0;
};

// Abstract class derived from another abstract class
struct AbstractDerived : Abstract {
    virtual void g() = 0;
};

// Concrete class: implements all pure virtuals
struct Concrete : Abstract {
    void f() override
    {}
};

// Non-polymorphic types
struct PlainStruct {
    int x;
};

class PrivateAbstract {
    virtual void h() = 0;
};

int main()
{
    // is_abstract_v tests
    expect_true("is_abstract_v<Abstract>", asc::std::is_abstract_v<Abstract>);
    expect_true("is_abstract_v<AbstractDerived>", asc::std::is_abstract_v<AbstractDerived>);
    expect_false("is_abstract_v<Concrete>", asc::std::is_abstract_v<Concrete>);
    expect_false("is_abstract_v<int>", asc::std::is_abstract_v<int>);
    expect_false("is_abstract_v<double>", asc::std::is_abstract_v<double>);
    expect_false("is_abstract_v<PlainStruct>", asc::std::is_abstract_v<PlainStruct>);
    expect_true("is_abstract_v<PrivateAbstract>", asc::std::is_abstract_v<PrivateAbstract>);

    // is_abstract<T>::value tests
    expect_true("is_abstract<Abstract>::value", asc::std::is_abstract<Abstract>::value);
    expect_true("is_abstract<AbstractDerived>::value", asc::std::is_abstract<AbstractDerived>::value);
    expect_false("is_abstract<Concrete>::value", asc::std::is_abstract<Concrete>::value);
    expect_false("is_abstract<int>::value", asc::std::is_abstract<int>::value);

    // is_abstract<T> inherits from bool_constant (true_type/false_type)
    expect_true("is_abstract<Abstract> inherits true_type", (asc::std::is_abstract<Abstract>::value == true));
    expect_true("is_abstract<int> inherits false_type", (asc::std::is_abstract<int>::value == false));

    // Test with pointer types
    expect_false("is_abstract_v<Abstract*>", asc::std::is_abstract_v<Abstract*>);
    expect_false("is_abstract_v<Abstract&>", asc::std::is_abstract_v<Abstract&>);

    // Test with void
    expect_false("is_abstract_v<void>", asc::std::is_abstract_v<void>);

    return g_failures == 0 ? 0 : 1;
}
