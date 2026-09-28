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

#ifndef ASC_STL_TEST_DLPACK_DLPACK_H
#define ASC_STL_TEST_DLPACK_DLPACK_H

#include <stdint.h>

typedef enum { kDLCPU = 1, kDLExtDev = 12 } DLDeviceType;
typedef struct {
    DLDeviceType device_type;
    int32_t device_id;
} DLDevice;
typedef enum { kDLInt = 0, kDLUInt = 1, kDLFloat = 2 } DLDataTypeCode;
typedef struct {
    uint8_t code;
    uint8_t bits;
    uint16_t lanes;
} DLDataType;
typedef struct {
    void* data;
    DLDevice device;
    int32_t ndim;
    DLDataType dtype;
    int64_t* shape;
    int64_t* strides;
    uint64_t byte_offset;
} DLTensor;

#endif  // ASC_STL_TEST_DLPACK_DLPACK_H
