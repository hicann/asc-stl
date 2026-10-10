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

#include <cmath>
#include <limits>
#include <type_traits>

// Load the Host reference library before the product's fallback math macros.
// Standalone product macro values are checked separately in host.pass.cpp.
#include <asc/std/cmath>  // NOLINT(build/include_order)

static_assert(std::is_same_v<decltype(asc::std::acos(0.5F)), float>);
static_assert(std::is_same_v<decltype(asc::std::acos(0.5)), double>);
static_assert(std::is_same_v<decltype(asc::std::acos(0.5L)), long double>);
static_assert(std::is_same_v<decltype(asc::std::acosl(0.5L)), long double>);
static_assert(std::is_same_v<decltype(asc::std::acos(1)), float>);
static_assert(std::is_same_v<decltype(asc::std::acos(1ULL)), float>);
static_assert(std::is_same_v<decltype(asc::std::acos(true)), float>);
static_assert(noexcept(asc::std::acos(0.5)) && noexcept(asc::std::acosl(0.5L)));

template <class T>
bool check_host_acos()
{
    const T pi = static_cast<T>(3.141592653589793238462643383279502884L);
    const T tolerance = 8 * std::numeric_limits<T>::epsilon();
    if (std::abs(asc::std::acos(T(-1)) - pi) > tolerance || std::abs(asc::std::acos(T(0)) - pi / 2) > tolerance ||
        asc::std::acos(T(1)) != T(0))
        return false;
    volatile T input = T(1) - 8 * std::numeric_limits<T>::epsilon();
    const T actual = asc::std::acos(input);
    const T expected = std::acos(input);
    if (!(actual > 0) || std::abs(actual - expected) > tolerance * expected)
        return false;
    return std::isnan(asc::std::acos(T(2))) && std::isnan(asc::std::acos(std::numeric_limits<T>::infinity())) &&
        std::isnan(asc::std::acos(std::numeric_limits<T>::quiet_NaN()));
}

int main()
{
    if (!check_host_acos<double>() || !check_host_acos<long double>())
        return 10;
    volatile long double input = 1.0L - 8 * std::numeric_limits<long double>::epsilon();
    if (asc::std::acosl(input) != asc::std::acos(input) || asc::std::acosl(input) <= 0)
        return 11;
    if (asc::std::acos(0) != asc::std::acos(0.0F) || asc::std::acos(1ULL) != 0.0F)
        return 12;
    return 0;
}
