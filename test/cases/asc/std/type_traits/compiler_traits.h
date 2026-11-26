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

#ifndef ASC_STL_TEST_TYPE_TRAITS_COMPILER_TRAITS_H
#define ASC_STL_TEST_TYPE_TRAITS_COMPILER_TRAITS_H

#include <asc/std/type_traits>

namespace asc_stl_native_traits_test {
namespace s = asc::std;
struct member {
    int field;
};
struct nontrivial {
    CANN_ASC_STL_API ~nontrivial()
    {}
};
using array = int[7][3];

static_assert(s::extent<array, 0>::value == 7 && s::extent_v<array, 1> == 3 && s::extent_v<array, 2> == 0);
static_assert(s::is_same_v<typename s::remove_cv<const volatile int>::type, int> &&
    s::is_same_v<s::remove_cv_t<const int* volatile>, const int*>);
static_assert(s::is_convertible<int, long>::value && !s::is_convertible_v<int*, int>);
static_assert(s::is_compound<member>::value && !s::is_compound_v<int>);
static_assert(s::is_function<int(int)>::value && !s::is_function_v<int (*)(int)>);
static_assert(s::is_fundamental<int>::value && !s::is_fundamental_v<member>);
static_assert(s::is_integral<unsigned>::value && !s::is_integral_v<double>);
static_assert(s::is_member_pointer<int member::*>::value && !s::is_member_pointer_v<int*>);
static_assert(s::is_object<array>::value && !s::is_object_v<int&>);
static_assert(s::is_pointer<int* const>::value && !s::is_pointer_v<int member::*>);
static_assert(s::is_scalar<int member::*>::value && !s::is_scalar_v<member>);
static_assert(s::is_unsigned<unsigned>::value && !s::is_unsigned_v<int>);
static_assert(s::is_lvalue_reference<int&>::value && !s::is_lvalue_reference_v<int&&>);
static_assert(s::is_rvalue_reference<int&&>::value && !s::is_rvalue_reference_v<int&>);
static_assert(s::is_reference<int&&>::value && !s::is_reference_v<int>);
static_assert(s::is_trivially_destructible<member>::value && !s::is_trivially_destructible_v<nontrivial>);
}  // namespace asc_stl_native_traits_test
#endif  // ASC_STL_TEST_TYPE_TRAITS_COMPILER_TRAITS_H
