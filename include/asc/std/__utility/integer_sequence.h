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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_INTEGER_SEQUENCE_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_INTEGER_SEQUENCE_H

#include <asc/std/detail/__config>

#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_integral.h>

#if !CANN_ASC_STL_DETAIL_FREESTANDING()
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#endif

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_FREESTANDING()
// In freestanding (kernel) mode, forward-declare tuple_size/tuple_element
// instead of including tuple_size.h/tuple_element.h, which define
// std::tuple_size<const _Tp> etc. specializations that conflict with the
// standard library <utility> pulled in via kernel_operator.h.
template <class _Tp>
struct tuple_size;

template <size_t _Ip, class _Tp>
struct tuple_element;
#endif

template <size_t...>
struct __tuple_indices {};

template <class _IdxType, _IdxType... _Values>
struct __integer_sequence {
    template <template <class _OIdxType, _OIdxType...> class _ToIndexSeq, class _ToIndexType>
    using __convert = _ToIndexSeq<_ToIndexType, _Values...>;

    template <size_t _Sp>
    using __to_tuple_indices = __tuple_indices<(_Values + _Sp)...>;
};

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_MAKE_INTEGER_SEQ)

template <size_t _Ep, size_t _Sp>
using __make_indices_imp = typename CANN_ASC_STL_DETAIL_BUILTIN_MAKE_INTEGER_SEQ(
    __integer_sequence, size_t, _Ep - _Sp)::template __to_tuple_indices<_Sp>;

#elif defined(CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK)

template <size_t _Ep, size_t _Sp>
using __make_indices_imp = typename __integer_sequence<size_t,
    CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK(_Ep - _Sp)...>::template __to_tuple_indices<_Sp>;

#else  // ^^^ CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK ^^^ / vvv !CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK vvv

namespace __detail {
template <typename _Tp, size_t... _Extra>
struct __repeat;
template <typename _Tp, _Tp... _Np, size_t... _Extra>
struct __repeat<__integer_sequence<_Tp, _Np...>, _Extra...> {
    using type = __integer_sequence<_Tp, _Np..., sizeof...(_Np) + _Np..., 2 * sizeof...(_Np) + _Np...,
        3 * sizeof...(_Np) + _Np..., 4 * sizeof...(_Np) + _Np..., 5 * sizeof...(_Np) + _Np...,
        6 * sizeof...(_Np) + _Np..., 7 * sizeof...(_Np) + _Np..., _Extra...>;
};

template <size_t _Np>
struct __parity;

template <size_t _Np>
struct __make : __parity<_Np % 8>::template __pmake<_Np> {};

template <>
struct __make<0> {
    using type = __integer_sequence<size_t>;
};
template <>
struct __make<1> {
    using type = __integer_sequence<size_t, 0>;
};
template <>
struct __make<2> {
    using type = __integer_sequence<size_t, 0, 1>;
};
template <>
struct __make<3> {
    using type = __integer_sequence<size_t, 0, 1, 2>;
};
template <>
struct __make<4> {
    using type = __integer_sequence<size_t, 0, 1, 2, 3>;
};
template <>
struct __make<5> {
    using type = __integer_sequence<size_t, 0, 1, 2, 3, 4>;
};
template <>
struct __make<6> {
    using type = __integer_sequence<size_t, 0, 1, 2, 3, 4, 5>;
};
template <>
struct __make<7> {
    using type = __integer_sequence<size_t, 0, 1, 2, 3, 4, 5, 6>;
};

template <>
struct __parity<0> {
    template <size_t _Np>
    struct __pmake : __repeat<typename __make<_Np / 8>::type> {};
};
template <>
struct __parity<1> {
    template <size_t _Np>
    struct __pmake : __repeat<typename __make<_Np / 8>::type, _Np - 1> {};
};
template <>
struct __parity<2> {
    template <size_t _Np>
    struct __pmake : __repeat<typename __make<_Np / 8>::type, _Np - 2, _Np - 1> {};
};
template <>
struct __parity<3> {
    template <size_t _Np>
    struct __pmake : __repeat<typename __make<_Np / 8>::type, _Np - 3, _Np - 2, _Np - 1> {};
};
template <>
struct __parity<4> {
    template <size_t _Np>
    struct __pmake : __repeat<typename __make<_Np / 8>::type, _Np - 4, _Np - 3, _Np - 2, _Np - 1> {};
};
template <>
struct __parity<5> {
    template <size_t _Np>
    struct __pmake : __repeat<typename __make<_Np / 8>::type, _Np - 5, _Np - 4, _Np - 3, _Np - 2, _Np - 1> {};
};
template <>
struct __parity<6> {
    template <size_t _Np>
    struct __pmake : __repeat<typename __make<_Np / 8>::type, _Np - 6, _Np - 5, _Np - 4, _Np - 3, _Np - 2, _Np - 1> {};
};
template <>
struct __parity<7> {
    template <size_t _Np>
    struct __pmake
        : __repeat<typename __make<_Np / 8>::type, _Np - 7, _Np - 6, _Np - 5, _Np - 4, _Np - 3, _Np - 2, _Np - 1> {};
};
}  // namespace __detail

template <size_t _Ep, size_t _Sp>
using __make_indices_imp = typename __detail::__make<_Ep - _Sp>::type::template __to_tuple_indices<_Sp>;

#endif  // !CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK

template <class _Tp, _Tp... _Ip>
struct integer_sequence {
    using value_type = _Tp;
    static_assert(is_integral_v<_Tp>, "std::integer_sequence can only be instantiated with an integral type");
    static CANN_ASC_STL_API constexpr size_t size() noexcept
    {
        return sizeof...(_Ip);
    }
};

template <size_t... _Ip>
using index_sequence = integer_sequence<size_t, _Ip...>;

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_MAKE_INTEGER_SEQ)

template <class _Tp, _Tp _Ep>
using __make_integer_sequence = CANN_ASC_STL_DETAIL_BUILTIN_MAKE_INTEGER_SEQ(integer_sequence, _Tp, _Ep);

#elif defined(CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK)

template <class _Tp, _Tp _Ep>
using __make_integer_sequence = integer_sequence<_Tp, CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK(_Ep)...>;

#else  // ^^^ CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK ^^^ / vvv !CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK vvv

template <typename _Tp, _Tp _Np>
using __make_integer_sequence_unchecked =
    typename __detail::__make<_Np>::type::template __convert<integer_sequence, _Tp>;

template <class _Tp, _Tp _Ep>
struct __make_integer_sequence_checked {
    static_assert(is_integral_v<_Tp>, "std::make_integer_sequence can only be instantiated with an integral type");
    static_assert(0 <= _Ep, "std::make_integer_sequence must have a non-negative sequence length");
    // Workaround GCC bug by preventing bad installations when 0 <= _Ep
    // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=68929
    using type = __make_integer_sequence_unchecked<_Tp, 0 <= _Ep ? _Ep : 0>;  // NOLINT(whitespace/operators)
};

template <class _Tp, _Tp _Ep>
using __make_integer_sequence = typename __make_integer_sequence_checked<_Tp, _Ep>::type;

#endif  // !CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK

template <class _Tp, _Tp _Np>
using make_integer_sequence = __make_integer_sequence<_Tp, _Np>;

template <size_t _Np>
using make_index_sequence = make_integer_sequence<size_t, _Np>;

template <class... _Tp>
using index_sequence_for = make_index_sequence<sizeof...(_Tp)>;

// specialize asc::std::tuple_size and asc::std::tuple_element for asc::std::integer_sequence

template <class _Tp, _Tp... _Indices>
struct tuple_size<integer_sequence<_Tp, _Indices...>> : integral_constant<size_t, sizeof...(_Indices)> {};

template <size_t _Ip, class _Tp, _Tp... _Indices>
struct tuple_element<_Ip, integer_sequence<_Tp, _Indices...>> {
    static_assert(
        _Ip < sizeof...(_Indices), "Index out of bounds in asc::std::tuple_element<> (asc::std::integer_sequence)");
    using type = _Tp;
};

template <size_t _Ip, class _Tp, _Tp... _Indices>
struct tuple_element<_Ip, const integer_sequence<_Tp, _Indices...>> {
    static_assert(_Ip < sizeof...(_Indices),
        "Index out of bounds in asc::std::tuple_element<> (const asc::std::integer_sequence)");
    using type = _Tp;
};

template <size_t _Ip, class _Tp, _Tp... _Indices>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp get(integer_sequence<_Tp, _Indices...>) noexcept
{
    static_assert(_Ip < sizeof...(_Indices), "Index out of bounds in asc::std::get<> (asc::std::integer_sequence)");
    constexpr _Tp __indices[]{_Indices...};
    return __indices[_Ip];
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

// tuple protocol for asc::std::integer_sequence

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD

#if CANN_ASC_STL_DETAIL_FREESTANDING()
template <class _Tp>
struct tuple_size;

template <size_t _Ip, class _Tp>
struct tuple_element;
#endif

template <class _Tp, _Tp... _Indices>
struct tuple_size<::asc::std::integer_sequence<_Tp, _Indices...>>
    : ::asc::std::integral_constant<::asc::std::size_t, sizeof...(_Indices)> {};

template <::asc::std::size_t _Ip, class _Tp, _Tp... _Indices>
struct tuple_element<_Ip, ::asc::std::integer_sequence<_Tp, _Indices...>> {
    static_assert(
        _Ip < sizeof...(_Indices), "Index out of bounds in std::tuple_element<> (asc::std::integer_sequence)");
    using type = _Tp;
};

template <::asc::std::size_t _Ip, class _Tp, _Tp... _Indices>
struct tuple_element<_Ip, const ::asc::std::integer_sequence<_Tp, _Indices...>> {
    static_assert(
        _Ip < sizeof...(_Indices), "Index out of bounds in std::tuple_element<> (const asc::std::integer_sequence)");
    using type = _Tp;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_INTEGER_SEQUENCE_H
