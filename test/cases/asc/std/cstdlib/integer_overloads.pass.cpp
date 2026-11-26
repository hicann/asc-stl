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

#include <asc/std/cstdlib>
#include <cstdlib>
#include <initializer_list>
#include <limits>
#include <type_traits>

static_assert(std::is_same_v<asc::std::div_t, std::div_t>);
static_assert(std::is_same_v<asc::std::ldiv_t, std::ldiv_t>);
static_assert(std::is_same_v<asc::std::lldiv_t, std::lldiv_t>);

template <class T>
bool division()
{
    for (T n : {std::numeric_limits<T>::min(), T{-31}, T{0}, T{47}, std::numeric_limits<T>::max()}) {
        for (T d : {T{-7}, T{3}, T{1}}) {
            const auto result = asc::std::div(n, d);
            if (result.quot != n / d || result.rem != n % d)
                return false;
        }
    }
    return asc::std::abs(T{-31}) == 31 && asc::std::abs(T{0}) == 0 &&
        asc::std::abs(std::numeric_limits<T>::max()) == std::numeric_limits<T>::max();
}

int main()
{
    return !(division<int>() && division<long>() && division<long long>());
}
