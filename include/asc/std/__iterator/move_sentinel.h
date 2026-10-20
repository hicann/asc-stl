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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_MOVE_SENTINEL_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_MOVE_SENTINEL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/semiregular.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__type_traits/enable_if.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <semiregular _Sent>
#else   // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())
template <class _Sent>
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
class move_sentinel {
    static_assert(semiregular<_Sent>, "move_sentinel requires a semiregular sentinel");

public:
    CANN_ASC_STL_API constexpr move_sentinel() = default;

    CANN_ASC_STL_API constexpr explicit move_sentinel(_Sent __s)
        : __last_(::asc::std::move(__s))  // NOLINT(build/include_what_you_use)
    {}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class _S2>
        requires convertible_to<const _S2&, _Sent>
#else   // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())
    template <class _S2, enable_if_t<convertible_to<const _S2&, _Sent>, int> = 0>
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr move_sentinel(const move_sentinel<_S2>& __s) : __last_(__s.base())
    {}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class _S2>
        requires assignable_from<_Sent&, const _S2&>
#else   // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())
    template <class _S2, enable_if_t<assignable_from<_Sent&, const _S2&>, int> = 0>
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr move_sentinel& operator=(const move_sentinel<_S2>& __s)
    {
        __last_ = __s.base();
        return *this;
    }

    CANN_ASC_STL_API constexpr _Sent base() const
    {
        return __last_;
    }

private:
    _Sent __last_ = _Sent();
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_MOVE_SENTINEL_H
