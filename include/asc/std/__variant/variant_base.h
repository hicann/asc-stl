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

#ifndef CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_BASE_H
#define CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_BASE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__variant/sfinae_helpers.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <__SIZE_TYPE__ Index, class T>
struct __variant_alt {
    T value;

    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __variant_alt(in_place_index_t<Index>, Args&&... args)
        : value(::asc::std::forward<Args>(args)...)
    {}
};

template <bool TrivialDestructor, __SIZE_TYPE__ Index, class... Types>
union __variant_union;

template <__SIZE_TYPE__ Index, class... Types>
using __variant_storage = __variant_union<(is_trivially_destructible_v<Types> && ...), Index, Types...>;

template <__SIZE_TYPE__ Index>
union __variant_union<true, Index> {
    unsigned char empty_;
    CANN_ASC_STL_API constexpr __variant_union() noexcept : empty_{}
    {}
};

// C++17 requires separate union definitions to keep the trivial destructor.
#define CANN_ASC_STL_DETAIL_VARIANT_UNION_MEMBERS                                                     \
    __variant_alt<Index, Head> head;                                                                  \
    __variant_storage<Index + 1, Tail...> tail;                                                       \
    CANN_ASC_STL_API constexpr __variant_union() noexcept : tail()                                    \
    {}                                                                                                \
    template <__SIZE_TYPE__ Target, class... Args>                                                    \
    CANN_ASC_STL_API constexpr explicit __variant_union(in_place_index_t<Target> tag, Args&&... args) \
        : tail(tag, ::asc::std::forward<Args>(args)...)                                               \
    {}                                                                                                \
    template <class... Args>                                                                          \
    CANN_ASC_STL_API constexpr explicit __variant_union(in_place_index_t<Index> tag, Args&&... args)  \
        : head(tag, ::asc::std::forward<Args>(args)...)                                               \
    {}

template <__SIZE_TYPE__ Index, class Head, class... Tail>
union __variant_union<true, Index, Head, Tail...> {
    CANN_ASC_STL_DETAIL_VARIANT_UNION_MEMBERS
};
template <__SIZE_TYPE__ Index, class Head, class... Tail>
union __variant_union<false, Index, Head, Tail...> {
    CANN_ASC_STL_DETAIL_VARIANT_UNION_MEMBERS
    CANN_ASC_STL_API ~__variant_union()
    {}
};
#undef CANN_ASC_STL_DETAIL_VARIANT_UNION_MEMBERS

// Keep the enclosing storage object alive if construction of the selected member throws.
template <__SIZE_TYPE__ Target, __SIZE_TYPE__ Index, class Head, class... Tail, class... Args>
CANN_ASC_STL_API constexpr void __variant_storage_construct(
    __variant_storage<Index, Head, Tail...>& storage, Args&&... args)
{
    if constexpr (Target == Index) {
        ::asc::std::__construct_at(
            ::asc::std::addressof(storage.head), in_place_index<Target>, ::asc::std::forward<Args>(args)...);
    } else {
        ::asc::std::__construct_at(
            ::asc::std::addressof(storage.tail), in_place_index<Target>, ::asc::std::forward<Args>(args)...);
    }
}

template <__SIZE_TYPE__ Target, __SIZE_TYPE__ Index, class Head, class... Tail>
CANN_ASC_STL_API constexpr decltype(auto) __variant_storage_get(__variant_storage<Index, Head, Tail...>& storage)
{
    if constexpr (Target == Index) {
        return (storage.head.value);
    } else {
        return __variant_storage_get<Target>(storage.tail);
    }
}
template <__SIZE_TYPE__ Target, __SIZE_TYPE__ Index, class Head, class... Tail>
CANN_ASC_STL_API constexpr decltype(auto) __variant_storage_get(const __variant_storage<Index, Head, Tail...>& storage)
{
    if constexpr (Target == Index) {
        return (storage.head.value);
    } else {
        return __variant_storage_get<Target>(storage.tail);
    }
}
template <__SIZE_TYPE__ Target, __SIZE_TYPE__ Index, class Head, class... Tail>
CANN_ASC_STL_API constexpr decltype(auto) __variant_storage_get(__variant_storage<Index, Head, Tail...>&& storage)
{
    return ::asc::std::move(__variant_storage_get<Target>(storage));
}

template <__SIZE_TYPE__ Index>
CANN_ASC_STL_API constexpr void __variant_storage_destroy(__SIZE_TYPE__, __variant_storage<Index>&) noexcept
{}
template <__SIZE_TYPE__ Index, class Head, class... Tail>
CANN_ASC_STL_API constexpr void __variant_storage_destroy(
    __SIZE_TYPE__ active, __variant_storage<Index, Head, Tail...>& storage) noexcept
{
    if (active == variant_npos) {
        return;
    }
    if (active == Index) {
        ::asc::std::__destroy_at(::asc::std::addressof(storage.head.value));
    } else {
        __variant_storage_destroy(active, storage.tail);
    }
}
template <class... Types>
struct __variant_state : __variant_sfinae_helper<__variant_state<Types...>,
                             ((is_copy_constructible_v<Types> && is_copy_assignable_v<Types>) && ...),
                             ((is_move_constructible_v<Types> && is_move_assignable_v<Types>) && ...)> {
    static constexpr bool __nothrow_move_construct = (is_nothrow_move_constructible_v<Types> && ...);
    static constexpr bool __nothrow_move_assign =
        __nothrow_move_construct && (is_nothrow_move_assignable_v<Types> && ...);
    __variant_storage<0, Types...> storage_{};
    __SIZE_TYPE__ index_ = variant_npos;

    CANN_ASC_STL_API constexpr __variant_state() = default;
    template <__SIZE_TYPE__ Index, class... Args>
    CANN_ASC_STL_API constexpr explicit __variant_state(in_place_index_t<Index> tag, Args&&... args)
        : storage_(tag, ::asc::std::forward<Args>(args)...), index_(Index)
    {}

    CANN_ASC_STL_API constexpr void __reset() noexcept
    {
        __variant_storage_destroy(index_, storage_);
        index_ = variant_npos;
    }

    template <__SIZE_TYPE__ Index, class... Args>
    CANN_ASC_STL_API constexpr auto& __emplace(Args&&... args)
    {
        __reset();
        __variant_storage_construct<Index>(storage_, ::asc::std::forward<Args>(args)...);
        index_ = Index;
        return __variant_storage_get<Index>(storage_);
    }

    template <__SIZE_TYPE__ Index = 0, class Visitor>
    static CANN_ASC_STL_API constexpr void __visit_index(__SIZE_TYPE__ active, const Visitor& visit)
    {
        if constexpr (Index < sizeof...(Types)) {
            if (active == Index) {
                visit(integral_constant<__SIZE_TYPE__, Index>{});
            } else {
                __visit_index<Index + 1>(active, visit);
            }
        }
    }

    template <class Other>
    CANN_ASC_STL_API constexpr void __construct_from(Other&& other)
    {
        __visit_index(other.index_, [&](auto index) {
            __variant_storage_construct<index.value>(
                storage_, __variant_storage_get<index.value>(::asc::std::forward<Other>(other).storage_));
        });
        index_ = other.index_;
    }

    template <class Other>
    CANN_ASC_STL_API constexpr void __assign_from(Other&& other)
    {
        if (other.index_ == variant_npos) {
            __reset();
            return;
        }
        __visit_index(other.index_, [&](auto index) {
            using T = __type_index_c<index.value, Types...>;
            auto&& value = __variant_storage_get<index.value>(::asc::std::forward<Other>(other).storage_);
            if (index_ == index.value) {
                __variant_storage_get<index.value>(storage_) = ::asc::std::forward<decltype(value)>(value);
                return;
            }
            if constexpr (is_lvalue_reference_v<Other> && !is_nothrow_copy_constructible_v<T> &&
                is_nothrow_move_constructible_v<T>) {
                // Finish the potentially throwing copy before releasing the old alternative.
                __emplace<index.value>(T(value));
            } else {
                __emplace<index.value>(::asc::std::forward<decltype(value)>(value));
            }
        });
    }
};

template <class Base>
struct __variant_destructor : Base {
    using Base::Base;
    CANN_ASC_STL_API ~__variant_destructor()
    {
        __variant_storage_destroy(this->index_, this->storage_);
    }
};

template <class Base>
struct __variant_copy_constructor : Base {
    using Base::Base;
    CANN_ASC_STL_API constexpr __variant_copy_constructor() = default;
    CANN_ASC_STL_API constexpr __variant_copy_constructor(const __variant_copy_constructor& other) : Base()
    {
        this->__construct_from(other);
    }
    CANN_ASC_STL_API __variant_copy_constructor(__variant_copy_constructor&&) = default;
    CANN_ASC_STL_API __variant_copy_constructor& operator=(const __variant_copy_constructor&) = default;
    CANN_ASC_STL_API __variant_copy_constructor& operator=(__variant_copy_constructor&&) = default;
};

template <class Base>
struct __variant_move_constructor : Base {
    using Base::Base;
    CANN_ASC_STL_API constexpr __variant_move_constructor() = default;
    CANN_ASC_STL_API __variant_move_constructor(const __variant_move_constructor&) = default;
    CANN_ASC_STL_API constexpr __variant_move_constructor(__variant_move_constructor&& other) noexcept(
        Base::__nothrow_move_construct)
        : Base()
    {
        this->__construct_from(::asc::std::move(other));
    }
    CANN_ASC_STL_API __variant_move_constructor& operator=(const __variant_move_constructor&) = default;
    CANN_ASC_STL_API __variant_move_constructor& operator=(__variant_move_constructor&&) = default;
};

template <class Base>
struct __variant_copy_assignment : Base {
    using Base::Base;
    CANN_ASC_STL_API constexpr __variant_copy_assignment() = default;
    CANN_ASC_STL_API __variant_copy_assignment(const __variant_copy_assignment&) = default;
    CANN_ASC_STL_API __variant_copy_assignment(__variant_copy_assignment&&) = default;
    CANN_ASC_STL_API constexpr __variant_copy_assignment& operator=(const __variant_copy_assignment& other)
    {
        this->__assign_from(other);
        return *this;
    }
    CANN_ASC_STL_API __variant_copy_assignment& operator=(__variant_copy_assignment&&) = default;
};

template <class Base>
struct __variant_move_assignment : Base {
    using Base::Base;
    CANN_ASC_STL_API constexpr __variant_move_assignment() = default;
    CANN_ASC_STL_API __variant_move_assignment(const __variant_move_assignment&) = default;
    CANN_ASC_STL_API __variant_move_assignment(__variant_move_assignment&&) = default;
    CANN_ASC_STL_API __variant_move_assignment& operator=(const __variant_move_assignment&) = default;
    CANN_ASC_STL_API constexpr __variant_move_assignment& operator=(__variant_move_assignment&& other) noexcept(
        Base::__nothrow_move_assign)
    {
        if (this != ::asc::std::addressof(other)) {
            this->__assign_from(::asc::std::move(other));  // NOLINT(build/include_what_you_use)
        }
        return *this;
    }
};

// The raw union supplies trivial or deleted operations. Insert a dispatching
// operation only when every alternative supports it and at least one needs it.
template <class... Types>
struct __variant_base {
    static constexpr bool trivial_destruct = (is_trivially_destructible_v<Types> && ...);
    static constexpr bool trivial_copy = (is_trivially_copy_constructible_v<Types> && ...);
    static constexpr bool trivial_move = (is_trivially_move_constructible_v<Types> && ...);
    static constexpr bool can_copy = (is_copy_constructible_v<Types> && ...);
    static constexpr bool can_move = (is_move_constructible_v<Types> && ...);

    using state = __variant_state<Types...>;
    using destruct = conditional_t<trivial_destruct, state, __variant_destructor<state>>;
    using copy_ctor = conditional_t<can_copy && !trivial_copy, __variant_copy_constructor<destruct>, destruct>;
    using move_ctor = conditional_t<can_move && !trivial_move, __variant_move_constructor<copy_ctor>, copy_ctor>;
    using copy_assign = conditional_t<can_copy && (is_copy_assignable_v<Types> && ...) &&
            !(trivial_destruct && trivial_copy && (is_trivially_copy_assignable_v<Types> && ...)),
        __variant_copy_assignment<move_ctor>, move_ctor>;
    using type = conditional_t<can_move && (is_move_assignable_v<Types> && ...) &&
            !(trivial_destruct && trivial_move && (is_trivially_move_assignable_v<Types> && ...)),
        __variant_move_assignment<copy_assign>, copy_assign>;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_BASE_H
