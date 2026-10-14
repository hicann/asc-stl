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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_CALENDAR_H
#define CANN_ASC_STL_ASC_STD___CHRONO_CALENDAR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__chrono/duration.h>
#include <asc/std/__chrono/time_point.h>

// asc/__detail/visibility.h provides no such macro, so define it here,
// keeping only the inline semantics for hiding from the ABI.
#ifndef CANN_ASC_STL_DETAIL_HIDE_FROM_ABI
#define CANN_ASC_STL_DETAIL_HIDE_FROM_ABI inline
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

struct local_t {};

template <class Duration>
using local_time = time_point<local_t, Duration>;
using local_seconds = local_time<seconds>;
using local_days = local_time<days>;

struct last_spec {
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI explicit last_spec() = default;
};

inline constexpr last_spec last{};

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_CALENDAR_H
