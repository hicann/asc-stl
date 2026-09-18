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

#include <asc/std/__functional/mem_fn.h>

struct Record {
    int value;
    constexpr int add(int amount) const noexcept
    {
        return value + amount;
    }
};

#if __cplusplus >= 202002L
constexpr
#endif
    bool
    test_mem_fn()
{
    Record record{5};
    auto data = asc::std::mem_fn(&Record::value);
    auto function = asc::std::mem_fn(&Record::add);
    return data(record) == 5 && function(record, 3) == 8;
}

#if __cplusplus >= 202002L
static_assert(test_mem_fn());
#endif

int main()
{
    return test_mem_fn() ? 0 : 1;
}
