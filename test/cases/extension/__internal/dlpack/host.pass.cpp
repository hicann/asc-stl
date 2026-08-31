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

#include <asc/__internal/dlpack.h>
#include <iostream>

static int g_failures = 0;

[[maybe_unused]] static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][dlpack] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

[[maybe_unused]] static void expect_eq_int(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][dlpack] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
#if CANN_ASC_STL_DETAIL_ACCL_HAS_DLPACK()
    std::cout << "[host][dlpack] DLPack support is enabled" << std::endl;

    // The header enforces DLPACK_MAJOR_VERSION == 1
    expect_eq_int("DLPACK_MAJOR_VERSION", DLPACK_MAJOR_VERSION, 1);

    // CANN_ASC_STL_DETAIL_ACCL_DLPACK_AT_LEAST should be true for (1, 0) and false for (2, 0)
    expect_true("CANN_ASC_STL_DETAIL_ACCL_DLPACK_AT_LEAST(1, 0)", CANN_ASC_STL_DETAIL_ACCL_DLPACK_AT_LEAST(1, 0));
    expect_true("!CANN_ASC_STL_DETAIL_ACCL_DLPACK_AT_LEAST(2, 0)", !CANN_ASC_STL_DETAIL_ACCL_DLPACK_AT_LEAST(2, 0));

    // CANN_ASC_STL_DETAIL_ACCL_DLPACK_BELOW is the negation of CANN_ASC_STL_DETAIL_ACCL_DLPACK_AT_LEAST
    expect_true("!CANN_ASC_STL_DETAIL_ACCL_DLPACK_BELOW(1, 0)", !CANN_ASC_STL_DETAIL_ACCL_DLPACK_BELOW(1, 0));
    expect_true("CANN_ASC_STL_DETAIL_ACCL_DLPACK_BELOW(2, 0)", CANN_ASC_STL_DETAIL_ACCL_DLPACK_BELOW(2, 0));

    // Verify DLDevice and DLTensor types are available from the included dlpack.h
    DLDevice dev;
    dev.device_type = kDLCPU;
    dev.device_id = 0;
    expect_eq_int("dev.device_type == kDLCPU", static_cast<int>(dev.device_type), static_cast<int>(kDLCPU));
    expect_eq_int("dev.device_id == 0", dev.device_id, 0);

    DLTensor tensor;
    tensor.data = nullptr;
    tensor.device = dev;
    tensor.ndim = 1;
    tensor.dtype.code = kDLFloat;
    tensor.dtype.bits = 32;
    tensor.dtype.lanes = 1;
    tensor.shape = nullptr;
    tensor.strides = nullptr;
    tensor.byte_offset = 0;
    expect_eq_int("tensor.ndim == 1", tensor.ndim, 1);
    expect_eq_int("tensor.dtype.code == kDLFloat", static_cast<int>(tensor.dtype.code), static_cast<int>(kDLFloat));
    expect_eq_int("tensor.dtype.bits == 32", tensor.dtype.bits, 32);
#else
    std::cout << "[host][dlpack] DLPack support is disabled (CANN_ASC_STL_DETAIL_ACCL_HAS_DLPACK() == 0)" << std::endl;
    // When DLPack is not available, the header should still compile without error.
    // Nothing to test functionally, but compilation success is itself a pass.
#endif

    return g_failures == 0 ? 0 : 1;
}
