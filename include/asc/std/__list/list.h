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

#ifndef CANN_ASC_STL_ASC_STD___LIST_LIST_H
#define CANN_ASC_STL_ASC_STD___LIST_LIST_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__exception/terminate.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__list/node.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__new/nonallocating_new.h>

namespace asc::std {

template <class T, class Allocator>
class list {
    using node = detail::list_node<T>;
    using node_allocator = typename Allocator::template rebind<node>::other;
    using node_pointer = typename node_allocator::pointer;

public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = __SIZE_TYPE__;
    using reference = T&;
    using const_reference = const T&;

    class iterator {
    public:
        using iterator_category = bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = __PTRDIFF_TYPE__;
        using pointer = T*;
        using reference = T&;

        CANN_ASC_STL_HOST_SIMT_API iterator() = default;
        CANN_ASC_STL_HOST_SIMT_API iterator(list* owner, node* current) : owner_(owner), current_(current)
        {}
        CANN_ASC_STL_HOST_SIMT_API reference operator*() const
        {
            return current_->value;
        }
        CANN_ASC_STL_HOST_SIMT_API pointer operator->() const
        {
            return &current_->value;
        }
        CANN_ASC_STL_HOST_SIMT_API iterator& operator++()
        {
            current_ = current_->next;
            return *this;
        }
        CANN_ASC_STL_HOST_SIMT_API iterator operator++(int)
        {
            iterator previous = *this;
            ++*this;
            return previous;
        }
        CANN_ASC_STL_HOST_SIMT_API iterator& operator--()
        {
            current_ = current_ == nullptr ? owner_->tail_ : current_->previous;
            return *this;
        }
        CANN_ASC_STL_HOST_SIMT_API iterator operator--(int)
        {
            iterator previous = *this;
            --*this;
            return previous;
        }
        friend CANN_ASC_STL_HOST_SIMT_API bool operator==(iterator left, iterator right)
        {
            return left.current_ == right.current_;
        }
        friend CANN_ASC_STL_HOST_SIMT_API bool operator!=(iterator left, iterator right)
        {
            return !(left == right);
        }

    private:
        list* owner_ = nullptr;
        node* current_ = nullptr;
    };

    CANN_ASC_STL_HOST_SIMT_API explicit list(const Allocator& allocator) noexcept : allocator_(allocator)
    {}
    list(const list&) = delete;
    list& operator=(const list&) = delete;
    CANN_ASC_STL_HOST_SIMT_API list(list&& other) noexcept
        : allocator_(other.allocator_), head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    CANN_ASC_STL_HOST_SIMT_API list& operator=(list&& other) noexcept
    {
        if (this != &other) {
            clear();
            allocator_ = other.allocator_;
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    CANN_ASC_STL_HOST_SIMT_API ~list()
    {
        clear();
    }

    CANN_ASC_STL_HOST_SIMT_API bool empty() const noexcept
    {
        return size_ == 0;
    }
    CANN_ASC_STL_HOST_SIMT_API size_type size() const noexcept
    {
        return size_;
    }
    CANN_ASC_STL_HOST_SIMT_API reference front() noexcept
    {
        return head_->value;
    }
    CANN_ASC_STL_HOST_SIMT_API const_reference front() const noexcept
    {
        return head_->value;
    }
    CANN_ASC_STL_HOST_SIMT_API reference back() noexcept
    {
        return tail_->value;
    }
    CANN_ASC_STL_HOST_SIMT_API const_reference back() const noexcept
    {
        return tail_->value;
    }
    CANN_ASC_STL_HOST_SIMT_API iterator begin() noexcept
    {
        return iterator(this, head_);
    }
    CANN_ASC_STL_HOST_SIMT_API iterator end() noexcept
    {
        return iterator(this, nullptr);
    }
    CANN_ASC_STL_HOST_SIMT_API void push_front(const T& value)
    {
        emplace_front(value);
    }
    CANN_ASC_STL_HOST_SIMT_API void push_front(T&& value)
    {
        emplace_front(static_cast<T&&>(value));
    }
    CANN_ASC_STL_HOST_SIMT_API void push_back(const T& value)
    {
        emplace_back(value);
    }
    CANN_ASC_STL_HOST_SIMT_API void push_back(T&& value)
    {
        emplace_back(static_cast<T&&>(value));
    }
    template <class... Args>
    CANN_ASC_STL_HOST_SIMT_API reference emplace_front(Args&&... args)
    {
        node* created = make_node(nullptr, head_, static_cast<Args&&>(args)...);
        if (head_ != nullptr)
            head_->previous = created;
        else
            tail_ = created;
        head_ = created;
        ++size_;
        return created->value;
    }
    template <class... Args>
    CANN_ASC_STL_HOST_SIMT_API reference emplace_back(Args&&... args)
    {
        node* created = make_node(tail_, nullptr, static_cast<Args&&>(args)...);
        if (tail_ != nullptr)
            tail_->next = created;
        else
            head_ = created;
        tail_ = created;
        ++size_;
        return created->value;
    }
    CANN_ASC_STL_HOST_SIMT_API void pop_front()
    {
        if (head_ == nullptr) {
            // Popping an empty list violates the precondition; fail with a
            // diagnostic instead of dereferencing null.
            ::asc::std::terminate();
        }
        node* removed = head_;
        head_ = removed->next;
        if (head_ != nullptr)
            head_->previous = nullptr;
        else
            tail_ = nullptr;
        destroy_node(removed);
        --size_;
    }
    CANN_ASC_STL_HOST_SIMT_API void pop_back()
    {
        if (tail_ == nullptr) {
            // Popping an empty list violates the precondition; fail with a
            // diagnostic instead of dereferencing null.
            ::asc::std::terminate();
        }
        node* removed = tail_;
        tail_ = removed->previous;
        if (tail_ != nullptr)
            tail_->next = nullptr;
        else
            head_ = nullptr;
        destroy_node(removed);
        --size_;
    }
    CANN_ASC_STL_HOST_SIMT_API void clear() noexcept
    {
        while (head_ != nullptr)
            pop_front();
    }

private:
    CANN_ASC_STL_HOST_SIMT_API void raise_allocation_failure() const
    {
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        throw ::std::bad_alloc();
#else
        ::asc::std::terminate();
#endif
    }
    template <class... Args>
    CANN_ASC_STL_HOST_SIMT_API node* make_node(node* before, node* after, Args&&... args)
    {
        node_allocator nodes(allocator_);
        node_pointer created = nodes.allocate(1);
        if (created == nullptr)
            raise_allocation_failure();
        // Links are raw node*: reach through the allocated pointer just for
        // construction and deallocation.
        ::new (static_cast<void*>(::asc::std::to_address(created))) node(before, after, static_cast<Args&&>(args)...);
        return ::asc::std::to_address(created);
    }
    CANN_ASC_STL_HOST_SIMT_API void destroy_node(node* removed)
    {
        node_allocator nodes(allocator_);
        removed->~node();
        nodes.deallocate(::asc::std::pointer_traits<node_pointer>::pointer_to(*removed), 1);
    }

    Allocator allocator_;
    node* head_ = nullptr;
    node* tail_ = nullptr;
    size_type size_ = 0;
};

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___LIST_LIST_H
