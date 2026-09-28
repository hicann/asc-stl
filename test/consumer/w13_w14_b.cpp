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

#include <asc/std/type_traits>
#include <asc/std/system_error>
#include <asc/std/random>
#include <asc/std/numeric>
#include <asc/std/linalg>
#include <asc/std/compare>
#include <asc/std/cwchar>
#include <asc/std/cerrno>
#include <asc/std/cctype>
#include <asc/std/bit>
#include <asc/utility>
#include <asc/semaphore>
#include <asc/latch>
#include <asc/bit>
#include <asc/barrier>

int asc_stl_w13_w14_consumer_b()
{
    static_assert(asc::std::is_same_v<asc::std::remove_cv_t<const volatile int>, int>);
    static_assert(asc::std::is_error_condition_enum<asc::std::errc>::value);
    return asc::std::wcslen(L"asc") == 3 ? 0 : 1;
}
