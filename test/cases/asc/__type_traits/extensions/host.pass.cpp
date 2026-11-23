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

#include <asc/type_traits>

#include <cassert>
#include <cstring>
#include <limits>
#include <new>

#include "support/extension_type_traits_semantics.h"

namespace {
struct Parity {
    unsigned value;
    friend bool operator==(const Parity& a, const Parity& b) noexcept
    {
        return a.value % 2 == b.value % 2;
    }
};
struct Counted {
    unsigned value;
    static unsigned calls;
    friend bool operator==(const Counted& a, const Counted& b) noexcept
    {
        ++calls;
        return a.value == b.value;
    }
};
unsigned Counted::calls = 0;

template <class T>
bool equal_value(const T& a, const T& b)
{
    if constexpr (asc::is_bitwise_comparable_v<T>) {
        return std::memcmp(&a, &b, sizeof(T)) == 0;
    } else {
        return a == b;
    }
}
}  // namespace

int main()
{
    static_assert(asc::std::is_trivially_copyable_v<Parity>);
    static_assert(asc::std::has_unique_object_representations_v<Parity>);
    static_assert(!asc::is_bitwise_comparable_v<Parity>);
    const Parity one{1}, three{3};
    assert(equal_value(one, three));
    assert(std::memcmp(&one, &three, sizeof(Parity)) != 0);
    assert(equal_value(Counted{7}, Counted{7}) && Counted::calls == 1);
    const float positive = 0.0f, negative = -0.0f;
    assert(equal_value(positive, negative));
    assert(std::memcmp(&positive, &negative, sizeof(float)) != 0);
    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float same_nan = __builtin_bit_cast(float, nan);
    assert(!equal_value(nan, same_nan) && std::memcmp(&nan, &same_nan, sizeof(nan)) == 0);
    assert(equal_value(123u, 123u) && !equal_value(123u, 124u));
    traits_test::SelfReference source, copied(source);
    assert(copied.self == &source.value && copied.self != &copied.value);
    // Legal C++17 relocation route: construct, then release source storage.
    using Value = traits_test::UserValue;
    void* old_storage = ::operator new(sizeof(Value));
    auto* old_value = ::new (old_storage) Value{41};
    void* new_storage = ::operator new(sizeof(Value));
    auto* new_value = ::new (new_storage) Value(static_cast<Value&&>(*old_value));
    ::operator delete(old_storage);
    assert(new_value->value == 41);
    ::operator delete(new_storage);
}
