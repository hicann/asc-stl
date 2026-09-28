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

#ifndef CANN_ASC_STL_ASC___MEMORY_POOLS_H
#define CANN_ASC_STL_ASC___MEMORY_POOLS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {

struct pool_block {
    void* pointer{};
    __SIZE_TYPE__ bytes{};
    __SIZE_TYPE__ alignment{};
    unsigned long long completion_token{};
    bool available{};
};

struct pool_statistics {
    __SIZE_TYPE__ registered_blocks{};
    __SIZE_TYPE__ available_blocks{};
    __SIZE_TYPE__ bytes{};
    __SIZE_TYPE__ reuse_hits{};
    __SIZE_TYPE__ reuse_misses{};
};

template <__SIZE_TYPE__ Capacity>
class software_pool {
public:
    CANN_ASC_STL_HOST_API constexpr bool register_block(
        void* pointer, __SIZE_TYPE__ bytes, __SIZE_TYPE__ alignment = alignof(void*)) noexcept
    {
        if (pointer == nullptr || bytes == 0 || size_ == Capacity)
            return false;
        blocks_[size_++] = {pointer, bytes, alignment, 0, true};
        total_bytes_ += bytes;
        return true;
    }

    CANN_ASC_STL_HOST_API constexpr void* acquire(
        __SIZE_TYPE__ bytes, __SIZE_TYPE__ alignment, unsigned long long completed_token) noexcept
    {
        for (__SIZE_TYPE__ index = 0; index != size_; ++index) {
            pool_block& block = blocks_[index];
            if (block.available && block.completion_token <= completed_token && block.bytes >= bytes &&
                block.alignment >= alignment) {
                block.available = false;
                ++reuse_hits_;
                return block.pointer;
            }
        }
        ++reuse_misses_;
        return nullptr;
    }

    CANN_ASC_STL_HOST_API constexpr bool release(void* pointer, unsigned long long completion_token) noexcept
    {
        for (__SIZE_TYPE__ index = 0; index != size_; ++index) {
            pool_block& block = blocks_[index];
            if (block.pointer == pointer && !block.available) {
                block.completion_token = completion_token;
                block.available = true;
                return true;
            }
        }
        return false;
    }

    CANN_ASC_STL_HOST_API constexpr pool_statistics statistics(unsigned long long completed_token) const noexcept
    {
        pool_statistics result{size_, 0, total_bytes_, reuse_hits_, reuse_misses_};
        for (__SIZE_TYPE__ index = 0; index != size_; ++index)
            result.available_blocks += blocks_[index].available && blocks_[index].completion_token <= completed_token;
        return result;
    }

private:
    pool_block blocks_[Capacity == 0 ? 1 : Capacity]{};
    __SIZE_TYPE__ size_{};
    __SIZE_TYPE__ total_bytes_{};
    __SIZE_TYPE__ reuse_hits_{};
    __SIZE_TYPE__ reuse_misses_{};
};

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___MEMORY_POOLS_H
