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

#ifndef ASC_STL_TEST_SUPPORT_VOCABULARY_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_VOCABULARY_SEMANTICS_H

#include <asc/std/__floating_point/format.h>
#include <asc/std/__fwd/char_traits.h>
#include <asc/std/__fwd/complex.h>
#include <asc/std/__fwd/fp.h>
#include <asc/std/__fwd/hash.h>
#include <asc/std/__fwd/iterator.h>
#include <asc/std/__fwd/optional.h>
#include <asc/std/__fwd/pair.h>
#include <asc/std/__fwd/reference_wrapper.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/add_rvalue_reference.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_extended_arithmetic.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_primary_template.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/underlying_type.h>
#include <asc/std/cfloat>

namespace asc_stl_vocabulary_test {

struct empty {};
struct runtime_payload {
    int first;
    int second;
};
struct nontrivial_copy_construct {
    CANN_ASC_STL_API nontrivial_copy_construct() : value(0)
    {}
    CANN_ASC_STL_API nontrivial_copy_construct(const nontrivial_copy_construct& other) : value(other.value)
    {}
    int value;
};
struct nontrivial_copy_assign {
    CANN_ASC_STL_API nontrivial_copy_assign() : value(0)
    {}
    CANN_ASC_STL_API nontrivial_copy_assign& operator=(const nontrivial_copy_assign& other)
    {
        value = other.value + 1;
        return *this;
    }
    int value;
};
struct nontrivial_move_construct {
    CANN_ASC_STL_API nontrivial_move_construct() : value(0)
    {}
    CANN_ASC_STL_API nontrivial_move_construct(nontrivial_move_construct&& other) : value(other.value)
    {}
    int value;
};
struct nontrivial_move_assign {
    CANN_ASC_STL_API nontrivial_move_assign() : value(0)
    {}
    CANN_ASC_STL_API nontrivial_move_assign& operator=(nontrivial_move_assign&& other)
    {
        value = other.value + 1;
        return *this;
    }
    int value;
};
struct variant_like {};
struct primary_traits_iterator {};

}  // namespace asc_stl_vocabulary_test

namespace asc {
namespace std {

template <>
struct variant_size<asc_stl_vocabulary_test::variant_like> : integral_constant<__SIZE_TYPE__, 3> {};

template <>
struct variant_alternative<0, asc_stl_vocabulary_test::variant_like> {
    using type = int;
};

template <>
struct variant_alternative<1, asc_stl_vocabulary_test::variant_like> {
    using type = double;
};

template <>
struct iterator_traits<asc_stl_vocabulary_test::primary_traits_iterator> {
    using __asc_primary_template = iterator_traits;
};

}  // namespace std
}  // namespace asc

namespace asc_stl_vocabulary_test {

using asc::std::__copy_cvref_t;
using asc::std::__fp_format;
using asc::std::__is_asc_std_char_traits_v;
using asc::std::__is_asc_std_complex_v;
using asc::std::__is_asc_std_optional_v;
using asc::std::__is_asc_std_pair;
using asc::std::__is_asc_std_reference_wrapper_v;
using asc::std::__is_asc_std_tuple;
using asc::std::__is_cv_integer_v;
using asc::std::__is_extended_arithmetic_v;
using asc::std::__is_integer_v;
using asc::std::__is_primary_asc_template;
using asc::std::__is_primary_std_template;
using asc::std::__is_tuple_of_iterator_references_v;
using asc::std::__select_traits;
using asc::std::__variant_npos;
using asc::std::add_lvalue_reference_t;
using asc::std::add_rvalue_reference_t;
using asc::std::bool_constant;
using asc::std::char_traits;
using asc::std::complex;
using asc::std::is_arithmetic;
using asc::std::is_arithmetic_v;
using asc::std::is_same_v;
using asc::std::is_signed;
using asc::std::is_signed_v;
using asc::std::is_trivially_copy_assignable_v;
using asc::std::is_trivially_copy_constructible_v;
using asc::std::is_trivially_move_assignable_v;
using asc::std::is_trivially_move_constructible_v;
using asc::std::is_unsigned;
using asc::std::is_unsigned_v;
using asc::std::iterator_traits;
using asc::std::optional;
using asc::std::pair;
using asc::std::reference_wrapper;
using asc::std::reverse_iterator;
using asc::std::tuple;
using asc::std::underlying_type_t;
using asc::std::variant;
using asc::std::variant_alternative_t;
using asc::std::variant_npos;
using asc::std::variant_size_v;

// __fwd/char_traits.h: declaration vocabulary and detection helper.
static_assert(!__is_asc_std_char_traits_v<int>);
static_assert(__is_asc_std_char_traits_v<char_traits<char>>);  // NOLINT(build/include_what_you_use)
static_assert(__is_asc_std_char_traits_v<char_traits<double>>);
static_assert(!__is_asc_std_char_traits_v<char_traits<char>&>);  // NOLINT(build/include_what_you_use)

// __fwd/complex.h: declaration vocabulary with cv passthrough detection.
static_assert(!__is_asc_std_complex_v<float>);
static_assert(!__is_asc_std_complex_v<complex<float>&>);
static_assert(__is_asc_std_complex_v<complex<float>>);
static_assert(__is_asc_std_complex_v<const complex<double>>);
static_assert(__is_asc_std_complex_v<volatile complex<float>>);
static_assert(__is_asc_std_complex_v<const volatile complex<float>>);

// __fwd/optional.h: declaration vocabulary and detection helper.
static_assert(!__is_asc_std_optional_v<int>);
static_assert(!__is_asc_std_optional_v<int*>);
static_assert(__is_asc_std_optional_v<optional<int>>);
static_assert(!__is_asc_std_optional_v<optional<int>&>);

// __fwd/pair.h: declaration vocabulary and detection helper.
static_assert(!__is_asc_std_pair<int>);
static_assert(!__is_asc_std_pair<pair<int, double>*>);
static_assert(__is_asc_std_pair<pair<int, double>>);            // NOLINT(build/include_what_you_use)
static_assert(__is_asc_std_pair<pair<float, pair<int, int>>>);  // NOLINT(build/include_what_you_use)

// __fwd/reference_wrapper.h: declaration vocabulary and detection helper.
static_assert(!__is_asc_std_reference_wrapper_v<int>);
static_assert(!__is_asc_std_reference_wrapper_v<int&>);
static_assert(__is_asc_std_reference_wrapper_v<reference_wrapper<int>>);

// __fwd/tuple.h: declaration vocabulary and detection helpers.
static_assert(!__is_asc_std_tuple<int>);
static_assert(!__is_asc_std_tuple<tuple<int, float>*>);
static_assert(__is_asc_std_tuple<tuple<>>);
static_assert(__is_asc_std_tuple<tuple<int, float>>);  // NOLINT(build/include_what_you_use)
static_assert(!__is_tuple_of_iterator_references_v<int>);
static_assert(!__is_tuple_of_iterator_references_v<tuple<int, float>>);  // NOLINT(build/include_what_you_use)

// __fwd/variant.h: declaration vocabulary, size/alternative helpers and npos markers.
static_assert(variant_size_v<variant_like> == 3);
static_assert(is_same_v<decltype(variant_size_v<variant_like>), const __SIZE_TYPE__>);
static_assert(is_same_v<variant_alternative_t<0, variant_like>, int>);
static_assert(is_same_v<variant_alternative_t<1, variant_like>, double>);
static_assert(variant_npos == ~static_cast<__SIZE_TYPE__>(0));
static_assert(is_same_v<decltype(variant_npos), const __SIZE_TYPE__>);
static_assert(__variant_npos<unsigned int> == 4294967295u);
static_assert(__variant_npos<unsigned char> == 255);

// __fwd/hash.h, __fwd/iterator.h, and __fwd/fp.h: forward declarations stay usable.
CANN_ASC_STL_API constexpr int forward_declarations_usable() noexcept
{
    asc::std::hash<int>* hash_ptr = nullptr;
    asc::std::__back_insert_iterator<int>* back_ptr = nullptr;
    iterator_traits<int>* traits_ptr = nullptr;
    reverse_iterator<int*>* reverse_ptr = nullptr;
    asc::std::__asc_fp<static_cast<__fp_format>(0)>* fp_ptr = nullptr;
    return (hash_ptr == nullptr && back_ptr == nullptr && traits_ptr == nullptr && reverse_ptr == nullptr &&
               fp_ptr == nullptr) ?
        0 :
        1;
}
static_assert(forward_declarations_usable() == 0);

// __type_traits/add_lvalue_reference.h: referenceable types gain lvalue references.
static_assert(is_same_v<add_lvalue_reference_t<int>, int&>);
static_assert(is_same_v<add_lvalue_reference_t<const int>, const int&>);
static_assert(is_same_v<add_lvalue_reference_t<int*>, int*&>);
static_assert(is_same_v<add_lvalue_reference_t<void>, void>);
static_assert(is_same_v<add_lvalue_reference_t<void()>, void (&)()>);
static_assert(is_same_v<asc::std::add_lvalue_reference<double>::type, double&>);

// __type_traits/add_rvalue_reference.h: referenceable types gain rvalue references.
static_assert(is_same_v<add_rvalue_reference_t<int>, int&&>);
static_assert(is_same_v<add_rvalue_reference_t<const int>, const int&&>);
static_assert(is_same_v<add_rvalue_reference_t<void>, void>);
static_assert(is_same_v<add_rvalue_reference_t<void()>, void (&&)()>);
static_assert(is_same_v<asc::std::add_rvalue_reference<float>::type, float&&>);

// __type_traits/is_arithmetic.h: integral and floating point categories.
static_assert(is_arithmetic_v<bool>);
static_assert(is_arithmetic_v<int>);
static_assert(is_arithmetic_v<unsigned long>);
static_assert(is_arithmetic_v<float>);
static_assert(is_arithmetic_v<const double>);
static_assert(is_arithmetic_v<volatile long double>);
static_assert(!is_arithmetic_v<int*>);
static_assert(!is_arithmetic_v<void>);
static_assert(!is_arithmetic_v<empty>);
static_assert(!is_arithmetic_v<int&>);
static_assert(is_arithmetic<char>::value);

// __type_traits/is_integer.h: arithmetic integer vocabulary without bool and characters.
static_assert(__is_integer_v<signed char>);
static_assert(__is_integer_v<short>);
static_assert(__is_integer_v<int>);
static_assert(__is_integer_v<long long>);
static_assert(__is_integer_v<unsigned int>);
static_assert(!__is_integer_v<bool>);
static_assert(!__is_integer_v<char>);
static_assert(!__is_integer_v<wchar_t>);
static_assert(!__is_integer_v<float>);
static_assert(!__is_integer_v<empty>);
static_assert(__is_cv_integer_v<const unsigned long>);
static_assert(__is_cv_integer_v<volatile int>);
static_assert(!__is_cv_integer_v<const float>);
static_assert(!__is_cv_integer_v<const char>);

// __type_traits/is_primary_template.h: primary-template detection and trait selection.
static_assert(!__is_primary_asc_template<int*>::value);
static_assert(__is_primary_asc_template<primary_traits_iterator>::value);
static_assert(__is_primary_std_template<int*>::value);
static_assert(is_same_v<__select_traits<int*, empty>, iterator_traits<int*>>);
static_assert(is_same_v<__select_traits<primary_traits_iterator, empty>, empty>);

// __type_traits/copy_cvref.h: full cv/ref qualification matrix.
static_assert(is_same_v<__copy_cvref_t<int, long>, long>);
static_assert(is_same_v<__copy_cvref_t<const int, long>, const long>);
static_assert(is_same_v<__copy_cvref_t<volatile int, long>, volatile long>);
static_assert(is_same_v<__copy_cvref_t<const volatile int, long>, const volatile long>);
static_assert(is_same_v<__copy_cvref_t<int&, long>, long&>);
static_assert(is_same_v<__copy_cvref_t<const int&, long>, const long&>);
static_assert(is_same_v<__copy_cvref_t<volatile int&, long>, volatile long&>);
static_assert(is_same_v<__copy_cvref_t<const volatile int&, long>, const volatile long&>);
static_assert(is_same_v<__copy_cvref_t<int&&, long>, long&&>);
static_assert(is_same_v<__copy_cvref_t<const int&&, long>, const long&&>);
static_assert(is_same_v<__copy_cvref_t<volatile int&&, long>, volatile long&&>);
static_assert(is_same_v<__copy_cvref_t<const volatile int&&, long>, const volatile long&&>);

// __type_traits/is_extended_arithmetic.h: arithmetic plus approved extended vocabulary.
static_assert(__is_extended_arithmetic_v<int>);
static_assert(__is_extended_arithmetic_v<float>);
static_assert(__is_extended_arithmetic_v<const double>);
static_assert(!__is_extended_arithmetic_v<void>);
static_assert(!__is_extended_arithmetic_v<int*>);
static_assert(!__is_extended_arithmetic_v<empty>);

// __type_traits/is_signed.h: signed categories across builtin and fallback paths.
static_assert(is_signed_v<signed char>);
static_assert(is_signed_v<short>);
static_assert(is_signed_v<int>);
static_assert(is_signed_v<long double>);
static_assert(is_signed_v<const short>);
static_assert(!is_signed_v<unsigned int>);
static_assert(!is_signed_v<unsigned long long>);
static_assert(!is_signed_v<bool>);
static_assert(!is_signed_v<empty>);
static_assert(!is_signed_v<int*>);
static_assert(is_signed<float>::value);

// __type_traits/is_unsigned.h: unsigned categories across builtin and fallback paths.
static_assert(is_unsigned_v<unsigned char>);
static_assert(is_unsigned_v<unsigned int>);
static_assert(is_unsigned_v<unsigned long long>);
static_assert(is_unsigned_v<bool>);
static_assert(is_unsigned_v<const unsigned short>);
static_assert(!is_unsigned_v<int>);
static_assert(!is_unsigned_v<float>);
static_assert(!is_unsigned_v<empty>);
static_assert(!is_unsigned_v<int*>);
static_assert(is_unsigned<unsigned long>::value);

// __type_traits/is_trivially_copy_assignable.h
static_assert(is_trivially_copy_assignable_v<empty>);
static_assert(is_trivially_copy_assignable_v<int>);
static_assert(is_trivially_copy_assignable_v<runtime_payload>);
static_assert(!is_trivially_copy_assignable_v<nontrivial_copy_assign>);
static_assert(asc::std::is_trivially_copy_assignable<empty>::value);

// __type_traits/is_trivially_copy_constructible.h
static_assert(is_trivially_copy_constructible_v<empty>);
static_assert(is_trivially_copy_constructible_v<int>);
static_assert(is_trivially_copy_constructible_v<runtime_payload>);
static_assert(!is_trivially_copy_constructible_v<nontrivial_copy_construct>);
static_assert(asc::std::is_trivially_copy_constructible<empty>::value);

// __type_traits/is_trivially_move_assignable.h
static_assert(is_trivially_move_assignable_v<empty>);
static_assert(is_trivially_move_assignable_v<int>);
static_assert(is_trivially_move_assignable_v<runtime_payload>);
static_assert(!is_trivially_move_assignable_v<nontrivial_move_assign>);
static_assert(asc::std::is_trivially_move_assignable<empty>::value);

// __type_traits/is_trivially_move_constructible.h
static_assert(is_trivially_move_constructible_v<empty>);
static_assert(is_trivially_move_constructible_v<int>);
static_assert(is_trivially_move_constructible_v<runtime_payload>);
static_assert(!is_trivially_move_constructible_v<nontrivial_move_construct>);
static_assert(asc::std::is_trivially_move_constructible<empty>::value);

// __floating_point/format.h: representation classification with independent <float.h> goldens.
#if FLT_RADIX == 2 && FLT_MANT_DIG == 24
static_assert(asc::std::__fp_format_of_v<float> == __fp_format::__binary32);
#endif
#if FLT_RADIX == 2 && DBL_MANT_DIG == 53
static_assert(asc::std::__fp_format_of_v<double> == __fp_format::__binary64);
#endif
#if LDBL_MIN_EXP == -1021 && LDBL_MAX_EXP == 1024 && LDBL_MANT_DIG == 53
static_assert(asc::std::__fp_format_of_v<long double> == __fp_format::__binary64);
#elif LDBL_MIN_EXP == -16381 && LDBL_MAX_EXP == 16384 && LDBL_MANT_DIG == 64
static_assert(asc::std::__fp_format_of_v<long double> == __fp_format::__fp80_x86);
#elif LDBL_MIN_EXP == -16381 && LDBL_MAX_EXP == 16384 && LDBL_MANT_DIG == 113
static_assert(asc::std::__fp_format_of_v<long double> == __fp_format::__binary128);
#endif

// __floating_point/format.h: cv passthrough, invalid classification, and fp wrapper identity.
static_assert(asc::std::__fp_format_of_v<const float> == __fp_format::__binary32);
static_assert(asc::std::__fp_format_of_v<volatile double> == __fp_format::__binary64);
static_assert(asc::std::__fp_format_of_v<const volatile float> == __fp_format::__binary32);
static_assert(asc::std::__fp_format_of_v<int> == __fp_format::__invalid);
static_assert(asc::std::__fp_format_of_v<void> == __fp_format::__invalid);
static_assert(asc::std::__fp_format_of_v<empty> == __fp_format::__invalid);
static_assert(asc::std::__fp_format_of_v<asc::std::__asc_fp<__fp_format::__bfloat16>> == __fp_format::__bfloat16);
static_assert(asc::std::__fp_format_of_v<asc::std::__asc_fp<__fp_format::__binary128>> == __fp_format::__binary128);

// __floating_point/format.h: ABI-layout contract of the representation vocabulary.
static_assert(is_same_v<underlying_type_t<__fp_format>, int>);
static_assert(sizeof(__fp_format) == sizeof(int));
static_assert(static_cast<int>(__fp_format::__binary32) != static_cast<int>(__fp_format::__binary64));
static_assert(static_cast<int>(__fp_format::__fp80_x86) != static_cast<int>(__fp_format::__binary128));
static_assert(static_cast<int>(__fp_format::__invalid) != static_cast<int>(__fp_format::__binary64));
CANN_ASC_STL_API constexpr int evaluate() noexcept
{
    // Runtime independent goldens: language arithmetic mirrors the trait outcomes.
    const int negative_value = -7;
    const unsigned int wrapped = 7u - 8u;
    const bool signed_golden = negative_value < 0;
    const bool unsigned_golden = wrapped > 0u;
    const runtime_payload original{3, 2};
    const runtime_payload copied = original;
    const bool trivial_copy_golden = copied.first == 3 && copied.second == 2;
    const bool format_golden = asc::std::__fp_format_of_v<float> == __fp_format::__binary32;
    return (signed_golden == is_signed_v<int>) && (unsigned_golden == is_unsigned_v<unsigned int>) &&
            trivial_copy_golden && is_trivially_copy_constructible_v<runtime_payload> && format_golden ?
        0 :
        1;
}

}  // namespace asc_stl_vocabulary_test
#endif
