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

#include <asc/std/__asc/sequence_access.h>
#include <iostream>
#include <iterator>

static int g_failures = 0;

static void expect_eq_int(const char* expr, int got, int expected)
{
    const bool ok = (got == expected);
    std::cout << "[host][sequence_access] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct simple_sequence {
    using iterator = int*;
    using const_iterator = const int*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    int values[3] = {1, 2, 3};

    iterator begin() noexcept
    {
        return values;
    }
    const_iterator begin() const noexcept
    {
        return values;
    }
    iterator end() noexcept
    {
        return values + 3;
    }
    const_iterator end() const noexcept
    {
        return values + 3;
    }
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    CANN_ASC_STL_DETAIL_SYNTHESIZE_SEQUENCE_ACCESS(simple_sequence, const_iterator)
    CANN_ASC_STL_DETAIL_SYNTHESIZE_SEQUENCE_REVERSE_ACCESS(simple_sequence, const_reverse_iterator)
};

int main()
{
    simple_sequence sequence;
    const simple_sequence& const_sequence = sequence;

    expect_eq_int("*begin(sequence)", *begin(sequence), 1);
    expect_eq_int("*(end(sequence) - 1)", *(end(sequence) - 1), 3);
    expect_eq_int("*begin(const_sequence)", *begin(const_sequence), 1);
    expect_eq_int("*(end(const_sequence) - 1)", *(end(const_sequence) - 1), 3);
    expect_eq_int("*cbegin(const_sequence)", *cbegin(const_sequence), 1);
    expect_eq_int("*(cend(const_sequence) - 1)", *(cend(const_sequence) - 1), 3);

    expect_eq_int("*rbegin(sequence)", *rbegin(sequence), 3);
    expect_eq_int("*(rend(sequence) - 1)", *(rend(sequence) - 1), 1);
    expect_eq_int("*rbegin(const_sequence)", *rbegin(const_sequence), 3);
    expect_eq_int("*(rend(const_sequence) - 1)", *(rend(const_sequence) - 1), 1);
    expect_eq_int("*crbegin(const_sequence)", *crbegin(const_sequence), 3);
    expect_eq_int("*(crend(const_sequence) - 1)", *(crend(const_sequence) - 1), 1);

    return g_failures == 0 ? 0 : 1;
}
