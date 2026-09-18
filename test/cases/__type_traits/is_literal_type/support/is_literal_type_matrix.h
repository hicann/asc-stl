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

#ifndef CANN_ASC_STL_TEST_CASES___TYPE_TRAITS_IS_LITERAL_TYPE_SUPPORT_IS_LITERAL_TYPE_MATRIX_H
#define CANN_ASC_STL_TEST_CASES___TYPE_TRAITS_IS_LITERAL_TYPE_SUPPORT_IS_LITERAL_TYPE_MATRIX_H

#include <asc/std/__type_traits/is_literal_type.h>

namespace asc_stl_test {

class Empty {};

class NonLiteral {
public:
    virtual ~NonLiteral() = default;
};

class Abstract {
public:
    virtual ~Abstract() = 0;
};

union LiteralUnion {};

struct ZeroWidthBitField {
    int : 0;
};

enum Enum {
    kZero,
    kOne,
};

using FunctionPointer = void (*)();

template <class T>
CANN_ASC_STL_DETAIL_ACCL_AICORE_FN constexpr void expect_literal_type()
{
    static_assert(asc::std::is_literal_type<T>::value);
    static_assert(asc::std::is_literal_type<const T>::value);
    static_assert(asc::std::is_literal_type<volatile T>::value);
    static_assert(asc::std::is_literal_type<const volatile T>::value);
    static_assert(asc::std::is_literal_type_v<T>);
    static_assert(asc::std::is_literal_type_v<const T>);
    static_assert(asc::std::is_literal_type_v<volatile T>);
    static_assert(asc::std::is_literal_type_v<const volatile T>);
}

template <class T>
CANN_ASC_STL_DETAIL_ACCL_AICORE_FN constexpr void expect_non_literal_type()
{
    static_assert(!asc::std::is_literal_type<T>::value);
    static_assert(!asc::std::is_literal_type<const T>::value);
    static_assert(!asc::std::is_literal_type<volatile T>::value);
    static_assert(!asc::std::is_literal_type<const volatile T>::value);
    static_assert(!asc::std::is_literal_type_v<T>);
    static_assert(!asc::std::is_literal_type_v<const T>);
    static_assert(!asc::std::is_literal_type_v<volatile T>);
    static_assert(!asc::std::is_literal_type_v<const volatile T>);
}

CANN_ASC_STL_DETAIL_ACCL_AICORE_FN constexpr void check_is_literal_type_matrix()
{
    expect_literal_type<decltype(nullptr)>();
    expect_literal_type<void>();
    expect_literal_type<int>();
    expect_literal_type<double>();
    expect_literal_type<int*>();
    expect_literal_type<const int*>();
    expect_literal_type<int&>();
    expect_literal_type<int&&>();
    expect_literal_type<char[3]>();
    expect_literal_type<char[]>();
    expect_literal_type<Empty>();
    expect_literal_type<ZeroWidthBitField>();
    expect_literal_type<LiteralUnion>();
    expect_literal_type<Enum>();
    expect_literal_type<FunctionPointer>();

    expect_non_literal_type<NonLiteral>();
    expect_non_literal_type<Abstract>();
}

}  // namespace asc_stl_test

#endif  // CANN_ASC_STL_TEST_CASES___TYPE_TRAITS_IS_LITERAL_TYPE_SUPPORT_IS_LITERAL_TYPE_MATRIX_H
