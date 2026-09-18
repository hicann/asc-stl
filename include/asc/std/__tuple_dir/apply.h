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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_APPLY_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_APPLY_H

#include <asc/std/detail/__config>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__tuple_dir/get.h>
#include <asc/std/__tuple_dir/tuple.h>
#include <asc/std/__tuple_dir/tuple_indices.h>
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__tuple_dir/tuple_types.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/move.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __apply_detail {
template <class _Fd, class _Tuple, size_t... _Ip>
CANN_ASC_STL_API constexpr decltype(auto) __apply_impl(_Fd&& __f, _Tuple&& __t, index_sequence<_Ip...>)
{
    using ::asc::std::get;
    return ::asc::std::__invoke(::asc::std::forward<_Fd>(__f), get<_Ip>(::asc::std::forward<_Tuple>(__t))...);
}
}  // namespace __apply_detail

//! @brief Invokes the callable @p __f with the elements of @p __t as arguments.
template <class _Fd, class _Tuple>
CANN_ASC_STL_API constexpr decltype(auto) apply(_Fd&& __f, _Tuple&& __t)
{
    return __apply_detail::__apply_impl(::asc::std::forward<_Fd>(__f), ::asc::std::forward<_Tuple>(__t),
        make_index_sequence<tuple_size<remove_reference_t<_Tuple>>::value>{});
}

//! @brief Constructs a T element-wise from a tuple (the companion of apply).
template <class _Tp, class _Tuple, size_t... _Idx>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp __make_from_tuple_impl(_Tuple&& __t, __tuple_indices<_Idx...>) noexcept(
    noexcept(_Tp(::asc::std::get<_Idx>(::asc::std::forward<_Tuple>(__t))...)))
{
    return _Tp(::asc::std::get<_Idx>(::asc::std::forward<_Tuple>(__t))...);
}

template <class _Tp, class _Tuple>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp make_from_tuple(_Tuple&& __t) noexcept(
    noexcept(::asc::std::__make_from_tuple_impl<_Tp>(
        ::asc::std::forward<_Tuple>(__t), __make_tuple_indices_t<tuple_size_v<remove_reference_t<_Tuple>>>{})))
{
    return ::asc::std::__make_from_tuple_impl<_Tp>(
        ::asc::std::forward<_Tuple>(__t),                                     // NOLINT(build/include_what_you_use)
        __make_tuple_indices_t<tuple_size_v<remove_reference_t<_Tuple>>>{});  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_APPLY_H
