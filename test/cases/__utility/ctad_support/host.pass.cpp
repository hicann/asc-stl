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

#include <asc/std/__utility/ctad_support.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][ctad_support] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// Tag types that carry the __allow_ctad nested typedef
struct TagA {
    using __allow_ctad = TagA;
};
struct TagB {
    using __allow_ctad = TagB;
};
struct TagC {
    using __allow_ctad = TagC;
};

// A class template that will use the CTAD macro
template <typename... Ts>
struct MyContainer {
    static constexpr int arity = static_cast<int>(sizeof...(Ts));
};

// Apply the CTAD macro at namespace scope — this generates a deduction guide:
//   template <class... _Tag>
//   MyContainer(typename _Tag::__allow_ctad...)->MyContainer<_Tag...>;
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(MyContainer);

// A second class template with a default template argument
template <typename T, typename Alloc = int>
struct MyVector {
    using value_type = T;
    using allocator_type = Alloc;
};

CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(MyVector);

int main()
{
    // 1. Verify the macro is defined
#ifdef CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE
    expect_true("CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE is defined", true);
#else
    expect_true("CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE is defined", false);
#endif

    // 2. Verify explicit template instantiation works with single tag
    {
        MyContainer<TagA> c{};
        expect_true("MyContainer<TagA>::arity == 1", c.arity == 1);
    }

    // 3. Verify explicit template instantiation works with two tags
    {
        MyContainer<TagA, TagB> c{};
        expect_true("MyContainer<TagA,TagB>::arity == 2", c.arity == 2);
    }

    // 4. Verify explicit template instantiation works with three tags
    {
        MyContainer<TagA, TagB, TagC> c{};
        expect_true("MyContainer<TagA,TagB,TagC>::arity == 3", c.arity == 3);
    }

    // 5. Verify empty pack instantiation
    {
        MyContainer<> c{};
        expect_true("MyContainer<>::arity == 0", c.arity == 0);
    }

    // 6. Verify the macro-generated deduction guide compiles (no syntax errors)
    //    The fact that the file compiles confirms the guide is well-formed.
    expect_true("deduction guide from CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE compiles", true);

    // 7. Verify MyVector with default template arg
    {
        MyVector<double> v{};
        expect_true("MyVector<double>::value_type is double", std::is_same_v<decltype(v)::value_type, double>);
        expect_true(
            "MyVector<double>::allocator_type is int (default)", std::is_same_v<decltype(v)::allocator_type, int>);
    }

    // 8. Verify MyVector with explicit allocator
    {
        MyVector<float, TagA> v{};
        expect_true("MyVector<float,TagA>::value_type is float", std::is_same_v<decltype(v)::value_type, float>);
        expect_true("MyVector<float,TagA>::allocator_type is TagA", std::is_same_v<decltype(v)::allocator_type, TagA>);
    }

    return g_failures == 0 ? 0 : 1;
}
