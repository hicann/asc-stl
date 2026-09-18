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

#include <asc/std/__type_traits/is_polymorphic.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_polymorphic] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// --- Test types ---
struct NonPoly {};
struct Poly {
    virtual void foo()
    {}
};
struct Abstract {
    virtual void bar() = 0;
};
struct VirtDtor {
    virtual ~VirtDtor()
    {}
};
struct Derived : Poly {};
struct FinalNonPoly final {};

int main()
{
    // Non-polymorphic types
    expect_true("is_polymorphic<int>::value", asc::std::is_polymorphic<int>::value, false);
    expect_true("is_polymorphic<NonPoly>::value", asc::std::is_polymorphic<NonPoly>::value, false);
    expect_true("is_polymorphic<FinalNonPoly>::value", asc::std::is_polymorphic<FinalNonPoly>::value, false);

    // Polymorphic types
    expect_true("is_polymorphic<Poly>::value", asc::std::is_polymorphic<Poly>::value, true);
    expect_true("is_polymorphic<VirtDtor>::value", asc::std::is_polymorphic<VirtDtor>::value, true);
    expect_true("is_polymorphic<Abstract>::value", asc::std::is_polymorphic<Abstract>::value, true);
    expect_true("is_polymorphic<Derived>::value", asc::std::is_polymorphic<Derived>::value, true);

    // _v shorthand
    expect_true("is_polymorphic_v<int>", asc::std::is_polymorphic_v<int>, false);
    expect_true("is_polymorphic_v<NonPoly>", asc::std::is_polymorphic_v<NonPoly>, false);
    expect_true("is_polymorphic_v<Poly>", asc::std::is_polymorphic_v<Poly>, true);
    expect_true("is_polymorphic_v<Abstract>", asc::std::is_polymorphic_v<Abstract>, true);
    expect_true("is_polymorphic_v<VirtDtor>", asc::std::is_polymorphic_v<VirtDtor>, true);
    expect_true("is_polymorphic_v<Derived>", asc::std::is_polymorphic_v<Derived>, true);

    return g_failures == 0 ? 0 : 1;
}
