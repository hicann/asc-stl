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
#ifndef CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_H
#define CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_H

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
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/dependent_type.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__variant/sfinae_helpers.h>
#include <asc/std/__variant/variant_access.h>
#include <asc/std/__variant/variant_base.h>
#include <asc/std/__variant/variant_constraints.h>
#include <asc/std/__variant/variant_match.h>
#include <asc/std/__variant/variant_visit.h>
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Brace-list constructor/emplace overloads go through the host initializer_list
// (the device side does not participate).
#include <initializer_list>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

template <class... Types>
class variant {
    static_assert(sizeof...(Types) > 0, "variant must have an alternative");
    static_assert((!is_array_v<Types> && ...), "variant cannot contain arrays");
    static_assert((!is_reference_v<Types> && ...), "variant cannot contain references");
    static_assert((!is_void_v<Types> && ...), "variant cannot contain void");
    using storage_type = __variant_storage<0, Types...>;

public:
    template <class First = variant_alternative_t<0, variant>, enable_if_t<is_default_constructible_v<First>, int> = 0>
    CANN_ASC_STL_API constexpr variant() noexcept(is_nothrow_default_constructible_v<First>)
        : storage_(in_place_index<0>), index_(0)
    {}
    CANN_ASC_STL_API constexpr variant(const variant& other) : storage_(), index_(other.index_)
    {
        __variant_storage_copy_construct(index_, storage_, other.storage_);
    }
    CANN_ASC_STL_API constexpr variant(variant&& other) : storage_(), index_(other.index_)
    {
        __variant_storage_move_construct(index_, storage_, other.storage_);
    }
    template <class T, __SIZE_TYPE__ Index = __variant_best_match<remove_cvref_t<T>, void, Types...>::value,
        enable_if_t<Index != variant_npos && is_constructible_v<variant_alternative_t<Index, variant>, T>, int> = 0>
    CANN_ASC_STL_API constexpr variant(T&& value) noexcept(
        is_nothrow_constructible_v<variant_alternative_t<Index, variant>, T>)
        : storage_(in_place_index<Index>, ::asc::std::forward<T>(value)), index_(Index)
    {}
    template <size_t Index, class... Args, enable_if_t<(Index < sizeof...(Types)), int> = 0>
    CANN_ASC_STL_API constexpr explicit variant(in_place_index_t<Index>, Args&&... args) noexcept(
        is_nothrow_constructible_v<variant_alternative_t<Index, variant>, Args...>)
        : storage_(in_place_index<Index>, ::asc::std::forward<Args>(args)...), index_(Index)
    {}
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <size_t Index, class Up, class... Args,
        enable_if_t<(Index < sizeof...(Types)) &&
                is_constructible_v<variant_alternative_t<Index, variant>, ::std::initializer_list<Up>&, Args...>,
            int> = 0>
    CANN_ASC_STL_API constexpr explicit variant(in_place_index_t<Index>, ::std::initializer_list<Up> list,
        Args&&... args) noexcept(is_nothrow_constructible_v<variant_alternative_t<Index, variant>,
        ::std::initializer_list<Up>&, Args...>)
        : storage_(in_place_index<Index>, list, ::asc::std::forward<Args>(args)...), index_(Index)
    {}
#endif
    template <class T, class... Args, __SIZE_TYPE__ Index = __variant_index_v<T, Types...>,
        enable_if_t<Index != variant_npos && __variant_type_count_v<T, Types...> == 1, int> = 0>
    CANN_ASC_STL_API constexpr explicit variant(in_place_type_t<T>, Args&&... args) noexcept(
        is_nothrow_constructible_v<T, Args...>)
        : storage_(in_place_index<Index>, ::asc::std::forward<Args>(args)...), index_(Index)
    {}
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class T, class Up, class... Args, __SIZE_TYPE__ Index = __variant_index_v<T, Types...>,
        enable_if_t<Index != variant_npos && __variant_type_count_v<T, Types...> == 1 &&
                is_constructible_v<T, ::std::initializer_list<Up>&, Args...>,
            int> = 0>
    CANN_ASC_STL_API constexpr explicit variant(in_place_type_t<T>, ::std::initializer_list<Up> list,
        Args&&... args) noexcept(is_nothrow_constructible_v<T, ::std::initializer_list<Up>&, Args...>)
        : storage_(in_place_index<Index>, list, ::asc::std::forward<Args>(args)...), index_(Index)
    {}
#endif
    CANN_ASC_STL_API ~variant()
    {
        __variant_storage_destroy(index_, storage_);
    }
    CANN_ASC_STL_API constexpr variant& operator=(const variant& other)
    {
        if (this == &other) {
            return *this;
        }
        if (index_ == other.index_) {
            __variant_storage_copy_assign(index_, storage_, other.storage_);
        } else {
            __variant_storage_destroy(index_, storage_);
            index_ = other.index_;
            __variant_storage_copy_construct(index_, storage_, other.storage_);
        }
        return *this;
    }
    CANN_ASC_STL_API constexpr variant& operator=(variant&& other)
    {
        if (this == &other) {
            return *this;
        }
        if (index_ == other.index_) {
            __variant_storage_move_assign(index_, storage_, other.storage_);
        } else {
            __variant_storage_destroy(index_, storage_);
            index_ = other.index_;
            __variant_storage_move_construct(index_, storage_, other.storage_);
        }
        return *this;
    }
    template <class T, __SIZE_TYPE__ Index = __variant_best_match<remove_cvref_t<T>, void, Types...>::value,
        enable_if_t<Index != variant_npos &&
                (is_assignable_v<variant_alternative_t<Index, variant>&, T> ||
                    is_constructible_v<variant_alternative_t<Index, variant>, T>),
            int> = 0>
    CANN_ASC_STL_API constexpr variant& operator=(T&& value)
    {
        if (index_ == Index) {
            __variant_storage_get<Index>(storage_) = ::asc::std::forward<T>(value);
        } else {
            (void)emplace<Index>(::asc::std::forward<T>(value));
        }
        return *this;
    }
    template <size_t Index, class... Args>
    CANN_ASC_STL_API constexpr variant_alternative_t<Index, variant>& emplace(Args&&... args)
    {
        static_assert(Index < sizeof...(Types), "variant index out of range");
        __variant_storage_destroy(index_, storage_);
        ::asc::std::__construct_at(
            ::asc::std::addressof(storage_), in_place_index<Index>, ::asc::std::forward<Args>(args)...);
        index_ = Index;
        return __variant_storage_get<Index>(storage_);
    }
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <size_t Index, class Up, class... Args,
        enable_if_t<(Index < sizeof...(Types)) &&
                is_constructible_v<variant_alternative_t<Index, variant>, ::std::initializer_list<Up>&, Args...>,
            int> = 0>
    CANN_ASC_STL_API constexpr variant_alternative_t<Index, variant>& emplace(
        ::std::initializer_list<Up> list, Args&&... args)
    {
        static_assert(Index < sizeof...(Types), "variant index out of range");
        __variant_storage_destroy(index_, storage_);
        ::asc::std::__construct_at(
            ::asc::std::addressof(storage_), in_place_index<Index>, list, ::asc::std::forward<Args>(args)...);
        index_ = Index;
        return __variant_storage_get<Index>(storage_);
    }
#endif
    template <class T, class... Args, __SIZE_TYPE__ Index = __variant_index_v<T, Types...>,
        enable_if_t<Index != variant_npos && __variant_type_count_v<T, Types...> == 1, int> = 0>
    CANN_ASC_STL_API constexpr T& emplace(Args&&... args)
    {
        return emplace<Index>(::asc::std::forward<Args>(args)...);
    }
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class T, class Up, class... Args, __SIZE_TYPE__ Index = __variant_index_v<T, Types...>,
        enable_if_t<Index != variant_npos && __variant_type_count_v<T, Types...> == 1 &&
                is_constructible_v<T, ::std::initializer_list<Up>&, Args...>,
            int> = 0>
    CANN_ASC_STL_API constexpr T& emplace(::std::initializer_list<Up> list, Args&&... args)
    {
        static_assert(Index < sizeof...(Types), "variant index out of range");
        __variant_storage_destroy(index_, storage_);
        ::asc::std::__construct_at(
            ::asc::std::addressof(storage_), in_place_index<Index>, list, ::asc::std::forward<Args>(args)...);
        index_ = Index;
        return __variant_storage_get<Index>(storage_);
    }
#endif
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __SIZE_TYPE__ index() const noexcept
    {
        return index_;
    }
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool valueless_by_exception() const noexcept
    {
        return index_ == variant_npos;
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() & noexcept
    {
        return __variant_storage_get<Index>(storage_);
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() const& noexcept
    {
        return __variant_storage_get<Index>(storage_);
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() && noexcept
    {
        return ::asc::std::move(__variant_storage_get<Index>(storage_));  // NOLINT(build/include_what_you_use)
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() const&& noexcept
    {
        return ::asc::std::move(__variant_storage_get<Index>(storage_));
    }
    CANN_ASC_STL_API constexpr void swap(variant& other) noexcept(
        __fold_and_v<(is_nothrow_move_constructible_v<Types> && is_nothrow_move_assignable_v<Types>)...>)
    {
        variant temporary(::asc::std::move(other));
        other = ::asc::std::move(*this);
        *this = ::asc::std::move(temporary);  // NOLINT(build/include_what_you_use)
    }

private:
    storage_type storage_;
    __SIZE_TYPE__ index_ = variant_npos;
};

// Free-function form of member swap: both ADL and unqualified swap call sites resolve to this overload.
template <class... Types>
CANN_ASC_STL_API constexpr void swap(  // NOLINT(build/include_what_you_use)
    variant<Types...>& left, variant<Types...>& right) noexcept(noexcept(left.swap(right)))
{
    left.swap(right);
}
template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr bool __variant_equal_at(const variant<Types...>& left, const variant<Types...>& right)
{
    if constexpr (Index == sizeof...(Types)) {
        return false;
    } else {
        return left.index() == Index ? left.template __get<Index>() == right.template __get<Index>() :
                                       __variant_equal_at<Index + 1>(left, right);
    }
}
template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr bool __variant_less_at(const variant<Types...>& left, const variant<Types...>& right)
{
    if constexpr (Index == sizeof...(Types)) {
        return false;
    } else {
        return left.index() == Index ? left.template __get<Index>() < right.template __get<Index>() :
                                       __variant_less_at<Index + 1>(left, right);
    }
}
template <class... Types>
CANN_ASC_STL_API constexpr bool operator==(const variant<Types...>& left, const variant<Types...>& right)
{
    return left.index() == right.index() && __variant_equal_at<0>(left, right);
}
template <class... Types>
CANN_ASC_STL_API constexpr bool operator!=(const variant<Types...>& left, const variant<Types...>& right)
{
    return !(left == right);
}
template <class... Types>
CANN_ASC_STL_API constexpr bool operator<(const variant<Types...>& left, const variant<Types...>& right)
{
    return left.index() == right.index() ? __variant_less_at<0>(left, right) : left.index() < right.index();
}
template <class... Types>
CANN_ASC_STL_API constexpr bool operator>(const variant<Types...>& left, const variant<Types...>& right)
{
    return right < left;
}
template <class... Types>
CANN_ASC_STL_API constexpr bool operator<=(const variant<Types...>& left, const variant<Types...>& right)
{
    return !(right < left);
}
template <class... Types>
CANN_ASC_STL_API constexpr bool operator>=(const variant<Types...>& left, const variant<Types...>& right)
{
    return !(left < right);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_H
