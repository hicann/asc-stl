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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_FORWARD_LIKE_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_FORWARD_LIKE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Ap, class _Bp>
struct __forward_like_result {
    using type = __copy_cvref_t<_Ap&&, remove_reference_t<_Bp>>;
};

template <class _Ap, class _Bp>
using _ForwardLike = typename __forward_like_result<_Ap, _Bp>::type;

template <class _Tp, class _Up>
[[nodiscard]] CANN_ASC_STL_API constexpr auto forward_like(_Up&& __ux) noexcept -> _ForwardLike<_Tp, _Up>
{
    return static_cast<_ForwardLike<_Tp, _Up>>(__ux);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_FORWARD_LIKE_H
