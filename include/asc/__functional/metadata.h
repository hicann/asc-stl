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

#ifndef CANN_ASC_STL_ASC___FUNCTIONAL_METADATA_H
#define CANN_ASC_STL_ASC___FUNCTIONAL_METADATA_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/functional>
#include <asc/std/limits>
#include <asc/std/type_traits>
#include <asc/std/utility>

namespace asc {
template <class T>
struct maximum;
template <class T>
struct minimum;
template <class T>
class equal_to_value;

namespace detail {
// Check completeness before using standard traits that require a complete object.
template <class T, bool = ::asc::std::is_object_v<T> && !::asc::std::is_array_v<T>, class = void>
struct functional_complete_object : ::asc::std::false_type {};

template <class T>
struct functional_complete_object<T, true, ::asc::std::void_t<decltype(sizeof(T))>> : ::asc::std::true_type {};

template <class T>
inline constexpr bool functional_value_v =
    functional_complete_object<T>::value && ::asc::std::is_same_v<T, ::asc::std::remove_cv_t<T>>;

template <class T>
inline constexpr bool functional_argument_v = functional_complete_object<::asc::std::remove_reference_t<T>>::value &&
    !::asc::std::is_volatile_v<::asc::std::remove_reference_t<T>>;

template <class T>
using functional_const_reference = const ::asc::std::remove_reference_t<T>&;

template <class Left, class Right>
CANN_ASC_STL_API constexpr auto functional_less(const Left& left, const Right& right) noexcept(
    noexcept(static_cast<bool>(left < right))) -> decltype(static_cast<bool>(left < right))
{
    if constexpr (::asc::std::is_integral_v<Left> && ::asc::std::is_integral_v<Right> &&
        (::asc::std::is_signed_v<Left> != ::asc::std::is_signed_v<Right>)) {
        // Preserve the built-in comparison's usual conversions without a sign-compare warning.
        using compared_type = decltype(left + right);
        return static_cast<compared_type>(left) < static_cast<compared_type>(right);
    } else {
        return static_cast<bool>(left < right);
    }
}

template <class Result, class Left, class Right, bool Minimum,
    bool = functional_value_v<Result> && functional_argument_v<Left> && functional_argument_v<Right>, class = void>
struct functional_extreme_call : ::asc::std::false_type {
    static constexpr bool nothrow = false;
};

template <class Result, class Left, class Right, bool Minimum>
struct functional_extreme_call<Result, Left, Right, Minimum, true,
    ::asc::std::void_t<decltype(Result(::asc::std::declval<Left>())), decltype(Result(::asc::std::declval<Right>())),
        decltype(functional_less(
            ::asc::std::declval<functional_const_reference<::asc::std::conditional_t<Minimum, Right, Left>>>(),
            ::asc::std::declval<functional_const_reference<::asc::std::conditional_t<Minimum, Left, Right>>>()))>>
    : ::asc::std::true_type {
    static constexpr bool nothrow = noexcept(Result(::asc::std::declval<Left>())) &&
        noexcept(Result(::asc::std::declval<Right>())) &&
        noexcept(functional_less(
            ::asc::std::declval<functional_const_reference<::asc::std::conditional_t<Minimum, Right, Left>>>(),
            ::asc::std::declval<functional_const_reference<::asc::std::conditional_t<Minimum, Left, Right>>>()));
};

template <class Left, class Right, bool Minimum, bool = functional_argument_v<Left> && functional_argument_v<Right>,
    class = void>
struct functional_extreme_result : ::asc::std::false_type {
    static constexpr bool nothrow = false;
};

template <class Left, class Right, bool Minimum>
struct functional_extreme_result<Left, Right, Minimum, true,
    ::asc::std::void_t<::asc::std::common_type_t<::asc::std::decay_t<Left>, ::asc::std::decay_t<Right>>>>
    : functional_extreme_call<::asc::std::common_type_t<::asc::std::decay_t<Left>, ::asc::std::decay_t<Right>>, Left,
          Right, Minimum> {
    using type = ::asc::std::common_type_t<::asc::std::decay_t<Left>, ::asc::std::decay_t<Right>>;
};

template <class T, bool = functional_value_v<T>>
struct functional_storable : ::asc::std::false_type {};
template <class T>
struct functional_storable<T, true> : ::asc::std::is_destructible<T> {};

template <class T>
struct functional_is_predicate : ::asc::std::false_type {};
template <class T>
struct functional_is_predicate<equal_to_value<T>> : ::asc::std::true_type {};

template <class T>
inline constexpr bool functional_unsigned_v = ::asc::std::is_same_v<T, unsigned char> ||
    ::asc::std::is_same_v<T, unsigned short> || ::asc::std::is_same_v<T, unsigned int> ||
    ::asc::std::is_same_v<T, unsigned long> || ::asc::std::is_same_v<T, unsigned long long>;

template <class T>
inline constexpr bool functional_signed_v = ::asc::std::is_same_v<T, signed char> || ::asc::std::is_same_v<T, short> ||
    ::asc::std::is_same_v<T, int> || ::asc::std::is_same_v<T, long> || ::asc::std::is_same_v<T, long long>;

template <class T>
inline constexpr bool functional_integer_v =
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
    ::asc::std::is_same_v<T, char8_t> ||
#endif
    functional_unsigned_v<T> || functional_signed_v<T> || ::asc::std::is_same_v<T, bool> ||
    ::asc::std::is_same_v<T, char> || ::asc::std::is_same_v<T, wchar_t> || ::asc::std::is_same_v<T, char16_t> ||
    ::asc::std::is_same_v<T, char32_t>;

template <class Argument, class T>
inline constexpr bool functional_matching_v =
    ::asc::std::is_same_v<Argument, void> || ::asc::std::is_same_v<Argument, T>;

// Each property is a separate column in the closed registration table.
template <bool Associative, bool Commutative, bool Identity, bool Absorbing>
struct functional_property_flags {
    static constexpr bool associative = Associative;
    static constexpr bool commutative = Commutative;
    static constexpr bool has_identity = Identity;
    static constexpr bool has_absorbing = Absorbing;
};

// Integer bounds are constant expressions without calling Device functions in global initializers.
template <class T, bool = ::asc::std::is_same_v<T, bool>>
struct functional_integer_limits {
    using unsigned_type = ::asc::std::make_unsigned_t<T>;
    static constexpr T maximum = static_cast<T>(
        static_cast<unsigned_type>(~unsigned_type{0}) >> static_cast<int>(::asc::std::numeric_limits<T>::is_signed));
    static constexpr T lowest = static_cast<T>(~maximum);
};

template <class T>
struct functional_integer_limits<T, true> {
    static constexpr bool maximum = true;
    static constexpr bool lowest = false;
};

template <class T>
struct functional_arithmetic_bounds {
    using promoted_type = decltype(+T{});
    static constexpr bool addition = !::asc::std::numeric_limits<promoted_type>::is_signed ||
        functional_integer_limits<T>::maximum <= functional_integer_limits<promoted_type>::maximum / 2;
    static constexpr bool multiplication = !::asc::std::numeric_limits<promoted_type>::is_signed ||
        functional_integer_limits<T>::maximum <=
            functional_integer_limits<promoted_type>::maximum / functional_integer_limits<T>::maximum;
};

template <class Operator, class T, class = void>
struct functional_properties : functional_property_flags<false, false, false, false> {};

template <class Argument, class T>
struct functional_properties<::asc::std::plus<Argument>, T,
    ::asc::std::enable_if_t<functional_matching_v<Argument, T> && (functional_unsigned_v<T> || functional_signed_v<T>)>>
    : functional_property_flags<functional_unsigned_v<T> && functional_arithmetic_bounds<T>::addition,
          functional_unsigned_v<T> && functional_arithmetic_bounds<T>::addition, true, false> {
    static constexpr T identity = T{0};
};

template <class Argument, class T>
struct functional_properties<::asc::std::multiplies<Argument>, T,
    ::asc::std::enable_if_t<functional_matching_v<Argument, T> && (functional_unsigned_v<T> || functional_signed_v<T>)>>
    : functional_property_flags<functional_unsigned_v<T> && functional_arithmetic_bounds<T>::multiplication,
          functional_unsigned_v<T> && functional_arithmetic_bounds<T>::multiplication, true, true> {
    static constexpr T identity = T{1};
    static constexpr T absorbing = T{0};
};

template <class Argument, class T>
struct functional_properties<::asc::std::bit_and<Argument>, T,
    ::asc::std::enable_if_t<functional_matching_v<Argument, T> && functional_unsigned_v<T>>>
    : functional_property_flags<true, true, true, true> {
    static constexpr T identity = functional_integer_limits<T>::maximum;
    static constexpr T absorbing = T{0};
};

template <class Argument, class T>
struct functional_properties<::asc::std::bit_or<Argument>, T,
    ::asc::std::enable_if_t<functional_matching_v<Argument, T> && functional_unsigned_v<T>>>
    : functional_property_flags<true, true, true, true> {
    static constexpr T identity = T{0};
    static constexpr T absorbing = functional_integer_limits<T>::maximum;
};

template <class Argument, class T>
struct functional_properties<::asc::std::bit_xor<Argument>, T,
    ::asc::std::enable_if_t<functional_matching_v<Argument, T> && functional_unsigned_v<T>>>
    : functional_property_flags<true, true, true, false> {
    static constexpr T identity = T{0};
};

template <class Argument, class T>
struct functional_properties<::asc::std::logical_and<Argument>, T,
    ::asc::std::enable_if_t<functional_matching_v<Argument, T>&& ::asc::std::is_same_v<T, bool>>>
    : functional_property_flags<true, true, true, true> {
    static constexpr bool identity = true;
    static constexpr bool absorbing = false;
};

template <class Argument, class T>
struct functional_properties<::asc::std::logical_or<Argument>, T,
    ::asc::std::enable_if_t<functional_matching_v<Argument, T>&& ::asc::std::is_same_v<T, bool>>>
    : functional_property_flags<true, true, true, true> {
    static constexpr bool identity = false;
    static constexpr bool absorbing = true;
};

template <class Argument, class T>
struct functional_properties<::asc::maximum<Argument>, T,
    ::asc::std::enable_if_t<functional_matching_v<Argument, T> && functional_integer_v<T>>>
    : functional_property_flags<true, true, true, true> {
    static constexpr T identity = functional_integer_limits<T>::lowest;
    static constexpr T absorbing = functional_integer_limits<T>::maximum;
};

template <class Argument, class T>
struct functional_properties<::asc::minimum<Argument>, T,
    ::asc::std::enable_if_t<functional_matching_v<Argument, T> && functional_integer_v<T>>>
    : functional_property_flags<true, true, true, true> {
    static constexpr T identity = functional_integer_limits<T>::maximum;
    static constexpr T absorbing = functional_integer_limits<T>::lowest;
};

}  // namespace detail
}  // namespace asc

#endif  // CANN_ASC_STL_ASC___FUNCTIONAL_METADATA_H
