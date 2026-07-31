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

#include <asc/std/__bit/blsr.h>

#include <iostream>
#include <limits>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static constexpr T independent_blsr(T value)
{
    static_assert(std::is_unsigned<T>::value, "blsr oracle requires an unsigned type");
    return value == 0 ? 0 : static_cast<T>(value & static_cast<T>(value - 1));
}

template <typename T>
static void check_value(const char* type_name, T value)
{
    const T got = asc::std::__accl_blsr(value);
    const T expected = independent_blsr(value);
    const bool ok = got == expected;
    std::cout << "[host][blsr] " << type_name << " value=" << value << " got=" << got << " expected=" << expected << " "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

template <typename T>
static void check_type(const char* type_name)
{
    constexpr T kValues[] = {
        static_cast<T>(0),
        static_cast<T>(1),
        static_cast<T>(2),
        static_cast<T>(3),
        static_cast<T>(6),
        static_cast<T>(7),
        static_cast<T>(12),
        static_cast<T>(100),
        static_cast<T>(T{1} << (std::numeric_limits<T>::digits - 1)),
        std::numeric_limits<T>::max(),
    };
    for (T value : kValues)
        check_value(type_name, value);
}

int main()
{
    check_type<unsigned>("unsigned");
    check_type<unsigned long>("unsigned long");
    check_type<unsigned long long>("unsigned long long");

    return g_failures == 0 ? 0 : 1;
}
