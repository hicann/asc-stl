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

// auto-workload=fast (n=64, cores=1, inputs=1, outputs=1, dtype=int32_t)
#include <iostream>
#include <vector>

#include "acl_runtime.h"
#include "launcher.h"

namespace {

constexpr size_t kElementCount = 64;

struct Main : public asc_stl_test::CannsimCaseBase<Main, int32_t, kElementCount, 1, 1> {
public:
    void InitializeInput()
    {
        auto& h_in0 = buffers_.input(0);
        auto& h_x = h_in0;
        std::vector<int32_t> h_y(kElementCount, static_cast<int32_t>(0));

        (void)h_x;
        (void)h_y;
        for (size_t i = 0; i < kElementCount; ++i) {
            {
                h_in0[i] = static_cast<int32_t>(i);
            }
        }
    }

    bool Launch(aclrtStream stream) const
    {
        return asc_stl_test::CheckAcl(asc_std_blsr_do(1, stream, static_cast<uint8_t*>(buffers_.device_input(0)),
                                          static_cast<uint8_t*>(buffers_.device_output(0))),
            "asc_std_blsr_do launch");
    }

    bool Verify() const
    {
        return VerifyElements("blsr");
    }

    void VerifyElement(size_t index, int64_t print_samples, size_t* mismatches) const
    {
        const int32_t in0_ref = buffers_.input(0)[index];
        const int32_t x_ref = in0_ref;
        const int32_t y_ref = static_cast<int32_t>(0);
        (void)x_ref;
        (void)y_ref;
        (void)in0_ref;
        int32_t expected0 = static_cast<int32_t>(0);
        int32_t& expected = expected0;
        (void)expected;
        (void)expected0;
        {
            expected0 = in0_ref & (in0_ref - 1);
        }
        CheckOutput0(index, print_samples, expected0, mismatches);
    }

    void CheckOutput0(size_t index, int64_t limit, int32_t expected, size_t* mismatches) const
    {
        if (limit < 0 || static_cast<int64_t>(index) < limit) {
            std::cout << "[kernel][blsr][" << index << "]" << " in0=" << buffers_.input(0)[index]
                      << " got=" << buffers_.output(0)[index] << " expected=" << expected << '\n';
        }
        asc_stl_test::RecordOutputMismatch(index, 0, buffers_.output(0)[index], expected, mismatches);
    }
};

}  // namespace

int main()
{
    Main test_case;
    return asc_stl_test::RunCannsimCase(
        &test_case, "ASC_STL_CANNSIM_BLSR_PASS", "kernel simulation verification passed.");
}
