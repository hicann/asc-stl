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
#include <asc/std/expected>
#include "support/expected_monad_regression.h"

namespace {

struct copy_failure {};
struct throwing_payload {
    inline static int defaults = 0;
    inline static int live = 0;
    inline static bool fail_copy = false;
    int value = 0;

    throwing_payload()
    {
        ++defaults;
        ++live;
    }
    explicit throwing_payload(int input) : value(input)
    {
        ++live;
    }
    throwing_payload(const throwing_payload& other) : value(other.value)
    {
        if (fail_copy) {
            throw copy_failure{};
        }
        ++live;
    }
    ~throwing_payload()
    {
        --live;
    }
};

bool copies_only_the_active_member()
{
    using expected = asc::std::expected<throwing_payload, throwing_payload>;
    const expected good(asc::std::in_place, 1);
    const expected bad(asc::std::unexpect, 2);
    int caught = 0;
    throwing_payload::fail_copy = true;
    const expected* sources[] = {&good, &bad};
    for (const expected* source : sources) {
        try {
            const expected copied(*source);
        } catch (const copy_failure&) {
            ++caught;
        }
    }
    throwing_payload::fail_copy = false;
    const expected good_copy(good);
    const expected bad_copy(bad);
    return caught == 2 && good_copy && good_copy->value == 1 && !bad_copy && bad_copy.error().value == 2 &&
        throwing_payload::defaults == 0 && throwing_payload::live == 4;
}

}  // namespace

int main()
{
    const bool balanced = copies_only_the_active_member() && throwing_payload::live == 0;
    return asc_stl_expected_monad_test::evaluate() + !balanced;
}
