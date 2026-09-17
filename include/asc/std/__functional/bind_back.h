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

// -*- C++ -*-
#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BIND_BACK_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BIND_BACK_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/perfect_forward.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/tuple>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <size_t _NBound, class = make_index_sequence<_NBound>>
struct __bind_back_op;

template <size_t _NBound, size_t... _Ip>
struct __bind_back_op<_NBound, index_sequence<_Ip...>> {
    template <class _Fn, class _BoundArgs, class... _Args>
    CANN_ASC_STL_API constexpr auto operator()(_Fn&& __f, _BoundArgs&& __bound_args, _Args&&... __args) const
        noexcept(noexcept(::asc::std::invoke(::asc::std::forward<_Fn>(__f), ::asc::std::forward<_Args>(__args)...,
            ::asc::std::get<_Ip>(::asc::std::forward<_BoundArgs>(__bound_args))...)))
            -> decltype(::asc::std::invoke(::asc::std::forward<_Fn>(__f), ::asc::std::forward<_Args>(__args)...,
                ::asc::std::get<_Ip>(::asc::std::forward<_BoundArgs>(__bound_args))...))
    {
        return ::asc::std::invoke(::asc::std::forward<_Fn>(__f), ::asc::std::forward<_Args>(__args)...,
            ::asc::std::get<_Ip>(::asc::std::forward<_BoundArgs>(__bound_args))...);
    }
};

template <class _Fn, class _BoundArgs>
struct __bind_back_t : __perfect_forward<__bind_back_op<tuple_size_v<_BoundArgs>>, _Fn, _BoundArgs> {
    using __base = __perfect_forward<__bind_back_op<tuple_size_v<_BoundArgs>>, _Fn, _BoundArgs>;
    using __base::__base;
    CANN_ASC_STL_API constexpr __bind_back_t() noexcept(
        ::asc::std::is_nothrow_default_constructible_v<__base>) = default;
};

template <class _Fn, class... _Args,
    class = enable_if_t<__fold_and_v<is_constructible_v<decay_t<_Fn>, _Fn>, is_move_constructible_v<decay_t<_Fn>>,
        is_constructible_v<decay_t<_Args>, _Args>..., is_move_constructible_v<decay_t<_Args>>...>>>
CANN_ASC_STL_API constexpr auto __bind_back(_Fn&& __f, _Args&&... __args) noexcept(
    noexcept(__bind_back_t<decay_t<_Fn>, tuple<decay_t<_Args>...>>(
        ::asc::std::forward<_Fn>(__f), ::asc::std::forward_as_tuple(::asc::std::forward<_Args>(__args)...))))
    -> decltype(__bind_back_t<decay_t<_Fn>, tuple<decay_t<_Args>...>>(
        ::asc::std::forward<_Fn>(__f), ::asc::std::forward_as_tuple(::asc::std::forward<_Args>(__args)...)))
{
    return __bind_back_t<decay_t<_Fn>, tuple<decay_t<_Args>...>>(  // NOLINT(build/include_what_you_use)
        ::asc::std::forward<_Fn>(__f),
        ::asc::std::forward_as_tuple(::asc::std::forward<_Args>(__args)...));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BIND_BACK_H
