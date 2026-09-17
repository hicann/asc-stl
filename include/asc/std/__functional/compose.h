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
#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_COMPOSE_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_COMPOSE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/perfect_forward.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

struct __compose_op {
    template <class _Fn1, class _Fn2, class... _Args>
    CANN_ASC_STL_API constexpr auto operator()(_Fn1&& __f1, _Fn2&& __f2, _Args&&... __args) const
        noexcept(noexcept(::asc::std::invoke(::asc::std::forward<_Fn1>(__f1),
            ::asc::std::invoke(::asc::std::forward<_Fn2>(__f2), ::asc::std::forward<_Args>(__args)...))))
            -> decltype(::asc::std::invoke(::asc::std::forward<_Fn1>(__f1),
                ::asc::std::invoke(::asc::std::forward<_Fn2>(__f2), ::asc::std::forward<_Args>(__args)...)))
    {
        return ::asc::std::invoke(::asc::std::forward<_Fn1>(__f1),
            ::asc::std::invoke(::asc::std::forward<_Fn2>(__f2), ::asc::std::forward<_Args>(__args)...));
    }
};

template <class _Fn1, class _Fn2>
struct __compose_t : __perfect_forward<__compose_op, _Fn1, _Fn2> {
    using __base = __perfect_forward<__compose_op, _Fn1, _Fn2>;
    using __base::__base;
    CANN_ASC_STL_API constexpr __compose_t() noexcept(::asc::std::is_nothrow_default_constructible_v<__base>) = default;
};

template <class _Fn1, class _Fn2>
CANN_ASC_STL_API constexpr auto __compose(_Fn1&& __f1, _Fn2&& __f2) noexcept(noexcept(
    __compose_t<decay_t<_Fn1>, decay_t<_Fn2>>(::asc::std::forward<_Fn1>(__f1), ::asc::std::forward<_Fn2>(__f2))))
    -> decltype(__compose_t<decay_t<_Fn1>, decay_t<_Fn2>>(
        ::asc::std::forward<_Fn1>(__f1), ::asc::std::forward<_Fn2>(__f2)))
{
    return __compose_t<decay_t<_Fn1>, decay_t<_Fn2>>(
        ::asc::std::forward<_Fn1>(__f1), ::asc::std::forward<_Fn2>(__f2));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_COMPOSE_H
