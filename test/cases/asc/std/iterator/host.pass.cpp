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

#include <asc/std/random>

#include "../../../../support/b024_semantics.h"

static_assert(asc_stl_b024_test::evaluate_lcg_recurrence() == 0);

int main()
{
    asc::std::minstd_rand0 minstd0;
    asc::std::minstd_rand minstd;
    minstd0.discard(9999);
    minstd.discard(9999);
    if (minstd0() != 1043618065u || minstd() != 399268537u) {
        return 1;
    }
    return asc_stl_b024_test::evaluate();
}
