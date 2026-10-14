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

#ifndef CANN_ASC_STL_ASC_STD___MUTEX_LOCK_TAGS_H
#define CANN_ASC_STL_ASC_STD___MUTEX_LOCK_TAGS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Single authoritative source of the lock-tag vocabulary. The lock RAII
// headers (lock_guard/scoped_lock/unique_lock/shared_lock) include this
// file instead of carrying their own copies; the historical copy-with-
// macro-guard scheme is retired so the vocabulary can never drift between
// translation units.

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __lock_detail {
template <int Value>
struct __lock_tag {};
}  // namespace __lock_detail

using defer_lock_t = __lock_detail::__lock_tag<0>;
using try_to_lock_t = __lock_detail::__lock_tag<1>;
using adopt_lock_t = __lock_detail::__lock_tag<2>;
inline constexpr defer_lock_t defer_lock{};
inline constexpr try_to_lock_t try_to_lock{};
inline constexpr adopt_lock_t adopt_lock{};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MUTEX_LOCK_TAGS_H
