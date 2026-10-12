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

#ifndef CANN_ASC_STL_ASC_STD___UTILITY_PAIR_H
#define CANN_ASC_STL_ASC_STD___UTILITY_PAIR_H

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
#include <asc/std/__functional/unwrap_ref.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__fwd/pair.h>
#include <asc/std/__fwd/subrange.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__tuple/sfinae_helpers.h>
#include <asc/std/__tuple/tuple_constraints.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_like.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/common_reference.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_implicitly_default_constructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/make_const_lvalue_ref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/piecewise_construct.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct __is_pair : false_type {};
template <class T1, class T2>
struct __is_pair<pair<T1, T2>> : true_type {};

template <class T1, class T2>
struct pair {
    using first_type = T1;
    using second_type = T2;

    T1 first;
    T2 second;

    template <class U1 = T1, class U2 = T2,
        enable_if_t<is_default_constructible_v<U1> && is_default_constructible_v<U2> &&
                __is_implicitly_default_constructible<U1>::value && __is_implicitly_default_constructible<U2>::value,
            int> = 0>
    CANN_ASC_STL_API constexpr pair() noexcept(
        is_nothrow_default_constructible_v<T1> && is_nothrow_default_constructible_v<T2>)
        : first(), second()
    {}

    template <class U1 = T1, class U2 = T2,
        enable_if_t<is_default_constructible_v<U1> && is_default_constructible_v<U2> &&
                !(__is_implicitly_default_constructible<U1>::value && __is_implicitly_default_constructible<U2>::value),
            long> = 0>
    CANN_ASC_STL_API explicit constexpr pair() noexcept(
        is_nothrow_default_constructible_v<T1> && is_nothrow_default_constructible_v<T2>)
        : first(), second()
    {}

    pair(const pair&) = default;
    pair(pair&&) = default;
    pair& operator=(const pair&) = default;
    pair& operator=(pair&&) = default;

    template <class U1 = T1, class U2 = T2,
        enable_if_t<is_constructible_v<T1, U1&&> && is_constructible_v<T2, U2&&> && is_convertible_v<U1&&, T1> &&
                is_convertible_v<U2&&, T2>,
            int> = 0>
    CANN_ASC_STL_API constexpr pair(U1&& left, U2&& right) noexcept(
        is_nothrow_constructible_v<T1, U1&&> && is_nothrow_constructible_v<T2, U2&&>)
        : first(::asc::std::forward<U1>(left)), second(::asc::std::forward<U2>(right))
    {}

    template <class U1, class U2,
        enable_if_t<is_constructible_v<T1, U1&&> && is_constructible_v<T2, U2&&> &&
                !(is_convertible_v<U1&&, T1> && is_convertible_v<U2&&, T2>),
            long> = 0>
    CANN_ASC_STL_API explicit constexpr pair(U1&& left, U2&& right) noexcept(
        is_nothrow_constructible_v<T1, U1&&> && is_nothrow_constructible_v<T2, U2&&>)
        : first(::asc::std::forward<U1>(left)), second(::asc::std::forward<U2>(right))
    {}

    template <class U1, class U2, enable_if_t<is_constructible_v<T1, U1&> && is_constructible_v<T2, U2&>, int> = 0>
    CANN_ASC_STL_API constexpr pair(pair<U1, U2>& other) noexcept(
        is_nothrow_constructible_v<T1, U1&> && is_nothrow_constructible_v<T2, U2&>)
        : first(other.first), second(other.second)
    {}

    template <class U1, class U2,
        enable_if_t<is_constructible_v<T1, const U1&&> && is_constructible_v<T2, const U2&&>, int> = 0>
    CANN_ASC_STL_API constexpr pair(const pair<U1, U2>&& other) noexcept(
        is_nothrow_constructible_v<T1, const U1&&> && is_nothrow_constructible_v<T2, const U2&&>)
        : first(::asc::std::move(other.first)), second(::asc::std::move(other.second))
    {}

    template <class PairLike,
        enable_if_t<__tuple_like_ext<remove_cvref_t<PairLike>> && !__is_pair<remove_cvref_t<PairLike>>::value &&
                is_constructible_v<T1, decltype(::asc::std::__adl_get<0>(::asc::std::declval<PairLike>()))> &&
                is_constructible_v<T2, decltype(::asc::std::__adl_get<1>(::asc::std::declval<PairLike>()))>,
            int> = 0>
    CANN_ASC_STL_API constexpr pair(PairLike&& other) noexcept(
        is_nothrow_constructible_v<T1, decltype(::asc::std::__adl_get<0>(::asc::std::declval<PairLike>()))> &&
        is_nothrow_constructible_v<T2, decltype(::asc::std::__adl_get<1>(::asc::std::declval<PairLike>()))>)
        : first(::asc::std::__adl_get<0>(::asc::std::forward<PairLike>(other))),
          second(::asc::std::__adl_get<1>(::asc::std::forward<PairLike>(other)))
    {}

    template <class U1, class U2,
        enable_if_t<is_constructible_v<T1, const U1&> && is_constructible_v<T2, const U2&>, int> = 0>
    CANN_ASC_STL_API constexpr pair(const pair<U1, U2>& other) noexcept(
        is_nothrow_constructible_v<T1, const U1&> && is_nothrow_constructible_v<T2, const U2&>)
        : first(other.first), second(other.second)
    {}

    template <class U1, class U2, enable_if_t<is_constructible_v<T1, U1&&> && is_constructible_v<T2, U2&&>, int> = 0>
    CANN_ASC_STL_API constexpr pair(pair<U1, U2>&& other) noexcept(
        is_nothrow_constructible_v<T1, U1&&> && is_nothrow_constructible_v<T2, U2&&>)
        : first(::asc::std::forward<U1>(other.first)), second(::asc::std::forward<U2>(other.second))
    {}

    template <class... Args1, class... Args2>
    CANN_ASC_STL_API constexpr pair(piecewise_construct_t, tuple<Args1...> left, tuple<Args2...> right) noexcept(
        is_nothrow_constructible_v<T1, Args1...> && is_nothrow_constructible_v<T2, Args2...>)
        : pair(piecewise_construct, ::asc::std::move(left), ::asc::std::move(right),
              __make_tuple_indices_t<sizeof...(Args1)>{}, __make_tuple_indices_t<sizeof...(Args2)>{})
    {}

    template <class U1, class U2,
        enable_if_t<is_assignable_v<T1&, const U1&> && is_assignable_v<T2&, const U2&>, int> = 0>
    CANN_ASC_STL_API constexpr pair& operator=(const pair<U1, U2>& other) noexcept(
        is_nothrow_assignable_v<T1&, const U1&> && is_nothrow_assignable_v<T2&, const U2&>)
    {
        first = other.first;
        second = other.second;
        return *this;
    }

    template <class U1, class U2, enable_if_t<is_assignable_v<T1&, U1> && is_assignable_v<T2&, U2>, int> = 0>
    CANN_ASC_STL_API constexpr pair& operator=(pair<U1, U2>&& other) noexcept(
        is_nothrow_assignable_v<T1&, U1> && is_nothrow_assignable_v<T2&, U2>)
    {
        first = ::asc::std::forward<U1>(other.first);
        second = ::asc::std::forward<U2>(other.second);
        return *this;
    }

    template <class U1, class U2,
        enable_if_t<is_assignable_v<const T1&, const U1&> && is_assignable_v<const T2&, const U2&>, int> = 0>
    CANN_ASC_STL_API constexpr const pair& operator=(const pair<U1, U2>& other) const
        noexcept(is_nothrow_assignable_v<const T1&, const U1&> && is_nothrow_assignable_v<const T2&, const U2&>)
    {
        first = other.first;
        second = other.second;
        return *this;
    }

    template <class U1, class U2,
        enable_if_t<is_assignable_v<const T1&, U1> && is_assignable_v<const T2&, U2>, int> = 0>
    CANN_ASC_STL_API constexpr const pair& operator=(pair<U1, U2>&& other) const
        noexcept(is_nothrow_assignable_v<const T1&, U1> && is_nothrow_assignable_v<const T2&, U2>)
    {
        first = ::asc::std::forward<U1>(other.first);
        second = ::asc::std::forward<U2>(other.second);
        return *this;
    }

    template <class PairLike,
        enable_if_t<__tuple_like_ext<remove_cvref_t<PairLike>> && !__is_pair<remove_cvref_t<PairLike>>::value &&
                is_assignable_v<T1&, decltype(::asc::std::__adl_get<0>(::asc::std::declval<PairLike>()))> &&
                is_assignable_v<T2&, decltype(::asc::std::__adl_get<1>(::asc::std::declval<PairLike>()))>,
            int> = 0>
    CANN_ASC_STL_API constexpr pair& operator=(PairLike&& other)
    {
        first = ::asc::std::__adl_get<0>(::asc::std::forward<PairLike>(other));
        second = ::asc::std::__adl_get<1>(::asc::std::forward<PairLike>(other));
        return *this;
    }

    CANN_ASC_STL_API constexpr void swap(pair& other) noexcept(is_nothrow_move_constructible_v<T1> &&
        is_nothrow_move_assignable_v<T1> && is_nothrow_move_constructible_v<T2> && is_nothrow_move_assignable_v<T2>)
    {
        ::asc::std::swap(first, other.first);
        ::asc::std::swap(second, other.second);
    }

private:
    template <class... Args1, class... Args2, size_t... I1, size_t... I2>
    CANN_ASC_STL_API constexpr pair(piecewise_construct_t,
        tuple<Args1...>&& left,                          // NOLINT(build/include_what_you_use)
        tuple<Args2...>&& right, index_sequence<I1...>,  // NOLINT(build/include_what_you_use)
        index_sequence<I2...>)
        : first(::asc::std::get<I1>(::asc::std::move(left))...), second(::asc::std::get<I2>(::asc::std::move(right))...)
    {}
};

template <class T1, class T2>
pair(T1, T2) -> pair<T1, T2>;

template <class T1, class T2>
CANN_ASC_STL_API constexpr pair<__unwrap_ref_decay_t<T1>, __unwrap_ref_decay_t<T2>> make_pair(T1&& left, T2&& right)
{
    return {::asc::std::forward<T1>(left), ::asc::std::forward<T2>(right)};
}

template <class T1, class T2>
CANN_ASC_STL_API constexpr bool operator==(const pair<T1, T2>& left, const pair<T1, T2>& right) noexcept(
    noexcept(left.first == right.first && left.second == right.second))
{
    return left.first == right.first && left.second == right.second;
}

template <class T1, class T2>
CANN_ASC_STL_API constexpr bool operator<(const pair<T1, T2>& left, const pair<T1, T2>& right) noexcept(
    noexcept(left.first < right.first && left.second < right.second))
{
    return left.first < right.first || (!(right.first < left.first) && left.second < right.second);
}

template <class T1, class T2>
struct tuple_size<pair<T1, T2>> : integral_constant<size_t, 2> {};
template <class T1, class T2>
struct tuple_element<0, pair<T1, T2>> {
    using type = T1;
};
template <class T1, class T2>
struct tuple_element<1, pair<T1, T2>> {
    using type = T2;
};

template <size_t Index, class T1, class T2>
CANN_ASC_STL_API constexpr tuple_element_t<Index, pair<T1, T2>>& get(pair<T1, T2>& value) noexcept
{
    if constexpr (Index == 0) {
        return value.first;
    } else {
        static_assert(Index == 1, "pair get index out of range");
        return value.second;
    }
}
template <size_t Index, class T1, class T2>
CANN_ASC_STL_API constexpr const tuple_element_t<Index, pair<T1, T2>>& get(const pair<T1, T2>& value) noexcept
{
    if constexpr (Index == 0) {
        return value.first;
    } else {
        static_assert(Index == 1, "pair get index out of range");
        return value.second;
    }
}
template <size_t Index, class T1, class T2>
CANN_ASC_STL_API constexpr tuple_element_t<Index, pair<T1, T2>>&& get(pair<T1, T2>&& value) noexcept
{
    return ::asc::std::move(::asc::std::get<Index>(value));
}
template <size_t Index, class T1, class T2>
CANN_ASC_STL_API constexpr const tuple_element_t<Index, pair<T1, T2>>&& get(const pair<T1, T2>&& value) noexcept
{
    return ::asc::std::move(::asc::std::get<Index>(value));
}

template <class T, class U>
CANN_ASC_STL_API constexpr T& get(pair<T, U>& value) noexcept
{
    return value.first;
}
template <class T, class U>
CANN_ASC_STL_API constexpr const T& get(const pair<T, U>& value) noexcept
{
    return value.first;
}
template <class T, class U>
CANN_ASC_STL_API constexpr T&& get(pair<T, U>&& value) noexcept
{
    return ::asc::std::move(value.first);
}
template <class T, class U>
CANN_ASC_STL_API constexpr const T&& get(const pair<T, U>&& value) noexcept
{
    return ::asc::std::move(value.first);
}
template <class T, class U>
CANN_ASC_STL_API constexpr T& get(pair<U, T>& value) noexcept
{
    return value.second;
}
template <class T, class U>
CANN_ASC_STL_API constexpr const T& get(const pair<U, T>& value) noexcept
{
    return value.second;
}
template <class T, class U>
CANN_ASC_STL_API constexpr T&& get(pair<U, T>&& value) noexcept
{
    return ::asc::std::move(value.second);  // NOLINT(build/include_what_you_use)
}
template <class T, class U>
CANN_ASC_STL_API constexpr const T&& get(const pair<U, T>&& value) noexcept
{
    return ::asc::std::move(value.second);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___UTILITY_PAIR_H
