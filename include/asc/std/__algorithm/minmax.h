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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_MINMAX_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_MINMAX_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/minmax_element.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<const _Tp&, const _Tp&> minmax(
    const _Tp& __a, const _Tp& __b, _Compare __comp)
{
    return __comp(__b, __a) ? pair<const _Tp&, const _Tp&>(__b, __a) : pair<const _Tp&, const _Tp&>(__a, __b);
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<const _Tp&, const _Tp&> minmax(const _Tp& __a, const _Tp& __b)
{
    return ::asc::std::minmax(__a, __b, __less{});
}

template <class _Tp, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<_Tp, _Tp> minmax(initializer_list<_Tp> __t, _Compare __comp)
{
    static_assert(__is_callable<_Compare, _Tp, _Tp>::value, "The comparator has to be callable");
    identity __proj{};
    auto __ret = ::asc::std::__minmax_element_impl(__t.begin(), __t.end(), __comp, __proj);
    return pair<_Tp, _Tp>(*__ret.first, *__ret.second);
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<_Tp, _Tp> minmax(  // NOLINT(build/include_what_you_use)
    initializer_list<_Tp> __t)                                   // NOLINT(build/include_what_you_use)
{
    return ::asc::std::minmax(__t, __less{});
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_MINMAX_H
