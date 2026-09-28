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

namespace asc::std {

template <class T, class Allocator>
class forward_list {
    struct node;
    using node_allocator = typename Allocator::template rebind<node>::other;
    using node_pointer = typename node_allocator::pointer;

    struct node {
        node_pointer next;
        T value;

        template <class... Args>
        CANN_ASC_STL_API explicit node(node_pointer successor, Args&&... args)
            : next(successor), value(static_cast<Args&&>(args)...)
        {}
    };

public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = __SIZE_TYPE__;
    using reference = T&;
    using const_reference = const T&;

    class iterator {
    public:
        using value_type = T;
        using difference_type = __PTRDIFF_TYPE__;
        using pointer = T*;
        using reference = T&;

        CANN_ASC_STL_API iterator() = default;
        CANN_ASC_STL_API explicit iterator(node_pointer current) : current_(current)
        {}
        CANN_ASC_STL_API reference operator*() const
        {
            return current_->value;
        }
        CANN_ASC_STL_API pointer operator->() const
        {
            return &current_->value;
        }
        CANN_ASC_STL_API iterator& operator++()
        {
            current_ = current_->next;
            return *this;
        }
        CANN_ASC_STL_API iterator operator++(int)
        {
            iterator previous = *this;
            ++*this;
            return previous;
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
        node_pointer current_ = nullptr;
    };

    CANN_ASC_STL_API explicit forward_list(const Allocator& allocator) noexcept : allocator_(allocator)
    {}
    forward_list(const forward_list&) = delete;
    forward_list& operator=(const forward_list&) = delete;
    CANN_ASC_STL_API forward_list(forward_list&& other) noexcept : allocator_(other.allocator_), head_(other.head_)
    {
        other.head_ = nullptr;
    }
    CANN_ASC_STL_API forward_list& operator=(forward_list&& other) noexcept
    {
        if (this != &other) {
            clear();
            allocator_ = other.allocator_;
            head_ = other.head_;
            other.head_ = nullptr;
        }
        return *this;
    }
    CANN_ASC_STL_API ~forward_list()
    {
        clear();
    }

    CANN_ASC_STL_API bool empty() const noexcept
    {
        return head_ == nullptr;
    }
    CANN_ASC_STL_API reference front() noexcept
    {
        return head_->value;
    }
    CANN_ASC_STL_API const_reference front() const noexcept
    {
        return head_->value;
    }
    CANN_ASC_STL_API iterator begin() noexcept
    {
        return iterator(head_);
    }
    CANN_ASC_STL_API iterator end() noexcept
    {
        return iterator(nullptr);
    }
    CANN_ASC_STL_API void push_front(const T& value)
    {
        emplace_front(value);
    }
    CANN_ASC_STL_API void push_front(T&& value)
    {
        emplace_front(static_cast<T&&>(value));
    }
    template <class... Args>
    CANN_ASC_STL_API reference emplace_front(Args&&... args)
    {
        node_allocator nodes(allocator_);
        node_pointer created = nodes.allocate(1);
        ::new (static_cast<void*>(created)) node(head_, static_cast<Args&&>(args)...);
        head_ = created;
        return head_->value;
    }
    CANN_ASC_STL_API void pop_front()
    {
        node_allocator nodes(allocator_);
        node_pointer removed = head_;
        head_ = head_->next;
        removed->~node();
        nodes.deallocate(removed, 1);
    }
    CANN_ASC_STL_API void clear() noexcept
    {
        while (head_ != nullptr)
            pop_front();
    }

private:
    Allocator allocator_;
    node_pointer head_ = nullptr;
};

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___FORWARD_LIST_FORWARD_LIST_H
