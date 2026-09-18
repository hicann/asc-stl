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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TIE_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TIE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/unwrap_ref.h>
#include <asc/std/__tuple_dir/tuple.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class... _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr tuple<_Tp&...> tie(_Tp&... __t) noexcept
{
    return tuple<_Tp&...>(__t...);
}

template <class... _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr tuple<unwrap_ref_decay_t<_Tp>...> make_tuple(_Tp&&... __t) noexcept(
    is_nothrow_constructible_v<tuple<unwrap_ref_decay_t<_Tp>...>, _Tp...>)
{
    return tuple<unwrap_ref_decay_t<_Tp>...>(::asc::std::forward<_Tp>(__t)...);
}

template <class... _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr tuple<_Tp&&...> forward_as_tuple(_Tp&&... __t) noexcept
{
    return tuple<_Tp&&...>(::asc::std::forward<_Tp>(__t)...);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TIE_H
