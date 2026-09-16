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

#ifndef CANN_ASC_STL_ASC_STD___FUNCTIONAL_OPERATIONS_H
#define CANN_ASC_STL_ASC_STD___FUNCTIONAL_OPERATIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Arithmetic operations

template <class _Tp = void>
struct plus {
    using __result_type = _Tp;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x + __y;
    }
};

template <>
struct plus<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) +
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) + ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) + ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct minus {
    using __result_type = _Tp;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x - __y;
    }
};

template <>
struct minus<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) -
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) - ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) - ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct multiplies {
    using __result_type = _Tp;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x * __y;
    }
};

template <>
struct multiplies<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) *
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) * ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) * ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct divides {
    using __result_type = _Tp;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x / __y;
    }
};

template <>
struct divides<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) /
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) / ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) / ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct modulus {
    using __result_type = _Tp;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x % __y;
    }
};

template <>
struct modulus<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) %
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) % ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) % ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct negate {
    using __result_type = _Tp;  // used by valarray

    constexpr CANN_ASC_STL_API _Tp operator()(const _Tp& __x) const
    {
        return -__x;
    }
};

template <>
struct negate<void> {
    template <class _Tp>
    constexpr CANN_ASC_STL_API auto operator()(_Tp&& __x) const
        noexcept(noexcept(-::asc::std::forward<_Tp>(__x))) -> decltype(-::asc::std::forward<_Tp>(__x))
    {
        return -::asc::std::forward<_Tp>(__x);
    }
    using is_transparent = void;
};

// Bitwise operations

template <class _Tp = void>
struct bit_and {
    using __result_type = _Tp;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x & __y;
    }
};

template <>
struct bit_and<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) &
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) & ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) & ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct bit_not {
    constexpr CANN_ASC_STL_API _Tp operator()(const _Tp& __x) const
    {
        return ~__x;
    }
};

template <>
struct bit_not<void> {
    template <class _Tp>
    constexpr CANN_ASC_STL_API auto operator()(_Tp&& __x) const
        noexcept(noexcept(~::asc::std::forward<_Tp>(__x))) -> decltype(~::asc::std::forward<_Tp>(__x))
    {
        return ~::asc::std::forward<_Tp>(__x);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct bit_or {
    using __result_type = _Tp;  // used by valarray

    constexpr CANN_ASC_STL_API _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x | __y;
    }
};

template <>
struct bit_or<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) |
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) | ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) | ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct bit_xor {
    using __result_type = _Tp;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x ^ __y;
    }
};

template <>
struct bit_xor<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) ^
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) ^ ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) ^ ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

// Comparison operations

template <class _Tp = void>
struct equal_to {
    using __result_type = bool;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x == __y;
    }
};

template <>
struct equal_to<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) ==
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) == ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) == ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct not_equal_to {
    using __result_type = bool;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x != __y;
    }
};

template <>
struct not_equal_to<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) !=
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) != ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) != ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct less {
    using __result_type = bool;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x < __y;
    }
};

template <>
struct less<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) <
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) < ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) < ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct less_equal {
    using __result_type = bool;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x <= __y;
    }
};

template <>
struct less_equal<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) <=
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) <= ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) <= ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct greater_equal {
    using __result_type = bool;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x >= __y;
    }
};

template <>
struct greater_equal<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) >=
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) >= ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) >= ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct greater {
    using __result_type = bool;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x > __y;
    }
};

template <>
struct greater<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) >
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) > ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) > ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

// Logical operations

template <class _Tp = void>
struct logical_and {
    using __result_type = bool;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x && __y;
    }
};

template <>
struct logical_and<void> {
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) &&
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) && ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) && ::asc::std::forward<_T2>(__u);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct logical_not {
    using __result_type = bool;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x) const
    {
        return !__x;
    }
};

template <>
struct logical_not<void> {
    template <class _Tp>
    constexpr CANN_ASC_STL_API auto operator()(_Tp&& __x) const
        noexcept(noexcept(!::asc::std::forward<_Tp>(__x))) -> decltype(!::asc::std::forward<_Tp>(__x))
    {
        return !::asc::std::forward<_Tp>(__x);
    }
    using is_transparent = void;
};

template <class _Tp = void>
struct logical_or {
    using __result_type = bool;  // used by valarray

    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x || __y;
    }
};

template <>
struct logical_or<void> {  // NOLINT(build/include_what_you_use)
    template <class _T1, class _T2>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_T1&& __t, _T2&& __u) const
        noexcept(noexcept(::asc::std::forward<_T1>(__t) ||
            ::asc::std::forward<_T2>(__u))) -> decltype(::asc::std::forward<_T1>(__t) || ::asc::std::forward<_T2>(__u))
    {
        return ::asc::std::forward<_T1>(__t) || ::asc::std::forward<_T2>(__u);  // NOLINT(build/include_what_you_use)
    }
    using is_transparent = void;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FUNCTIONAL_OPERATIONS_H
