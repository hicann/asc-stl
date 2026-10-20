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

// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef CANN_ASC_STL_ASC_STD___FUNCTIONAL_RANGES_OPERATIONS_H
#define CANN_ASC_STL_ASC_STD___FUNCTIONAL_RANGES_OPERATIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/totally_ordered.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// The concept constraints (equality_comparable_with / totally_ordered_with)
// verify per [concept.equalitycomparable]/[concept.totallyordered] that
// comparison results are boolean-testable in every supported language mode.

struct equal_to {
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Tp, class _Up)
    CANN_ASC_STL_DETAIL_REQUIRES(equality_comparable_with<_Tp, _Up>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Tp&& __t, _Up&& __u) const
        noexcept(noexcept(static_cast<bool>(::asc::std::forward<_Tp>(__t) == ::asc::std::forward<_Up>(__u))))
    {
        return ::asc::std::forward<_Tp>(__t) == ::asc::std::forward<_Up>(__u);
    }

    using is_transparent = void;
};

struct not_equal_to {
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Tp, class _Up)
    CANN_ASC_STL_DETAIL_REQUIRES(equality_comparable_with<_Tp, _Up>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Tp&& __t, _Up&& __u) const
        noexcept(noexcept(static_cast<bool>(!(::asc::std::forward<_Tp>(__t) == ::asc::std::forward<_Up>(__u)))))
    {
        return !(::asc::std::forward<_Tp>(__t) == ::asc::std::forward<_Up>(__u));
    }

    using is_transparent = void;
};

struct less {
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Tp, class _Up)
    CANN_ASC_STL_DETAIL_REQUIRES(totally_ordered_with<_Tp, _Up>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Tp&& __t, _Up&& __u) const
        noexcept(noexcept(static_cast<bool>(::asc::std::forward<_Tp>(__t) < ::asc::std::forward<_Up>(__u))))
    {
        return ::asc::std::forward<_Tp>(__t) < ::asc::std::forward<_Up>(__u);
    }

    using is_transparent = void;
};

struct less_equal {
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Tp, class _Up)
    CANN_ASC_STL_DETAIL_REQUIRES(totally_ordered_with<_Tp, _Up>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Tp&& __t, _Up&& __u) const
        noexcept(noexcept(static_cast<bool>(!(::asc::std::forward<_Up>(__u) < ::asc::std::forward<_Tp>(__t)))))
    {
        return !(::asc::std::forward<_Up>(__u) < ::asc::std::forward<_Tp>(__t));
    }

    using is_transparent = void;
};

struct greater {
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Tp, class _Up)
    CANN_ASC_STL_DETAIL_REQUIRES(totally_ordered_with<_Tp, _Up>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Tp&& __t, _Up&& __u) const
        noexcept(noexcept(static_cast<bool>(::asc::std::forward<_Up>(__u) < ::asc::std::forward<_Tp>(__t))))
    {
        return ::asc::std::forward<_Up>(__u) < ::asc::std::forward<_Tp>(__t);
    }

    using is_transparent = void;
};

struct greater_equal {
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Tp, class _Up)
    CANN_ASC_STL_DETAIL_REQUIRES(totally_ordered_with<_Tp, _Up>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Tp&& __t, _Up&& __u) const
        noexcept(noexcept(static_cast<bool>(!(::asc::std::forward<_Tp>(__t) < ::asc::std::forward<_Up>(__u)))))
    {
        return !(::asc::std::forward<_Tp>(__t) < ::asc::std::forward<_Up>(__u));  // NOLINT(build/include_what_you_use)
    }

    using is_transparent = void;
};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FUNCTIONAL_RANGES_OPERATIONS_H
