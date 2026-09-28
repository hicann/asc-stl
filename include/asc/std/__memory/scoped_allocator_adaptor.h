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

#include <asc/std/__memory/allocator_traits.h>
#include <asc/std/__memory/allocator_arg_t.h>
#include <asc/std/__memory/uses_allocator.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/tuple>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class OuterAllocator, class... InnerAllocators>
class scoped_allocator_adaptor;

namespace detail {

template <class T>
struct is_scoped_allocator_adaptor : false_type {};
template <class Outer, class... Inner>
struct is_scoped_allocator_adaptor<scoped_allocator_adaptor<Outer, Inner...>> : true_type {};
template <class T>
struct is_scoped_allocator_adaptor<const T> : is_scoped_allocator_adaptor<T> {};
template <class T>
struct is_scoped_allocator_adaptor<volatile T> : is_scoped_allocator_adaptor<T> {};

template <class T, class Allocator, class... Args>
CANN_ASC_STL_API constexpr auto scoped_uses_allocator_args(const Allocator& allocator, Args&&... args) noexcept;

template <class T, class Allocator>
struct scoped_from_tuple {
    const Allocator& allocator;
    template <class... Args>
    CANN_ASC_STL_API constexpr auto operator()(Args&&... args) const noexcept
    {
        return scoped_uses_allocator_args<T>(allocator, static_cast<Args&&>(args)...);
    }
};

template <class Pair, class Allocator, class FirstTuple, class SecondTuple>
CANN_ASC_STL_API constexpr auto scoped_pair_args(
    const Allocator& allocator, piecewise_construct_t, FirstTuple&& first_args, SecondTuple&& second_args) noexcept
{
    using first_type = typename Pair::first_type;
    using second_type = typename Pair::second_type;
    auto first =
        ::asc::std::apply(scoped_from_tuple<first_type, Allocator>{allocator}, static_cast<FirstTuple&&>(first_args));
    auto second = ::asc::std::apply(
        scoped_from_tuple<second_type, Allocator>{allocator}, static_cast<SecondTuple&&>(second_args));
    return tuple<piecewise_construct_t, decltype(first), decltype(second)>(
        piecewise_construct, static_cast<decltype(first)&&>(first), static_cast<decltype(second)&&>(second));
}

template <class Pair, class Allocator, class First, class Second>
CANN_ASC_STL_API constexpr auto scoped_pair_args(const Allocator& allocator, First&& first, Second&& second) noexcept
{
    return scoped_pair_args<Pair>(allocator, piecewise_construct,
        ::asc::std::forward_as_tuple(static_cast<First&&>(first)),
        ::asc::std::forward_as_tuple(static_cast<Second&&>(second)));
}

template <class Pair, class Allocator>
CANN_ASC_STL_API constexpr auto scoped_pair_args(const Allocator& allocator) noexcept
{
    return scoped_pair_args<Pair>(allocator, piecewise_construct, tuple<>{}, tuple<>{});
}

template <class Pair, class Allocator, class First, class Second>
CANN_ASC_STL_API constexpr auto scoped_pair_args(const Allocator& allocator, const pair<First, Second>& value) noexcept
{
    return scoped_pair_args<Pair>(allocator, value.first, value.second);
}

template <class Pair, class Allocator, class First, class Second>
// NOLINTNEXTLINE(build/include_what_you_use)
CANN_ASC_STL_API constexpr auto scoped_pair_args(const Allocator& allocator, pair<First, Second>&& value) noexcept
{
    return scoped_pair_args<Pair>(allocator, static_cast<First&&>(value.first), static_cast<Second&&>(value.second));
}

template <class T, class Allocator, class... Args>
CANN_ASC_STL_API constexpr auto scoped_uses_allocator_args(const Allocator& allocator, Args&&... args) noexcept
{
    if constexpr (__is_pair<T>::value) {
        return scoped_pair_args<T>(allocator, static_cast<Args&&>(args)...);
    } else if constexpr (!uses_allocator_v<T, Allocator>) {
        return ::asc::std::forward_as_tuple(static_cast<Args&&>(args)...);
    } else if constexpr (__is_constructible(T, allocator_arg_t, const Allocator&, Args...)) {
        // NOLINTNEXTLINE(build/include_what_you_use)
        return tuple<allocator_arg_t, const Allocator&, Args&&...>(
            allocator_arg, allocator, static_cast<Args&&>(args)...);
    } else {
        static_assert(__is_constructible(T, Args..., const Allocator&), "invalid scoped allocator construction");
        return ::asc::std::forward_as_tuple(static_cast<Args&&>(args)..., allocator);
    }
}

template <class Allocator>
CANN_ASC_STL_API decltype(auto) scoped_outermost(Allocator& allocator)
{
    if constexpr (is_scoped_allocator_adaptor<Allocator>::value)
        return scoped_outermost(allocator.outer_allocator());
    else
        return (allocator);
}

template <class Allocator, class T>
struct scoped_constructor {
    Allocator& allocator;
    T* address;
    template <class... Args>
    CANN_ASC_STL_API void operator()(Args&&... args) const
    {
        allocator_traits<Allocator>::construct(allocator, address, static_cast<Args&&>(args)...);
    }
};

template <class Outer, class Inner, class T, class... Args>
CANN_ASC_STL_API void scoped_construct(Outer& outer, const Inner& inner, T* address, Args&&... args)
{
    auto& outermost = scoped_outermost(outer);
    using outermost_type = remove_reference_t<decltype(outermost)>;
    ::asc::std::apply(scoped_constructor<outermost_type, T>{outermost, address},
        scoped_uses_allocator_args<T>(inner, static_cast<Args&&>(args)...));
}

}  // namespace detail

template <class OuterAllocator>
class scoped_allocator_adaptor<OuterAllocator> : public OuterAllocator {
public:
    using outer_traits = allocator_traits<OuterAllocator>;
    using outer_allocator_type = OuterAllocator;
    using inner_allocator_type = scoped_allocator_adaptor;
    using value_type = typename outer_traits::value_type;
    using pointer = typename outer_traits::pointer;
    using const_pointer = typename outer_traits::const_pointer;
    using void_pointer = typename outer_traits::void_pointer;
    using const_void_pointer = typename outer_traits::const_void_pointer;
    using size_type = typename outer_traits::size_type;
    using difference_type = typename outer_traits::difference_type;
    using propagate_on_container_copy_assignment = typename outer_traits::propagate_on_container_copy_assignment;
    using propagate_on_container_move_assignment = typename outer_traits::propagate_on_container_move_assignment;
    using propagate_on_container_swap = typename outer_traits::propagate_on_container_swap;
    using is_always_equal = typename outer_traits::is_always_equal;
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
    template <class OuterA2,
        enable_if_t<!detail::is_scoped_allocator_adaptor<remove_reference_t<OuterA2>>::value, int> = 0>
    CANN_ASC_STL_API constexpr explicit scoped_allocator_adaptor(OuterA2&& outer) noexcept
        : OuterAllocator(static_cast<OuterA2&&>(outer))
    {}
    template <class OuterA2>
    CANN_ASC_STL_API constexpr scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterA2>& other) noexcept
        : OuterAllocator(other.outer_allocator())
    {}
    template <class OuterA2>
    CANN_ASC_STL_API constexpr scoped_allocator_adaptor(scoped_allocator_adaptor<OuterA2>&& other) noexcept
        : OuterAllocator(static_cast<OuterA2&&>(other.outer_allocator()))
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
        return outer_traits::allocate(outer_allocator(), count);
    }
    CANN_ASC_STL_API pointer allocate(size_type count, const_void_pointer hint)
    {
        return outer_traits::allocate(outer_allocator(), count, hint);
    }
    CANN_ASC_STL_API void deallocate(pointer address, size_type count) noexcept
    {
        outer_traits::deallocate(outer_allocator(), address, count);
    }
    CANN_ASC_STL_API size_type max_size() const noexcept
    {
        return outer_traits::max_size(outer_allocator());
    }
    CANN_ASC_STL_API scoped_allocator_adaptor select_on_container_copy_construction() const
    {
        return scoped_allocator_adaptor(outer_traits::select_on_container_copy_construction(outer_allocator()));
    }
    template <class T, class... Args>
    CANN_ASC_STL_API void construct(T* address, Args&&... args)
    {
        detail::scoped_construct(outer_allocator(), inner_allocator(), address, static_cast<Args&&>(args)...);
    }
    template <class T>
    CANN_ASC_STL_API void destroy(T* address)
    {
        auto& outermost = detail::scoped_outermost(outer_allocator());
        allocator_traits<remove_reference_t<decltype(outermost)>>::destroy(outermost, address);
    }
};

template <class OuterAllocator, class FirstInner, class... RestInner>
class scoped_allocator_adaptor<OuterAllocator, FirstInner, RestInner...> : public OuterAllocator {
public:
    using outer_traits = allocator_traits<OuterAllocator>;
    using outer_allocator_type = OuterAllocator;
    using inner_allocator_type = scoped_allocator_adaptor<FirstInner, RestInner...>;
    using value_type = typename outer_traits::value_type;
    using pointer = typename outer_traits::pointer;
    using const_pointer = typename outer_traits::const_pointer;
    using void_pointer = typename outer_traits::void_pointer;
    using const_void_pointer = typename outer_traits::const_void_pointer;
    using size_type = typename outer_traits::size_type;
    using difference_type = typename outer_traits::difference_type;
    using propagate_on_container_copy_assignment =
        bool_constant<outer_traits::propagate_on_container_copy_assignment::value ||
            inner_allocator_type::propagate_on_container_copy_assignment::value>;
    using propagate_on_container_move_assignment =
        bool_constant<outer_traits::propagate_on_container_move_assignment::value ||
            inner_allocator_type::propagate_on_container_move_assignment::value>;
    using propagate_on_container_swap = bool_constant<outer_traits::propagate_on_container_swap::value ||
        inner_allocator_type::propagate_on_container_swap::value>;
    using is_always_equal =
        bool_constant<outer_traits::is_always_equal::value && inner_allocator_type::is_always_equal::value>;
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
    template <class OuterA2,
        enable_if_t<!detail::is_scoped_allocator_adaptor<remove_reference_t<OuterA2>>::value, int> = 0>
    CANN_ASC_STL_API constexpr scoped_allocator_adaptor(
        OuterA2&& outer, const FirstInner& first, const RestInner&... rest) noexcept
        : OuterAllocator(static_cast<OuterA2&&>(outer)), inner_(first, rest...)
    {}
    template <class OuterA2>
    CANN_ASC_STL_API constexpr scoped_allocator_adaptor(
        const scoped_allocator_adaptor<OuterA2, FirstInner, RestInner...>& other) noexcept
        : OuterAllocator(other.outer_allocator()), inner_(other.inner_allocator())
    {}
    template <class OuterA2>
    CANN_ASC_STL_API constexpr scoped_allocator_adaptor(
        scoped_allocator_adaptor<OuterA2, FirstInner, RestInner...>&& other) noexcept
        : OuterAllocator(static_cast<OuterA2&&>(other.outer_allocator())),
          inner_(static_cast<inner_allocator_type&&>(other.inner_allocator()))
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
        return outer_traits::allocate(outer_allocator(), count);
    }
    CANN_ASC_STL_API pointer allocate(size_type count, const_void_pointer hint)
    {
        return outer_traits::allocate(outer_allocator(), count, hint);
    }
    CANN_ASC_STL_API void deallocate(pointer address, size_type count) noexcept
    {
        outer_traits::deallocate(outer_allocator(), address, count);
    }
    CANN_ASC_STL_API size_type max_size() const noexcept
    {
        return outer_traits::max_size(outer_allocator());
    }
    CANN_ASC_STL_API scoped_allocator_adaptor select_on_container_copy_construction() const
    {
        return scoped_allocator_adaptor(outer_traits::select_on_container_copy_construction(outer_allocator()),
            inner_.select_on_container_copy_construction(), 0);
    }
    template <class T, class... Args>
    CANN_ASC_STL_API void construct(T* address, Args&&... args)
    {
        detail::scoped_construct(outer_allocator(), inner_, address, static_cast<Args&&>(args)...);
    }
    template <class T>
    CANN_ASC_STL_API void destroy(T* address)
    {
        auto& outermost = detail::scoped_outermost(outer_allocator());
        allocator_traits<remove_reference_t<decltype(outermost)>>::destroy(outermost, address);
    }

private:
    CANN_ASC_STL_API scoped_allocator_adaptor(const OuterAllocator& outer, const inner_allocator_type& inner, int)
        : OuterAllocator(outer), inner_(inner)
    {}
    inner_allocator_type inner_{};
};

template <class OuterAlloc, class... InnerAllocs>
CANN_ASC_STL_HOST_DEVICE scoped_allocator_adaptor(
    OuterAlloc, InnerAllocs...) -> scoped_allocator_adaptor<OuterAlloc, InnerAllocs...>;

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
