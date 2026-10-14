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
#ifndef CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_H
#define CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__memory/allocator_arg_t.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_leaf.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__tuple/tuple_types.h>
#include <asc/std/__type_traits/common_reference.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/__utility/swap.h>

// The structured-binding protocol for asc::std::tuple is bridged into
// namespace std at the bottom of this header; the bridge needs the primary
// std::tuple_size / std::tuple_element templates, which hosted builds take
// from the host standard library. Device compilations have none and skip it.
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && __has_include(<utility>)
#include <utility>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

// Internal selection tag for the uses-allocator implementation constructors:
// allocator_arg_t itself can show up as a regular element (e.g. the tuple
// built by uses_allocator_construction_args), so the allocator paths of
// __tuple_impl need a prefix that user-facing construction can never produce.
struct __tuple_alloc_tag {};

template <class Indices, class... Types>
class __tuple_impl;
template <size_t... Indices, class... Types>
class __tuple_impl<__tuple_indices<Indices...>, Types...>
    : public __tuple_impl_sfinae_helper<__tuple_impl<__tuple_indices<Indices...>, Types...>,
          (is_copy_assignable_v<Types> && ...), (is_move_assignable_v<Types> && ...)>,
      public __tuple_leaf<Indices, Types>... {
public:
    CANN_ASC_STL_API constexpr __tuple_impl() = default;
    template <class... Values,
        enable_if_t<sizeof...(Values) == sizeof...(Types) && (is_constructible_v<Types, Values> && ...), int> = 0>
    CANN_ASC_STL_API constexpr explicit __tuple_impl(Values&&... values)
        : __tuple_leaf<Indices, Types>(::asc::std::forward<Values>(values))...
    {}
    // Uses-allocator construction: each element is constructed with the
    // flavor selected by __uses_alloc_ctor (0: ignore the allocator,
    // 1: leading (allocator_arg, alloc), 2: trailing alloc). The value-less
    // form default-constructs every element; partial ordering keeps the two
    // forms unambiguous for zero values.
    template <class Alloc>
    CANN_ASC_STL_API constexpr explicit __tuple_impl(__tuple_alloc_tag, const Alloc& alloc)
        : __tuple_leaf<Indices, Types>(integral_constant<int, __uses_alloc_ctor<Types, Alloc>::value>{}, alloc)...
    {}
    template <class Alloc, class... Values>
    CANN_ASC_STL_API constexpr explicit __tuple_impl(__tuple_alloc_tag, const Alloc& alloc, Values&&... values)
        : __tuple_leaf<Indices, Types>(integral_constant<int, __uses_alloc_ctor<Types, Alloc, Values&&>::value>{},
              alloc, ::asc::std::forward<Values>(values))...
    {}
    template <size_t Index>
    CANN_ASC_STL_API constexpr tuple_element_t<Index, tuple<Types...>>& __get() & noexcept
    {
        using leaf = __tuple_leaf<Index, tuple_element_t<Index, tuple<Types...>>>;
        return static_cast<leaf&>(*this).__get();
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr const tuple_element_t<Index, tuple<Types...>>& __get() const& noexcept
    {
        using leaf = __tuple_leaf<Index, tuple_element_t<Index, tuple<Types...>>>;
        return static_cast<const leaf&>(*this).__get();
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr tuple_element_t<Index, tuple<Types...>>&& __get() && noexcept
    {
        using leaf = __tuple_leaf<Index, tuple_element_t<Index, tuple<Types...>>>;
        // The leaf-level __get() preserves the element's reference category.
        // Moving here would turn an int& element into int&&.
        return static_cast<leaf&&>(*this).__get();
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr const tuple_element_t<Index, tuple<Types...>>&& __get() const&& noexcept
    {
        using leaf = __tuple_leaf<Index, tuple_element_t<Index, tuple<Types...>>>;
        return static_cast<const leaf&&>(*this).__get();
    }
    CANN_ASC_STL_API constexpr void swap(__tuple_impl& other) noexcept(
        (noexcept(static_cast<__tuple_leaf<Indices, Types>&>(*this).swap(
             static_cast<__tuple_leaf<Indices, Types>&>(other))) &&
            ...))
    {
        (static_cast<__tuple_leaf<Indices, Types>&>(*this).swap(static_cast<__tuple_leaf<Indices, Types>&>(other)),
            ...);
    }
};
template <class... Types>
class tuple : public __tuple_impl<__make_tuple_indices_t<sizeof...(Types)>, Types...> {
    using base = __tuple_impl<__make_tuple_indices_t<sizeof...(Types)>, Types...>;
    using indices = __make_tuple_indices_t<sizeof...(Types)>;

private:
    // A converting constructor taking a tuple parameter must not interfere
    // with the element constructor (tuple(UTypes&&...)) or the copy/move
    // constructors. For single-element tuples the tuple parameter loses to
    // the element constructor whenever the element could be initialized from
    // the whole source tuple; a source of the same tuple type always loses to
    // the copy/move constructors.
    template <class SourceTuple>
    static constexpr bool __tuple_use_other_ctor()
    {
        if constexpr (sizeof...(Types) != 1) {
            return false;
        } else if constexpr (is_same_v<remove_cvref_t<SourceTuple>, tuple>) {
            return true;
        } else {
            using element = tuple_element_t<0, tuple>;
            return is_convertible_v<SourceTuple, element> || is_constructible_v<element, SourceTuple>;
        }
    }

public:
    CANN_ASC_STL_API constexpr tuple() = default;
    CANN_ASC_STL_API tuple(const tuple&) = default;
    CANN_ASC_STL_API tuple(tuple&&) = default;

    // tuple(const Types&...): the Enable guard keeps the empty tuple from
    // redeclaring its default constructor through this form.
    template <bool Enable = sizeof...(Types) >= 1,
        enable_if_t<Enable && (is_copy_constructible_v<Types> && ...) && (is_convertible_v<const Types&, Types> && ...),
            int> = 0>
    CANN_ASC_STL_API constexpr tuple(const Types&... values) : base(values...)
    {}
    template <bool Enable = sizeof...(Types) >= 1,
        enable_if_t<
            Enable && (is_copy_constructible_v<Types> && ...) && !(is_convertible_v<const Types&, Types> && ...), int> =
            0>
    CANN_ASC_STL_API constexpr explicit tuple(const Types&... values) : base(values...)
    {}

    // tuple(UTypes&&...): gated on per-element constructibility so that
    // infeasible combinations drop out of the overload set instead of
    // hard-erroring inside the leaf, and explicit only when some element is
    // not implicitly constructible from its argument.
    template <class... Values,
        enable_if_t<sizeof...(Values) == sizeof...(Types) && (is_constructible_v<Types, Values> && ...) &&
                (is_convertible_v<Values, Types> && ...),
            int> = 0>
    CANN_ASC_STL_API constexpr tuple(Values&&... values) : base(::asc::std::forward<Values>(values)...)
    {}
    template <class... Values,
        enable_if_t<sizeof...(Values) == sizeof...(Types) && (is_constructible_v<Types, Values> && ...) &&
                !(is_convertible_v<Values, Types> && ...),
            int> = 0>
    CANN_ASC_STL_API constexpr explicit tuple(Values&&... values) : base(::asc::std::forward<Values>(values)...)
    {}

    // Converting constructors from differently-typed tuples: without them,
    // e.g. tuple<int>(tuple<double>{1.5}) is hijacked by the element
    // constructor above (a single Values = tuple<double>) and fails inside
    // the leaf. The __tuple_use_other_ctor guard mirrors the reference
    // implementations: for single-element tuples a tuple parameter must not
    // steal construction from the element constructor (or the copy/move
    // constructors), otherwise e.g. tuple<tuple<T>&&>(move(tuple<T>{}))
    // would materialize a temporary and bind a dangling reference.
    template <class... UTypes,
        enable_if_t<(sizeof...(UTypes) == sizeof...(Types)) && !__tuple_use_other_ctor<tuple<UTypes...>>() &&
                (is_constructible_v<Types, const UTypes&> && ...) && (is_convertible_v<const UTypes&, Types> && ...),
            int> = 0>
    CANN_ASC_STL_API constexpr tuple(const tuple<UTypes...>& other) : tuple(indices{}, other)
    {}
    template <class... UTypes,
        enable_if_t<(sizeof...(UTypes) == sizeof...(Types)) && !__tuple_use_other_ctor<tuple<UTypes...>>() &&
                (is_constructible_v<Types, const UTypes&> && ...) && !(is_convertible_v<const UTypes&, Types> && ...),
            int> = 0>
    CANN_ASC_STL_API constexpr explicit tuple(const tuple<UTypes...>& other) : tuple(indices{}, other)
    {}
    template <class... UTypes,
        enable_if_t<(sizeof...(UTypes) == sizeof...(Types)) && !__tuple_use_other_ctor<tuple<UTypes...>>() &&
                (is_constructible_v<Types, UTypes&&> && ...) && (is_convertible_v<UTypes&&, Types> && ...),
            int> = 0>
    CANN_ASC_STL_API constexpr tuple(tuple<UTypes...>&& other) : tuple(indices{}, ::asc::std::move(other))
    {}
    template <class... UTypes,
        enable_if_t<(sizeof...(UTypes) == sizeof...(Types)) && !__tuple_use_other_ctor<tuple<UTypes...>>() &&
                (is_constructible_v<Types, UTypes&&> && ...) && !(is_convertible_v<UTypes&&, Types> && ...),
            int> = 0>
    CANN_ASC_STL_API constexpr explicit tuple(tuple<UTypes...>&& other) : tuple(indices{}, ::asc::std::move(other))
    {}

    // Allocator-extended constructors: uses_allocator<tuple, Alloc> is true
    // for every allocator, so uses-allocator construction
    // (uses_allocator_construction_args / allocator_traits) must find these.
    template <class Alloc>
    CANN_ASC_STL_API constexpr tuple(allocator_arg_t, const Alloc& alloc) : base(__tuple_alloc_tag{}, alloc)
    {}
    template <class Alloc, bool Enable = sizeof...(Types) >= 1, enable_if_t<Enable, int> = 0>
    CANN_ASC_STL_API constexpr tuple(allocator_arg_t, const Alloc& alloc, const Types&... values)
        : tuple(indices{}, allocator_arg, alloc, values...)
    {}
    template <class Alloc>
    CANN_ASC_STL_API constexpr tuple(allocator_arg_t, const Alloc& alloc, const tuple& other)
        : tuple(indices{}, allocator_arg, alloc, other)
    {}
    template <class Alloc>
    CANN_ASC_STL_API constexpr tuple(allocator_arg_t, const Alloc& alloc, tuple&& other)
        : tuple(indices{}, allocator_arg, alloc, ::asc::std::move(other))
    {}
    template <class Alloc, class... UTypes,
        enable_if_t<(sizeof...(UTypes) == sizeof...(Types)) && !__tuple_use_other_ctor<tuple<UTypes...>>() &&
                (is_constructible_v<Types, const UTypes&> && ...) && (is_convertible_v<const UTypes&, Types> && ...),
            int> = 0>
    CANN_ASC_STL_API constexpr tuple(allocator_arg_t, const Alloc& alloc, const tuple<UTypes...>& other)
        : tuple(indices{}, allocator_arg, alloc, other)
    {}

    // Same-type assignment is defaulted: deleted-ness propagates from
    // __tuple_impl_sfinae_helper through the base, so the assignment traits
    // tell the truth (tuple<const int> has a deleted copy assignment instead
    // of passing the trait and failing in the body). The synthesize leaf
    // provides write-through assignment for reference elements.
    CANN_ASC_STL_API tuple& operator=(const tuple&) = default;
    CANN_ASC_STL_API tuple& operator=(tuple&&) = default;
    template <class... Other,
        enable_if_t<sizeof...(Other) == sizeof...(Types) && (is_assignable_v<Types&, const Other&> && ...), int> = 0>
    CANN_ASC_STL_API constexpr tuple& operator=(const tuple<Other...>& other)
    {
        __assign(other, indices{});
        return *this;
    }
    template <class... Other,
        enable_if_t<sizeof...(Other) == sizeof...(Types) && (is_assignable_v<Types&, Other> && ...), int> = 0>
    CANN_ASC_STL_API constexpr tuple& operator=(tuple<Other...>&& other)
    {
        __assign(::asc::std::move(other), indices{});
        return *this;
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() & noexcept
    {
        return static_cast<base&>(*this).template __get<Index>();
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() const& noexcept
    {
        return static_cast<const base&>(*this).template __get<Index>();
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() && noexcept
    {
        // Forwarding through the base preserves the element's reference
        // category; an unconditional move here would break tuples of
        // references (tie / forward_as_tuple products).
        return static_cast<base&&>(*this).template __get<Index>();
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() const&& noexcept
    {
        return static_cast<const base&&>(*this).template __get<Index>();
    }
    CANN_ASC_STL_API constexpr void swap(tuple& other) noexcept(noexcept(base::swap(other)))
    {
        base::swap(other);
    }

private:
    // Tagged element-wise constructors: the index pack in the parameter list
    // makes the per-element expansion possible inside the mem-initializer.
    // The free get overloads cannot be used here (they are declared after
    // the class), and the member __get keeps each element's value category.
    template <size_t... Indices_, class... UTypes>
    CANN_ASC_STL_API constexpr tuple(__tuple_indices<Indices_...>, const tuple<UTypes...>& other)
        : base(other.template __get<Indices_>()...)
    {}
    template <size_t... Indices_, class... UTypes>
    CANN_ASC_STL_API constexpr tuple(__tuple_indices<Indices_...>, tuple<UTypes...>&& other)
        : base(::asc::std::move(other).template __get<Indices_>()...)
    {}

    // Allocator-extended construction: each element's construction flavor is
    // selected by __uses_alloc_ctor inside the implementation constructor.
    template <size_t... Indices_, class Alloc, class... Values>
    CANN_ASC_STL_API constexpr tuple(
        __tuple_indices<Indices_...>, allocator_arg_t, const Alloc& alloc, Values&&... values)
        : base(__tuple_alloc_tag{}, alloc, ::asc::std::forward<Values>(values)...)
    {}
    template <size_t... Indices_, class Alloc, class... UTypes>
    CANN_ASC_STL_API constexpr tuple(
        __tuple_indices<Indices_...>, allocator_arg_t, const Alloc& alloc, const tuple<UTypes...>& other)
        : tuple(__tuple_indices<Indices_...>{}, allocator_arg, alloc, other.template __get<Indices_>()...)
    {}
    template <size_t... Indices_, class Alloc>
    CANN_ASC_STL_API constexpr tuple(__tuple_indices<Indices_...>, allocator_arg_t, const Alloc& alloc, tuple&& other)
        : tuple(__tuple_indices<Indices_...>{}, allocator_arg, alloc,
              ::asc::std::move(other).template __get<Indices_>()...)
    {}

    template <class Other, size_t... Indices_>
    CANN_ASC_STL_API constexpr void __assign(Other&& other, __tuple_indices<Indices_...>)
    {
        ((this->template __get<Indices_>() = ::asc::std::forward<Other>(other).template __get<Indices_>()), ...);
    }
};
template <class... Types>
struct tuple_size<tuple<Types...>> : integral_constant<size_t, sizeof...(Types)> {};
template <size_t Index, class Head, class... Tail>
struct tuple_element<Index, tuple<Head, Tail...>> : tuple_element<Index - 1, tuple<Tail...>> {};
template <class Head, class... Tail>
struct tuple_element<0, tuple<Head, Tail...>> {
    using type = Head;
};
template <size_t Index>
struct tuple_element<Index, tuple<>> {};
// Comparison kernels: a single fold-expression pass over the index pack, in
// line with swap/__assign below - no per-element template recursion, so the
// instantiated call chain depth does not grow with the number of elements.
template <class Left, class Right, size_t... Indices>
CANN_ASC_STL_API constexpr bool __tuple_equal(const Left& left, const Right& right, __tuple_indices<Indices...>)
{
    return ((left.template __get<Indices>() == right.template __get<Indices>()) && ...);
}
template <class Left, class Right, size_t... Indices>
CANN_ASC_STL_API constexpr bool __tuple_less(const Left& left, const Right& right, __tuple_indices<Indices...>)
{
    // Lexicographical order in one flat pass: __state stays 0 while the
    // elements compared so far are equal, then records the first difference
    // (+1 left smaller, -1 left greater).
    int __state = 0;
    ((__state == 0 ? (left.template __get<Indices>() < right.template __get<Indices>()        ? (__state = 1, 0) :
                             right.template __get<Indices>() < left.template __get<Indices>() ? (__state = -1, 0) :
                                                                                                0) :
                     0),
        ...);
    return __state == 1;
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator==(const tuple<Left...>& left, const tuple<Right...>& right)
{
    static_assert(sizeof...(Left) == sizeof...(Right), "tuple sizes must match");
    return __tuple_equal(left, right, __make_tuple_indices_t<sizeof...(Left)>{});
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator!=(const tuple<Left...>& left, const tuple<Right...>& right)
{
    return !(left == right);
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator<(const tuple<Left...>& left, const tuple<Right...>& right)
{
    static_assert(sizeof...(Left) == sizeof...(Right), "tuple sizes must match");
    return __tuple_less(left, right, __make_tuple_indices_t<sizeof...(Left)>{});
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator>(const tuple<Left...>& left, const tuple<Right...>& right)
{
    return right < left;
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator<=(const tuple<Left...>& left, const tuple<Right...>& right)
{
    return !(right < left);
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator>=(const tuple<Left...>& left, const tuple<Right...>& right)
{
    return !(left < right);
}
template <class... Types>
CANN_ASC_STL_API constexpr void swap(
    tuple<Types...>& left, tuple<Types...>& right) noexcept(  // NOLINT(build/include_what_you_use)
    noexcept(left.swap(right)))                               // NOLINT(build/include_what_you_use)
{
    left.swap(right);
}

CANN_ASC_STL_END_NAMESPACE

// Structured-binding support: all member accessors are named __get so that
// class-scope lookup for get finds nothing and the tuple protocol resolves
// the ADL free asc::std::get. The protocol additionally requires
// std::tuple_size / std::tuple_element specializations, bridged here for
// hosted builds (device compilations have no std namespace to bridge into).
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && __has_include(<utility>)
namespace std {
template <class... Types>
struct tuple_size<::asc::std::tuple<Types...>> : ::asc::std::integral_constant<::asc::std::size_t, sizeof...(Types)> {};
template <::asc::std::size_t Index, class... Types>
struct tuple_element<Index, ::asc::std::tuple<Types...>> {
    using type = ::asc::std::tuple_element_t<Index, ::asc::std::tuple<Types...>>;
};
}  // namespace std
#endif

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_H
