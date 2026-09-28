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

#ifndef CANN_ASC_STL_ASC_STD___VARIANT_COMPARISON_H
#define CANN_ASC_STL_ASC_STD___VARIANT_COMPARISON_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/operations.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__variant/variant.h>
#include <asc/std/__variant/visit.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// The variant, pair and tuple relational surface is owned by the completed
// definition headers this path aggregates; every operator declared here is the
// same entity re-exported through the CCCL-mirrored comparison path that the
// public <asc/std/variant> facade composes.

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_COMPARISON_H
