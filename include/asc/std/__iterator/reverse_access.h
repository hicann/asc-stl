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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_REVERSE_ACCESS_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_REVERSE_ACCESS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/cstddef>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __rbegin {
struct __fn {
    template <class _Tp, size_t _Np>
    CANN_ASC_STL_API constexpr reverse_iterator<_Tp*> operator()(_Tp (&__array)[_Np]) const noexcept
    {
        return reverse_iterator<_Tp*>(__array + _Np);
    }

    template <class _Ep>
    CANN_ASC_STL_API constexpr reverse_iterator<const _Ep*> operator()(initializer_list<_Ep> __il) const noexcept
    {
        return reverse_iterator<const _Ep*>(__il.end());
    }

    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(_Cp& __c) const
        noexcept(noexcept(__c.rbegin())) -> decltype(__c.rbegin())
    {
        return __c.rbegin();
    }

    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(const _Cp& __c) const
        noexcept(noexcept(__c.rbegin())) -> decltype(__c.rbegin())
    {
        return __c.rbegin();
    }
};
}  // namespace __rbegin

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto rbegin = __rbegin::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __rbegin_cpo = __rbegin::__fn;
}  // namespace __cpo

namespace __rend {
struct __fn {
    template <class _Tp, size_t _Np>
    CANN_ASC_STL_API constexpr reverse_iterator<_Tp*> operator()(_Tp (&__array)[_Np]) const noexcept
    {
        return reverse_iterator<_Tp*>(__array);
    }

    template <class _Ep>
    CANN_ASC_STL_API constexpr reverse_iterator<const _Ep*> operator()(initializer_list<_Ep> __il) const noexcept
    {
        return reverse_iterator<const _Ep*>(__il.begin());
    }

    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(_Cp& __c) const noexcept(noexcept(__c.rend())) -> decltype(__c.rend())
    {
        return __c.rend();
    }

    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(const _Cp& __c) const
        noexcept(noexcept(__c.rend())) -> decltype(__c.rend())
    {
        return __c.rend();
    }
};
}  // namespace __rend

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto rend = __rend::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __rend_cpo = __rend::__fn;
}  // namespace __cpo

namespace __crbegin {
struct __fn {
    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(const _Cp& __c) const
        noexcept(noexcept(::asc::std::__rbegin_cpo{}(__c))) -> decltype(::asc::std::__rbegin_cpo{}(__c))
    {
        return ::asc::std::__rbegin_cpo{}(__c);
    }
};
}  // namespace __crbegin

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto crbegin = __crbegin::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __crbegin_cpo = __crbegin::__fn;
}  // namespace __cpo

namespace __crend {
struct __fn {
    template <class _Cp>
    CANN_ASC_STL_API constexpr auto operator()(const _Cp& __c) const
        noexcept(noexcept(::asc::std::__rend_cpo{}(__c))) -> decltype(::asc::std::__rend_cpo{}(__c))
    {
        return ::asc::std::__rend_cpo{}(__c);
    }
};
}  // namespace __crend

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto crend = __crend::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __crend_cpo = __crend::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_REVERSE_ACCESS_H
