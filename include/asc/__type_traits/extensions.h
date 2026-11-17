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

#ifndef CANN_ASC_STL_ASC___TYPE_TRAITS_EXTENSIONS_H
#define CANN_ASC_STL_ASC___TYPE_TRAITS_EXTENSIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__numeric_types/storage.h>

// Extension trait vocabulary for the later public <asc/type_traits>.  The
// traits are documented customization points: a user specialization must keep
// the documented semantic precondition, and the value vocabulary stays
// self-contained because this root has no trait-header dependencies.

namespace asc {

// True when comparing object representations byte by byte gives the same
// answer as comparing values with operator==.  Standard integer types satisfy
// the precondition; floating-point types do not (signed zero and NaN), and no
// CCE register-vector type is classified.  cv-qualified views of a comparable
// type stay comparable (the qualifiers do not change the object
// representation), so the cv forms forward to the unqualified answer instead
// of silently falling back to false and disabling byte-wise fast paths for
// const-element containers.
template <class T>
struct is_bitwise_comparable {
    static constexpr bool value = false;
};

template <class T>
inline constexpr bool is_bitwise_comparable_v = is_bitwise_comparable<T>::value;

#define CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(...) \
    template <>                                     \
    struct is_bitwise_comparable<__VA_ARGS__> {     \
        static constexpr bool value = true;         \
    };
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(bool)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(char)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(signed char)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(unsigned char)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(short)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(unsigned short)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(int)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(unsigned int)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(long)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(unsigned long)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(long long)
CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE(unsigned long long)
#undef CANN_ASC_STL_DETAIL_BITWISE_COMPARABLE

template <class T>
struct is_bitwise_comparable<const T> : is_bitwise_comparable<T> {};
template <class T>
struct is_bitwise_comparable<volatile T> : is_bitwise_comparable<T> {};
template <class T>
struct is_bitwise_comparable<const volatile T> : is_bitwise_comparable<T> {};

// True for the scalar floating formats registered by numeric_types. E8M0
// is a scale encoding; packed formats and int4 are distinct categories.
template <class T>
struct is_extended_floating_point {
    static constexpr bool value = false;
};

template <numeric_format F>
struct is_extended_floating_point<detail::numeric_storage<F>> {
    static constexpr bool value = F == numeric_format::fp16 || F == numeric_format::bf16 ||
        F == numeric_format::fp8_e4m3fn || F == numeric_format::fp8_e5m2 || F == numeric_format::hif8;
};

template <class T>
inline constexpr bool is_extended_floating_point_v = is_extended_floating_point<T>::value;

// True when relocation (destroy the source, bitwise copy to the destination)
// is equivalent to moving the object with memcpy.  Trivially copyable types
// satisfy the precondition because trivial copyability already requires a
// trivial, non-deleted destructor.  A type with custom copy/destruction whose
// object is still memcpy-safe may opt in through an explicit specialization.
// The struct is the customization point on purpose: the _v alias reads
// through it, so a single struct specialization is enough and the _v variable
// stays non-specializable.  (The dev-side reference instead makes the
// variable template the customization point; switching forms would break
// existing struct specializations and is a registry-level decision.)
template <class T>
struct is_trivially_relocatable {
    static constexpr bool value = __is_trivially_copyable(T);
};

template <class T>
inline constexpr bool is_trivially_relocatable_v = is_trivially_relocatable<T>::value;

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___TYPE_TRAITS_EXTENSIONS_H
