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

#ifndef ASC_STL_TEST_DLPACK_REVIEW_REGRESSION_H
#define ASC_STL_TEST_DLPACK_REVIEW_REGRESSION_H

#include <asc/mdspan>

#if defined(CANN_ASC_STL_HAS_DLPACK) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
namespace asc_stl_dlpack_review {
inline bool evaluate()
{
    int values[6] = {10, 20, 30, 40, 50, 60};
    using extents_type = asc::std::dextents<asc::std::size_t, 1>;
    const extents_type extents(3);
    using mapping_type = asc::layout_stride_relaxed::mapping<extents_type>;
    mapping_type mapping(extents, asc::steps<1>(1), 2);
    asc::host_mdspan<int, extents_type, asc::layout_stride_relaxed> offset(values, mapping);
    asc::dlpack_tensor<1> exported;
    if (!asc::to_dlpack_tensor(offset, kDLCPU, 0, exported) || exported.get().data != values + 2)
        return false;
    int64_t shape[1] = {3};
    int64_t strides[1] = {-1};
    DLTensor tensor{};
    tensor.data = values + 4;
    tensor.device = DLDevice{kDLCPU, 0};
    tensor.ndim = 1;
    tensor.dtype = DLDataType{static_cast<uint8_t>(kDLInt), 32, 1};
    tensor.shape = shape;
    tensor.strides = strides;
    asc::host_mdspan<int, extents_type, asc::layout_stride_relaxed> reversed;
    if (!asc::to_host_mdspan<int, 1>(tensor, reversed) || reversed[0] != 50 || reversed[1] != 40 || reversed[2] != 30)
        return false;
    if (!asc::to_dlpack_tensor(reversed, kDLCPU, 0, exported) || exported.get().data != values + 4 ||
        exported.get().strides[0] != -1)
        return false;
    tensor.device.device_type = kDLExtDev;
    asc::gm_mdspan<int, extents_type, asc::layout_stride_relaxed> gm;
    if (!asc::to_gm_mdspan<int, 1>(tensor, gm) || gm[0] != 50 || gm[2] != 30)
        return false;
    tensor.device.device_type = kDLCPU;
    shape[0] = 3;
    strides[0] = __PTRDIFF_MAX__;
    const int* retained = reversed.data_handle();
    return !asc::to_host_mdspan<int, 1>(tensor, reversed) && reversed.data_handle() == retained;
}
}  // namespace asc_stl_dlpack_review
#endif

#endif  // ASC_STL_TEST_DLPACK_REVIEW_REGRESSION_H
