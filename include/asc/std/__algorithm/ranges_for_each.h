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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FOR_EACH_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FOR_EACH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/in_fun_result.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

template <class _Iter, class _Func>
using for_each_result = in_fun_result<_Iter, _Func>;

namespace __for_each {

struct __fn {
    template <class _Iter, class _Sent, class _Proj, class _Func>
    CANN_ASC_STL_API static constexpr for_each_result<_Iter, _Func> __for_each_impl(
        _Iter __first, _Sent __last, _Func& __func, _Proj& __proj)
    {
        for (; __first != __last; ++__first) {
            ::asc::std::invoke(__func, ::asc::std::invoke(__proj, *__first));
        }
        return {::asc::std::move(__first), ::asc::std::move(__func)};  // NOLINT(build/include_what_you_use)
    }

    template <class _Iter, class _Sent, class _Func, class _Proj = identity,
        class = decltype(::asc::std::declval<_Iter&>() != ::asc::std::declval<_Sent&>())>
    CANN_ASC_STL_API constexpr for_each_result<_Iter, _Func> operator()(
        _Iter __first, _Sent __last, _Func __func, _Proj __proj = {}) const
    {
        return __for_each_impl(
            ::asc::std::move(__first), ::asc::std::move(__last), __func, __proj);  // NOLINT(build/include_what_you_use)
    }
    template <class _Range, class _Func, class _Proj = identity,
        class = enable_if_t<is_invocable_v<_Func&, invoke_result_t<_Proj&, iter_reference_t<iterator_t<_Range>>>>>>
    CANN_ASC_STL_API constexpr for_each_result<borrowed_iterator_t<_Range>, _Func> operator()(
        _Range&& __range, _Func __func, _Proj __proj = {}) const
    {
        auto __result = __for_each_impl(ranges::begin(__range), ranges::end(__range), __func, __proj);
        return {::asc::std::move(__result.in), ::asc::std::move(__result.fun)};  // NOLINT(build/include_what_you_use)
    }
};

}  // namespace __for_each

inline namespace __cpo {
inline constexpr auto for_each = __for_each::__fn{};
}  // namespace __cpo

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FOR_EACH_H
