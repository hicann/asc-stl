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

#include <asc/std/__optional/hash.h>
#include <iostream>

struct TestKey {
    int val;
    TestKey(int v = 0) : val(v)  // NOLINT(runtime/explicit)
    {}
    bool operator==(const TestKey& o) const
    {
        return val == o.val;
    }
};

namespace asc::std {
template <>
struct hash<TestKey> {
    size_t operator()(const TestKey& k) const
    {
        return static_cast<size_t>(k.val) * 31u;
    }
};
}  // namespace asc::std

static int g_failures = 0;

static void expect_eq(const char* expr, size_t got, size_t expected)
{
    bool ok = (got == expected);
    std::cout << "[host][hash] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Empty optional should hash to 0
    {
        asc::std::optional<TestKey> opt;
        size_t h = asc::std::hash<asc::std::optional<TestKey>>{}(opt);
        expect_eq("hash(optional<TestKey>(nullopt))", h, 0u);
    }

    // Engaged optional should hash to hash<TestKey>(value)
    {
        asc::std::optional<TestKey> opt(TestKey{42});
        size_t h = asc::std::hash<asc::std::optional<TestKey>>{}(opt);
        expect_eq("hash(optional<TestKey>(42))", h, 42u * 31u);
    }

    {
        asc::std::optional<TestKey> opt(TestKey{100});
        size_t h = asc::std::hash<asc::std::optional<TestKey>>{}(opt);
        expect_eq("hash(optional<TestKey>(100))", h, 100u * 31u);
    }

    // Value that hashes to 0 (same as empty, but engaged)
    {
        asc::std::optional<TestKey> opt(TestKey{0});
        size_t h = asc::std::hash<asc::std::optional<TestKey>>{}(opt);
        expect_eq("hash(optional<TestKey>(0))", h, 0u);
    }

    // Test with const type (verify remove_const_t works)
    {
        asc::std::optional<const TestKey> opt(TestKey{7});
        size_t h = asc::std::hash<asc::std::optional<const TestKey>>{}(opt);
        expect_eq("hash(optional<const TestKey>(7))", h, 7u * 31u);
    }

    // Test with nullopt explicit
    {
        asc::std::optional<TestKey> opt(asc::std::nullopt);
        size_t h = asc::std::hash<asc::std::optional<TestKey>>{}(opt);
        expect_eq("hash(optional<TestKey>(nullopt_t))", h, 0u);
    }

    // Test with different values
    {
        asc::std::optional<TestKey> opt(TestKey{255});
        size_t h = asc::std::hash<asc::std::optional<TestKey>>{}(opt);
        expect_eq("hash(optional<TestKey>(255))", h, 255u * 31u);
    }

    // Verify hash is consistent across calls with same value
    {
        asc::std::optional<TestKey> opt1(TestKey{55});
        asc::std::optional<TestKey> opt2(TestKey{55});
        size_t h1 = asc::std::hash<asc::std::optional<TestKey>>{}(opt1);
        size_t h2 = asc::std::hash<asc::std::optional<TestKey>>{}(opt2);
        bool ok = (h1 == h2);
        std::cout << "[host][hash] hash(opt1{55}) == hash(opt2{55}) = " << (ok ? "true" : "false")
                  << " (expected true) " << (ok ? "OK" : "FAIL") << std::endl;
        if (!ok)
            ++g_failures;
    }

    return g_failures == 0 ? 0 : 1;
}
