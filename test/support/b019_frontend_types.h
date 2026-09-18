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

#ifndef ASC_STL_TEST_B019_FRONTEND_TYPES_H
#define ASC_STL_TEST_B019_FRONTEND_TYPES_H

#include <asc/__algorithm/frontend.h>

namespace asc_stl_b019_compile {

struct plus_one {
    __aicore__ int operator()(int value) const noexcept
    {
        return value + 1;
    }
};
struct plus_int {
    __aicore__ int operator()(int left, int right) const noexcept
    {
        return left + right;
    }
};
struct less_int {
    __aicore__ bool operator()(int left, int right) const noexcept
    {
        return left < right;
    }
};
struct equal_int {
    __aicore__ bool operator()(int left, int right) const noexcept
    {
        return left == right;
    }
};
struct positive_int {
    __aicore__ bool operator()(int value) const noexcept
    {
        return value > 0;
    }
};
struct generate_int {
    __aicore__ int operator()() const noexcept
    {
        return 1;
    }
};

struct arguments {
    asc::device_policy policy;
    int* input;
    int* output;
    int* scalar;

    asc::std::size_t* count() const noexcept
    {
        return reinterpret_cast<asc::std::size_t*>(scalar);
    }
    asc::std::uint32_t* flag() const noexcept
    {
        return reinterpret_cast<asc::std::uint32_t*>(scalar);
    }
};

}  // namespace asc_stl_b019_compile

#endif  // ASC_STL_TEST_B019_FRONTEND_TYPES_H
