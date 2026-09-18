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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_MAKE_TUPLE_TYPES_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_MAKE_TUPLE_TYPES_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__fwd/complex.h>
#include <asc/std/__fwd/array.h>
#include <asc/std/__fwd/complex.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__tuple_dir/tuple_indices.h>
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__tuple_dir/tuple_types.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// __make_tuple_types<_Tuple<_Types...>, _Ep, _Sp>::type is a
// __tuple_types<_Types...> using only those _Types in the range [_Sp, _Ep).
// _Sp defaults to 0 and _Ep defaults to tuple_size<_Tuple>.  If _Tuple is a
// lvalue_reference type, then __tuple_types<_Types&...> is the result.

template <class _TupleTypes, class _TupleIndices>
struct __make_tuple_types_flat;

template <template <class...> class _Tuple, class... _Types, size_t... _Idx>
struct __make_tuple_types_flat<_Tuple<_Types...>, __tuple_indices<_Idx...>> {
    using __tuple_types_list = __type_list<_Types...>;

    // Specialization for pair, tuple, and __tuple_types
    template <class _Tp, class _ApplyFn = __apply_cvref_fn<_Tp>>
    using __apply_quals = __tuple_types<__type_call<_ApplyFn, __type_at_c<_Idx, __tuple_types_list>>...>;
};

template <class _Vt, size_t _Np, size_t... _Idx>
struct __make_tuple_types_flat<array<_Vt, _Np>, __tuple_indices<_Idx...>> {
    template <size_t>
    using __value_type = _Vt;
    template <class _Tp, class _ApplyFn = __apply_cvref_fn<_Tp>>
    using __apply_quals = __tuple_types<__type_call<_ApplyFn, __value_type<_Idx>>...>;
};

#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
template <class _Vt, size_t _Np, size_t... _Idx>
struct __make_tuple_types_flat<::std::array<_Vt, _Np>, __tuple_indices<_Idx...>> {
    template <size_t>
    using __value_type = _Vt;
    template <class _Tp, class _ApplyFn = __apply_cvref_fn<_Tp>>
    using __apply_quals = __tuple_types<__type_call<_ApplyFn, __value_type<_Idx>>...>;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

template <class _Vt, size_t... _Idx>
struct __make_tuple_types_flat<complex<_Vt>, __tuple_indices<_Idx...>> {
    static_assert(sizeof...(_Idx) == 2, "__make_tuple_types: complex has only 2 members");
    template <size_t>
    using __value_type = _Vt;
    template <class _Tp, class _ApplyFn = __apply_cvref_fn<_Tp>>
    using __apply_quals = __tuple_types<__type_call<_ApplyFn, __value_type<_Idx>>...>;
};

template <class _Vt, size_t... _Idx>
struct __make_tuple_types_flat<::asc::complex<_Vt>, __tuple_indices<_Idx...>> {
    static_assert(sizeof...(_Idx) == 2, "__make_tuple_types: complex has only 2 members");
    template <size_t>
    using __value_type = _Vt;
    template <class _Tp, class _ApplyFn = __apply_cvref_fn<_Tp>>
    using __apply_quals = __tuple_types<__type_call<_ApplyFn, __value_type<_Idx>>...>;
};

#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
template <class _Vt, size_t... _Idx>
struct __make_tuple_types_flat<::std::complex<_Vt>, __tuple_indices<_Idx...>> {
    static_assert(sizeof...(_Idx) == 2, "__make_tuple_types: complex has only 2 members");
    template <size_t>
    using __value_type = _Vt;
    template <class _Tp, class _ApplyFn = __apply_cvref_fn<_Tp>>
    using __apply_quals = __tuple_types<__type_call<_ApplyFn, __value_type<_Idx>>...>;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

template <class _Tp, size_t _Ep = tuple_size<remove_reference_t<_Tp>>::value, size_t _Sp = 0,
    bool _SameSize = (_Ep == tuple_size<remove_reference_t<_Tp>>::value)>
struct __make_tuple_types {
    static_assert(_Sp <= _Ep, "__make_tuple_types input error");
    using _RawTp = remove_cv_t<remove_reference_t<_Tp>>;
    using _Maker = __make_tuple_types_flat<_RawTp, __make_tuple_indices_t<_Ep, _Sp>>;
    using type = typename _Maker::template __apply_quals<_Tp>;
};

template <class... _Types, size_t _Ep>
struct __make_tuple_types<tuple<_Types...>, _Ep, 0, true> {  // NOLINT(build/include_what_you_use)
    using type = __tuple_types<_Types...>;
};

template <class... _Types, size_t _Ep>
struct __make_tuple_types<__tuple_types<_Types...>, _Ep, 0, true> {
    using type = __tuple_types<_Types...>;
};

template <class _Tp, size_t _Ep = tuple_size<remove_reference_t<_Tp>>::value, size_t _Sp = 0>
using __make_tuple_types_t = typename __make_tuple_types<_Tp, _Ep, _Sp>::type;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_MAKE_TUPLE_TYPES_H
