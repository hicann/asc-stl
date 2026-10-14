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

#ifndef ASC_STL_TEST_SUPPORT_TYPE_TRANSFORM_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_TYPE_TRANSFORM_SEMANTICS_H

#include <asc/std/__floating_point/properties.h>
#include <asc/std/__floating_point/traits.h>
#include <asc/std/__type_traits/copy_cv.h>
#include <asc/std/__type_traits/extent.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_destructible.h>
#include <asc/std/__type_traits/is_member_function_pointer.h>
#include <asc/std/__type_traits/is_member_object_pointer.h>
#include <asc/std/__type_traits/is_member_pointer.h>
#include <asc/std/__type_traits/is_null_pointer.h>
#include <asc/std/__type_traits/is_scalar.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/make_const_lvalue_ref.h>
#include <asc/std/__type_traits/make_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_all_extents.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_extent.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/__type_traits/type_set.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/forward_like.h>
#include <asc/std/cfloat>
#include <asc/std/cstddef>

namespace asc_stl_type_transform_test {

struct empty {};
struct runtime_payload {
    int first;
    int second;
};
struct nontrivial_destruct {
    CANN_ASC_STL_API ~nontrivial_destruct()
    {}
};
struct deleted_destruct {
    CANN_ASC_STL_API deleted_destruct() = default;
    CANN_ASC_STL_API ~deleted_destruct() = delete;
};
struct host_struct {};
enum class enumeration { value };
union union_type {
    int integer;
    float real;
};

using asc::std::__copy_cv_t;
using asc::std::__fp_format;
using asc::std::__is_ext_asc_fp_v;
using asc::std::__is_ext_fp_v;
using asc::std::__is_fp_v;
using asc::std::__is_included_in_v;
using asc::std::__is_std_fp_v;
using asc::std::__make_const_lvalue_ref;
using asc::std::__make_type_set;
using asc::std::__to_unsigned_like;
using asc::std::__type_apply_q;
using asc::std::__type_at_c;
using asc::std::__type_back;
using asc::std::__type_concat;
using asc::std::__type_find_if;
using asc::std::__type_flatten;
using asc::std::__type_fold_left;
using asc::std::__type_fold_right;
using asc::std::__type_front;
using asc::std::__type_list;
using asc::std::__type_not;
using asc::std::__type_push_back;
using asc::std::__type_push_front;
using asc::std::__type_quote;
using asc::std::__type_self;
using asc::std::__type_set;
using asc::std::__type_set_eq_v;
using asc::std::__type_transform;
using asc::std::__type_unique;
using asc::std::conditional_t;
using asc::std::extent;
using asc::std::extent_v;
using asc::std::forward;
using asc::std::forward_like;
using asc::std::is_array;
using asc::std::is_array_v;
using asc::std::is_destructible;
using asc::std::is_destructible_v;
using asc::std::is_member_function_pointer;
using asc::std::is_member_function_pointer_v;
using asc::std::is_member_object_pointer;
using asc::std::is_member_object_pointer_v;
using asc::std::is_member_pointer;
using asc::std::is_member_pointer_v;
using asc::std::is_null_pointer;
using asc::std::is_null_pointer_v;
using asc::std::is_same_v;
using asc::std::is_scalar;
using asc::std::is_scalar_v;
using asc::std::is_trivially_destructible;
using asc::std::is_trivially_destructible_v;
using asc::std::is_void;
using asc::std::is_void_v;
using asc::std::make_signed;
using asc::std::make_signed_t;
using asc::std::make_unsigned;
using asc::std::make_unsigned_t;
using asc::std::remove_all_extents;
using asc::std::remove_all_extents_t;
using asc::std::remove_cvref;
using asc::std::remove_cvref_t;
using asc::std::remove_extent;
using asc::std::remove_extent_t;
using asc::std::remove_reference;
using asc::std::remove_reference_t;
using asc::std::type_identity_t;

template <class, class>
inline constexpr bool same_type = false;
template <class T>
inline constexpr bool same_type<T, T> = true;

// __type_traits/remove_reference.h: reference removal across cv matrices.
static_assert(same_type<remove_reference_t<int>, int>);
static_assert(same_type<remove_reference_t<int&>, int>);
static_assert(same_type<remove_reference_t<int&&>, int>);
static_assert(same_type<remove_reference_t<const int&>, const int>);
static_assert(same_type<remove_reference_t<const int&&>, const int>);
static_assert(same_type<typename remove_reference<void>::type, void>);
static_assert(same_type<remove_reference_t<int (&)[3]>, int[3]>);

// __type_traits/remove_extent.h: one extent level removed per instantiation.
static_assert(same_type<remove_extent_t<int>, int>);
static_assert(same_type<remove_extent_t<int[3]>, int>);
static_assert(same_type<remove_extent_t<int[3][5]>, int[5]>);
static_assert(same_type<remove_extent_t<int[]>, int>);
static_assert(same_type<typename remove_extent<int[3]>::type, int>);

// __type_traits/remove_all_extents.h: every extent level removed.
static_assert(same_type<remove_all_extents_t<int>, int>);
static_assert(same_type<remove_all_extents_t<int[3]>, int>);
static_assert(same_type<remove_all_extents_t<int[3][5]>, int>);
static_assert(same_type<remove_all_extents_t<int[][5]>, int>);
static_assert(same_type<typename remove_all_extents<const int[2][3]>::type, const int>);

// __type_traits/remove_cvref.h: cv and reference removal with same-uncvref helper.
static_assert(same_type<remove_cvref_t<int>, int>);
static_assert(same_type<remove_cvref_t<const int&>, int>);
static_assert(same_type<remove_cvref_t<volatile int&&>, int>);
static_assert(same_type<remove_cvref_t<const volatile int* const&>, const volatile int*>);
static_assert(same_type<typename remove_cvref<const double&&>::type, double>);
static_assert(asc::std::__is_same_uncvref<const int&, int>::value);
static_assert(asc::std::__is_same_uncvref<const int, int>::value);
static_assert(!asc::std::__is_same_uncvref<const int, long>::value);

// __type_traits/copy_cv.h: cv propagation without reference propagation.
static_assert(same_type<__copy_cv_t<const int, long>, const long>);
static_assert(same_type<__copy_cv_t<volatile int, long>, volatile long>);
static_assert(same_type<__copy_cv_t<const volatile int, long>, const volatile long>);
static_assert(same_type<__copy_cv_t<int, long>, long>);
static_assert(same_type<__copy_cv_t<const int&, long>, long>);

// __type_traits/make_const_lvalue_ref.h: const lvalue reference vocabulary.
static_assert(same_type<__make_const_lvalue_ref<int>, const int&>);
static_assert(same_type<__make_const_lvalue_ref<int&>, const int&>);
static_assert(same_type<__make_const_lvalue_ref<int&&>, const int&>);
static_assert(same_type<__make_const_lvalue_ref<const int&>, const int&>);

// __type_traits/extent.h: array extent across ranks and cv matrices.
static_assert(extent_v<int> == 0);
static_assert(extent_v<int[]> == 0);
static_assert(extent_v<int[3]> == 3);
static_assert(extent_v<int[3][5]> == 3);
static_assert(extent_v<int[3][5], 1> == 5);
static_assert(extent_v<int[3][5], 2> == 0);
static_assert(extent_v<const int[7]> == 7);
static_assert(asc::std::extent<int[2][4][6]>::value == 2);
static_assert(asc::std::extent<int[2][4][6], 2>::value == 6);
static_assert(is_same_v<decltype(extent_v<int[3]>), const unsigned long>);

// __type_traits/is_array.h: array classification.
static_assert(is_array_v<int[3]>);
static_assert(is_array_v<int[]>);
static_assert(is_array_v<const int[3]>);
static_assert(!is_array_v<int*>);
static_assert(!is_array_v<int&>);
static_assert(!is_array_v<empty>);
static_assert(!is_array_v<void>);
static_assert(is_array<int[3]>::value);

// __type_traits/is_void.h: void classification with cv passthrough.
static_assert(is_void_v<void>);
static_assert(is_void_v<const void>);
static_assert(is_void_v<volatile void>);
static_assert(!is_void_v<int>);
static_assert(!is_void_v<void*>);
static_assert(!is_void_v<int&>);
static_assert(is_void<const void>::value);

// __type_traits/is_null_pointer.h: nullptr_t classification.
static_assert(is_null_pointer_v<decltype(nullptr)>);
static_assert(is_null_pointer_v<const decltype(nullptr)>);
static_assert(!is_null_pointer_v<void*>);
static_assert(!is_null_pointer_v<int>);
static_assert(!is_null_pointer_v<empty>);
static_assert(is_null_pointer<decltype(nullptr)>::value);

// __type_traits/is_member_function_pointer.h: member function classification.
static_assert(is_member_function_pointer_v<int (host_struct::*)(double)>);
static_assert(is_member_function_pointer_v<int (host_struct::*)(double) const>);
static_assert(is_member_function_pointer_v<int (host_struct::*)(double) noexcept>);  // NOLINT(readability/casting)
static_assert(!is_member_function_pointer_v<int host_struct::*>);
static_assert(is_member_function_pointer_v<int (host_struct::*)(double) const&>);
static_assert(!is_member_function_pointer_v<int*>);
static_assert(is_member_function_pointer<int (host_struct::*)(double)>::value);

// __type_traits/is_member_object_pointer.h: member object classification.
static_assert(is_member_object_pointer_v<int host_struct::*>);
static_assert(is_member_object_pointer_v<const int host_struct::*>);
static_assert(!is_member_object_pointer_v<int (host_struct::*)(double)>);
static_assert(!is_member_object_pointer_v<int*>);
static_assert(is_member_object_pointer<int host_struct::*>::value);

// __type_traits/is_member_pointer.h: member pointer classification.
static_assert(is_member_pointer_v<int host_struct::*>);
static_assert(is_member_pointer_v<int (host_struct::*)(double)>);
static_assert(is_member_pointer_v<int (union_type::*)()>);
static_assert(!is_member_pointer_v<int*>);
static_assert(!is_member_pointer_v<empty>);
static_assert(is_member_pointer<int host_struct::*>::value);

// __type_traits/is_scalar.h: scalar classification.
static_assert(is_scalar_v<int>);
static_assert(is_scalar_v<double>);
static_assert(is_scalar_v<enumeration>);
static_assert(is_scalar_v<int*>);
static_assert(is_scalar_v<int host_struct::*>);
static_assert(is_scalar_v<decltype(nullptr)>);
static_assert(is_scalar_v<const float>);
static_assert(!is_scalar_v<empty>);
static_assert(!is_scalar_v<int&>);
static_assert(!is_scalar_v<int[3]>);
static_assert(!is_scalar_v<void>);
static_assert(is_scalar<enumeration>::value);

// __type_traits/is_destructible.h: destructibility classification.
static_assert(is_destructible_v<int>);
static_assert(is_destructible_v<int&>);
static_assert(is_destructible_v<int[3]>);
static_assert(is_destructible_v<empty>);
static_assert(is_destructible_v<runtime_payload>);
static_assert(is_destructible_v<nontrivial_destruct>);
static_assert(!is_destructible_v<void>);
static_assert(!is_destructible_v<int[]>);
static_assert(!is_destructible_v<void()>);
static_assert(!is_destructible_v<deleted_destruct>);
static_assert(is_destructible<empty>::value);

// __type_traits/is_trivially_destructible.h: trivial destruction classification.
static_assert(is_trivially_destructible_v<int>);
static_assert(is_trivially_destructible_v<empty>);
static_assert(is_trivially_destructible_v<runtime_payload>);
static_assert(is_trivially_destructible_v<int[3]>);
static_assert(!is_trivially_destructible_v<nontrivial_destruct>);
static_assert(!is_trivially_destructible_v<void>);
static_assert(is_trivially_destructible<int[3]>::value);

// __type_traits/make_signed.h: signed transformation with cv/ref passthrough.
static_assert(same_type<make_signed_t<int>, int>);
static_assert(same_type<make_signed_t<unsigned int>, int>);
static_assert(same_type<make_signed_t<unsigned long>, long>);
static_assert(same_type<make_signed_t<unsigned long long>, long long>);
static_assert(same_type<make_signed_t<const unsigned int>, const int>);
static_assert(same_type<make_signed_t<volatile unsigned short>, volatile short>);
static_assert(same_type<make_signed_t<signed char>, signed char>);
static_assert(same_type<typename make_signed<unsigned long>::type, long>);

// __type_traits/make_unsigned.h: unsigned transformation and helper vocabulary.
static_assert(same_type<make_unsigned_t<int>, unsigned int>);
static_assert(same_type<make_unsigned_t<unsigned int>, unsigned int>);
static_assert(same_type<make_unsigned_t<long>, unsigned long>);
static_assert(same_type<make_unsigned_t<const int>, const unsigned int>);
static_assert(same_type<typename make_unsigned<long long>::type, unsigned long long>);
static_assert(same_type<asc::std::__copy_unsigned_t<unsigned int, long>, unsigned long>);
static_assert(same_type<asc::std::__copy_unsigned_t<int, long>, long>);
static_assert(__to_unsigned_like(-1) == static_cast<unsigned int>(-1));

// __type_traits/type_set.h: set construction, membership, and equality.
using small_set = __make_type_set<int, long, int, char, long>;
static_assert(small_set::__size() == 3);
static_assert(__type_set_eq_v<small_set, char, int, long>);
static_assert(!__type_set_eq_v<small_set, char, int>);
static_assert(__type_set_eq_v<__type_set<>>);
static_assert(__is_included_in_v<long, int, long, char>);
static_assert(!__is_included_in_v<float, int, long, char>);

// __type_traits/type_list.h: list algorithms with hand-written type goldens.
using list_3 = __type_list<int, long, char>;
static_assert(list_3::__size == 3);
static_assert(same_type<__type_at_c<1, list_3>, long>);
static_assert(same_type<__type_front<list_3>, int>);
static_assert(same_type<__type_back<list_3>, char>);
static_assert(same_type<__type_push_back<list_3, double>, __type_list<int, long, char, double>>);
static_assert(same_type<__type_push_front<list_3, double>, __type_list<double, int, long, char>>);
static_assert(same_type<__type_concat<list_3, __type_list<double>, __type_list<float>>,
    __type_list<int, long, char, double, float>>);
static_assert(same_type<__type_concat<>, __type_list<>>);
static_assert(
    same_type<__type_flatten<__type_list<list_3, __type_list<double>>>, __type_list<int, long, char, double>>);
struct to_pointer {
    template <class T>
    using __call = T*;
};
static_assert(same_type<__type_transform<list_3, to_pointer>, __type_list<int*, long*, char*>>);
static_assert(same_type<__type_find_if<list_3, asc::std::__detail::__type_same_as<long>>, __type_list<long, char>>);
static_assert(same_type<__type_find_if<list_3, asc::std::__detail::__type_same_as<float>>, __type_list<>>);
static_assert(same_type<__type_unique<__type_list<int, long, int, char, long>>, __type_list<char, long, int>>);
struct push_back_step {
    template <class T, class L>
    using __call = __type_push_back<L, T>;
};
static_assert(same_type<__type_fold_right<list_3, __type_list<>, push_back_step>, __type_list<char, long, int>>);
struct append_step {
    template <class L, class T>
    using __call = __type_push_back<L, T>;
};
static_assert(same_type<__type_fold_left<list_3, __type_list<>, append_step>, __type_list<int, long, char>>);
template <class... Ts>
struct pack {};
static_assert(same_type<asc::std::__type_apply_q<pack, __type_list<int, long>>, pack<int, long>>);
static_assert(
    same_type<asc::std::__as_type_list<conditional_t<true, __type_list<int>, __type_list<long>>>, __type_list<int>>);
static_assert(asc::std::__type_callable<__type_self, int>::value);
static_assert(!asc::std::__type_callable<__type_not, int>::value);
static_assert(same_type<asc::std::__type_defer<__type_self, int>::type, int>);
static_assert(same_type<asc::std::__type_switch<2, asc::std::__type_case<1, char>, asc::std::__type_case<2, double>,
                            asc::std::__type_default<float>>,
    double>);
static_assert(
    same_type<asc::std::__type_switch<9, asc::std::__type_case<1, char>, asc::std::__type_default<float>>, float>);

// __floating_point/properties.h: representation goldens from the independent
// <float.h> macro oracle and IEEE 754 language constants.
static_assert(asc::std::__fp_exp_nbits_v<__fp_format::__binary32> == 8);
static_assert(asc::std::__fp_exp_nbits_v<__fp_format::__binary64> == 11);
static_assert(asc::std::__fp_exp_nbits_v<__fp_format::__binary128> == 15);
static_assert(asc::std::__fp_exp_nbits_v<__fp_format::__binary16> == 5);
static_assert(asc::std::__fp_exp_nbits_v<__fp_format::__bfloat16> == 8);
static_assert(asc::std::__fp_exp_nbits_v<__fp_format::__fp80_x86> == 15);
static_assert(asc::std::__fp_mant_nbits_v<__fp_format::__binary32> == FLT_MANT_DIG - 1);
static_assert(asc::std::__fp_mant_nbits_v<__fp_format::__binary64> == DBL_MANT_DIG - 1);
static_assert(asc::std::__fp_mant_nbits_v<__fp_format::__binary128> == 112);
static_assert(asc::std::__fp_mant_nbits_v<__fp_format::__binary16> == 10);
static_assert(asc::std::__fp_mant_nbits_v<__fp_format::__bfloat16> == 7);
static_assert(asc::std::__fp_mant_nbits_v<__fp_format::__fp80_x86> == 64);
static_assert(asc::std::__fp_digits_v<__fp_format::__binary32> == FLT_MANT_DIG);
static_assert(asc::std::__fp_digits_v<__fp_format::__binary64> == DBL_MANT_DIG);
static_assert(asc::std::__fp_digits_v<__fp_format::__fp80_x86> == 64);
static_assert(asc::std::__fp_exp_bias_v<__fp_format::__binary32> == FLT_MAX_EXP - 1);
static_assert(asc::std::__fp_exp_bias_v<__fp_format::__binary64> == DBL_MAX_EXP - 1);
static_assert(asc::std::__fp_exp_bias_v<__fp_format::__binary128> == 16383);
static_assert(asc::std::__fp_exp_min_v<__fp_format::__binary32> == FLT_MIN_EXP - 1);
static_assert(asc::std::__fp_exp_min_v<__fp_format::__binary64> == DBL_MIN_EXP - 1);
static_assert(asc::std::__fp_exp_max_v<__fp_format::__binary32> == FLT_MAX_EXP - 1);
static_assert(asc::std::__fp_exp_max_v<__fp_format::__binary64> == DBL_MAX_EXP - 1);
static_assert(asc::std::__fp_is_signed_v<__fp_format::__binary32>);
static_assert(asc::std::__fp_has_implicit_bit_v<__fp_format::__binary32>);
static_assert(!asc::std::__fp_has_implicit_bit_v<__fp_format::__fp80_x86>);
static_assert(asc::std::__fp_has_denorm_v<__fp_format::__binary32>);
static_assert(asc::std::__fp_has_inf_v<__fp_format::__binary32>);
static_assert(asc::std::__fp_has_nan_v<__fp_format::__binary32>);
static_assert(asc::std::__fp_has_nans_v<__fp_format::__binary32>);

// __floating_point/traits.h: floating-point classification and subsets.
static_assert(__is_std_fp_v<float>);
static_assert(__is_std_fp_v<double>);
static_assert(__is_std_fp_v<long double>);
static_assert(__is_std_fp_v<const double>);
static_assert(__is_std_fp_v<volatile float>);
static_assert(!__is_std_fp_v<int>);
static_assert(!__is_std_fp_v<empty>);
static_assert(__is_ext_asc_fp_v<asc::std::__asc_fp<__fp_format::__bfloat16>>);
static_assert(__is_ext_asc_fp_v<const asc::std::__asc_fp<__fp_format::__binary16>>);
static_assert(!__is_ext_asc_fp_v<float>);
static_assert(__is_ext_fp_v<asc::std::__asc_fp<__fp_format::__binary16>>);
static_assert(!__is_ext_fp_v<float>);
static_assert(__is_fp_v<float>);
static_assert(__is_fp_v<asc::std::__asc_fp<__fp_format::__binary16>>);
static_assert(!__is_fp_v<int>);
static_assert(asc::std::__fp_is_subset_v<__fp_format::__binary32, __fp_format::__binary64>);
static_assert(asc::std::__fp_is_subset_v<__fp_format::__binary32, __fp_format::__binary32>);
static_assert(!asc::std::__fp_is_subset_v<__fp_format::__binary64, __fp_format::__binary32>);
static_assert(!asc::std::__fp_is_subset_v<__fp_format::__binary128, __fp_format::__binary64>);
static_assert(asc::std::__fp_is_subset_of_v<float, double>);
static_assert(!asc::std::__fp_is_subset_of_v<double, float>);

// __utility/forward.h: value-category preservation through reference identity.
CANN_ASC_STL_API constexpr int forward_golden(int& value) noexcept  // NOLINT(build/include_what_you_use)
{
    return forward<int&>(value);
}
CANN_ASC_STL_API constexpr int forward_golden(int&& value) noexcept  // NOLINT(build/include_what_you_use)
{
    return forward<int>(value);
}

// __utility/forward_like.h: const and value-category borrowing.
CANN_ASC_STL_API constexpr int forward_like_golden(int& value) noexcept
{
    const int& borrowed = forward_like<const long&>(value);
    return borrowed;
}
CANN_ASC_STL_API constexpr int forward_like_move_golden(int& value) noexcept
{
    int&& borrowed = forward_like<long&&>(value);
    return borrowed;
}

CANN_ASC_STL_API constexpr int evaluate() noexcept
{
    // Runtime independent goldens: address identity and value preservation
    // are language properties, not outputs of the API under test.
    int value = 17;
    int& forwarded_lvalue = forward<int&>(value);  // NOLINT(build/include_what_you_use)
    int&& forwarded_rvalue = forward<int>(value);  // NOLINT(build/include_what_you_use)
    const int& const_borrowed = forward_like<const long&>(value);
    int&& move_borrowed = forward_like<long&&>(value);
    const bool identity_golden = &forwarded_lvalue == &value;
    const bool move_identity_golden = &forwarded_rvalue == &value;
    const bool like_identity_golden = &const_borrowed == &value;
    const bool like_move_identity_golden = &move_borrowed == &value;
    const runtime_payload payload{3, 5};
    const bool transform_golden =
        same_type<make_signed_t<unsigned char>, signed char> && same_type<remove_cvref_t<const int&>, int>;
    const bool property_golden = asc::std::__fp_digits_v<__fp_format::__binary32> == FLT_MANT_DIG &&
        asc::std::__fp_is_subset_of_v<float, double>;
    return identity_golden && move_identity_golden && like_identity_golden && like_move_identity_golden &&
            transform_golden && property_golden && payload.first + payload.second == 8 ?
        0 :
        1;
}

}  // namespace asc_stl_type_transform_test
#endif
