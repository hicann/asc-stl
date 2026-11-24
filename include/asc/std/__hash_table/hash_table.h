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

#ifndef CANN_ASC_STL_ASC_STD___HASH_TABLE_HASH_TABLE_H
#define CANN_ASC_STL_ASC_STD___HASH_TABLE_HASH_TABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_same.h>

namespace asc::std {

#ifndef CANN_ASC_STL_DETAIL_ARENA_ASSOCIATIVE_SHARED
#define CANN_ASC_STL_DETAIL_ARENA_ASSOCIATIVE_SHARED
template <class First, class Second>
struct __arena_pair {
    First first;
    Second second;

    CANN_ASC_STL_API __arena_pair() = default;
    template <class Left, class Right>
    CANN_ASC_STL_API __arena_pair(Left&& left, Right&& right)
        : first(static_cast<Left&&>(left)), second(static_cast<Right&&>(right))
    {}
};

namespace __arena_associative_detail {

template <class Key>
struct identity_key {
    CANN_ASC_STL_API const Key& operator()(const Key& value) const noexcept
    {
        return value;
    }
};

template <class Key, class Mapped>
struct __arena_pair_key {
    CANN_ASC_STL_API const Key& operator()(const __arena_pair<const Key, Mapped>& value) const noexcept
    {
        return value.first;
    }
};
}  // namespace __arena_associative_detail
#endif

#ifndef CANN_ASC_STL_DETAIL_ARENA_HASH_IMPLEMENTATION
#define CANN_ASC_STL_DETAIL_ARENA_HASH_IMPLEMENTATION
namespace __arena_associative_detail {

template <class Key, class Value, class KeyOfValue, class Hash, class Equal, class Allocator>
class basic_hash_table {
    struct node {
        node* next;
        node* iteration_next;
        Value value;
        template <class Input>
        CANN_ASC_STL_API node(node* successor, node* iteration_successor, Input&& input)
            : next(successor), iteration_next(iteration_successor), value(static_cast<Input&&>(input))
        {}
    };
    using node_allocator = typename Allocator::template rebind<node>::other;
    using bucket_allocator = typename Allocator::template rebind<node*>::other;

public:
    using size_type = __SIZE_TYPE__;

    class iterator {
        // A set stores the key itself. A map stores a pair with a const key.
        using element_type = conditional_t<is_same_v<Key, Value>, const Value, Value>;

    public:
        CANN_ASC_STL_API iterator() = default;
        CANN_ASC_STL_API explicit iterator(node* current) : current_(current)
        {}
        CANN_ASC_STL_API element_type& operator*() const
        {
            return current_->value;
        }
        CANN_ASC_STL_API element_type* operator->() const
        {
            return ::asc::std::addressof(current_->value);
        }
        CANN_ASC_STL_API iterator& operator++()
        {
            current_ = current_->iteration_next;
            return *this;
        }
        friend CANN_ASC_STL_API bool operator==(iterator left, iterator right)
        {
            return left.current_ == right.current_;
        }
        friend CANN_ASC_STL_API bool operator!=(iterator left, iterator right)
        {
            return !(left == right);
        }

    private:
        node* current_ = nullptr;
    };

    CANN_ASC_STL_API basic_hash_table(const Hash& hash, const Equal& equal, const Allocator& allocator)
        : hash_(hash), equal_(equal), allocator_(allocator)
    {
        initialize_buckets(8);
    }
    basic_hash_table(const basic_hash_table&) = delete;
    basic_hash_table& operator=(const basic_hash_table&) = delete;
    CANN_ASC_STL_API basic_hash_table(basic_hash_table&& other) noexcept
        : hash_(other.hash_), equal_(other.equal_), allocator_(other.allocator_), size_(other.size_)
    {
        take_buckets(other);
    }
    CANN_ASC_STL_API basic_hash_table& operator=(basic_hash_table&& other) noexcept
    {
        if (this != &other) {
            clear();
            release_buckets();
            hash_ = other.hash_;
            equal_ = other.equal_;
            allocator_ = other.allocator_;
            size_ = other.size_;
            take_buckets(other);
        }
        return *this;
    }
    CANN_ASC_STL_API ~basic_hash_table()
    {
        clear();
        release_buckets();
    }

    CANN_ASC_STL_API bool empty() const noexcept
    {
        return size_ == 0;
    }
    CANN_ASC_STL_API size_type size() const noexcept
    {
        return size_;
    }
    CANN_ASC_STL_API size_type bucket_count() const noexcept
    {
        return buckets_count_;
    }
    CANN_ASC_STL_API iterator begin() noexcept
    {
        return iterator(iteration_head_);
    }
    CANN_ASC_STL_API iterator end() noexcept
    {
        return iterator(nullptr);
    }
    template <class Input>
    CANN_ASC_STL_API __arena_pair<iterator, bool> insert(Input&& input)
    {
        const Key& key = key_of_(input);
        if (buckets_count_ == 0 && !initialize_buckets(8)) {
            return __arena_pair<iterator, bool>(end(), false);
        }
        const size_type hash = hash_(key);
        size_type bucket = bucket_index(hash, buckets_count_);
        node* current = buckets_[bucket];
        while (current != nullptr) {
            if (equal_(key_of_(current->value), key)) {
                return __arena_pair<iterator, bool>(iterator(current), false);
            }
            current = current->next;
        }
        if (size_ + 1 > buckets_count_) {
            if (!rehash_to(buckets_count_ * 2)) {
                return __arena_pair<iterator, bool>(end(), false);
            }
            bucket = bucket_index(hash, buckets_count_);
        }
        node_allocator nodes(allocator_);
        node* created = nodes.allocate(1);
        ::new (static_cast<void*>(created)) node(buckets_[bucket], iteration_head_, static_cast<Input&&>(input));
        buckets_[bucket] = created;
        iteration_head_ = created;
        ++size_;
        return __arena_pair<iterator, bool>(iterator(created), true);
    }
    CANN_ASC_STL_API iterator find(const Key& key) noexcept
    {
        if (buckets_count_ == 0)
            return end();
        const size_type bucket = bucket_index(hash_(key), buckets_count_);
        node* current = buckets_[bucket];
        while (current != nullptr) {
            if (equal_(key_of_(current->value), key)) {
                return iterator(current);
            }
            current = current->next;
        }
        return end();
    }
    CANN_ASC_STL_API size_type count(const Key& key) noexcept
    {
        return find(key) == end() ? 0 : 1;
    }
    CANN_ASC_STL_API void clear() noexcept
    {
        node_allocator nodes(allocator_);
        node* current = iteration_head_;
        while (current != nullptr) {
            node* next = current->iteration_next;
            current->~node();
            nodes.deallocate(current, 1);
            current = next;
        }
        for (size_type bucket = 0; bucket < buckets_count_; ++bucket) {
            buckets_[bucket] = nullptr;
        }
        iteration_head_ = nullptr;
        size_ = 0;
    }

private:
    CANN_ASC_STL_API static constexpr size_type bucket_index(size_type hash, size_type count) noexcept
    {
        // The first allocation has eight buckets and each rehash doubles that count, so count is a power of two.
        return hash & (count - 1);
    }

    CANN_ASC_STL_API bool initialize_buckets(size_type count)
    {
        bucket_allocator bucket_nodes(allocator_);
        node** created = bucket_nodes.allocate(count);
        if (created == nullptr)
            return false;
        for (size_type bucket = 0; bucket < count; ++bucket)
            created[bucket] = nullptr;
        buckets_ = created;
        buckets_count_ = count;
        return true;
    }

    CANN_ASC_STL_API bool rehash_to(size_type count)
    {
        if (count == 0) {
            return false;
        }
        bucket_allocator bucket_nodes(allocator_);
        node** replacement = bucket_nodes.allocate(count);
        if (replacement == nullptr)
            return false;
        for (size_type bucket = 0; bucket < count; ++bucket)
            replacement[bucket] = nullptr;
        node* current = iteration_head_;
        while (current != nullptr) {
            const size_type bucket = bucket_index(hash_(key_of_(current->value)), count);
            current->next = replacement[bucket];
            replacement[bucket] = current;
            current = current->iteration_next;
        }
        if (buckets_ != nullptr)
            bucket_nodes.deallocate(buckets_, buckets_count_);
        buckets_ = replacement;
        buckets_count_ = count;
        return true;
    }

    CANN_ASC_STL_API void release_buckets() noexcept
    {
        if (buckets_ != nullptr) {
            bucket_allocator bucket_nodes(allocator_);
            bucket_nodes.deallocate(buckets_, buckets_count_);
            buckets_ = nullptr;
            buckets_count_ = 0;
        }
    }

    CANN_ASC_STL_API void take_buckets(basic_hash_table& other) noexcept
    {
        buckets_ = other.buckets_;
        buckets_count_ = other.buckets_count_;
        iteration_head_ = other.iteration_head_;
        other.buckets_ = nullptr;
        other.buckets_count_ = 0;
        other.iteration_head_ = nullptr;
        other.size_ = 0;
    }
    Hash hash_;
    Equal equal_;
    Allocator allocator_;
    KeyOfValue key_of_{};
    node** buckets_ = nullptr;
    size_type buckets_count_ = 0;
    node* iteration_head_ = nullptr;
    size_type size_ = 0;
};

}  // namespace __arena_associative_detail
#endif

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___HASH_TABLE_HASH_TABLE_H
