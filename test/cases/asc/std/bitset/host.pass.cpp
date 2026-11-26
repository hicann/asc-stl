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

// Exercise the unordered_set-first include order. The Device compile case includes unordered_map first.
#include <asc/std/unordered_set>

#include "../../../../support/b027_semantics.h"
#include "support/bitmap_mask_semantics.h"

static_assert(std::is_same_v<asc::std::bitset<65>::base::const_reference, bool>);

int main()
{
    const asc::std::bitset<65> initial;
    if (!initial.none() || initial.count() != 0)
        return 102;
    if (asc_stl_bitmap_mask_test::evaluate() != 0) {
        return 101;
    }
    return asc_stl_b027_test::evaluate_host();
}
