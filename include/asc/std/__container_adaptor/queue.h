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

#ifndef CANN_ASC_STL_ASC_STD___CONTAINER_ADAPTOR_QUEUE_H
#define CANN_ASC_STL_ASC_STD___CONTAINER_ADAPTOR_QUEUE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T, class Container>
class queue {
public:
    using container_type = Container;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

    CANN_ASC_STL_API constexpr queue() = default;
    CANN_ASC_STL_API constexpr explicit queue(const Container& container) : c(container)
    {}
    CANN_ASC_STL_API constexpr explicit queue(Container&& container) : c(static_cast<Container&&>(container))
    {}
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return c.empty();
    }
    CANN_ASC_STL_API constexpr size_type size() const
    {
        return c.size();
    }
    CANN_ASC_STL_API constexpr reference front()
    {
        return c.front();
    }
    CANN_ASC_STL_API constexpr const_reference front() const
    {
        return c.front();
    }
    CANN_ASC_STL_API constexpr reference back()
    {
        return c.back();
    }
    CANN_ASC_STL_API constexpr const_reference back() const
    {
        return c.back();
    }
    CANN_ASC_STL_API constexpr void push(const value_type& value)
    {
        c.push_back(value);
    }
    CANN_ASC_STL_API constexpr void push(value_type&& value)
    {
        c.push_back(static_cast<value_type&&>(value));
    }
    template <class... Args>
    CANN_ASC_STL_API constexpr decltype(auto) emplace(Args&&... args)
    {
        return c.emplace_back(static_cast<Args&&>(args)...);
    }
    CANN_ASC_STL_API constexpr void pop()
    {
        c.pop_front();
    }
    CANN_ASC_STL_API constexpr void swap(queue& other) noexcept(  // NOLINT(build/include_what_you_use)
        noexcept(::asc::std::declval<Container&>().swap(::asc::std::declval<Container&>())))
    {
        c.swap(other.c);
    }

protected:
    Container c{};
};

template <class T, class Container>
CANN_ASC_STL_API constexpr void swap(  // NOLINT(build/include_what_you_use)
    queue<T, Container>& left,
    queue<T, Container>& right) noexcept(noexcept(left.swap(right)))  // NOLINT(build/include_what_you_use)
{
    left.swap(right);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CONTAINER_ADAPTOR_QUEUE_H
