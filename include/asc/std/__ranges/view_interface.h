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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_VIEW_INTERFACE_H
#define CANN_ASC_STL_ASC_STD___RANGES_VIEW_INTERFACE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/prev.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__utility/declval.h>
// The C++17 backport definition is provided by the already delivered
// enable-view vocabulary reached through the frozen ranges concept closure.
// This source-granular Header preserves the reviewed decomposition point.

#endif  // CANN_ASC_STL_ASC_STD___RANGES_VIEW_INTERFACE_H
