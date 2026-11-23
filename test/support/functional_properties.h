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

#ifndef ASC_STL_TEST_FUNCTIONAL_PROPERTIES_H
#define ASC_STL_TEST_FUNCTIONAL_PROPERTIES_H

#include <asc/functional>
#include <asc/std/limits>
#include <asc/std/type_traits>

#include "functional_objects.h"

namespace asc_stl_functional_properties {
template <class Operator, class T, class = void>
struct can_get_identity : asc::std::false_type {};
template <class Operator, class T>
struct can_get_identity<Operator, T, asc::std::void_t<decltype(asc::identity_element<Operator, T>())>>
    : asc::std::true_type {};
template <class Operator, class T, class = void>
struct can_get_absorbing : asc::std::false_type {};
template <class Operator, class T>
struct can_get_absorbing<Operator, T, asc::std::void_t<decltype(asc::absorbing_element<Operator, T>())>>
    : asc::std::true_type {};

template <class T, template <class> class Operator>
CANN_ASC_STL_API constexpr bool same_forms()
{
    using Typed = Operator<T>;
    using Transparent = Operator<void>;
    return asc::is_associative_v<Typed, T> == asc::is_associative_v<Transparent, T> &&
        asc::is_commutative_v<Typed, T> == asc::is_commutative_v<Transparent, T> &&
        asc::has_identity_element_v<Typed, T> == asc::has_identity_element_v<Transparent, T> &&
        asc::has_absorbing_element_v<Typed, T> == asc::has_absorbing_element_v<Transparent, T>;
}

template <class T, bool Additive, bool Multiplicative>
CANN_ASC_STL_API constexpr bool unsigned_registration()
{
    using Add = asc::std::plus<T>;
    using Multiply = asc::std::multiplies<T>;
    static_assert(asc::is_associative_v<Add, T> == Additive);
    static_assert(asc::is_commutative_v<Add, T> == Additive);
    static_assert(asc::is_associative_v<Multiply, T> == Multiplicative);
    static_assert(asc::is_commutative_v<Multiply, T> == Multiplicative);
    static_assert(asc::has_identity_element_v<Add, T> && !asc::has_absorbing_element_v<Add, T>);
    static_assert(asc::has_identity_element_v<Multiply, T> && asc::has_absorbing_element_v<Multiply, T>);
    static_assert(asc::identity_element<Add, T>() == T{0});
    static_assert(asc::identity_element<Multiply, T>() == T{1});
    static_assert(asc::absorbing_element<Multiply, T>() == T{0});
    static_assert(same_forms<T, asc::std::plus>() && same_forms<T, asc::std::multiplies>());
    return true;
}

template <class T>
CANN_ASC_STL_API constexpr bool signed_registration()
{
    using Add = asc::std::plus<T>;
    using Multiply = asc::std::multiplies<T>;
    static_assert(!asc::is_associative_v<Add, T> && !asc::is_commutative_v<Add, T>);
    static_assert(!asc::is_associative_v<Multiply, T> && !asc::is_commutative_v<Multiply, T>);
    static_assert(asc::identity_element<Add, T>() == T{0});
    static_assert(asc::identity_element<Multiply, T>() == T{1});
    static_assert(asc::absorbing_element<Multiply, T>() == T{0});
    static_assert(!can_get_absorbing<Add, T>::value);
    static_assert(same_forms<T, asc::std::plus>() && same_forms<T, asc::std::multiplies>());
    const T low = (asc::std::numeric_limits<T>::lowest)();
    const T high = (asc::std::numeric_limits<T>::max)();
    return Add{}(low, T{0}) == low && Add{}(T{0}, high) == high && Multiply{}(low, T{1}) == low &&
        Multiply{}(T{1}, high) == high && Multiply{}(low, T{0}) == T{0} && Multiply{}(T{0}, high) == T{0};
}

template <class T>
CANN_ASC_STL_API constexpr bool bitwise_registration()
{
    using And = asc::std::bit_and<T>;
    using Or = asc::std::bit_or<T>;
    using Xor = asc::std::bit_xor<T>;
    static_assert(asc::is_associative_v<And, T> && asc::is_commutative_v<And, T>);
    static_assert(asc::is_associative_v<Or, T> && asc::is_commutative_v<Or, T>);
    static_assert(asc::is_associative_v<Xor, T> && asc::is_commutative_v<Xor, T>);
    static_assert(asc::identity_element<And, T>() == (asc::std::numeric_limits<T>::max)());
    static_assert(asc::identity_element<Or, T>() == T{0} && asc::identity_element<Xor, T>() == T{0});
    static_assert(asc::absorbing_element<And, T>() == T{0});
    static_assert(asc::absorbing_element<Or, T>() == (asc::std::numeric_limits<T>::max)());
    static_assert(!can_get_absorbing<Xor, T>::value);
    static_assert(same_forms<T, asc::std::bit_and>() && same_forms<T, asc::std::bit_or>());
    static_assert(same_forms<T, asc::std::bit_xor>());
    return true;
}

template <class T>
CANN_ASC_STL_API constexpr bool extreme_registration()
{
    using Max = asc::maximum<T>;
    using Min = asc::minimum<T>;
    constexpr T low = (asc::std::numeric_limits<T>::lowest)();
    constexpr T high = (asc::std::numeric_limits<T>::max)();
    static_assert(asc::is_associative_v<Max, T> && asc::is_commutative_v<Max, T>);
    static_assert(asc::is_associative_v<Min, T> && asc::is_commutative_v<Min, T>);
    static_assert(asc::identity_element<Max, T>() == low && asc::absorbing_element<Max, T>() == high);
    static_assert(asc::identity_element<Min, T>() == high && asc::absorbing_element<Min, T>() == low);
    static_assert(same_forms<T, asc::maximum>() && same_forms<T, asc::minimum>());
    static_assert(asc::std::is_same_v<decltype(asc::identity_element<Max, T>()), T>);
    static_assert(noexcept(asc::identity_element<Max, T>()) && noexcept(asc::absorbing_element<Min, T>()));
    return Max{}(low, high) == high && Max{}(high, low) == high && Min{}(low, high) == low && Min{}(high, low) == low;
}

template <class Operator, class T>
CANN_ASC_STL_API constexpr bool unregistered()
{
    static_assert(!asc::is_associative_v<Operator, T> && !asc::is_commutative_v<Operator, T>);
    static_assert(!asc::has_identity_element_v<Operator, T> && !asc::has_absorbing_element_v<Operator, T>);
    static_assert(!can_get_identity<Operator, T>::value && !can_get_absorbing<Operator, T>::value);
    return true;
}

struct incomplete;
struct left_projection {
    CANN_ASC_STL_API constexpr int operator()(int left, int) const noexcept
    {
        return left;
    }
};
struct average {
    CANN_ASC_STL_API constexpr int operator()(int left, int right) const noexcept
    {
        return (left + right) / 2;
    }
};

CANN_ASC_STL_API constexpr bool exclusions()
{
    static_assert(unregistered<asc::std::plus<int>, unsigned>());
    static_assert(unregistered<const asc::std::plus<int>, int>());
    static_assert(unregistered<asc::std::plus<void>, const int>());
    static_assert(unregistered<asc::std::plus<void>, int&>());
    static_assert(unregistered<asc::std::plus<void>, bool>());
    static_assert(unregistered<asc::std::logical_and<int>, bool>());
    static_assert(unregistered<asc::std::logical_and<void>, int>());
    static_assert(unregistered<asc::std::bit_and<void>, int>());
    static_assert(unregistered<asc::maximum<float>, float>());
    static_assert(unregistered<asc::minimum<void>, double>());
    static_assert(unregistered<asc::std::plus<void>, float>());
    static_assert(unregistered<asc::std::multiplies<void>, double>());
    static_assert(unregistered<asc::std::plus<void>, incomplete>());
    static_assert(unregistered<incomplete, int>());
    static_assert(unregistered<asc::maximum<void>, void>());
    static_assert(unregistered<asc::maximum<void>, int*>());
    static_assert(unregistered<left_projection, int>() && unregistered<average, int>());
    return true;
}

CANN_ASC_STL_API constexpr bool registrations()
{
    // These independent expected values describe the supported GNU/CCE integer ABI.
    static_assert(asc::std::numeric_limits<unsigned char>::digits == 8);
    static_assert(asc::std::numeric_limits<unsigned short>::digits == 16);
    static_assert(asc::std::numeric_limits<int>::digits == 31);
    return unsigned_registration<unsigned char, true, true>() && unsigned_registration<unsigned short, true, false>() &&
        unsigned_registration<unsigned, true, true>() && unsigned_registration<unsigned long, true, true>() &&
        unsigned_registration<unsigned long long, true, true>() && signed_registration<signed char>() &&
        signed_registration<short>() && signed_registration<int>() && signed_registration<long>() &&
        signed_registration<long long>() && bitwise_registration<unsigned char>() &&
        bitwise_registration<unsigned short>() && bitwise_registration<unsigned>() &&
        bitwise_registration<unsigned long>() && bitwise_registration<unsigned long long>();
}

CANN_ASC_STL_API constexpr bool extreme_registrations()
{
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
    if (!extreme_registration<char8_t>())
        return false;
#endif
    return extreme_registration<bool>() && extreme_registration<char>() && extreme_registration<signed char>() &&
        extreme_registration<unsigned char>() && extreme_registration<short>() &&
        extreme_registration<unsigned short>() && extreme_registration<int>() && extreme_registration<unsigned>() &&
        extreme_registration<long>() && extreme_registration<unsigned long>() && extreme_registration<long long>() &&
        extreme_registration<unsigned long long>() && extreme_registration<wchar_t>() &&
        extreme_registration<char16_t>() && extreme_registration<char32_t>();
}

CANN_ASC_STL_API constexpr bool logical_registrations()
{
    using And = asc::std::logical_and<bool>;
    using Or = asc::std::logical_or<void>;
    static_assert(asc::is_associative_v<And, bool> && asc::is_commutative_v<And, bool>);
    static_assert(asc::is_associative_v<Or, bool> && asc::is_commutative_v<Or, bool>);
    static_assert(asc::identity_element<And, bool>() && !asc::absorbing_element<And, bool>());
    static_assert(!asc::identity_element<Or, bool>() && asc::absorbing_element<Or, bool>());
    static_assert(same_forms<bool, asc::std::logical_and>() && same_forms<bool, asc::std::logical_or>());
    for (int a = 0; a != 2; ++a) {
        const bool value = a != 0;
        if (And{}(true, value) != value || And{}(value, true) != value || Or{}(false, value) != value ||
            Or{}(value, false) != value || And{}(false, value) || And{}(value, false) || !Or{}(true, value) ||
            !Or{}(value, true)) {
            return false;
        }
    }
    return true;
}

CANN_ASC_STL_API constexpr bool independent_laws()
{
    const left_projection left{};
    const average mean{};
    bool projection_commutes = true;
    bool mean_associates = true;
    for (int a = 0; a < 6; ++a) {
        for (int b = 0; b < 6; ++b) {
            projection_commutes = projection_commutes && left(a, b) == left(b, a);
            if (mean(a, b) != mean(b, a))
                return false;
            for (int c = 0; c < 6; ++c) {
                if (left(left(a, b), c) != left(a, left(b, c)))
                    return false;
                mean_associates = mean_associates && mean(mean(a, b), c) == mean(a, mean(b, c));
            }
        }
    }
    // Projection is associative only; truncated averaging is commutative only.
    // Zero is a right identity and a left absorbing element for left projection, not two-sided.
    return !projection_commutes && !mean_associates && left(4, 0) == 4 && left(0, 4) != 4 && left(0, 4) == 0 &&
        left(4, 0) != 0;
}

CANN_ASC_STL_API constexpr bool evaluate(unsigned value)
{
    const auto zero = asc::identity_element<asc::std::plus<void>, unsigned>();
    const auto one = asc::identity_element<asc::std::multiplies<void>, unsigned>();
    return registrations() && extreme_registrations() && logical_registrations() && exclusions() &&
        independent_laws() && asc_stl_functional_objects::evaluate(value) &&
        asc::std::plus<void>{}(value, zero) == value && asc::std::multiplies<void>{}(one, value) == value;
}
}  // namespace asc_stl_functional_properties

#endif  // ASC_STL_TEST_FUNCTIONAL_PROPERTIES_H
