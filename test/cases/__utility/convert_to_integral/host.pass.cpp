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

#include <asc/std/__utility/convert_to_integral.h>

#include <iostream>
#include <type_traits>

enum signed_count : signed char { minus_one = -1, three = 3 };

enum unsigned_count : unsigned short { four = 4 };

static_assert(asc::std::__convert_to_integral(3) == 3);
static_assert(asc::std::__convert_to_integral(4u) == 4u);
static_assert(asc::std::__convert_to_integral(5L) == 5L);
static_assert(asc::std::__convert_to_integral(6UL) == 6UL);
static_assert(asc::std::__convert_to_integral(7LL) == 7LL);
static_assert(asc::std::__convert_to_integral(8ULL) == 8ULL);
static_assert(asc::std::__convert_to_integral(3.75f) == 3LL);
static_assert(asc::std::__convert_to_integral(-2.75) == -2LL);
static_assert(asc::std::__convert_to_integral(three) == 3);
static_assert(asc::std::__convert_to_integral(four) == 4);

static_assert(std::is_same_v<decltype(asc::std::__convert_to_integral(1.0f)), long long>);
static_assert(std::is_same_v<decltype(asc::std::__convert_to_integral(three)), int>);
static_assert(std::is_same_v<decltype(asc::std::__convert_to_integral(four)), int>);

int main()
{
    const bool ok = asc::std::__convert_to_integral(9.9f) == 9 && asc::std::__convert_to_integral(minus_one) == -1;
    std::cout << "[host][convert_to_integral] overload and truncation semantics " << (ok ? "OK" : "FAIL") << std::endl;
    return ok ? 0 : 1;
}
