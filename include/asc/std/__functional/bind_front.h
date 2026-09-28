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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BIND_FRONT_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BIND_FRONT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/perfect_forward.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_BEGIN_NAMESPACE

struct __bind_front_op {
    template <class Fn, class... Args>
    CANN_ASC_STL_API constexpr auto operator()(Fn&& function, Args&&... args) const
        noexcept(noexcept(::asc::std::invoke(::asc::std::forward<Fn>(function), ::asc::std::forward<Args>(args)...)))
            -> decltype(::asc::std::invoke(::asc::std::forward<Fn>(function), ::asc::std::forward<Args>(args)...))
    {
        return ::asc::std::invoke(  // NOLINT(build/include_what_you_use)
            ::asc::std::forward<Fn>(function), ::asc::std::forward<Args>(args)...);
    }
};

template <class Fn, class... BoundArgs>
struct __bind_front_t : __perfect_forward<__bind_front_op, Fn, BoundArgs...> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__bind_front_t, __perfect_forward, __bind_front_op, Fn, BoundArgs...);
};

template <class Fn, class... Args,
    class = enable_if_t<is_constructible_v<decay_t<Fn>, Fn> && is_move_constructible_v<decay_t<Fn>> &&
        (is_constructible_v<decay_t<Args>, Args> && ...) && (is_move_constructible_v<decay_t<Args>> && ...)>>
CANN_ASC_STL_API constexpr auto bind_front(Fn&& function, Args&&... args) noexcept(
    is_nothrow_constructible_v<tuple<decay_t<Args>...>, Args&&...>)  // NOLINT(build/include_what_you_use)
{
    return __bind_front_t<decay_t<Fn>, decay_t<Args>...>(
        ::asc::std::forward<Fn>(function), ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BIND_FRONT_H
