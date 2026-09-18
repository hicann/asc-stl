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

#ifndef CANN_ASC_STL_STD_DETAIL_OPTIONAL_MAKE_OPTIONAL_H
#define CANN_ASC_STL_STD_DETAIL_OPTIONAL_MAKE_OPTIONAL_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__optional/optional.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp = nullopt_t::__secret_tag, class _Up)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_same_v<_Tp, nullopt_t::__secret_tag>)
CANN_ASC_STL_API constexpr optional<decay_t<_Up>> make_optional(_Up&& __v)
{
    return optional<decay_t<_Up>>(::asc::std::forward<_Up>(__v));
}

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class... _Args)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_reference_v<_Tp>))
CANN_ASC_STL_API constexpr optional<_Tp> make_optional(_Args&&... __args)
{
    return optional<_Tp>(in_place_t{}, ::asc::std::forward<_Args>(__args)...);
}

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up, class... _Args)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_reference_v<_Tp>))
CANN_ASC_STL_API constexpr optional<_Tp> make_optional(initializer_list<_Up> __il, _Args&&... __args)
{
    return optional<_Tp>(
        in_place_t{}, __il, ::asc::std::forward<_Args>(__args)...);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_OPTIONAL_MAKE_OPTIONAL_H
