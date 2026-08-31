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

#include <asc/__type_traits/is_floating_point.h>
#include <iostream>

static int g_failures = 0;

// 表格驱动：每个条目是 (类型, 期望结果)，统一走一个探测函数。
template <class T>
struct fp_check {
    static bool value()
    {
        return asc::is_floating_point<T>::value;
    }
    static bool variable()
    {
        return asc::is_floating_point_v<T>;
    }
};

struct NotEmpty {
    virtual ~NotEmpty();
};
union PackedUnion {};
enum Color { red, green };
using Callback = void (*)();

int main()
{
    struct {
        const char* name;
        bool expected;
        bool got_value;
        bool got_variable;
    } rows[] = {
        {"float", true, fp_check<float>::value(), fp_check<float>::variable()},
        {"double", true, fp_check<double>::value(), fp_check<double>::variable()},
        {"long double", true, fp_check<long double>::value(), fp_check<long double>::variable()},
        {"const float", true, fp_check<const float>::value(), fp_check<const float>::variable()},
        {"volatile double", true, fp_check<volatile double>::value(), fp_check<volatile double>::variable()},
        {"short", false, fp_check<short>::value(), fp_check<short>::variable()},
        {"unsigned int", false, fp_check<unsigned int>::value(), fp_check<unsigned int>::variable()},
        {"long", false, fp_check<long>::value(), fp_check<long>::variable()},
        {"bool", false, fp_check<bool>::value(), fp_check<bool>::variable()},
        {"char", false, fp_check<char>::value(), fp_check<char>::variable()},
        {"void", false, fp_check<void>::value(), fp_check<void>::variable()},
        {"std::nullptr_t", false, fp_check<std::nullptr_t>::value(), fp_check<std::nullptr_t>::variable()},
        {"int&", false, fp_check<int&>::value(), fp_check<int&>::variable()},
        {"int&&", false, fp_check<int&&>::value(), fp_check<int&&>::variable()},
        {"int*", false, fp_check<int*>::value(), fp_check<int*>::variable()},
        {"char[3]", false, fp_check<char[3]>::value(), fp_check<char[3]>::variable()},
        {"char[]", false, fp_check<char[]>::value(), fp_check<char[]>::variable()},
        {"PackedUnion", false, fp_check<PackedUnion>::value(), fp_check<PackedUnion>::variable()},
        {"Color", false, fp_check<Color>::value(), fp_check<Color>::variable()},
        {"Callback", false, fp_check<Callback>::value(), fp_check<Callback>::variable()},
        {"NotEmpty", false, fp_check<NotEmpty>::value(), fp_check<NotEmpty>::variable()},
    };

    for (const auto& row : rows) {
        const bool ok = (row.got_value == row.expected) && (row.got_variable == row.expected);
        std::cout << "[host][is_floating_point] " << row.name << ": value=" << (row.got_value ? "true" : "false")
                  << " _v=" << (row.got_variable ? "true" : "false") << " (expected "
                  << (row.expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
        if (!ok)
            ++g_failures;
    }

    return g_failures == 0 ? 0 : 1;
}
