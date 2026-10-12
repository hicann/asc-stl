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

#include <asc/std/cassert>
#include <asc/std/cfloat>
#include <asc/std/ciso646>
#include <asc/std/cstddef>
#include <asc/std/climits>
#include <asc/std/cstdalign>
#include <asc/std/cstdbool>
#include <asc/std/cstdint>
#include <asc/std/source_location>
#include <asc/std/version>

int asc_stl_type_traits_consumer_a();
int asc_stl_type_traits_consumer_b();
int asc_stl_core_consumer_a();
int asc_stl_core_consumer_b();
int asc_stl_vocabulary_consumer_a();
int asc_stl_vocabulary_consumer_b();
int asc_stl_type_transform_consumer_a();
int asc_stl_type_transform_consumer_b();
int asc_stl_constructibility_consumer_a();
int asc_stl_constructibility_consumer_b();
int asc_stl_execution_properties_consumer_a();
int asc_stl_concepts_limits_consumer_a();
int asc_stl_memory_consumer_a();
int asc_stl_b016_consumer_a();
int asc_stl_b017_consumer_a();
int asc_stl_b018_consumer_a();
int asc_stl_b019_consumer_a();
int asc_stl_b021_consumer_a();
int asc_stl_b021_consumer_b();
int asc_stl_b022_consumer_a();
int asc_stl_b022_consumer_b();
int asc_stl_b023_consumer_a();
int asc_stl_b024_consumer_a();
int asc_stl_b024_consumer_b();
int asc_stl_b025_consumer_a();
int asc_stl_b025_consumer_b();
int asc_stl_b023_consumer_b();
int asc_stl_b026_consumer_a();
int asc_stl_b026_consumer_b();
int asc_stl_b028_consumer_a();
int asc_stl_b028_consumer_b();
int asc_stl_w08_consumer_a();
int asc_stl_w08_consumer_b();
int asc_stl_w09_w10_consumer_a();
int asc_stl_w09_w10_consumer_b();
int asc_stl_w13_w14_consumer_a();
int asc_stl_w13_w14_consumer_b();

int main()
{
    constexpr auto location = asc::std::source_location::current("consumer.cpp", "consumer", 77, 9);
    static_assert(location.line() == 77);
    static_assert(location.column() == 9);
    static_assert(sizeof(asc::std::uint32_t) == 4);
    static_assert(CHAR_BIT == 8);
    static_assert(DECIMAL_DIG >= 10);
    assert(location.file_name()[0] == 'c');
    static_assert(asc::std::to_integer<int>(asc::std::byte{0x10} << 1) == 0x20);
    return asc_stl_type_transform_consumer_a() + asc_stl_type_transform_consumer_b() +
        asc_stl_constructibility_consumer_a() + asc_stl_constructibility_consumer_b() +
        asc_stl_execution_properties_consumer_a() + asc_stl_type_traits_consumer_a() +
        asc_stl_type_traits_consumer_b() + asc_stl_core_consumer_a() + asc_stl_core_consumer_b() +
        asc_stl_vocabulary_consumer_a() + asc_stl_vocabulary_consumer_b() + asc_stl_concepts_limits_consumer_a() +
        asc_stl_memory_consumer_a() + asc_stl_b016_consumer_a() + asc_stl_b017_consumer_a() +
        asc_stl_b018_consumer_a() + asc_stl_b019_consumer_a() + asc_stl_b021_consumer_a() + asc_stl_b021_consumer_b() +
        asc_stl_b022_consumer_a() + asc_stl_b022_consumer_b() + asc_stl_b023_consumer_a() + asc_stl_b023_consumer_b() +
        asc_stl_b024_consumer_a() + asc_stl_b024_consumer_b() + asc_stl_b025_consumer_a() + asc_stl_b025_consumer_b() +
        asc_stl_b026_consumer_a() + asc_stl_b026_consumer_b() + asc_stl_b028_consumer_a() + asc_stl_b028_consumer_b() +
        asc_stl_w08_consumer_a() + asc_stl_w08_consumer_b() + asc_stl_w09_w10_consumer_a() +
        asc_stl_w09_w10_consumer_b() + asc_stl_w13_w14_consumer_a() + asc_stl_w13_w14_consumer_b();
}
