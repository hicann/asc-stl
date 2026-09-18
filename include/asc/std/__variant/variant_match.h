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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_MATCH_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_MATCH_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/invoke.h>
#include <asc/std/__asc/is_non_narrowing_convertible.h>
#include <asc/std/__tuple_dir/tuple_indices.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__utility/integer_sequence.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __variant_detail {
struct __no_narrowing_check {
    template <class _Dest, class _Source>
    using _Apply = type_identity<_Dest>;
};

struct __narrowing_check {
    template <class _Dest, class _Source, bool = __asc_internal::__is_non_narrowing_convertible<_Dest, _Source>::value>
    struct __narrowing_check_impl {};

    template <class _Dest, class _Source>
    struct __narrowing_check_impl<_Dest, _Source, true> {
        using type = type_identity<_Dest>;
    };

    template <class _Dest, class _Source>
    using _Apply = typename __narrowing_check_impl<_Dest, _Source>::type;
};

template <class _Dest, class _Source>
using __check_for_narrowing = typename conditional_t<
#ifdef CANN_ASC_STL_DETAIL_ENABLE_NARROWING_CONVERSIONS_IN_VARIANT
    false &&
#endif  // CANN_ASC_STL_DETAIL_ENABLE_NARROWING_CONVERSIONS_IN_VARIANT
        is_arithmetic_v<_Dest>,
    __narrowing_check, __no_narrowing_check>::template _Apply<_Dest, _Source>;

template <class _Tp, size_t _Idx>
struct __overload {
    template <class _Up>
    CANN_ASC_STL_API auto operator()(_Tp, _Up&&) const -> __check_for_narrowing<_Tp, _Up>;
};

template <class _Tp, size_t>
struct __overload_bool {
    template <class _Up, class _Ap = remove_cvref_t<_Up>>
    CANN_ASC_STL_API auto operator()(bool, _Up&&) const -> enable_if_t<is_same_v<_Ap, bool>, type_identity<_Tp>>;
};

template <size_t _Idx>
struct __overload<bool, _Idx> : __overload_bool<bool, _Idx> {};
template <size_t _Idx>
struct __overload<bool const, _Idx> : __overload_bool<bool const, _Idx> {};
template <size_t _Idx>
struct __overload<bool volatile, _Idx> : __overload_bool<bool volatile, _Idx> {};
template <size_t _Idx>
struct __overload<bool const volatile, _Idx> : __overload_bool<bool const volatile, _Idx> {};

template <class... _Bases>
struct __all_overloads : _Bases... {
    CANN_ASC_STL_API void operator()() const;
    using _Bases::operator()...;
};

template <class IdxSeq>
struct __make_overloads_imp;

template <size_t... _Idx>
struct __make_overloads_imp<__tuple_indices<_Idx...>> {
    template <class... _Types>
    using _Apply = __all_overloads<__overload<_Types, _Idx>...>;
};

template <class... _Types>
using _MakeOverloads =
    typename __make_overloads_imp<__make_indices_imp<sizeof...(_Types), 0>>::template _Apply<_Types...>;

template <class _Tp, class... _Types>
using __best_match_t = typename invoke_result_t<_MakeOverloads<_Types...>, _Tp, _Tp>::type;
}  // namespace __variant_detail

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_MATCH_H
