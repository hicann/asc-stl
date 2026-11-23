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

#include <asc/__numeric_types/traits.h>
#include <asc/__type_traits/address_space.h>
#include <asc/std/__type_traits/has_unique_object_representation.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_member_pointer.h>
#include <asc/std/__type_traits/is_null_pointer.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/is_union.h>
#include <asc/std/__type_traits/is_volatile.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/void_t.h>

#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_DETAIL_TRAIT_API __host__ __aicore__ CANN_ASC_STL_DETAIL_VISIBILITY_HIDDEN inline
#else
#define CANN_ASC_STL_DETAIL_TRAIT_API CANN_ASC_STL_API
#endif

namespace asc {
namespace detail {

// Keep the standard Boolean vocabulary while making the value operations
// available in both phases of a pure-SIMT translation unit.
template <bool Value>
struct trait_bool_constant : asc::std::bool_constant<Value> {
    CANN_ASC_STL_DETAIL_TRAIT_API constexpr operator bool() const noexcept
    {
        return Value;
    }
    CANN_ASC_STL_DETAIL_TRAIT_API constexpr bool operator()() const noexcept
    {
        return Value;
    }
};

// An explicit standard set avoids treating a compiler vector/packed integer
// or an extension integer as a standard integer merely because a builtin does.
template <class T>
inline constexpr bool standard_integer_type = asc::std::is_same_v<T, bool> || asc::std::is_same_v<T, char> ||
    asc::std::is_same_v<T, signed char> || asc::std::is_same_v<T, unsigned char> || asc::std::is_same_v<T, short> ||
    asc::std::is_same_v<T, unsigned short> || asc::std::is_same_v<T, int> || asc::std::is_same_v<T, unsigned int> ||
    asc::std::is_same_v<T, long> || asc::std::is_same_v<T, unsigned long> || asc::std::is_same_v<T, long long> ||
    asc::std::is_same_v<T, unsigned long long> || asc::std::is_same_v<T, wchar_t> || asc::std::is_same_v<T, char16_t>
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
    || asc::std::is_same_v<T, char8_t>
#endif
    || asc::std::is_same_v<T, char32_t>;

template <class T>
inline constexpr bool standard_arithmetic_type = standard_integer_type<T> || asc::std::is_same_v<T, float> ||
    asc::std::is_same_v<T, double> || asc::std::is_same_v<T, long double>;

template <class T, class = void>
struct complete_property_type : asc::std::false_type {};

template <class T>
struct complete_property_type<T, asc::std::void_t<decltype(sizeof(T))>> : asc::std::true_type {};

template <class T, bool = asc::std::is_class_v<T> || asc::std::is_union_v<T>>
struct property_query_requirement : asc::std::true_type {};

template <class T>
struct property_query_requirement<T, true> : complete_property_type<T> {};

template <class T, bool = numeric_type_registration<T>::value && !standard_arithmetic_type<T>>
struct numeric_type_categories {
    static constexpr bool low_precision = false;
    static constexpr bool extended_floating_point = false;
    static constexpr bool packed_numeric = false;
};

template <class T>
struct numeric_type_categories<T, true> {
    using registration = numeric_type_registration<T>;
    static constexpr bool low_precision = true;
    static constexpr bool extended_floating_point = registration::format == numeric_format::fp16 ||
        registration::format == numeric_format::bf16 || registration::format == numeric_format::fp8_e4m3fn ||
        registration::format == numeric_format::fp8_e5m2 || registration::format == numeric_format::hif8;
    static constexpr bool packed_numeric = registration::lanes > 1;
};

template <class T, bool = standard_integer_type<T> && !asc::std::is_same_v<T, bool>>
struct bitwise_comparable_default : asc::std::false_type {};

template <class T>
struct bitwise_comparable_default<T, true> : asc::std::bool_constant<asc::std::is_trivially_copyable_v<T> &&
                                                 asc::std::has_unique_object_representations_v<T>> {};

template <class T,
    bool = !asc::std::is_const_v<T> && !asc::std::is_volatile_v<T> && !asc::std::is_array_v<T> &&
        (standard_arithmetic_type<T> || asc::std::is_enum_v<T> || asc::std::is_pointer_v<T> ||
            asc::std::is_member_pointer_v<T> || asc::std::is_null_pointer_v<T> || numeric_type_registration<T>::value)>
struct trivially_relocatable_default : asc::std::false_type {};

template <class T>
struct trivially_relocatable_default<T, true>
    : asc::std::bool_constant<asc::std::is_trivially_copyable_v<T> && asc::std::is_trivially_move_constructible_v<T> &&
          asc::std::is_trivially_destructible_v<T>> {};

}  // namespace detail

// These two object properties are the only public customization points.
// Complete user types may specialize their class templates before first use.
template <class T>
struct is_bitwise_comparable : detail::trait_bool_constant<detail::bitwise_comparable_default<T>::value> {
    static_assert(
        detail::property_query_requirement<T>::value, "is_bitwise_comparable requires a complete class or union");
};

template <class T>
struct is_bitwise_comparable<const T> : is_bitwise_comparable<T> {};

template <class T>
struct is_bitwise_comparable<volatile T> : detail::trait_bool_constant<false> {
    static_assert(
        detail::property_query_requirement<T>::value, "is_bitwise_comparable requires a complete class or union");
};

template <class T>
struct is_bitwise_comparable<const volatile T> : is_bitwise_comparable<volatile T> {};

template <class T>
inline constexpr bool is_bitwise_comparable_v = is_bitwise_comparable<T>::value;

template <class T>
struct is_trivially_relocatable : detail::trait_bool_constant<detail::trivially_relocatable_default<T>::value> {
    static_assert(
        detail::property_query_requirement<T>::value, "is_trivially_relocatable requires a complete class or union");
};

template <class T>
inline constexpr bool is_trivially_relocatable_v = is_trivially_relocatable<T>::value;

template <class T>
struct is_low_precision
    : detail::trait_bool_constant<detail::numeric_type_categories<asc::std::remove_cv_t<T>>::low_precision> {};

template <class T>
inline constexpr bool is_low_precision_v = is_low_precision<T>::value;

template <class T>
struct is_extended_floating_point
    : detail::trait_bool_constant<detail::numeric_type_categories<asc::std::remove_cv_t<T>>::extended_floating_point> {
};

template <class T>
inline constexpr bool is_extended_floating_point_v = is_extended_floating_point<T>::value;

template <class T>
struct is_packed_numeric
    : detail::trait_bool_constant<detail::numeric_type_categories<asc::std::remove_cv_t<T>>::packed_numeric> {};

template <class T>
inline constexpr bool is_packed_numeric_v = is_packed_numeric<T>::value;

template <class T>
struct is_address_space_qualified : detail::trait_bool_constant<detail::normalized_native_pointer_space<T>::value !=
                                        detail::native_memory_space::unqualified> {};

template <class T>
inline constexpr bool is_address_space_qualified_v = is_address_space_qualified<T>::value;

}  // namespace asc

#undef CANN_ASC_STL_DETAIL_TRAIT_API

#endif  // CANN_ASC_STL_ASC___TYPE_TRAITS_EXTENSIONS_H
