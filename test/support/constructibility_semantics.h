/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef ASC_STL_TEST_CONSTRUCTIBILITY_SEMANTICS_H
#define ASC_STL_TEST_CONSTRUCTIBILITY_SEMANTICS_H

#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__floating_point/storage.h>
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_implicitly_default_constructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_convertible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_destructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/numbers>

namespace asc_stl_constructibility_test {

struct empty {};
struct base_class {};
struct derived_class : base_class {};

struct throwing_dtor {
    CANN_ASC_STL_API ~throwing_dtor() noexcept(false)
    {}
};

struct deleted_copy {
    CANN_ASC_STL_API deleted_copy() = default;
    CANN_ASC_STL_API deleted_copy(const deleted_copy&) = delete;
    CANN_ASC_STL_API deleted_copy& operator=(const deleted_copy&) = delete;
};

struct throwing_assign {
    CANN_ASC_STL_API throwing_assign() = default;
    CANN_ASC_STL_API throwing_assign& operator=(const throwing_assign&) noexcept(false)
    {
        return *this;
    }
};

struct throwing_copy {
    CANN_ASC_STL_API throwing_copy() = default;
    CANN_ASC_STL_API throwing_copy(const throwing_copy&) noexcept(false)
    {}
};

struct noexcept_movable {
    CANN_ASC_STL_API noexcept_movable() = default;
    CANN_ASC_STL_API noexcept_movable(noexcept_movable&&) noexcept = default;
    CANN_ASC_STL_API noexcept_movable& operator=(noexcept_movable&&) noexcept = default;
    CANN_ASC_STL_API noexcept_movable(const noexcept_movable&) noexcept = default;
    CANN_ASC_STL_API noexcept_movable& operator=(const noexcept_movable&) noexcept = default;
};

struct two_arg_only {
    CANN_ASC_STL_API two_arg_only(int, int)
    {}
};

struct explicit_default {
    CANN_ASC_STL_API explicit explicit_default()
    {}
};

struct throwing_conversion {
    CANN_ASC_STL_API operator int() noexcept(false)
    {
        return 7;
    }
};

using asc::std::__fp_format;
using asc::std::__fp_from_storage;
using asc::std::__fp_get_storage;
using asc::std::__fp_storage_of_t;
using asc::std::__fp_storage_t;
using asc::std::__has_common_type;
using asc::std::add_pointer_t;
using asc::std::common_type_t;
using asc::std::decay_t;

// Independent goldens: every expected value below is spelled as a language
// literal or a hand-derived language fact, never as another trait call.

// add_pointer: pointer formation through reference removal.
static_assert(asc::std::is_same_v<add_pointer_t<int>, int*>);
static_assert(asc::std::is_same_v<add_pointer_t<int&>, int*>);
static_assert(asc::std::is_same_v<add_pointer_t<const int&>, const int*>);
static_assert(asc::std::is_same_v<add_pointer_t<int*>, int**>);
static_assert(asc::std::is_same_v<add_pointer_t<void>, void*>);
static_assert(asc::std::is_same_v<add_pointer_t<int(int)>, int (*)(int)>);
static_assert(asc::std::is_same_v<asc::std::add_pointer<int>::type, int*>);

// decay: lvalue-to-rvalue, array-to-pointer, and function-to-pointer.
static_assert(asc::std::is_same_v<decay_t<const int&>, int>);
static_assert(asc::std::is_same_v<decay_t<int&&>, int>);
static_assert(asc::std::is_same_v<decay_t<const int>, int>);
static_assert(asc::std::is_same_v<decay_t<int[2]>, int*>);
static_assert(asc::std::is_same_v<decay_t<const int[3]>, const int*>);
static_assert(asc::std::is_same_v<decay_t<void(int)>, void (*)(int)>);
static_assert(asc::std::is_same_v<asc::std::decay<empty>::type, empty>);

// is_assignable: assignment well-formedness for reference and value targets.
static_assert(asc::std::is_assignable_v<int&, int>);
static_assert(asc::std::is_assignable_v<int&, double>);
static_assert(!asc::std::is_assignable_v<const int&, int>);
static_assert(!asc::std::is_assignable_v<int, int>);
static_assert(asc::std::is_assignable_v<empty&, empty&&>);

// is_constructible: constructor and reference-binding well-formedness.
static_assert(asc::std::is_constructible_v<int>);
static_assert(asc::std::is_constructible_v<int, double>);
static_assert(asc::std::is_constructible_v<empty, const empty&>);
static_assert(!asc::std::is_constructible_v<void, int>);
static_assert(!asc::std::is_constructible_v<empty, int>);
static_assert(asc::std::is_constructible_v<int&, int&>);
static_assert(!asc::std::is_constructible_v<int&, int&&>);
static_assert(asc::std::is_constructible_v<int&&, int>);
static_assert(asc::std::is_constructible_v<int[3]>);
static_assert(!asc::std::is_constructible_v<int[]>);

// is_convertible: implicit conversion well-formedness.
static_assert(asc::std::is_convertible_v<int, double>);
static_assert(asc::std::is_convertible_v<derived_class*, base_class*>);
static_assert(!asc::std::is_convertible_v<base_class*, derived_class*>);
static_assert(!asc::std::is_convertible_v<double, void*>);
static_assert(asc::std::is_convertible_v<void, void>);
static_assert(!asc::std::is_convertible_v<int, empty>);

// is_nothrow_destructible: exception specification of destruction.
static_assert(asc::std::is_nothrow_destructible_v<int>);
static_assert(asc::std::is_nothrow_destructible_v<empty>);
static_assert(!asc::std::is_nothrow_destructible_v<throwing_dtor>);
static_assert(asc::std::is_nothrow_destructible_v<int&>);
static_assert(asc::std::is_nothrow_destructible_v<int[3]>);

// is_object: scalars, arrays, unions, and classes are objects.
static_assert(asc::std::is_object_v<int>);
static_assert(asc::std::is_object_v<int*>);
static_assert(asc::std::is_object_v<empty>);
static_assert(asc::std::is_object_v<int[3]>);
static_assert(!asc::std::is_object_v<int&>);
static_assert(!asc::std::is_object_v<void>);
static_assert(!asc::std::is_object_v<int(int)>);

// The copy/move/default constructibility and assignability wrappers.
static_assert(asc::std::is_copy_assignable_v<int>);
static_assert(asc::std::is_copy_assignable_v<empty>);
static_assert(!asc::std::is_copy_assignable_v<deleted_copy>);
static_assert(asc::std::is_copy_constructible_v<empty>);
static_assert(!asc::std::is_copy_constructible_v<deleted_copy>);
static_assert(asc::std::is_default_constructible_v<int>);
static_assert(asc::std::is_default_constructible_v<int[3]>);
static_assert(!asc::std::is_default_constructible_v<void>);
static_assert(!asc::std::is_default_constructible_v<two_arg_only>);
static_assert(asc::std::is_move_assignable_v<empty>);
static_assert(!asc::std::is_move_assignable_v<deleted_copy>);
static_assert(asc::std::is_move_constructible_v<empty>);
static_assert(!asc::std::is_move_constructible_v<deleted_copy>);

// The nothrow constructibility and assignability wrappers.
static_assert(asc::std::is_nothrow_assignable_v<int&, int>);
static_assert(!asc::std::is_nothrow_assignable_v<throwing_assign&, const throwing_assign&>);
static_assert(asc::std::is_nothrow_constructible_v<int>);
static_assert(asc::std::is_nothrow_constructible_v<empty, const empty&>);
static_assert(!asc::std::is_nothrow_constructible_v<throwing_copy, const throwing_copy&>);
static_assert(asc::std::is_nothrow_copy_assignable_v<noexcept_movable>);
static_assert(!asc::std::is_nothrow_copy_assignable_v<throwing_assign>);
static_assert(asc::std::is_nothrow_copy_constructible_v<noexcept_movable>);
static_assert(!asc::std::is_nothrow_copy_constructible_v<throwing_copy>);
static_assert(asc::std::is_nothrow_default_constructible_v<empty>);
static_assert(asc::std::is_nothrow_move_assignable_v<noexcept_movable>);
static_assert(!asc::std::is_nothrow_move_assignable_v<throwing_assign>);
static_assert(asc::std::is_nothrow_move_constructible_v<noexcept_movable>);
static_assert(!asc::std::is_nothrow_move_constructible_v<throwing_copy>);

// is_nothrow_convertible: exception specification of the conversion.
static_assert(asc::std::is_nothrow_convertible_v<int, float>);
static_assert(asc::std::is_nothrow_convertible_v<void, void>);
static_assert(!asc::std::is_nothrow_convertible_v<throwing_conversion, int>);
static_assert(!asc::std::is_nothrow_convertible_v<int, empty>);

// is_implicitly_default_constructible: implicit default initialization.
static_assert(asc::std::__is_implicitly_default_constructible<empty>::value);
static_assert(asc::std::__is_implicitly_default_constructible<int>::value);
static_assert(!asc::std::__is_implicitly_default_constructible<explicit_default>::value);
static_assert(!asc::std::__is_implicitly_default_constructible<two_arg_only>::value);

// common_type: conditional-expression and decay composition. The expected
// types are language-level usual arithmetic conversion results.
static_assert(asc::std::is_same_v<common_type_t<int>, int>);
static_assert(asc::std::is_same_v<common_type_t<int, int>, int>);
static_assert(asc::std::is_same_v<common_type_t<int, long long>, long long>);
static_assert(asc::std::is_same_v<common_type_t<int, double>, double>);
static_assert(asc::std::is_same_v<common_type_t<int&, const int&>, int>);
static_assert(asc::std::is_same_v<common_type_t<int, long, double>, double>);
static_assert(asc::std::is_same_v<common_type_t<empty, empty>, empty>);
static_assert(__has_common_type<int, double>);
static_assert(!__has_common_type<empty, int>);

// bit_cast: IEEE 754 bit patterns are independent goldens.
static_assert(asc::std::bit_cast<asc::std::uint32_t>(1.0f) == 0x3F800000u);
static_assert(asc::std::bit_cast<float>(0x3F800000u) == 1.0f);
static_assert(asc::std::bit_cast<asc::std::uint32_t>(-2.0f) == 0xC0000000u);
static_assert(asc::std::bit_cast<asc::std::uint64_t>(1.0) == 0x3FF0000000000000ULL);

// __floating_point storage: width mapping and bit-pattern round trip.
static_assert(asc::std::is_same_v<__fp_storage_t<__fp_format::__binary16>, asc::std::uint16_t>);
static_assert(asc::std::is_same_v<__fp_storage_t<__fp_format::__bfloat16>, asc::std::uint16_t>);
static_assert(asc::std::is_same_v<__fp_storage_t<__fp_format::__binary32>, asc::std::uint32_t>);
static_assert(asc::std::is_same_v<__fp_storage_t<__fp_format::__binary64>, asc::std::uint64_t>);
static_assert(asc::std::is_same_v<__fp_storage_of_t<float>, asc::std::uint32_t>);
static_assert(asc::std::is_same_v<__fp_storage_of_t<double>, asc::std::uint64_t>);
static_assert(__fp_get_storage(1.0f) == 0x3F800000u);
static_assert(__fp_get_storage(1.0) == 0x3FF0000000000000ULL);
static_assert(__fp_from_storage<float>(0x3F800000u) == 1.0f);
static_assert(__fp_from_storage<double>(__fp_storage_of_t<double>{0x3FF0000000000000ULL}) == 1.0);

// numbers: the mathematical values are the independent goldens. The double
// comparisons are constant expressions only; Device runtime usage below
// stays on constant-folded and float paths.
static_assert(asc::std::numbers::e == 2.718281828459045235360287471352662498);
static_assert(asc::std::numbers::log2e == 1.442695040888963407359924681001892137);
static_assert(asc::std::numbers::log10e == 0.434294481903251827651128918916605082);
static_assert(asc::std::numbers::pi == 3.141592653589793238462643383279502884);
static_assert(asc::std::numbers::inv_pi == 0.318309886183790671537767526745028724);
static_assert(asc::std::numbers::inv_sqrtpi == 0.564189583547756286948079451560772586);
static_assert(asc::std::numbers::ln2 == 0.693147180559945309417232121458176568);
static_assert(asc::std::numbers::ln10 == 2.302585092994045684017991454684364208);
static_assert(asc::std::numbers::sqrt2 == 1.414213562373095048801688724209698079);
static_assert(asc::std::numbers::sqrt3 == 1.732050807568877293527446341505872367);
static_assert(asc::std::numbers::inv_sqrt3 == 0.577350269189625764509148780501957456);
static_assert(asc::std::numbers::egamma == 0.577215664901532860606512090082402431);
static_assert(asc::std::numbers::phi == 1.618033988749894848204586834365638118);

static_assert(asc::std::e_v<float> == 2.718281828459045235360287471352662498f);
static_assert(asc::std::log2e_v<float> == 1.442695040888963407359924681001892137f);
static_assert(asc::std::log10e_v<float> == 0.434294481903251827651128918916605082f);
static_assert(asc::std::pi_v<float> == 3.141592653589793238462643383279502884f);
static_assert(asc::std::inv_pi_v<float> == 0.318309886183790671537767526745028724f);
static_assert(asc::std::inv_sqrtpi_v<float> == 0.564189583547756286948079451560772586f);
static_assert(asc::std::ln2_v<float> == 0.693147180559945309417232121458176568f);
static_assert(asc::std::ln10_v<float> == 2.302585092994045684017991454684364208f);
static_assert(asc::std::sqrt2_v<float> == 1.414213562373095048801688724209698079f);
static_assert(asc::std::sqrt3_v<float> == 1.732050807568877293527446341505872367f);
static_assert(asc::std::inv_sqrt3_v<float> == 0.577350269189625764509148780501957456f);
static_assert(asc::std::egamma_v<float> == 0.577215664901532860606512090082402431f);
static_assert(asc::std::phi_v<float> == 1.618033988749894848204586834365638118f);

CANN_ASC_STL_API constexpr int evaluate() noexcept
{
    // Runtime independent goldens: IEEE 754 bit patterns, round trips, and
    // scaled float arithmetic stay off runtime double operations, which the
    // ordinary-AICore mode does not deliver.
    const float one = 1.0f;
    const bool bit_golden =
        asc::std::bit_cast<asc::std::uint32_t>(one) == 0x3F800000u && asc::std::bit_cast<float>(0x3F800000u) == one;
    const bool storage_golden = __fp_get_storage(2.0f) == 0x40000000u && __fp_from_storage<float>(0x40000000u) == 2.0f;
    constexpr float pi_folded = static_cast<float>(asc::std::numbers::pi);
    constexpr float e_folded = static_cast<float>(asc::std::numbers::e);
    const bool numbers_golden = static_cast<unsigned>(pi_folded * 100.0f) == 314u &&
        static_cast<unsigned>(e_folded * 100.0f) == 271u &&
        static_cast<unsigned>(asc::std::pi_v<float> * 100.0f) == 314u &&
        static_cast<unsigned>(asc::std::sqrt2_v<float> * 1000.0f) == 1414u;
    const bool runtime_golden = bit_golden && storage_golden && numbers_golden;
    return runtime_golden ? 0 : 1;
}

}  // namespace asc_stl_constructibility_test

#endif  // ASC_STL_TEST_CONSTRUCTIBILITY_SEMANTICS_H
