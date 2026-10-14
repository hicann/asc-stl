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

#ifndef CANN_ASC_STL_ASC_STD___RANDOM_IS_VALID_H
#define CANN_ASC_STL_ASC_STD___RANDOM_IS_VALID_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// [rand.req.genl] (P4037R1 wording): the argument for a RealType template
// parameter must be a cv-unqualified (extended) floating-point type, otherwise
// the program is ill-formed. The check is deliberately cv-sensitive: qualified
// floating-point types such as const float do not qualify (is_floating_point_v
// alone would wrongly admit them, since it ignores cv-qualifiers).
template <class T>
inline constexpr bool __asc_random_is_valid_realtype = is_floating_point_v<T> && is_same_v<T, remove_cv_t<T>>;

// [rand.req.genl] (P4037R1 wording): the argument for an IntType template
// parameter must be a cv-unqualified (extended) integer type; __is_integer_v
// is exactly that semantic: it includes signed char and unsigned char while
// excluding char, bool, and the character/wide-character types.
template <class T>
inline constexpr bool __asc_random_is_valid_inttype = __is_integer_v<T>;

// [rand.req.genl] (P4037R1 wording): the argument for a UIntType template
// parameter must be a cv-unqualified (extended) unsigned integer type.
// P4037R1 section 4.5 admits unsigned char into the implementation-defined
// subset, which keeps narrow engines such as
// linear_congruential_engine<unsigned char, ...> usable.
template <class T>
inline constexpr bool __asc_random_is_valid_uinttype = __is_unsigned_integer_v<T>;

// [rand.req.urng]: G satisfies the uniform random bit generator requirements
// if and only if invoke_result_t<G&> is an unsigned integer type and G
// provides a matching nested result_type. Generators with signed result
// types are rejected (the distribution implementations cannot handle them).
template <class, class = void>
inline constexpr bool __asc_random_is_valid_urng = false;
template <class G>
inline constexpr bool __asc_random_is_valid_urng<G,
    enable_if_t<is_unsigned_v<typename G::result_type> &&
        is_same_v<decltype(::asc::std::declval<G&>()()), typename G::result_type>>> = true;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANDOM_IS_VALID_H
