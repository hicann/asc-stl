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

#include <asc/__memory/buffers.h>

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
        // Alignments are powers of two by contract (same rule as the buffer
        // and resource layers); rejecting here keeps the acquire-side
        // divisibility check exact. A magnitude comparison such as
        // block.alignment >= alignment is only equivalent to it when both
        // sides are powers of two.
        // Inlined from buffer_alignment_valid: this host-side entry cannot call the
        // dual-attributes helper under pure SIMT (host -> aicore is rejected),
        // and the rule is two arithmetic lines.
        if (pointer == nullptr || bytes == 0 || alignment == 0 || (alignment & (alignment - 1)) != 0)
            return false;
        // Slots must not grow monotonically. The steady-state recycle cycle
        // driven by the pool frontend (register, acquire, complete, register
        // the same pointer again) refreshes the existing entry instead of
        // appending a fresh slot; otherwise the bounded table saturates and
        // the pool silently degrades into a non-caching allocator.
        __SIZE_TYPE__ index = size_;
        for (__SIZE_TYPE__ scan = 0; scan != size_; ++scan) {
            if (blocks_[scan].pointer == pointer) {
                index = scan;
                break;
            }
        }
        if (index == size_ && size_ == Capacity) {
            // Table full: reclaim an entry whose block is not available. Such
            // an entry only matters if the same pointer is registered again,
            // which lands in the refresh path above, so overwriting it is
            // lossless for the cache.
            for (__SIZE_TYPE__ scan = 0; scan != size_; ++scan) {
                if (!blocks_[scan].available) {
                    index = scan;
                    break;
                }
            }
            if (index == size_)
                return false;
        }
        if (index == size_) {
            blocks_[size_++] = {pointer, bytes, alignment, 0, true};
            total_bytes_ += bytes;
            return true;
        }
        pool_block& block = blocks_[index];
        total_bytes_ -= block.bytes;
        total_bytes_ += bytes;
        block.pointer = pointer;
        block.bytes = bytes;
        block.alignment = alignment;
        block.completion_token = 0;
        block.available = true;
        return true;
    }

    CANN_ASC_STL_HOST_API constexpr void* acquire(
        __SIZE_TYPE__ bytes, __SIZE_TYPE__ alignment, unsigned long long completed_token) noexcept
    {
        // Alignment sufficiency is divisibility, not magnitude: a block is
        // usable for a request only when its alignment is a multiple of the
        // requested one (every registered alignment is a power of two, so a
        // zero or non-power-of-two request never matches).
        for (__SIZE_TYPE__ index = 0; index != size_; ++index) {
            pool_block& block = blocks_[index];
            if (block.available && block.completion_token <= completed_token && block.bytes >= bytes &&
                alignment != 0 && block.alignment % alignment == 0) {
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
