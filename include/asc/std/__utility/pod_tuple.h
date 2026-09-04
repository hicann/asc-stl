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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_POD_TUPLE_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_POD_TUPLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/undefined.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_NO_CWG1835
#endif

#ifdef CANN_ASC_STL_DETAIL_NO_CWG1835
#define CANN_ASC_STL_DETAIL_CWG1835_TEMPLATE
#else
#define CANN_ASC_STL_DETAIL_CWG1835_TEMPLATE template
#endif

template <class... _Ts>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __tuple;

namespace __detail {
template <class _Fn, class _Tuple, class... _Us>
extern __undefined<_Fn, _Tuple, _Us...> __applicable_v;

template <class _Fn, class... _Ts, class... _Us>
inline constexpr bool __applicable_v<_Fn, __tuple<_Ts...>, _Us...> = __is_callable_v<_Fn, _Us..., _Ts...>;

template <class _Fn, class... _Ts, class... _Us>
inline constexpr bool __applicable_v<_Fn, __tuple<_Ts...>&, _Us...> = __is_callable_v<_Fn, _Us..., _Ts&...>;

template <class _Fn, class... _Ts, class... _Us>
inline constexpr bool __applicable_v<_Fn, const __tuple<_Ts...>&, _Us...> = __is_callable_v<_Fn, _Us..., const _Ts&...>;

template <class _Fn, class _Tuple, class... _Us>
extern __undefined<_Fn, _Tuple, _Us...> __nothrow_applicable_v;

template <class _Fn, class... _Ts, class... _Us>
inline constexpr bool __nothrow_applicable_v<_Fn, __tuple<_Ts...>, _Us...> =
    __is_nothrow_callable_v<_Fn, _Us..., _Ts...>;

template <class _Fn, class... _Ts, class... _Us>
inline constexpr bool __nothrow_applicable_v<_Fn, __tuple<_Ts...>&, _Us...> =
    __is_nothrow_callable_v<_Fn, _Us..., _Ts&...>;

template <class _Fn, class... _Ts, class... _Us>
inline constexpr bool __nothrow_applicable_v<_Fn, const __tuple<_Ts...>&, _Us...> =
    __is_nothrow_callable_v<_Fn, _Us..., const _Ts&...>;

template <size_t _Index, class _Ty>
struct __box {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Ty __value;
};

template <class _Index, class... _Ts>
struct __tupl_base;

template <size_t... _Index, class... _Ts>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __tupl_base<index_sequence<_Index...>, _Ts...> : __box<_Index, _Ts>... {
    static constexpr size_t __size = sizeof...(_Ts);

    template <class _Fn, class _Self, class... _Us>
    CANN_ASC_STL_DETAIL_TRIVIAL_API static constexpr auto __apply(_Fn&& __fn, _Self&& __self, _Us&&... __us) noexcept(
        __nothrow_applicable_v<_Fn, _Self, _Us...>) -> decltype(auto)
    {
        return static_cast<_Fn&&>(__fn)(static_cast<_Us&&>(__us)...,
            static_cast<_Self&&>(__self).CANN_ASC_STL_DETAIL_CWG1835_TEMPLATE __box<_Index, _Ts>::__value...);
    }
};
}  // namespace __detail

template <class... _Ts>
struct __tuple : __detail::__tupl_base<index_sequence_for<_Ts...>, _Ts...> {};

template <>
struct __tuple<> {
    static constexpr size_t __size = 0;
};

template <class _Tp0>
struct __tuple<_Tp0> {
    static constexpr size_t __size = 1;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp0 __val0;
};

template <class _Tp0, class _Tp1>
struct __tuple<_Tp0, _Tp1> {
    static constexpr size_t __size = 2;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp0 __val0;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp1 __val1;
};

template <class _Tp0, class _Tp1, class _Tp2>
struct __tuple<_Tp0, _Tp1, _Tp2> {
    static constexpr size_t __size = 3;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp0 __val0;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp1 __val1;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp2 __val2;
};

template <class _Tp0, class _Tp1, class _Tp2, class _Tp3>
struct __tuple<_Tp0, _Tp1, _Tp2, _Tp3> {
    static constexpr size_t __size = 4;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp0 __val0;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp1 __val1;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp2 __val2;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp3 __val3;
};

template <class _Tp0, class _Tp1, class _Tp2, class _Tp3, class _Tp4>
struct __tuple<_Tp0, _Tp1, _Tp2, _Tp3, _Tp4> {
    static constexpr size_t __size = 5;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp0 __val0;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp1 __val1;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp2 __val2;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp3 __val3;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp4 __val4;
};

template <class _Tp0, class _Tp1, class _Tp2, class _Tp3, class _Tp4, class _Tp5>
struct __tuple<_Tp0, _Tp1, _Tp2, _Tp3, _Tp4, _Tp5> {
    static constexpr size_t __size = 6;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp0 __val0;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp1 __val1;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp2 __val2;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp3 __val3;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp4 __val4;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp5 __val5;
};

template <class _Tp0, class _Tp1, class _Tp2, class _Tp3, class _Tp4, class _Tp5, class _Tp6>
struct __tuple<_Tp0, _Tp1, _Tp2, _Tp3, _Tp4, _Tp5, _Tp6> {
    static constexpr size_t __size = 7;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp0 __val0;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp1 __val1;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp2 __val2;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp3 __val3;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp4 __val4;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp5 __val5;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp6 __val6;
};

template <class _Tp0, class _Tp1, class _Tp2, class _Tp3, class _Tp4, class _Tp5, class _Tp6, class _Tp7>
struct __tuple<_Tp0, _Tp1, _Tp2, _Tp3, _Tp4, _Tp5, _Tp6, _Tp7> {
    static constexpr size_t __size = 8;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp0 __val0;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp1 __val1;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp2 __val2;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp3 __val3;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp4 __val4;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp5 __val5;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp6 __val6;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp7 __val7;
};

template <class... _Ts>
CANN_ASC_STL_HOST_DEVICE __tuple(_Ts...) -> __tuple<_Ts...>;

#define CANN_ASC_STL_DETAIL_TUPLE_GET(_Index) , static_cast<_Tuple&&>(__tupl).__val##_Index

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fn, class _Tuple, class... _Us)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__detail::__applicable_v<_Fn, _Tuple, _Us...>)
CANN_ASC_STL_DETAIL_TRIVIAL_API constexpr auto __apply(_Fn&& __fn, _Tuple&& __tupl, _Us&&... __us) noexcept(
    __detail::__nothrow_applicable_v<_Fn, _Tuple, _Us...>) -> decltype(auto)
{
    constexpr size_t __size = remove_reference_t<_Tuple>::__size;
    if constexpr (__size == 0) {
        return static_cast<_Fn&&>(__fn)(static_cast<_Us&&>(__us)...);
    } else if constexpr (__size == 1) {
        return static_cast<_Fn&&>(__fn)(
            static_cast<_Us&&>(__us)... CANN_ASC_STL_DETAIL_PP_REPEAT(1, CANN_ASC_STL_DETAIL_TUPLE_GET));
    } else if constexpr (__size == 2) {
        return static_cast<_Fn&&>(__fn)(
            static_cast<_Us&&>(__us)... CANN_ASC_STL_DETAIL_PP_REPEAT(2, CANN_ASC_STL_DETAIL_TUPLE_GET));
    } else if constexpr (__size == 3) {
        return static_cast<_Fn&&>(__fn)(
            static_cast<_Us&&>(__us)... CANN_ASC_STL_DETAIL_PP_REPEAT(3, CANN_ASC_STL_DETAIL_TUPLE_GET));
    } else if constexpr (__size == 4) {
        return static_cast<_Fn&&>(__fn)(
            static_cast<_Us&&>(__us)... CANN_ASC_STL_DETAIL_PP_REPEAT(4, CANN_ASC_STL_DETAIL_TUPLE_GET));
    } else if constexpr (__size == 5) {
        return static_cast<_Fn&&>(__fn)(
            static_cast<_Us&&>(__us)... CANN_ASC_STL_DETAIL_PP_REPEAT(5, CANN_ASC_STL_DETAIL_TUPLE_GET));
    } else if constexpr (__size == 6) {
        return static_cast<_Fn&&>(__fn)(
            static_cast<_Us&&>(__us)... CANN_ASC_STL_DETAIL_PP_REPEAT(6, CANN_ASC_STL_DETAIL_TUPLE_GET));
    } else if constexpr (__size == 7) {
        return static_cast<_Fn&&>(__fn)(
            static_cast<_Us&&>(__us)... CANN_ASC_STL_DETAIL_PP_REPEAT(7, CANN_ASC_STL_DETAIL_TUPLE_GET));
    } else if constexpr (__size == 8) {
        return static_cast<_Fn&&>(__fn)(
            static_cast<_Us&&>(__us)... CANN_ASC_STL_DETAIL_PP_REPEAT(8, CANN_ASC_STL_DETAIL_TUPLE_GET));
    } else {
        return __tupl.__apply(static_cast<_Fn&&>(__fn), static_cast<_Tuple&&>(__tupl), static_cast<_Us&&>(__us)...);
    }
}

#undef CANN_ASC_STL_DETAIL_TUPLE_GET

template <class _Fn, class _Tuple, class... _Us>
using __apply_result_t = decltype(__apply(declval<_Fn>(), declval<_Tuple>(), declval<_Us>()...));

template <class _Fn, class _Tuple, class... _Us>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __applicable = __detail::__applicable_v<_Fn, _Tuple, _Us...>;

template <class _Fn, class _Tuple, class... _Us>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __nothrow_applicable = __detail::__nothrow_applicable_v<_Fn, _Tuple, _Us...>;

namespace __detail {
template <size_t _Index, class _Value>
CANN_ASC_STL_DETAIL_TRIVIAL_API constexpr auto __get(__box<_Index, _Value>&& __box_value) noexcept -> _Value&&
{
    return static_cast<_Value&&>(__box_value.__value);
}

template <size_t _Index, class _Value>
CANN_ASC_STL_DETAIL_TRIVIAL_API constexpr auto __get(__box<_Index, _Value>& __box_value) noexcept -> _Value&
{
    return __box_value.__value;
}

template <size_t _Index, class _Value>
CANN_ASC_STL_DETAIL_TRIVIAL_API constexpr auto __get(const __box<_Index, _Value>& __box_value) noexcept -> const _Value&
{
    return __box_value.__value;
}
}  // namespace __detail

template <size_t _Index, class _Tuple>
CANN_ASC_STL_DETAIL_TRIVIAL_API constexpr auto __get(_Tuple&& __tupl) noexcept -> auto&&
{
    constexpr size_t __size = remove_reference_t<_Tuple>::__size;
    static_assert(_Index < __size, "Index out of bounds in __get");

    if constexpr (__size > 8) {
        return __detail::__get<_Index>(static_cast<_Tuple&&>(__tupl));
    } else if constexpr (_Index == 0) {
        return static_cast<_Tuple&&>(__tupl).__val0;
    } else if constexpr (_Index == 1) {
        return static_cast<_Tuple&&>(__tupl).__val1;
    } else if constexpr (_Index == 2) {
        return static_cast<_Tuple&&>(__tupl).__val2;
    } else if constexpr (_Index == 3) {
        return static_cast<_Tuple&&>(__tupl).__val3;
    } else if constexpr (_Index == 4) {
        return static_cast<_Tuple&&>(__tupl).__val4;
    } else if constexpr (_Index == 5) {
        return static_cast<_Tuple&&>(__tupl).__val5;
    } else if constexpr (_Index == 6) {
        return static_cast<_Tuple&&>(__tupl).__val6;
    } else if constexpr (_Index == 7) {
        return static_cast<_Tuple&&>(__tupl).__val7;
    } else {
        return static_cast<_Tuple&&>(__tupl).__val7;
    }
}

template <class... _Ts>
using __decayed_tuple = __tuple<decay_t<_Ts>...>;

template <class _First, class _Second>
struct __pair {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _First first;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Second second;
};

template <class _First, class _Second>
CANN_ASC_STL_HOST_DEVICE __pair(_First, _Second) -> __pair<_First, _Second>;

template <class _Tuple>
extern __undefined<_Tuple> __tuple_size_v;

template <class... _Ts>
inline constexpr size_t __tuple_size_v<__tuple<_Ts...>> = sizeof...(_Ts);
template <class... _Ts>
inline constexpr size_t __tuple_size_v<const __tuple<_Ts...>> = sizeof...(_Ts);
template <class... _Ts>
inline constexpr size_t __tuple_size_v<__tuple<_Ts...>&> = sizeof...(_Ts);
template <class... _Ts>
inline constexpr size_t __tuple_size_v<const __tuple<_Ts...>&> = sizeof...(_Ts);

template <class _Tp>
CANN_ASC_STL_API auto __remove_rvalue_ref(_Tp&&) noexcept -> _Tp;

template <size_t _Index, class _Tuple>
using __tuple_element_t = decltype(__remove_rvalue_ref(__get<_Index>(declval<_Tuple>())));

#undef CANN_ASC_STL_DETAIL_CWG1835_TEMPLATE
#undef CANN_ASC_STL_DETAIL_NO_CWG1835

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_POD_TUPLE_H
