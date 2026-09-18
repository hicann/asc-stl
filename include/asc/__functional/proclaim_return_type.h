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

#ifndef CANN_ASC_STL_DETAIL_FUNCTIONAL_PROCLAIM_RETURN_TYPE_H
#define CANN_ASC_STL_DETAIL_FUNCTIONAL_PROCLAIM_RETURN_TYPE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/invoke.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC
namespace __detail {
template <class _Ret, class _DecayFn>
class __return_type_wrapper {
private:
    _DecayFn __fn_;

public:
    __return_type_wrapper() = delete;

    template <class _Fn, class = ::asc::std::enable_if_t<::asc::std::is_same_v<::asc::std::decay_t<_Fn>, _DecayFn>>>
    CANN_ASC_STL_API constexpr explicit __return_type_wrapper(_Fn&& __fn) noexcept
        : __fn_(::asc::std::forward<_Fn>(__fn))
    {}

    template <class... _As>
    CANN_ASC_STL_API constexpr _Ret operator()(_As&&... __as) & noexcept
    {
        static_assert(::asc::std::is_same_v<_Ret, ::asc::std::invoke_result_t<_DecayFn&, _As...>>,
            "Return type shall match the proclaimed one exactly");

        return ::asc::std::__invoke(__fn_, ::asc::std::forward<_As>(__as)...);
    }

    template <class... _As>
    CANN_ASC_STL_API constexpr _Ret operator()(_As&&... __as) && noexcept
    {
        static_assert(::asc::std::is_same_v<_Ret, ::asc::std::invoke_result_t<_DecayFn, _As...>>,
            "Return type shall match the proclaimed one exactly");

        return ::asc::std::__invoke(::asc::std::move(__fn_), ::asc::std::forward<_As>(__as)...);
    }

    template <class... _As>
    CANN_ASC_STL_API constexpr _Ret operator()(_As&&... __as) const& noexcept
    {
        static_assert(::asc::std::is_same_v<_Ret, ::asc::std::invoke_result_t<const _DecayFn&, _As...>>,
            "Return type shall match the proclaimed one exactly");

        return ::asc::std::__invoke(__fn_, ::asc::std::forward<_As>(__as)...);
    }

    template <class... _As>
    CANN_ASC_STL_API constexpr _Ret operator()(_As&&... __as) const&& noexcept
    {
        static_assert(::asc::std::is_same_v<_Ret, ::asc::std::invoke_result_t<const _DecayFn, _As...>>,
            "Return type shall match the proclaimed one exactly");

        return ::asc::std::__invoke(::asc::std::move(__fn_), ::asc::std::forward<_As>(__as)...);
    }
};
}  // namespace __detail

template <class _Ret, class _Fn>
CANN_ASC_STL_API __detail::__return_type_wrapper<_Ret, ::asc::std::decay_t<_Fn>> proclaim_return_type(
    _Fn&& __fn) noexcept
{
    return __detail::__return_type_wrapper<_Ret, ::asc::std::decay_t<_Fn>>(
        ::asc::std::forward<_Fn>(__fn));  // NOLINT(build/include_what_you_use)
}
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_FUNCTIONAL_PROCLAIM_RETURN_TYPE_H
