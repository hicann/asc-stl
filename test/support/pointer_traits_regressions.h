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

#ifndef ASC_STL_TEST_SUPPORT_POINTER_TRAITS_REGRESSIONS_H
#define ASC_STL_TEST_SUPPORT_POINTER_TRAITS_REGRESSIONS_H

#include <asc/std/iterator>
#include <asc/std/type_traits>

namespace asc_stl_pointer_traits_test {
struct Incomplete;
struct Object {
    int member;
    int function();
};
enum class Enumeration { value };

template <class T, class = void>
struct HasPointerTraits : asc::std::false_type {};
template <class T>
struct HasPointerTraits<T, asc::std::void_t<typename asc::std::iterator_traits<T>::pointer>> : asc::std::true_type {};

static_assert(HasPointerTraits<Incomplete*>::value);
static_assert(HasPointerTraits<int (*)[3]>::value);
static_assert(!HasPointerTraits<void*>::value);
static_assert(!HasPointerTraits<const void*>::value);
static_assert(!HasPointerTraits<int (*)()>::value);
static_assert(asc::std::is_same_v<asc::std::iterator_traits<const int*>::value_type, int>);
static_assert(asc::std::is_same_v<asc::std::iterator_traits<const volatile int*>::pointer, const volatile int*>);
static_assert(asc::std::is_same_v<asc::std::iterator_traits<volatile int*>::reference, volatile int&>);

static_assert(asc::std::is_scalar<int>::value);
static_assert(asc::std::is_scalar_v<const volatile double>);
static_assert(asc::std::is_scalar_v<Enumeration>);
static_assert(asc::std::is_scalar_v<void*>);
static_assert(asc::std::is_scalar_v<int (*)()>);
static_assert(asc::std::is_scalar_v<int Object::*>);
static_assert(asc::std::is_scalar_v<int (Object::*)()>);
static_assert(asc::std::is_scalar_v<decltype(nullptr)>);
static_assert(!asc::std::is_scalar_v<int&>);
static_assert(!asc::std::is_scalar_v<int[3]>);
static_assert(!asc::std::is_scalar_v<int()>);
static_assert(!asc::std::is_scalar_v<Object>);
static_assert(!asc::std::is_scalar_v<void>);

}  // namespace asc_stl_pointer_traits_test

#endif  // ASC_STL_TEST_SUPPORT_POINTER_TRAITS_REGRESSIONS_H
