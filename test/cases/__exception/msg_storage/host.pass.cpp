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

#include <asc/std/__exception/msg_storage.h>
#include <iostream>
#include <cstring>

static int g_failures = 0;

static void expect_eq(const char* expr, unsigned long long got, unsigned long long expected)
{
    bool ok = (got == expected);
    std::cout << "[host][msg_storage] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][msg_storage] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // 1. __size is 512
    expect_eq("__msg_storage::__size", asc::__msg_storage::__size, 512ULL);

    // 2. Default-constructed buffer is zero-initialized
    {
        asc::__msg_storage s;
        bool all_zero = true;
        for (asc::std::size_t i = 0; i < asc::__msg_storage::__size; ++i) {
            if (s.__buffer[i] != 0) {
                all_zero = false;
                break;
            }
        }
        expect_true("default __buffer all zero", all_zero);
    }

    // 3. sizeof matches __size
    expect_eq("sizeof(__msg_storage)", (unsigned long long)sizeof(asc::__msg_storage), 512ULL);

    // 4. Can write and read back
    {
        asc::__msg_storage s;
        const char* msg = "hello asc";
        for (std::size_t i = 0; i <= std::strlen(msg); ++i) {
            s.__buffer[i] = msg[i];
        }
        expect_true("write/read back 'hello asc'", std::strcmp(s.__buffer, "hello asc") == 0);
    }

    // 5. Buffer can hold a long message up to __size
    {
        asc::__msg_storage s;
        for (asc::std::size_t i = 0; i < asc::__msg_storage::__size; ++i) {
            s.__buffer[i] = static_cast<char>(i % 128);
        }
        bool ok = true;
        for (asc::std::size_t i = 0; i < asc::__msg_storage::__size; ++i) {
            if (s.__buffer[i] != static_cast<char>(i % 128)) {
                ok = false;
                break;
            }
        }
        expect_true("fill and verify full buffer", ok);
    }

    // 6. Two independent instances don't share state
    {
        asc::__msg_storage a;
        asc::__msg_storage b;
        a.__buffer[0] = 'A';
        b.__buffer[0] = 'B';
        expect_true("a.__buffer[0]=='A'", a.__buffer[0] == 'A');
        expect_true("b.__buffer[0]=='B'", b.__buffer[0] == 'B');
    }

    return g_failures == 0 ? 0 : 1;
}
