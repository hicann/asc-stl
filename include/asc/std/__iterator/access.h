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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_ACCESS_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_ACCESS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __begin {
struct __fn {
    template <class _Tp, size_t _Np>
    CANN_ASC_STL_API constexpr _Tp* operator()(_Tp (&__array)[_Np]) const noexcept
    {
        return __array;
    }

    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(_Cp& __c) const noexcept(noexcept(__c.begin())) -> decltype(__c.begin())
    {
        return __c.begin();
    }

    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(const _Cp& __c) const
        noexcept(noexcept(__c.begin())) -> decltype(__c.begin())
    {
        return __c.begin();
    }
};
}  // namespace __begin

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto begin = __begin::__fn{};

// Use the function-object type directly for internal dispatch.
using __begin_cpo = __begin::__fn;
}  // namespace __cpo

namespace __end {
struct __fn {
    template <class _Tp, size_t _Np>
    CANN_ASC_STL_API constexpr _Tp* operator()(_Tp (&__array)[_Np]) const noexcept
    {
        return __array + _Np;
    }

    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(_Cp& __c) const noexcept(noexcept(__c.end())) -> decltype(__c.end())
    {
        return __c.end();
    }

    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(const _Cp& __c) const
        noexcept(noexcept(__c.end())) -> decltype(__c.end())
    {
        return __c.end();
    }
};
}  // namespace __end

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto end = __end::__fn{};

// Use the function-object type directly for internal dispatch.
using __end_cpo = __end::__fn;
}  // namespace __cpo

namespace __cbegin {
struct __fn {
    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(const _Cp& __c) const
        noexcept(noexcept(::asc::std::__begin_cpo{}(__c))) -> decltype(::asc::std::__begin_cpo{}(__c))
    {
        return ::asc::std::__begin_cpo{}(__c);
    }
};
}  // namespace __cbegin

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto cbegin = __cbegin::__fn{};

// Use the function-object type directly for internal dispatch.
using __cbegin_cpo = __cbegin::__fn;
}  // namespace __cpo

namespace __cend {
struct __fn {
    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(const _Cp& __c) const
        noexcept(noexcept(::asc::std::__end_cpo{}(__c))) -> decltype(::asc::std::__end_cpo{}(__c))
    {
        return ::asc::std::__end_cpo{}(__c);
    }
};
}  // namespace __cend

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto cend = __cend::__fn{};

// Use the function-object type directly for internal dispatch.
using __cend_cpo = __cend::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_ACCESS_H
