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

#ifndef CANN_ASC_STL_ASC_STD___DEQUE_DEQUE_H
#define CANN_ASC_STL_ASC_STD___DEQUE_DEQUE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <new>
#endif

#ifndef CANN_ASC_STL_DETAIL_PLACEMENT_NEW_DECLARED
#define CANN_ASC_STL_DETAIL_PLACEMENT_NEW_DECLARED
#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
CANN_ASC_STL_DEVICE_API void* operator new(__SIZE_TYPE__, void* address) noexcept
{
    return address;
}
#elif CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
void* operator new(__SIZE_TYPE__, void* address) noexcept;
#endif
#endif

namespace asc::std {

template <class T, class Allocator>
class deque {
    static constexpr __SIZE_TYPE__ elements_per_block = 4;
    static constexpr __SIZE_TYPE__ block_count = 4;
    static constexpr __SIZE_TYPE__ initial_position = 8;

    struct block {
        alignas(T) unsigned char storage[sizeof(T) * elements_per_block];
    };

    using block_allocator = typename Allocator::template rebind<block>::other;

public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = __SIZE_TYPE__;
    using difference_type = __PTRDIFF_TYPE__;
    using reference = T&;
    using const_reference = const T&;

    class iterator {
    public:
        using value_type = T;
        using difference_type = __PTRDIFF_TYPE__;
        using pointer = T*;
        using reference = T&;

        CANN_ASC_STL_API iterator() = default;
        CANN_ASC_STL_API iterator(deque* owner, size_type position) : owner_(owner), position_(position)
        {}
        CANN_ASC_STL_API reference operator*() const
        {
            return owner_->value_at(position_);
        }
        CANN_ASC_STL_API iterator& operator++()
        {
            ++position_;
            return *this;
        }
        CANN_ASC_STL_API iterator operator++(int)
        {
            iterator previous = *this;
            ++*this;
            return previous;
        }
        CANN_ASC_STL_API iterator& operator--()
        {
            --position_;
            return *this;
        }
        CANN_ASC_STL_API iterator& operator+=(difference_type offset)
        {
            position_ = static_cast<size_type>(static_cast<difference_type>(position_) + offset);
            return *this;
        }
        CANN_ASC_STL_API iterator& operator-=(difference_type offset)
        {
            return *this += -offset;
        }
        CANN_ASC_STL_API reference operator[](difference_type offset) const
        {
            iterator value = *this;
            value += offset;
            return *value;
        }
        friend CANN_ASC_STL_API iterator operator+(iterator value, difference_type offset)
        {
            value += offset;
            return value;
        }
        friend CANN_ASC_STL_API iterator operator-(iterator value, difference_type offset)
        {
            value -= offset;
            return value;
        }
        friend CANN_ASC_STL_API difference_type operator-(iterator left, iterator right)
        {
            return static_cast<difference_type>(left.position_) - static_cast<difference_type>(right.position_);
        }
        friend CANN_ASC_STL_API bool operator==(iterator left, iterator right)
        {
            return left.owner_ == right.owner_ && left.position_ == right.position_;
        }
        friend CANN_ASC_STL_API bool operator!=(iterator left, iterator right)
        {
            return !(left == right);
        }
        friend CANN_ASC_STL_API bool operator<(iterator left, iterator right)
        {
            return left.position_ < right.position_;
        }
        friend CANN_ASC_STL_API bool operator>(iterator left, iterator right)
        {
            return right < left;
        }

    private:
        deque* owner_ = nullptr;
        size_type position_ = 0;
    };

    CANN_ASC_STL_API explicit deque(const Allocator& allocator) noexcept : allocator_(allocator)
    {}
    deque(const deque&) = delete;
    deque& operator=(const deque&) = delete;
    deque(deque&&) = delete;
    deque& operator=(deque&&) = delete;
    CANN_ASC_STL_API ~deque()
    {
        release();
    }

    CANN_ASC_STL_API bool empty() const noexcept
    {
        return begin_ == end_;
    }
    CANN_ASC_STL_API size_type size() const noexcept
    {
        return end_ - begin_;
    }
    CANN_ASC_STL_API reference front() noexcept
    {
        return value_at(begin_);
    }
    CANN_ASC_STL_API const_reference front() const noexcept
    {
        return value_at(begin_);
    }
    CANN_ASC_STL_API reference back() noexcept
    {
        return value_at(end_ - 1);
    }
    CANN_ASC_STL_API const_reference back() const noexcept
    {
        return value_at(end_ - 1);
    }
    CANN_ASC_STL_API reference operator[](size_type index) noexcept
    {
        return value_at(begin_ + index);
    }
    CANN_ASC_STL_API const_reference operator[](size_type index) const noexcept
    {
        return value_at(begin_ + index);
    }
    CANN_ASC_STL_API iterator begin() noexcept
    {
        return iterator(this, begin_);
    }
    CANN_ASC_STL_API iterator end() noexcept
    {
        return iterator(this, end_);
    }
    CANN_ASC_STL_API void push_front(const T& value)
    {
        emplace_front(value);
    }
    CANN_ASC_STL_API void push_front(T&& value)
    {
        emplace_front(static_cast<T&&>(value));
    }
    CANN_ASC_STL_API void push_back(const T& value)
    {
        emplace_back(value);
    }
    CANN_ASC_STL_API void push_back(T&& value)
    {
        emplace_back(static_cast<T&&>(value));
    }
    template <class... Args>
    CANN_ASC_STL_API reference emplace_front(Args&&... args)
    {
        --begin_;
        T* address = address_at(begin_, true);
        ::new (static_cast<void*>(address)) T(static_cast<Args&&>(args)...);
        return *address;
    }
    template <class... Args>
    CANN_ASC_STL_API reference emplace_back(Args&&... args)
    {
        T* address = address_at(end_, true);
        ::new (static_cast<void*>(address)) T(static_cast<Args&&>(args)...);
        ++end_;
        return *address;
    }
    CANN_ASC_STL_API void pop_front()
    {
        address_at(begin_, false)->~T();
        ++begin_;
    }
    CANN_ASC_STL_API void pop_back()
    {
        --end_;
        address_at(end_, false)->~T();
    }
    CANN_ASC_STL_API void clear() noexcept
    {
        while (!empty())
            pop_back();
    }

private:
    CANN_ASC_STL_API T* address_at(size_type position, bool create)
    {
        const size_type block_index = position / elements_per_block;
        if (blocks_[block_index] == nullptr && create) {
            block_allocator blocks(allocator_);
            blocks_[block_index] = blocks.allocate(1);
        }
        unsigned char* bytes = blocks_[block_index]->storage;
        return reinterpret_cast<T*>(bytes) + position % elements_per_block;
    }
    CANN_ASC_STL_API const T* address_at(size_type position, bool) const
    {
        const size_type block_index = position / elements_per_block;
        const unsigned char* bytes = blocks_[block_index]->storage;
        return reinterpret_cast<const T*>(bytes) + position % elements_per_block;
    }
    CANN_ASC_STL_API reference value_at(size_type position)
    {
        return *address_at(position, false);
    }
    CANN_ASC_STL_API const_reference value_at(size_type position) const
    {
        return *address_at(position, false);
    }
    CANN_ASC_STL_API void release() noexcept
    {
        clear();
        block_allocator blocks(allocator_);
        for (size_type index = 0; index < block_count; ++index) {
            if (blocks_[index] != nullptr) {
                blocks.deallocate(blocks_[index], 1);
                blocks_[index] = nullptr;
            }
        }
        begin_ = initial_position;
        end_ = initial_position;
    }

    Allocator allocator_;
    block* blocks_[block_count]{};
    size_type begin_ = initial_position;
    size_type end_ = initial_position;
};

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___DEQUE_DEQUE_H
