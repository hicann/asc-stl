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
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_integral.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <size_t...>
struct __tuple_indices {};

template <class IdxType, IdxType... Values>
struct __integer_sequence {
    template <template <class OIdxType, OIdxType...> class ToIndexSeq, class ToIndexType>
    using __convert = ToIndexSeq<ToIndexType, Values...>;

    template <size_t Sp>
    using __to_tuple_indices = __tuple_indices<(Values + Sp)...>;
};

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__make_integer_seq)

#define CANN_ASC_STL_DETAIL_BUILTIN_MAKE_INTEGER_SEQ(...) __make_integer_seq<__VA_ARGS__>

template <size_t Ep, size_t Sp>
using __make_indices_imp = typename CANN_ASC_STL_DETAIL_BUILTIN_MAKE_INTEGER_SEQ(
    __integer_sequence, size_t, Ep - Sp)::template __to_tuple_indices<Sp>;

#elif CANN_ASC_STL_DETAIL_HAS_BUILTIN(__integer_pack)

#define CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK(...) __integer_pack(__VA_ARGS__)

template <size_t Ep, size_t Sp>
using __make_indices_imp = typename __integer_sequence<size_t,
    CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK(Ep - Sp)...>::template __to_tuple_indices<Sp>;

#else

// 无编译器内建时的倍增展开回退（每次递归翻 8 倍）。
namespace __detail {
template <class Tp, size_t... Extra>
struct __repeat;

template <class Tp, Tp... Np, size_t... Extra>
struct __repeat<__integer_sequence<Tp, Np...>, Extra...> {
    using type = __integer_sequence<Tp, Np..., sizeof...(Np) + Np..., 2 * sizeof...(Np) + Np...,
        3 * sizeof...(Np) + Np..., 4 * sizeof...(Np) + Np..., 5 * sizeof...(Np) + Np..., 6 * sizeof...(Np) + Np...,
        7 * sizeof...(Np) + Np..., Extra...>;
};

template <size_t Np>
struct __parity;

template <size_t Np>
struct __make : __parity<Np % 8>::template __pmake<Np> {};

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
    template <size_t Np>
    struct __pmake : __repeat<typename __make<Np / 8>::type> {};
};

template <>
struct __parity<1> {
    template <size_t Np>
    struct __pmake : __repeat<typename __make<Np / 8>::type, Np - 1> {};
};

template <>
struct __parity<2> {
    template <size_t Np>
    struct __pmake : __repeat<typename __make<Np / 8>::type, Np - 2, Np - 1> {};
};

template <>
struct __parity<3> {
    template <size_t Np>
    struct __pmake : __repeat<typename __make<Np / 8>::type, Np - 3, Np - 2, Np - 1> {};
};

template <>
struct __parity<4> {
    template <size_t Np>
    struct __pmake : __repeat<typename __make<Np / 8>::type, Np - 4, Np - 3, Np - 2, Np - 1> {};
};

template <>
struct __parity<5> {
    template <size_t Np>
    struct __pmake : __repeat<typename __make<Np / 8>::type, Np - 5, Np - 4, Np - 3, Np - 2, Np - 1> {};
};

template <>
struct __parity<6> {
    template <size_t Np>
    struct __pmake : __repeat<typename __make<Np / 8>::type, Np - 6, Np - 5, Np - 4, Np - 3, Np - 2, Np - 1> {};
};

template <>
struct __parity<7> {
    template <size_t Np>
    struct __pmake : __repeat<typename __make<Np / 8>::type, Np - 7, Np - 6, Np - 5, Np - 4, Np - 3, Np - 2, Np - 1> {};
};

}  // namespace __detail

template <size_t Ep, size_t Sp>
using __make_indices_imp = typename __detail::__make<Ep - Sp>::type::template __to_tuple_indices<Sp>;

#endif

template <class T, T... Ip>
struct integer_sequence {
    using value_type = T;
    static_assert(is_integral_v<T>, "std::integer_sequence can only be instantiated with an integral type");
    static CANN_ASC_STL_API constexpr size_t size() noexcept
    {
        return sizeof...(Ip);
    }
};

template <size_t... Ip>
using index_sequence = integer_sequence<size_t, Ip...>;

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_MAKE_INTEGER_SEQ)

template <class T, T Ep>
using __make_integer_sequence = CANN_ASC_STL_DETAIL_BUILTIN_MAKE_INTEGER_SEQ(integer_sequence, T, Ep);

#elif defined(CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK)

template <class T, T Ep>
using __make_integer_sequence = integer_sequence<T, CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK(Ep)...>;

#else

template <class T, T Np>
using __make_integer_sequence_unchecked = typename __detail::__make<Np>::type::template __convert<integer_sequence, T>;

template <class T, T Ep>
using __make_integer_sequence = __make_integer_sequence_unchecked<T, Ep>;

#endif

template <class T, T Np>
struct __make_integer_sequence_checked {
    static_assert(is_integral_v<T>, "std::make_integer_sequence can only be instantiated with an integral type");
    static_assert(0 <= Np, "std::make_integer_sequence must have a non-negative sequence length");
    // Guard against bad instantiations when 0 <= Np does not hold.
    static constexpr T checked = 0 <= Np ? Np : 0;
    using type = __make_integer_sequence<T, checked>;
};

template <class T, T Np>
using __make_integer_sequence_t = typename __make_integer_sequence_checked<T, Np>::type;

template <class T, T Np>
using make_integer_sequence = __make_integer_sequence_t<T, Np>;

template <size_t Np>
using make_index_sequence = make_integer_sequence<size_t, Np>;

template <class... T>
using index_sequence_for = make_index_sequence<sizeof...(T)>;

template <class T, T... Indices>
struct tuple_size<integer_sequence<T, Indices...>> : integral_constant<size_t, sizeof...(Indices)> {};

template <size_t Ip, class T, T... Indices>
struct tuple_element<Ip, integer_sequence<T, Indices...>> {
    static_assert(
        Ip < sizeof...(Indices), "Index out of bounds in asc::std::tuple_element<> (asc::std::integer_sequence)");
    using type = T;
};

template <size_t Ip, class T, T... Indices>
struct tuple_element<Ip, const integer_sequence<T, Indices...>> {
    static_assert(
        Ip < sizeof...(Indices), "Index out of bounds in asc::std::tuple_element<> (const asc::std::integer_sequence)");
    using type = T;
};

template <size_t Ip, class T, T... Indices>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T get(integer_sequence<T, Indices...>) noexcept
{
    static_assert(Ip < sizeof...(Indices), "Index out of bounds in asc::std::get<> (asc::std::integer_sequence)");
    constexpr T indices[]{Indices...};
    return indices[Ip];
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_INTEGER_SEQUENCE_H
