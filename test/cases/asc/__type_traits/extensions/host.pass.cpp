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

#include <asc/__type_traits/extensions.h>

#include <cassert>
#include <cstdint>

enum Enum { A };
struct Trivial {
    int value;
};
struct NonTrivial {
    ~NonTrivial();
    int value;
};
struct BitwiseRelocatable {
    BitwiseRelocatable() = default;
    BitwiseRelocatable(const BitwiseRelocatable&) = default;
    BitwiseRelocatable& operator=(const BitwiseRelocatable&) = default;
    ~BitwiseRelocatable() = default;
    int value;
};

// A user specialization opts a memcpy-safe custom type in.
template <>
struct asc::is_trivially_relocatable<NonTrivial> {
    static constexpr bool value = true;
};

int main()
{
    // Standard integer types are bitwise comparable; floats and composites
    // are not classified by the product.
    static_assert(asc::is_bitwise_comparable_v<int>);
    static_assert(asc::is_bitwise_comparable_v<std::uint64_t>);
    static_assert(asc::is_bitwise_comparable_v<bool>);
    static_assert(asc::is_bitwise_comparable_v<char>);
    static_assert(!asc::is_bitwise_comparable_v<float>);
    static_assert(!asc::is_bitwise_comparable_v<double>);
    static_assert(!asc::is_bitwise_comparable_v<Enum>);
    static_assert(!asc::is_bitwise_comparable_v<Trivial>);
    static_assert(asc::is_bitwise_comparable<int>::value);

    // No extended floating-point type exists in the delivered surface yet.
    static_assert(!asc::is_extended_floating_point_v<float>);
    static_assert(!asc::is_extended_floating_point_v<double>);
    static_assert(!asc::is_extended_floating_point_v<long double>);
    static_assert(!asc::is_extended_floating_point_v<int>);
    static_assert(!asc::is_extended_floating_point<float>::value);

    // Trivially copyable types are trivially relocatable; a documented user
    // specialization extends the classification without touching the default.
    static_assert(asc::is_trivially_relocatable_v<Trivial>);
    static_assert(asc::is_trivially_relocatable_v<int>);
    static_assert(!asc::is_trivially_relocatable_v<BitwiseRelocatable&>);
    static_assert(asc::is_trivially_relocatable<NonTrivial>::value);
    return 0;
}
