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

#include <asc/execution.determinism.h>
#include <asc/execution.tie_break.h>
#include <asc/std/cassert>
#include <asc/std/cfloat>
#include <asc/std/ciso646>
#include <asc/std/climits>
#include <asc/std/cstdalign>
#include <asc/std/cstdbool>
#include <asc/std/ratio>
#include <asc/std/source_location>
#include <asc/std/version>

int main()
{
    static_assert(asc::determinism::run_to_run != asc::determinism::not_guaranteed);
    static_assert(asc::tie_break::prefer_smaller_index != asc::tie_break::prefer_larger_index);
    static_assert(CHAR_BIT >= 8);
    static_assert(DECIMAL_DIG >= 10);
    static_assert(asc::std::ratio_equal_v<asc::std::ratio<2, 4>, asc::std::ratio<1, 2>>);
    constexpr auto location = asc::std::source_location::current("consumer.cpp", "consumer", 77, 9);
    static_assert(location.line() == 77);
    static_assert(location.column() == 9);
    return 0;
}
