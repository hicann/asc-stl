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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_OPERATIONS_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_OPERATIONS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/binary_function.h>
#include <asc/std/__functional/unary_function.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// Arithmetic operations

template <class _Tp = void>
struct plus : __binary_function<_Tp, _Tp, _Tp> {
    using __result_type = _Tp;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x + __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(plus);

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
struct minus : __binary_function<_Tp, _Tp, _Tp> {
    using __result_type = _Tp;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x - __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(minus);

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
struct multiplies : __binary_function<_Tp, _Tp, _Tp> {
    using __result_type = _Tp;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x * __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(multiplies);

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
struct divides : __binary_function<_Tp, _Tp, _Tp> {
    using __result_type = _Tp;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x / __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(divides);

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
struct modulus : __binary_function<_Tp, _Tp, _Tp> {
    using __result_type = _Tp;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x % __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(modulus);

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
struct negate : __unary_function<_Tp, _Tp> {
    using __result_type = _Tp;  // used by valarray
    constexpr CANN_ASC_STL_API _Tp operator()(const _Tp& __x) const
    {
        return -__x;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(negate);

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
struct bit_and : __binary_function<_Tp, _Tp, _Tp> {
    using __result_type = _Tp;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x & __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(bit_and);

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
struct bit_not : __unary_function<_Tp, _Tp> {
    constexpr CANN_ASC_STL_API _Tp operator()(const _Tp& __x) const
    {
        return ~__x;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(bit_not);

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
struct bit_or : __binary_function<_Tp, _Tp, _Tp> {
    using __result_type = _Tp;  // used by valarray
    constexpr CANN_ASC_STL_API _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x | __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(bit_or);

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
struct bit_xor : __binary_function<_Tp, _Tp, _Tp> {
    using __result_type = _Tp;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x ^ __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(bit_xor);

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
struct equal_to : __binary_function<_Tp, _Tp, bool> {
    using __result_type = bool;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x == __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(equal_to);

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
struct not_equal_to : __binary_function<_Tp, _Tp, bool> {
    using __result_type = bool;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x != __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(not_equal_to);

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
struct less : __binary_function<_Tp, _Tp, bool> {
    using __result_type = bool;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x < __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(less);

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
struct less_equal : __binary_function<_Tp, _Tp, bool> {
    using __result_type = bool;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x <= __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(less_equal);

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
struct greater_equal : __binary_function<_Tp, _Tp, bool> {
    using __result_type = bool;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x >= __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(greater_equal);

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
struct greater : __binary_function<_Tp, _Tp, bool> {
    using __result_type = bool;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x > __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(greater);

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
struct logical_and : __binary_function<_Tp, _Tp, bool> {
    using __result_type = bool;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x && __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(logical_and);

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
struct logical_not : __unary_function<_Tp, bool> {
    using __result_type = bool;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x) const
    {
        return !__x;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(logical_not);

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
struct logical_or : __binary_function<_Tp, _Tp, bool> {
    using __result_type = bool;  // used by valarray
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Tp& __y) const
    {
        return __x || __y;
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(logical_or);

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

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_OPERATIONS_H
