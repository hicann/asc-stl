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

#ifndef CANN_ASC_STL_ASC_STD___OPTIONAL_MAKE_OPTIONAL_H
#define CANN_ASC_STL_ASC_STD___OPTIONAL_MAKE_OPTIONAL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__optional/optional.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_API constexpr optional<decay_t<T>> make_optional(T&& value)
{
    return optional<decay_t<T>>(::asc::std::forward<T>(value));  // NOLINT(build/include_what_you_use)
}
template <class T, class... Args>
CANN_ASC_STL_API constexpr optional<T> make_optional(Args&&... args)
{
    return optional<T>(in_place, ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___OPTIONAL_MAKE_OPTIONAL_H
