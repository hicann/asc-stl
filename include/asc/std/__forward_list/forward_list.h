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

#ifndef CANN_ASC_STL_ASC_STD___FORWARD_LIST_FORWARD_LIST_H
#define CANN_ASC_STL_ASC_STD___FORWARD_LIST_FORWARD_LIST_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__exception/terminate.h>
#include <asc/std/__forward_list/node.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__new/nonallocating_new.h>

namespace asc::std {

template <class T, class Allocator>
class forward_list {
    using node = detail::forward_list_node<T>;
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
        using iterator_category = forward_iterator_tag;
        using value_type = T;
        using difference_type = __PTRDIFF_TYPE__;
        using pointer = T*;
        using reference = T&;

        CANN_ASC_STL_HOST_SIMT_API iterator() = default;
        CANN_ASC_STL_HOST_SIMT_API explicit iterator(node* current) : current_(current)
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
        friend CANN_ASC_STL_HOST_SIMT_API bool operator==(iterator left, iterator right)
        {
            return left.current_ == right.current_;
        }
        friend CANN_ASC_STL_HOST_SIMT_API bool operator!=(iterator left, iterator right)
        {
            return !(left == right);
        }

    private:
        node* current_ = nullptr;
    };

    CANN_ASC_STL_HOST_SIMT_API explicit forward_list(const Allocator& allocator) noexcept : allocator_(allocator)
    {}
    forward_list(const forward_list&) = delete;
    forward_list& operator=(const forward_list&) = delete;
    CANN_ASC_STL_HOST_SIMT_API forward_list(forward_list&& other) noexcept
        : allocator_(other.allocator_), head_(other.head_)
    {
        other.head_ = nullptr;
    }
    CANN_ASC_STL_HOST_SIMT_API forward_list& operator=(forward_list&& other) noexcept
    {
        if (this != &other) {
            clear();
            allocator_ = other.allocator_;
            head_ = other.head_;
            other.head_ = nullptr;
        }
        return *this;
    }
    CANN_ASC_STL_HOST_SIMT_API ~forward_list()
    {
        clear();
    }

    CANN_ASC_STL_HOST_SIMT_API bool empty() const noexcept
    {
        return head_ == nullptr;
    }
    CANN_ASC_STL_HOST_SIMT_API reference front() noexcept
    {
        return head_->value;
    }
    CANN_ASC_STL_HOST_SIMT_API const_reference front() const noexcept
    {
        return head_->value;
    }
    CANN_ASC_STL_HOST_SIMT_API iterator begin() noexcept
    {
        return iterator(head_);
    }
    CANN_ASC_STL_HOST_SIMT_API iterator end() noexcept
    {
        return iterator(nullptr);
    }
    CANN_ASC_STL_HOST_SIMT_API void push_front(const T& value)
    {
        emplace_front(value);
    }
    CANN_ASC_STL_HOST_SIMT_API void push_front(T&& value)
    {
        emplace_front(static_cast<T&&>(value));
    }
    template <class... Args>
    CANN_ASC_STL_HOST_SIMT_API reference emplace_front(Args&&... args)
    {
        node_allocator nodes(allocator_);
        node_pointer created = nodes.allocate(1);
        if (created == nullptr)
            raise_allocation_failure();
        // Links are raw node*: reach through the allocated pointer just for
        // construction and deallocation.
        node* created_node = ::asc::std::to_address(created);
        ::new (static_cast<void*>(created_node)) node(head_, static_cast<Args&&>(args)...);
        head_ = created_node;
        return head_->value;
    }
    CANN_ASC_STL_HOST_SIMT_API void pop_front()
    {
        if (head_ == nullptr) {
            // Popping an empty list violates the precondition; fail with a
            // diagnostic instead of dereferencing null.
            ::asc::std::terminate();
        }
        node_allocator nodes(allocator_);
        node* removed = head_;
        head_ = head_->next;
        removed->~node();
        nodes.deallocate(::asc::std::pointer_traits<node_pointer>::pointer_to(*removed), 1);
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

    Allocator allocator_;
    node* head_ = nullptr;
};

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___FORWARD_LIST_FORWARD_LIST_H
