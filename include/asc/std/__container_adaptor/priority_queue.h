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

#ifndef CANN_ASC_STL_ASC_STD___CONTAINER_ADAPTOR_PRIORITY_QUEUE_H
#define CANN_ASC_STL_ASC_STD___CONTAINER_ADAPTOR_PRIORITY_QUEUE_H

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
template <class T>
struct priority_less {
    CANN_ASC_STL_API constexpr bool operator()(const T& left, const T& right) const
    {
        return left < right;
    }
};
}  // namespace detail

template <class T, class Container, class Compare = detail::priority_less<typename Container::value_type>>
class priority_queue {
public:
    using container_type = Container;
    using value_compare = Compare;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

    CANN_ASC_STL_API constexpr priority_queue() = default;
    CANN_ASC_STL_API constexpr explicit priority_queue(const Compare& compare) : comp(compare)
    {}
    CANN_ASC_STL_API constexpr priority_queue(const Compare& compare, const Container& container)
        : c(container), comp(compare)
    {
        heapify();
    }
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return c.empty();
    }
    CANN_ASC_STL_API constexpr size_type size() const
    {
        return c.size();
    }
    CANN_ASC_STL_API constexpr const_reference top() const
    {
        return c.front();
    }
    CANN_ASC_STL_API constexpr void push(const value_type& value)
    {
        c.push_back(value);
        sift_up(c.size() - 1);
    }
    CANN_ASC_STL_API constexpr void push(value_type&& value)
    {
        c.push_back(static_cast<value_type&&>(value));
        sift_up(c.size() - 1);
    }
    template <class... Args>
    CANN_ASC_STL_API constexpr void emplace(Args&&... args)
    {
        c.emplace_back(static_cast<Args&&>(args)...);
        sift_up(c.size() - 1);
    }
    CANN_ASC_STL_API constexpr void pop()
    {
        exchange(c[0], c[c.size() - 1]);
        c.pop_back();
        if (!c.empty()) {
            sift_down(0);
        }
    }
    CANN_ASC_STL_API constexpr void swap(priority_queue& other)  // NOLINT(build/include_what_you_use)
    {
        c.swap(other.c);
        Compare temporary(static_cast<Compare&&>(comp));
        comp = static_cast<Compare&&>(other.comp);
        other.comp = static_cast<Compare&&>(temporary);
    }

protected:
    Container c{};
    Compare comp{};

private:
    CANN_ASC_STL_API static constexpr void exchange(value_type& left, value_type& right)
    {
        value_type temporary = static_cast<value_type&&>(left);
        left = static_cast<value_type&&>(right);
        right = static_cast<value_type&&>(temporary);
    }
    CANN_ASC_STL_API constexpr void sift_up(size_type child)
    {
        while (child != 0) {
            const size_type parent = (child - 1) / 2;
            if (!comp(c[parent], c[child])) {
                return;
            }
            exchange(c[parent], c[child]);
            child = parent;
        }
    }
    CANN_ASC_STL_API constexpr void sift_down(size_type parent)
    {
        while (parent * 2 + 1 < c.size()) {
            size_type child = parent * 2 + 1;
            if (child + 1 < c.size() && comp(c[child], c[child + 1])) {
                ++child;
            }
            if (!comp(c[parent], c[child])) {
                return;
            }
            exchange(c[parent], c[child]);
            parent = child;
        }
    }
    CANN_ASC_STL_API constexpr void heapify()
    {
        for (size_type parent = c.size() / 2; parent != 0; --parent) {
            sift_down(parent - 1);
        }
    }
};

template <class T, class Container, class Compare>
CANN_ASC_STL_API constexpr void swap(  // NOLINT(build/include_what_you_use)
    priority_queue<T, Container, Compare>& left,
    priority_queue<T, Container, Compare>& right)  // NOLINT(build/include_what_you_use)
{
    left.swap(right);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CONTAINER_ADAPTOR_PRIORITY_QUEUE_H
