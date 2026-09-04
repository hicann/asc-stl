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

#ifndef CANN_ASC_STL_DETAIL_FUNCTIONAL_CALL_OR_H
#define CANN_ASC_STL_DETAIL_FUNCTIONAL_CALL_OR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__tuple_dir/ignore.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

struct __call_or_t {
    template <class _Fn, class _Fallback, class... _Args,
        ::asc::std::enable_if_t<::asc::std::__is_callable_v<_Fn, _Args...>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(_Fn __fn, _Fallback&&, _Args&&... __args) const
        noexcept(::asc::std::__is_nothrow_callable_v<_Fn, _Args...>) -> ::asc::std::__call_result_t<_Fn, _Args...>
    {
        return __fn(static_cast<_Args&&>(__args)...);
    }

    template <class _Fallback, class... _Args>
    CANN_ASC_STL_API constexpr auto operator()(::asc::std::__ignore_t, _Fallback&& __fallback, _Args&&...) const
        noexcept(::asc::std::is_nothrow_move_constructible_v<_Fallback>) -> _Fallback
    {
        return static_cast<_Fallback&&>(__fallback);
    }
};

CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto __call_or = __call_or_t{};

template <class _Fn, class _Fallback, class... _Args>
using __call_result_or_t = ::asc::std::__call_result_t<__call_or_t, _Fn, _Fallback, _Args...>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif
