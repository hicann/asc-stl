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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_SCOPED_ALLOCATOR_ADAPTOR_H
#define CANN_ASC_STL_ASC_STD___MEMORY_SCOPED_ALLOCATOR_ADAPTOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

template <class OuterAllocator, class... InnerAllocators>
class scoped_allocator_adaptor;

namespace detail {

template <class Allocator, class T, class... Args>
CANN_ASC_STL_API void scoped_construct(Allocator&, T* address, Args&&... args)
{
    ::new (static_cast<void*>(address)) T(static_cast<Args&&>(args)...);
}

}  // namespace detail

template <class OuterAllocator>
class scoped_allocator_adaptor<OuterAllocator> : public OuterAllocator {
public:
    using outer_allocator_type = OuterAllocator;
    using inner_allocator_type = scoped_allocator_adaptor;
    using value_type = typename OuterAllocator::value_type;
    using pointer = typename OuterAllocator::pointer;
    using size_type = typename OuterAllocator::size_type;
    using difference_type = typename OuterAllocator::difference_type;
    template <class T>
    struct rebind {
        using other = scoped_allocator_adaptor<typename OuterAllocator::template rebind<T>::other>;
    };

    CANN_ASC_STL_API constexpr scoped_allocator_adaptor() = default;
    CANN_ASC_STL_API constexpr explicit scoped_allocator_adaptor(const OuterAllocator& outer) noexcept
        : OuterAllocator(outer)
    {}
    CANN_ASC_STL_API constexpr explicit scoped_allocator_adaptor(OuterAllocator&& outer) noexcept
        : OuterAllocator(static_cast<OuterAllocator&&>(outer))
    {}
    CANN_ASC_STL_API outer_allocator_type& outer_allocator() noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API const outer_allocator_type& outer_allocator() const noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API inner_allocator_type& inner_allocator() noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API const inner_allocator_type& inner_allocator() const noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API pointer allocate(size_type count)
    {
        return outer_allocator().allocate(count);
    }
    CANN_ASC_STL_API void deallocate(pointer address, size_type count)
    {
        outer_allocator().deallocate(address, count);
    }
    CANN_ASC_STL_API size_type max_size() const noexcept
    {
        return outer_allocator().max_size();
    }
    template <class T, class... Args>
    CANN_ASC_STL_API void construct(T* address, Args&&... args)
    {
        detail::scoped_construct(inner_allocator(), address, static_cast<Args&&>(args)...);
    }
    template <class T>
    CANN_ASC_STL_API void destroy(T* address)
    {
        address->~T();
    }
};

template <class OuterAllocator, class FirstInner, class... RestInner>
class scoped_allocator_adaptor<OuterAllocator, FirstInner, RestInner...> : public OuterAllocator {
public:
    using outer_allocator_type = OuterAllocator;
    using inner_allocator_type = scoped_allocator_adaptor<FirstInner, RestInner...>;
    using value_type = typename OuterAllocator::value_type;
    using pointer = typename OuterAllocator::pointer;
    using size_type = typename OuterAllocator::size_type;
    using difference_type = typename OuterAllocator::difference_type;
    template <class T>
    struct rebind {
        using other =
            scoped_allocator_adaptor<typename OuterAllocator::template rebind<T>::other, FirstInner, RestInner...>;
    };

    CANN_ASC_STL_API constexpr scoped_allocator_adaptor() = default;
    CANN_ASC_STL_API constexpr scoped_allocator_adaptor(
        const OuterAllocator& outer, const FirstInner& first, const RestInner&... rest) noexcept
        : OuterAllocator(outer), inner_(first, rest...)
    {}
    CANN_ASC_STL_API outer_allocator_type& outer_allocator() noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API const outer_allocator_type& outer_allocator() const noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API inner_allocator_type& inner_allocator() noexcept
    {
        return inner_;
    }
    CANN_ASC_STL_API const inner_allocator_type& inner_allocator() const noexcept
    {
        return inner_;
    }
    CANN_ASC_STL_API pointer allocate(size_type count)
    {
        return outer_allocator().allocate(count);
    }
    CANN_ASC_STL_API void deallocate(pointer address, size_type count)
    {
        outer_allocator().deallocate(address, count);
    }
    CANN_ASC_STL_API size_type max_size() const noexcept
    {
        return outer_allocator().max_size();
    }
    template <class T, class... Args>
    CANN_ASC_STL_API void construct(T* address, Args&&... args)
    {
        detail::scoped_construct(inner_, address, static_cast<Args&&>(args)...);
    }
    template <class T>
    CANN_ASC_STL_API void destroy(T* address)
    {
        address->~T();
    }

private:
    inner_allocator_type inner_{};
};

template <class LeftOuter, class RightOuter, class... Inner>
CANN_ASC_STL_API constexpr bool operator==(const scoped_allocator_adaptor<LeftOuter, Inner...>& left,
    const scoped_allocator_adaptor<RightOuter, Inner...>& right) noexcept
{
    if constexpr (sizeof...(Inner) == 0) {
        return left.outer_allocator() == right.outer_allocator();
    } else {
        return left.outer_allocator() == right.outer_allocator() && left.inner_allocator() == right.inner_allocator();
    }
}

template <class LeftOuter, class RightOuter, class... Inner>
CANN_ASC_STL_API constexpr bool operator!=(const scoped_allocator_adaptor<LeftOuter, Inner...>& left,
    const scoped_allocator_adaptor<RightOuter, Inner...>& right) noexcept
{
    return !(left == right);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_SCOPED_ALLOCATOR_ADAPTOR_H
