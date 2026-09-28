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

#include <asc/std/atomic>
#include <asc/std/ccomplex>
#include <asc/std/__algorithm/find_if.h>
#include <asc/std/__algorithm/transform.h>
#include <asc/std/__algorithm/replace_copy.h>

int asc_stl_b022_consumer_b()
{
    asc::std::atomic_llong counter{1};
    if (counter.exchange(4) != 1 || counter.load() != 4) {
        return 1;
    }
    asc::std::atomic_flag flag = CANN_ASC_STL_ATOMIC_FLAG_INIT;
    if (flag.test_and_set()) {
        return 2;
    }
    const int data[] = {1, 2, 3, 4};
    const int* located = asc::std::find_if(data, data + 4, [](int value) { return value == 3; });
    if (located != data + 2) {
        return 3;
    }
    int mapped[4] = {};
    const int* transformed = asc::std::transform(  // NOLINT(build/include_what_you_use)
        data, data + 4, mapped, [](int value) { return value * value; });
    if (transformed != mapped + 4) {
        return 4;
    }
    if (mapped[2] != 9) {
        return 5;
    }
    int replaced[4] = {};
    asc::std::replace_copy(data, data + 4, replaced, 2, 9);
    if (replaced[1] != 9 || replaced[2] != 3) {
        return 6;
    }
    return asc::std::abs(asc::std::complex<float>(3.0f, 4.0f)) == 5.0f ? 0 : 7;
}
