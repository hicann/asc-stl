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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_PAIR_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_PAIR_H

#include <asc/std/detail/__config>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__asc/host_std_lib.h>
#include <asc/std/__fwd/pair.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__tuple_dir/tuple_types.h>
#include <asc/std/__tuple_dir/sfinae_helpers.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_implicitly_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/make_const_lvalue_ref.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

struct __invalid_pair_constraints {
    static constexpr bool __implicit_constructible = false;
    static constexpr bool __explicit_constructible = false;
    static constexpr bool __enable_assign = false;
};

template <class _T1, class _T2>
struct __pair_constraints {
    static constexpr bool __implicit_default_constructible =
        __is_implicitly_default_constructible<_T1>::value && __is_implicitly_default_constructible<_T2>::value;
    static constexpr bool __explicit_default_constructible =
        !__implicit_default_constructible && is_default_constructible_v<_T1> && is_default_constructible_v<_T2>;
    static constexpr bool __explicit_constructible_from_elements = is_copy_constructible_v<_T1> &&
        is_copy_constructible_v<_T2> &&
        (!is_convertible_v<__make_const_lvalue_ref<_T1>, _T1> || !is_convertible_v<__make_const_lvalue_ref<_T2>, _T2>);
    static constexpr bool __implicit_constructible_from_elements = is_copy_constructible_v<_T1> &&
        is_copy_constructible_v<_T2> && is_convertible_v<__make_const_lvalue_ref<_T1>, _T1> &&
        is_convertible_v<__make_const_lvalue_ref<_T2>, _T2>;

    template <class _U1, class _U2>
    struct __constructible {
        static constexpr bool __explicit_constructible = is_constructible_v<_T1, _U1> && is_constructible_v<_T2, _U2> &&
            (!is_convertible_v<_U1, _T1> || !is_convertible_v<_U2, _T2>);
        static constexpr bool __implicit_constructible = is_constructible_v<_T1, _U1> && is_constructible_v<_T2, _U2> &&
            is_convertible_v<_U1, _T1> && is_convertible_v<_U2, _T2>;
    };

    template <class _U1, class _U2>
    struct __assignable {
        static constexpr bool __enable_assign = is_assignable_v<_T1&, _U1> && is_assignable_v<_T2&, _U2>;
    };
};

template <class _T1, class _T2, bool = __must_synthesize_assignment_v<_T1> || __must_synthesize_assignment_v<_T2>>
struct __pair_base {
    _T1 first;
    _T2 second;

    template <class _Constraints = __pair_constraints<_T1, _T2>,
        enable_if_t<_Constraints::__implicit_default_constructible, int> = 0>
    CANN_ASC_STL_API constexpr __pair_base() noexcept(
        is_nothrow_default_constructible_v<_T1> && is_nothrow_default_constructible_v<_T2>)
        : first(), second()
    {}

    template <class _Constraints = __pair_constraints<_T1, _T2>,
        enable_if_t<_Constraints::__explicit_default_constructible, int> = 0>
    CANN_ASC_STL_API explicit constexpr __pair_base() noexcept(
        is_nothrow_default_constructible_v<_T1> && is_nothrow_default_constructible_v<_T2>)
        : first(), second()
    {}

    template <class _U1, class _U2>
    CANN_ASC_STL_API constexpr __pair_base(_U1&& __t1, _U2&& __t2) noexcept(
        is_nothrow_constructible_v<_T1, _U1> && is_nothrow_constructible_v<_T2, _U2>)
        : first(::asc::std::forward<_U1>(__t1)), second(::asc::std::forward<_U2>(__t2))
    {}
};

template <class _T1, class _T2>
struct __pair_base<_T1, _T2, true> {
    _T1 first;
    _T2 second;

    CANN_ASC_STL_API constexpr __pair_base() noexcept(
        is_nothrow_default_constructible_v<_T1> && is_nothrow_default_constructible_v<_T2>)
        : first(), second()
    {}

    CANN_ASC_STL_API constexpr __pair_base(const __pair_base&) = default;
    CANN_ASC_STL_API constexpr __pair_base(__pair_base&&) = default;

    template <class _U1, class _U2>
    CANN_ASC_STL_API constexpr __pair_base(_U1&& __t1, _U2&& __t2) noexcept(
        is_nothrow_constructible_v<_T1, _U1> && is_nothrow_constructible_v<_T2, _U2>)
        : first(::asc::std::forward<_U1>(__t1)), second(::asc::std::forward<_U2>(__t2))
    {}

    template <class _U1, class _U2, class _Constraints = __pair_constraints<_T1, _T2>>
    CANN_ASC_STL_API constexpr __pair_base& operator=(const __pair_base<_U1, _U2>& __p)
    {
        first = __p.first;
        second = __p.second;
        return *this;
    }

    template <class _U1, class _U2, class _Constraints = __pair_constraints<_T1, _T2>>
    CANN_ASC_STL_API constexpr __pair_base& operator=(__pair_base<_U1, _U2>&& __p)
    {
        first = ::asc::std::forward<_U1>(__p.first);
        second = ::asc::std::forward<_U2>(__p.second);
        return *this;
    }
};

template <class _T1, class _T2>
struct pair : protected __pair_base<_T1, _T2> {
    using __base = __pair_base<_T1, _T2>;
    using __base::first;
    using __base::second;
    using first_type = _T1;
    using second_type = _T2;

    using __base::__base;

    pair(const pair&) = default;
    pair(pair&&) = default;

    template <class _U1 = _T1, class _U2 = _T2,
        enable_if_t<__pair_constraints<_T1, _T2>::template __constructible<_U1, _U2>::__implicit_constructible, int> =
            0>
    CANN_ASC_STL_API constexpr pair(_U1&& __u1, _U2&& __u2)
        : __base(::asc::std::forward<_U1>(__u1), ::asc::std::forward<_U2>(__u2))
    {}

    template <class _U1 = _T1, class _U2 = _T2,
        enable_if_t<__pair_constraints<_T1, _T2>::template __constructible<_U1, _U2>::__explicit_constructible, int> =
            0>
    CANN_ASC_STL_API explicit constexpr pair(_U1&& __u1, _U2&& __u2)
        : __base(::asc::std::forward<_U1>(__u1), ::asc::std::forward<_U2>(__u2))
    {}

    template <class _U1, class _U2,
        enable_if_t<is_constructible_v<first_type, const _U1&> && is_constructible_v<second_type, const _U2&>, int> = 0>
    CANN_ASC_STL_API constexpr pair(const pair<_U1, _U2>& __p) : __base(__p.first, __p.second)
    {}

    template <class _U1, class _U2,
        enable_if_t<is_constructible_v<first_type, _U1> && is_constructible_v<second_type, _U2>, int> = 0>
    CANN_ASC_STL_API constexpr pair(pair<_U1, _U2>&& __p)
        : __base(::asc::std::move(__p.first), ::asc::std::move(__p.second))
    {}

    CANN_ASC_STL_API pair& operator=(const pair& __p)
    {
        this->first = __p.first;
        this->second = __p.second;
        return *this;
    }

    CANN_ASC_STL_API pair& operator=(pair&& __p) noexcept(
        is_nothrow_move_assignable_v<_T1> && is_nothrow_move_assignable_v<_T2>)
    {
        this->first = ::asc::std::move(__p.first);
        this->second = ::asc::std::move(__p.second);
        return *this;
    }

    template <class _U1, class _U2,
        enable_if_t<is_assignable_v<_T1&, const _U1&> && is_assignable_v<_T2&, const _U2&>, int> = 0>
    CANN_ASC_STL_API pair& operator=(const pair<_U1, _U2>& __p)
    {
        this->first = __p.first;
        this->second = __p.second;
        return *this;
    }

    CANN_ASC_STL_API void swap(pair& __p) noexcept(
        __is_nothrow_swappable<_T1>::value && __is_nothrow_swappable<_T2>::value)
    {
        using ::asc::std::swap;
        swap(this->first, __p.first);
        swap(this->second, __p.second);
    }
};

template <class _T1, class _T2>
pair(_T1, _T2) -> pair<_T1, _T2>;

template <class _T1, class _T2>
CANN_ASC_STL_API void swap(pair<_T1, _T2>& __x, pair<_T1, _T2>& __y) noexcept(noexcept(__x.swap(__y)))
{
    __x.swap(__y);
}

template <class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{
    return __x.first == __y.first && __x.second == __y.second;
}

template <class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{
    return !(__x == __y);
}

template <class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{
    return __x.first < __y.first || (!(__y.first < __x.first) && __x.second < __y.second);
}

template <class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{
    return !(__y < __x);
}

template <class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{
    return __y < __x;
}

template <class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{
    return !(__x < __y);
}

template <class _T1, class _T2>
struct tuple_size<pair<_T1, _T2>> : integral_constant<size_t, 2> {};

template <size_t _Ip, class _T1, class _T2>
struct tuple_element<_Ip, pair<_T1, _T2>> {};

template <class _T1, class _T2>
struct tuple_element<0, pair<_T1, _T2>> {
    using type = _T1;
};

template <class _T1, class _T2>
struct tuple_element<1, pair<_T1, _T2>> {
    using type = _T2;
};

template <size_t _Ip, class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr tuple_element_t<_Ip, pair<_T1, _T2>>& get(pair<_T1, _T2>& __p) noexcept
{
    if constexpr (_Ip == 0) {
        return __p.first;
    } else {
        return __p.second;
    }
}

template <size_t _Ip, class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr const tuple_element_t<_Ip, pair<_T1, _T2>>& get(
    const pair<_T1, _T2>& __p) noexcept
{
    if constexpr (_Ip == 0) {
        return __p.first;
    } else {
        return __p.second;
    }
}

template <size_t _Ip, class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr tuple_element_t<_Ip, pair<_T1, _T2>>&& get(pair<_T1, _T2>&& __p) noexcept
{
    if constexpr (_Ip == 0) {
        return ::asc::std::move(__p.first);
    } else {
        return ::asc::std::move(__p.second);
    }
}

template <class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<decay_t<_T1>, decay_t<_T2>> make_pair(_T1&& __t1, _T2&& __t2)
{
    return pair<decay_t<_T1>, decay_t<_T2>>(
        ::asc::std::forward<_T1>(__t1), ::asc::std::forward<_T2>(__t2));  // NOLINT(build/include_what_you_use)
}

// std::pair tuple-protocol bridging (host std lib only). Without this
// bridge, tuple-like detection over std::pair (e.g. __complex/traits.h's
// __is_complex_compatible_tuple_like) wrongly evaluates false on hosted
// builds. Device/freestanding builds have no std::pair and skip the block.
#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
template <class _T1, class _T2>
struct tuple_size<::std::pair<_T1, _T2>> : integral_constant<size_t, 2> {};

template <size_t _Ip, class _T1, class _T2>
struct tuple_element<_Ip, ::std::pair<_T1, _T2>> {
    static_assert(_Ip < 2, "Index out of bounds in asc::std::tuple_element<> (std::pair)");
};

template <class _T1, class _T2>
struct tuple_element<0, ::std::pair<_T1, _T2>> {
    using type = _T1;
};

template <class _T1, class _T2>
struct tuple_element<1, ::std::pair<_T1, _T2>> {  // NOLINT
    using type = _T2;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

CANN_ASC_STL_END_NAMESPACE

// tuple protocol for asc::std::pair (structured-binding bridge into
// namespace std).
namespace std {

template <class _T1, class _T2>
struct tuple_size<::asc::std::pair<_T1, _T2>> : ::asc::std::integral_constant<::asc::std::size_t, 2> {};

template <::asc::std::size_t _Ip, class _T1, class _T2>
struct tuple_element<_Ip, ::asc::std::pair<_T1, _T2>> {
    static_assert(_Ip < 2, "Index out of bounds in std::tuple_element<> (asc::std::pair)");
};

template <class _T1, class _T2>
struct tuple_element<0, ::asc::std::pair<_T1, _T2>> {
    using type = _T1;
};

template <class _T1, class _T2>
struct tuple_element<1, ::asc::std::pair<_T1, _T2>> {
    using type = _T2;
};

}  // namespace std

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_PAIR_H
