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

#include <algorithm>
#include <limits>

#include "device_checks.h"

template <class T>
bool all_byte_pairs()
{
    const int lo = std::numeric_limits<T>::min();
    const int hi = std::numeric_limits<T>::max();
    const auto clamp = [=](int n) { return std::clamp(n, lo, hi); };
    for (int i = lo; i <= hi; ++i) {
        for (int j = lo; j <= hi; ++j) {
            const T a = static_cast<T>(i);
            const T b = static_cast<T>(j);
            if (asc::std::saturating_add(a, b) != clamp(i + j) || asc::std::saturating_sub(a, b) != clamp(i - j) ||
                asc::std::saturating_mul(a, b) != clamp(i * j) ||
                (b != 0 && asc::std::saturating_div(a, b) != clamp(i / j)) ||
                asc::std::saturating_cast<T>(i + j) != clamp(i + j))
                return false;
        }
    }
    return true;
}

int main()
{
    int workspace[15];
    if (const int error = asc_stl_test_numeric::check(7, workspace))
        return error;
    return all_byte_pairs<signed char>() && all_byte_pairs<unsigned char>() ? 0 : 8;
}
