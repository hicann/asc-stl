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

#include <asc/std/__asc/rtti.h>
#include <iostream>
#include <typeinfo>

int g_failures = 0;

void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][rtti] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct Base {
    virtual ~Base()
    {}
};
struct Derived : Base {};

int main()
{
#ifdef CANN_ASC_STL_DETAIL_NO_RTTI
    expect_eq("CANN_ASC_STL_DETAIL_NO_RTTI defined", true, false);
#else
    expect_eq("CANN_ASC_STL_DETAIL_NO_RTTI defined", false, false);
#endif

#ifdef CANN_ASC_STL_DETAIL_NO_TYPEID
    expect_eq("CANN_ASC_STL_DETAIL_NO_TYPEID defined", true, false);
#else
    expect_eq("CANN_ASC_STL_DETAIL_NO_TYPEID defined", false, false);
#endif

    {
        int x = 42;
        const std::type_info& ti = typeid(x);
        bool same = (ti == typeid(int));
        expect_eq("typeid(int) == typeid(int)", same, true);
    }

    {
        Derived d;
        Base* bp = &d;
        const std::type_info& ti = typeid(*bp);
        bool is_derived = (ti == typeid(Derived));
        expect_eq("typeid(*bp) == typeid(Derived)", is_derived, true);
    }

    {
        Derived d;
        Base* bp = &d;
        Derived* dp = dynamic_cast<Derived*>(bp);
        expect_eq("dynamic_cast<Derived*>(bp) != nullptr", dp != nullptr, true);
    }

    {
        Base b;
        Base* bp = &b;
        Derived* dp = dynamic_cast<Derived*>(bp);
        expect_eq("dynamic_cast<Derived*>(base_ptr) == nullptr", dp == nullptr, true);
    }

    return g_failures == 0 ? 0 : 1;
}
