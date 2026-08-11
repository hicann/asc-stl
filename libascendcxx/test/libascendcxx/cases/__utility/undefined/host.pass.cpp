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

#include <asc/std/__utility/undefined.h>

#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][undefined] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond) {
        ++g_failures;
    }
}

template <class T, class = void>
struct is_complete : std::false_type {};

template <class T>
struct is_complete<T, std::void_t<decltype(sizeof(T))>> : std::true_type {};

struct Incomplete;
struct Complete {};

using Array = int[3];
using Function = int(double);
using U0 = asc::std::__undefined<>;
using U1 = asc::std::__undefined<int>;
using U2 = asc::std::__undefined<int, double>;
using UMany = asc::std::__undefined<int, double, char, float, long>;
using UBoundary = asc::std::__undefined<void, int&, const double, Array, Function, Incomplete>;

template <class T>
using Wrapped = asc::std::__undefined<T>;

int main()
{
    expect_true("U0 is incomplete", !is_complete<U0>::value);
    expect_true("U1 is incomplete", !is_complete<U1>::value);
    expect_true("U2 is incomplete", !is_complete<U2>::value);
    expect_true("UMany is incomplete", !is_complete<UMany>::value);
    expect_true("UBoundary is incomplete", !is_complete<UBoundary>::value);

    expect_true("different arity gives distinct type", !std::is_same<U0, U1>::value);
    expect_true("different arguments give distinct type", !std::is_same<U1, asc::std::__undefined<double>>::value);
    expect_true("different order gives distinct type", !std::is_same<U2, asc::std::__undefined<double, int>>::value);
    expect_true("same arguments give same type", std::is_same<U2, asc::std::__undefined<int, double>>::value);
    expect_true("alias preserves identity", std::is_same<Wrapped<int>, U1>::value);
    expect_true("undefined differs from parameter", !std::is_same<U1, int>::value);
    expect_true("undefined differs from void", !std::is_same<U0, void>::value);

    expect_true("pointer to incomplete sentinel is an object pointer",
        std::is_pointer<U1*>::value && std::is_same<std::remove_pointer_t<U1*>, U1>::value);
    expect_true(
        "const pointer preserves pointee identity", std::is_same<const U1*, const asc::std::__undefined<int>*>::value);
    expect_true("reference can be formed", std::is_same<U1&, asc::std::__undefined<int>&>::value);
    expect_true("rvalue reference can be formed", std::is_same<U1&&, asc::std::__undefined<int>&&>::value);
    expect_true("pointer size is independent of pointee completeness", sizeof(U1*) == sizeof(void*));

    expect_true("parameter completeness does not complete sentinel",
        is_complete<Complete>::value && !is_complete<asc::std::__undefined<Complete>>::value);
    expect_true("incomplete parameter is accepted",
        !is_complete<Incomplete>::value && !is_complete<asc::std::__undefined<Incomplete>>::value);

    static_assert(!is_complete<U0>::value, "");
    static_assert(!is_complete<UBoundary>::value, "");
    static_assert(std::is_same<Wrapped<int>, U1>::value, "");

    return g_failures == 0 ? 0 : 1;
}
