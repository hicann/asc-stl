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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_GET_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_GET_H

#include <asc/std/detail/__config>
#include <asc/std/__tuple_dir/tuple.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// The get<I>(tuple) overloads live in tuple.h (avoiding a cyclic dependency); this
// header re-exports them and provides the __find_exactly_one lookup machinery for
// get<T> (consumed by variant/get.h).
namespace __find_detail {
static constexpr size_t __not_found = ~size_t(0);
static constexpr size_t __ambiguous = __not_found - 1;

[[nodiscard]] constexpr size_t __find_idx_return(size_t __curr_i, size_t __res, bool __matches) noexcept
{
    return !__matches ? __res : (__res == __not_found ? __curr_i : __ambiguous);
}

template <size_t _Nx>
[[nodiscard]] constexpr size_t __find_idx(size_t __i, const bool (&__matches)[_Nx]) noexcept
{
    return __i == _Nx ? __not_found : __find_idx_return(__i, __find_idx(__i + 1, __matches), __matches[__i]);
}

template <class _T1, class... _Args>
struct __find_exactly_one_checked {
    static constexpr bool __matches[sizeof...(_Args)] = {is_same_v<_T1, _Args>...};
    static constexpr size_t value = __find_detail::__find_idx(0, __matches);
    static_assert(value != __not_found, "type not found in type list");
    static_assert(value != __ambiguous, "type occurs more than once in type list");
};

template <class _T1>
struct __find_exactly_one_checked<_T1> {
    static_assert(!is_same_v<_T1, _T1>, "type not in empty type list");
};
}  // namespace __find_detail

template <typename _T1, typename... _Args>
struct __find_exactly_one_t : public __find_detail::__find_exactly_one_checked<_T1, _Args...> {};

template <class _T1, class... _Args>
[[nodiscard]] CANN_ASC_STL_API constexpr _T1& get(tuple<_Args...>& __tup) noexcept
{
    return ::asc::std::get<__find_exactly_one_t<_T1, _Args...>::value>(__tup);
}

template <class _T1, class... _Args>
[[nodiscard]] CANN_ASC_STL_API constexpr const _T1& get(const tuple<_Args...>& __tup) noexcept
{
    return ::asc::std::get<__find_exactly_one_t<_T1, _Args...>::value>(__tup);
}

template <class _T1, class... _Args>
[[nodiscard]] CANN_ASC_STL_API constexpr _T1&& get(tuple<_Args...>&& __tup) noexcept
{
    return ::asc::std::get<__find_exactly_one_t<_T1, _Args...>::value>(::asc::std::move(__tup));
}

template <class _T1, class... _Args>
[[nodiscard]] CANN_ASC_STL_API constexpr const _T1&& get(
    const tuple<_Args...>&& __tup) noexcept  // NOLINT(build/include_what_you_use)
{
    return ::asc::std::get<__find_exactly_one_t<_T1, _Args...>::value>(
        ::asc::std::move(__tup));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_GET_H
