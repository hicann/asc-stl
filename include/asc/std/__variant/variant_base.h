/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/__variant/variant_access.h>
#include <asc/std/__variant/variant_traits.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <__SIZE_TYPE__ Index, class T>
struct __variant_alt {
    T value;

    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __variant_alt(in_place_index_t<Index>, Args&&... args)
        : value(::asc::std::forward<Args>(args)...)
    {}
};

template <__SIZE_TYPE__ Index, class... Types>
union __variant_storage;
template <__SIZE_TYPE__ Index>
union __variant_storage<Index> {
    CANN_ASC_STL_API constexpr __variant_storage() noexcept
    {}
};
template <__SIZE_TYPE__ Index, class Head, class... Tail>
union __variant_storage<Index, Head, Tail...> {
    __variant_alt<Index, Head> head;
    __variant_storage<Index + 1, Tail...> tail;

    CANN_ASC_STL_API constexpr __variant_storage() noexcept : tail()
    {}
    template <__SIZE_TYPE__ Target, class... Args>
    CANN_ASC_STL_API constexpr explicit __variant_storage(in_place_index_t<Target>, Args&&... args)
        : tail(in_place_index<Target>, ::asc::std::forward<Args>(args)...)  // NOLINT(build/include_what_you_use)
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __variant_storage(in_place_index_t<Index>, Args&&... args)
        : head(in_place_index<Index>, ::asc::std::forward<Args>(args)...)  // NOLINT(build/include_what_you_use)
    {}
    CANN_ASC_STL_API ~__variant_storage()
    {}
};

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
template <__SIZE_TYPE__ Index>
CANN_ASC_STL_API constexpr void __variant_storage_destroy(__SIZE_TYPE__, __variant_storage<Index>&) noexcept
{}
template <__SIZE_TYPE__ Index, class Head, class... Tail>
CANN_ASC_STL_API constexpr void __variant_storage_destroy(
    __SIZE_TYPE__ active, __variant_storage<Index, Head, Tail...>& storage) noexcept
{
    if (active == Index) {
        ::asc::std::__destroy_at(::asc::std::addressof(storage.head.value));
    } else {
        __variant_storage_destroy(active, storage.tail);
    }
}
template <__SIZE_TYPE__ Index>
CANN_ASC_STL_API constexpr void __variant_storage_copy_construct(
    __SIZE_TYPE__, __variant_storage<Index>&, const __variant_storage<Index>&)
{}
template <__SIZE_TYPE__ Index, class Head, class... Tail>
CANN_ASC_STL_API constexpr void __variant_storage_copy_construct(__SIZE_TYPE__ active,
    __variant_storage<Index, Head, Tail...>& destination, const __variant_storage<Index, Head, Tail...>& source)
{
    if (active == Index) {
        ::asc::std::__construct_at(::asc::std::addressof(destination.head), in_place_index<Index>, source.head.value);
    } else {
        __variant_storage_copy_construct(active, destination.tail, source.tail);
    }
}
template <__SIZE_TYPE__ Index>
CANN_ASC_STL_API constexpr void __variant_storage_move_construct(
    __SIZE_TYPE__, __variant_storage<Index>&, __variant_storage<Index>&)
{}
template <__SIZE_TYPE__ Index, class Head, class... Tail>
CANN_ASC_STL_API constexpr void __variant_storage_move_construct(__SIZE_TYPE__ active,
    __variant_storage<Index, Head, Tail...>& destination, __variant_storage<Index, Head, Tail...>& source)
{
    if (active == Index) {
        ::asc::std::__construct_at(
            ::asc::std::addressof(destination.head), in_place_index<Index>, ::asc::std::move(source.head.value));
    } else {
        __variant_storage_move_construct(active, destination.tail, source.tail);
    }
}
template <__SIZE_TYPE__ Index>
CANN_ASC_STL_API constexpr void __variant_storage_copy_assign(
    __SIZE_TYPE__, __variant_storage<Index>&, const __variant_storage<Index>&)
{}
template <__SIZE_TYPE__ Index, class Head, class... Tail>
CANN_ASC_STL_API constexpr void __variant_storage_copy_assign(__SIZE_TYPE__ active,
    __variant_storage<Index, Head, Tail...>& destination, const __variant_storage<Index, Head, Tail...>& source)
{
    if (active == Index) {
        destination.head.value = source.head.value;
    } else {
        __variant_storage_copy_assign(active, destination.tail, source.tail);
    }
}
template <__SIZE_TYPE__ Index>
CANN_ASC_STL_API constexpr void __variant_storage_move_assign(
    __SIZE_TYPE__, __variant_storage<Index>&, __variant_storage<Index>&)
{}
template <__SIZE_TYPE__ Index, class Head, class... Tail>
CANN_ASC_STL_API constexpr void __variant_storage_move_assign(__SIZE_TYPE__ active,
    __variant_storage<Index, Head, Tail...>& destination, __variant_storage<Index, Head, Tail...>& source)
{
    if (active == Index) {
        destination.head.value = ::asc::std::move(source.head.value);  // NOLINT(build/include_what_you_use)
    } else {
        __variant_storage_move_assign(active, destination.tail, source.tail);
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_BASE_H
