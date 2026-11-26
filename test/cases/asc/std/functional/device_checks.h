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

#pragma once

#include <asc/std/functional>
#include <asc/std/bit>

namespace asc_stl_test_functional {
template <class T>
CANN_ASC_STL_API constexpr bool check_operators(int a, int b)
{
    return asc::std::plus<T>{}(a, b) == (a + b) && asc::std::minus<T>{}(a, b) == (a - b) &&
        asc::std::multiplies<T>{}(a, b) == (a * b) && asc::std::divides<T>{}(a, b) == (a / b) &&
        asc::std::modulus<T>{}(a, b) == (a % b) && asc::std::bit_and<T>{}(a, b) == (a & b) &&
        asc::std::bit_or<T>{}(a, b) == (a | b) && asc::std::bit_xor<T>{}(a, b) == (a ^ b) &&
        asc::std::equal_to<T>{}(a, b) == (a == b) && asc::std::not_equal_to<T>{}(a, b) == (a != b) &&
        asc::std::less<T>{}(a, b) == (a < b) && asc::std::greater<T>{}(a, b) == (a > b) &&
        asc::std::less_equal<T>{}(a, b) == (a <= b) && asc::std::greater_equal<T>{}(a, b) == (a >= b) &&
        asc::std::logical_and<T>{}(a, b) == (a && b) && asc::std::logical_or<T>{}(a, b) == (a || b) &&
        asc::std::negate<T>{}(a) == -a && asc::std::bit_not<T>{}(a) == ~a && asc::std::logical_not<T>{}(a) == !a;
}

CANN_ASC_STL_API int check(int seed = 7)
{
    // Equal signed zeros must remain interchangeable as hash keys.
    const auto sign = static_cast<__UINT64_TYPE__>(seed & 1) << 63;
    if (asc::std::hash<double>{}(asc::std::bit_cast<double>(sign)) != asc::std::hash<double>{}(0.0))
        return 4;
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && __SIZEOF_LONG_DOUBLE__ == 8 && __LDBL_MANT_DIG__ == 53
    const long double negative_zero = asc::std::bit_cast<long double>(sign);
    const long double positive_zero = asc::std::bit_cast<long double>(static_cast<__UINT64_TYPE__>(0));
    if (asc::std::hash<long double>{}(negative_zero) != asc::std::hash<long double>{}(positive_zero))
        return 5;
#endif
    for (int a = -3; a <= 3; ++a) {
        for (int b = 1; b <= 4; ++b) {
            if (!check_operators<int>(a, b) || !check_operators<void>(a, b))
                return 1;
        }
    }
    int data[] = {1, 2, 1, 2, 3};
    asc::std::default_searcher search(data + 2, data + 5);
    const auto match = search(data, data + 5);
    const auto absent = search(data, data + 2);
    if (match.first != data + 2 || match.second != data + 5 || absent.first != data + 2 || absent.second != data + 2)
        return 2;
    int& id = asc::std::identity{}(data[0]);
    asc::std::ref(id).get() = 7;
    return &asc::std::cref(id).get() != data || data[0] != 7;
}

}  // namespace asc_stl_test_functional
