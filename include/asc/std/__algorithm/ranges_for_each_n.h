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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FOR_EACH_N_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FOR_EACH_N_H

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
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

template <class _Iter, class _Func>
using for_each_n_result = in_fun_result<_Iter, _Func>;

namespace __for_each_n {

struct __fn {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // 约束保持表达式级（可解引用、可自增、谓词可经投影调用）：冻结用例以仅有
    // operator*/operator++ 的经典裸迭代器调用本定制点，标准 input_iterator 级
    // 校验会破坏既有交付面。
    template <class _Iter, class _Func, class _Proj = identity>
        requires requires {
            *::asc::std::declval<_Iter&>();
            ++::asc::std::declval<_Iter&>();
            ::asc::std::invoke(::asc::std::declval<_Func&>(),
                ::asc::std::invoke(::asc::std::declval<_Proj&>(), *::asc::std::declval<_Iter&>()));
        }
    CANN_ASC_STL_API constexpr for_each_n_result<_Iter, _Func> operator()(
        _Iter __first, iter_difference_t<_Iter> __count, _Func __func, _Proj __proj = {}) const
    {
        while (__count-- > 0) {
            ::asc::std::invoke(__func, ::asc::std::invoke(__proj, *__first));
            ++__first;
        }
        return {::asc::std::move(__first), ::asc::std::move(__func)};  // NOLINT(build/include_what_you_use)
    }
#else
    template <class _Iter, class _Func, class _Proj = identity>
    CANN_ASC_STL_API constexpr for_each_n_result<_Iter, _Func> operator()(
        _Iter __first, iter_difference_t<_Iter> __count, _Func __func, _Proj __proj = {}) const
    {
        while (__count-- > 0) {
            ::asc::std::invoke(__func, ::asc::std::invoke(__proj, *__first));
            ++__first;
        }
        return {::asc::std::move(__first), ::asc::std::move(__func)};  // NOLINT(build/include_what_you_use)
    }
#endif
};
}  // namespace __for_each_n

inline namespace __cpo {
inline constexpr auto for_each_n = __for_each_n::__fn{};
}  // namespace __cpo

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FOR_EACH_N_H
