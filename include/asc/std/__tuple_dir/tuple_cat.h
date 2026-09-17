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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_CAT_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_CAT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__tuple_dir/tie.h>
#include <asc/std/__tuple_dir/tuple.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__tuple_dir/tuple_indices.h>
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__tuple_dir/tuple_types.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp, class _Up>
struct __tuple_cat_type;

template <class... _Ttypes, class... _Utypes>
struct __tuple_cat_type<tuple<_Ttypes...>, __tuple_types<_Utypes...>> {
    using type = tuple<_Ttypes..., _Utypes...>;
};

template <class _ResultTuple, bool _Is_Tuple0TupleLike, class... _Tuples>
struct __tuple_cat_return_1 {};

template <class... _Types, class _Tuple0>
struct __tuple_cat_return_1<tuple<_Types...>, true, _Tuple0> {
    using type = typename __tuple_cat_type<tuple<_Types...>, __make_tuple_types_t<remove_cvref_t<_Tuple0>>>::type;
};

template <class... _Types, class _Tuple0, class _Tuple1, class... _Tuples>
struct __tuple_cat_return_1<tuple<_Types...>, true, _Tuple0, _Tuple1, _Tuples...>
    : public __tuple_cat_return_1<
          typename __tuple_cat_type<tuple<_Types...>, __make_tuple_types_t<remove_cvref_t<_Tuple0>>>::type,
          __tuple_like_ext<remove_reference_t<_Tuple1>>, _Tuple1, _Tuples...> {};

template <class... _Tuples>
struct __tuple_cat_return;

template <class _Tuple0, class... _Tuples>
struct __tuple_cat_return<_Tuple0, _Tuples...>
    : public __tuple_cat_return_1<tuple<>, __tuple_like_ext<remove_reference_t<_Tuple0>>, _Tuple0, _Tuples...> {};

template <>
struct __tuple_cat_return<> {
    using type = tuple<>;
};

CANN_ASC_STL_API constexpr tuple<> tuple_cat()
{
    return tuple<>();
}

template <class _Rp, class _Indices, class _Tuple0, class... _Tuples>
struct __tuple_cat_return_ref_imp;

template <class... _Types, size_t... _I0, class _Tuple0>
struct __tuple_cat_return_ref_imp<tuple<_Types...>, __tuple_indices<_I0...>, _Tuple0> {
    using _T0 = remove_reference_t<_Tuple0>;
    using type = tuple<_Types..., __copy_cvref_t<_Tuple0, tuple_element_t<_I0, _T0>>&&...>;
};

template <class... _Types, size_t... _I0, class _Tuple0, class _Tuple1, class... _Tuples>
struct __tuple_cat_return_ref_imp<tuple<_Types...>, __tuple_indices<_I0...>, _Tuple0, _Tuple1, _Tuples...>
    : public __tuple_cat_return_ref_imp<
          tuple<_Types..., __copy_cvref_t<_Tuple0, tuple_element_t<_I0, remove_reference_t<_Tuple0>>>&&...>,
          __make_tuple_indices_t<tuple_size<remove_reference_t<_Tuple1>>::value>, _Tuple1, _Tuples...> {};

template <class _Tuple0, class... _Tuples>
struct __tuple_cat_return_ref
    : public __tuple_cat_return_ref_imp<tuple<>, __make_tuple_indices_t<tuple_size<remove_reference_t<_Tuple0>>::value>,
          _Tuple0, _Tuples...> {};

template <class _Types, class _I0, class _J0>
struct __tuple_cat;

template <class... _Types, size_t... _I0, size_t... _J0>
struct __tuple_cat<tuple<_Types...>, __tuple_indices<_I0...>, __tuple_indices<_J0...>> {
    template <class _Tuple0>
    CANN_ASC_STL_API constexpr typename __tuple_cat_return_ref<tuple<_Types...>&&, _Tuple0&&>::type operator()(
        [[maybe_unused]] tuple<_Types...> __t, _Tuple0&& __t0)
    {
        return ::asc::std::forward_as_tuple(::asc::std::forward<_Types>(::asc::std::get<_I0>(__t))...,
            ::asc::std::get<_J0>(::asc::std::forward<_Tuple0>(__t0))...);
    }

    template <class _Tuple0, class _Tuple1, class... _Tuples>
    CANN_ASC_STL_API constexpr
        typename __tuple_cat_return_ref<tuple<_Types...>&&, _Tuple0&&, _Tuple1&&, _Tuples&&...>::type
        operator()([[maybe_unused]] tuple<_Types...> __t, _Tuple0&& __t0, _Tuple1&& __t1, _Tuples&&... __tpls)
    {
        using _T0 = remove_reference_t<_Tuple0>;
        using _T1 = remove_reference_t<_Tuple1>;
        return __tuple_cat<tuple<_Types..., __copy_cvref_t<_Tuple0, tuple_element_t<_J0, _T0>>&&...>,
            __make_tuple_indices_t<sizeof...(_Types) + tuple_size<_T0>::value>,
            __make_tuple_indices_t<tuple_size<_T1>::value>>()(
            ::asc::std::forward_as_tuple(::asc::std::forward<_Types>(::asc::std::get<_I0>(__t))...,
                ::asc::std::get<_J0>(::asc::std::forward<_Tuple0>(__t0))...),
            ::asc::std::forward<_Tuple1>(__t1), ::asc::std::forward<_Tuples>(__tpls)...);
    }
};

template <class _Tuple0, class... _Tuples>
CANN_ASC_STL_API constexpr typename __tuple_cat_return<_Tuple0, _Tuples...>::type tuple_cat(
    _Tuple0&& __t0, _Tuples&&... __tpls)
{
    using _T0 = remove_reference_t<_Tuple0>;
    return __tuple_cat<tuple<>, __tuple_indices<>, __make_tuple_indices_t<tuple_size<_T0>::value>>()(
        tuple<>(),  // NOLINT(build/include_what_you_use)
        ::asc::std::forward<_Tuple0>(__t0),
        ::asc::std::forward<_Tuples>(__tpls)...);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_CAT_H
