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

#ifndef ASC_STL_TEST_CTIME_RUNTIME_TIME_FIELDS_H
#define ASC_STL_TEST_CTIME_RUNTIME_TIME_FIELDS_H

#include <asc/std/ctime>
#include <asc/std/type_traits>

namespace asc_stl_time_fields_test {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
static_assert(asc::std::is_same_v<asc::std::clock_t, long long>);
static_assert(asc::std::is_same_v<asc::std::time_t, long long>);
static_assert(asc::std::is_same_v<asc::std::size_t, __SIZE_TYPE__>);
static_assert(asc::std::is_same_v<decltype(asc::std::timespec::tv_sec), asc::std::time_t>);
static_assert(asc::std::is_same_v<decltype(asc::std::timespec::tv_nsec), long>);
static_assert(TIME_UTC == 1);
#endif

template <class OutputPointer>
CANN_ASC_STL_API void write_fields(OutputPointer output, asc::std::clock_t ticks)
{
    const int sample = static_cast<int>(ticks & 0x3fff);
    volatile asc::std::timespec stamp{};
    stamp.tv_sec = -37 - sample;
    stamp.tv_nsec = 1234567 + sample;
    output[1] = sample;
    output[2] = static_cast<int>(stamp.tv_sec);
    output[3] = static_cast<int>(stamp.tv_nsec);
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
inline bool matches(const int (&result)[4])
{
    return result[0] == 0 && result[1] >= 0 && result[1] <= 0x3fff && result[2] == -37 - result[1] &&
        result[3] == 1234567 + result[1];
}
#endif
}  // namespace asc_stl_time_fields_test

#endif  // ASC_STL_TEST_CTIME_RUNTIME_TIME_FIELDS_H
