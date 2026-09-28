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

#include <asc/std/__bit/has_single_bit.h>

#include <cassert>

int main()
{
    static_assert(asc::std::has_single_bit(1u));
    static_assert(asc::std::has_single_bit(2u));
    static_assert(asc::std::has_single_bit(4u));
    static_assert(asc::std::has_single_bit(1u << 31));
    static_assert(!asc::std::has_single_bit(0u));
    static_assert(!asc::std::has_single_bit(3u));
    static_assert(!asc::std::has_single_bit(6u));
    static_assert(!asc::std::has_single_bit(255u));
    assert(asc::std::has_single_bit(0x8000u));
    constexpr unsigned long long wide = asc::std::has_single_bit(1ULL << 63);
    static_assert(wide);
    return 0;
}
