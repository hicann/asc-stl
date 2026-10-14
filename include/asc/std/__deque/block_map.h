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

#ifndef CANN_ASC_STL_ASC_STD___DEQUE_BLOCK_MAP_H
#define CANN_ASC_STL_ASC_STD___DEQUE_BLOCK_MAP_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace detail {

// Fixed-capacity block table backing asc::std::deque: a fixed number of
// block slots, each lazily allocated from the block allocator on first use
// and all released when the table is destroyed.  Growth beyond the table is
// rejected by the owning container, keeping indexing bounds-checkable.
template <class Block, __SIZE_TYPE__ BlockCount, class Allocator>
class deque_block_map {
    using block_allocator = typename Allocator::template rebind<Block>::other;

public:
    CANN_ASC_STL_API explicit deque_block_map(const Allocator& allocator) noexcept : allocator_(allocator)
    {}
    deque_block_map(const deque_block_map&) = delete;
    deque_block_map& operator=(const deque_block_map&) = delete;
    CANN_ASC_STL_API ~deque_block_map()
    {
        release();
    }

    // Returns the block stored at index without allocating; nullptr when the
    // slot has not been populated yet.
    CANN_ASC_STL_API Block* at(__SIZE_TYPE__ index) const noexcept
    {
        return blocks_[index];
    }
    // Returns the block stored at index, allocating it on first use.  A
    // nullptr result reports allocator failure; the caller diagnoses it.
    CANN_ASC_STL_API Block* ensure_allocated(__SIZE_TYPE__ index)
    {
        if (blocks_[index] == nullptr) {
            block_allocator blocks(allocator_);
            blocks_[index] = blocks.allocate(1);
        }
        return blocks_[index];
    }
    CANN_ASC_STL_API void release() noexcept
    {
        block_allocator blocks(allocator_);
        for (__SIZE_TYPE__ index = 0; index < BlockCount; ++index) {
            if (blocks_[index] != nullptr) {
                blocks.deallocate(blocks_[index], 1);
                blocks_[index] = nullptr;
            }
        }
    }

private:
    Allocator allocator_;
    Block* blocks_[BlockCount]{};
};

}  // namespace detail

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___DEQUE_BLOCK_MAP_H
