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
#ifndef ASC_STL_TEST_SUPPORT_TYPE_TRAITS_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_TYPE_TRAITS_SEMANTICS_H
#include <asc/std/__type_traits/conjunction.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/is_abstract.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_complete.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_core_convertible.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_final.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_standard_layout.h>
#include <asc/std/__type_traits/is_trivial.h>
#include <asc/std/__type_traits/is_trivially_assignable.h>
#include <asc/std/__type_traits/is_trivially_constructible.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>
#include <asc/std/__type_traits/is_unbounded_array.h>
#include <asc/std/__type_traits/is_union.h>
#include <asc/std/__type_traits/is_valid_expansion.h>
#include <asc/std/__type_traits/is_volatile.h>
#include <asc/std/__type_traits/negation.h>
#include <asc/std/__type_traits/rank.h>
#include <asc/std/__type_traits/remove_cv.h>

namespace asc_stl_type_traits_test {
struct incomplete;
struct empty {};
struct nonempty {
    int value;
};
struct base {};
struct derived : base {};
struct abstract {
    CANN_ASC_STL_API virtual void call() = 0;
};
struct final_type final {};
struct nontrivial {
    CANN_ASC_STL_API nontrivial()
    {}
    CANN_ASC_STL_API nontrivial(const nontrivial& other) : value(other.value)
    {}
    int value;
};
enum class enumeration { value };
union union_type {
    int integer;
    float real;
};
template <class T>
using member_type = typename T::type;
template <class>
struct undefined_predicate;

static_assert(asc::std::conjunction_v<>);
static_assert(asc::std::conjunction_v<asc::std::true_type, asc::std::true_type>);
static_assert(!asc::std::conjunction_v<asc::std::false_type, undefined_predicate<int>>);
static_assert(!asc::std::disjunction_v<>);
static_assert(asc::std::disjunction_v<asc::std::false_type, asc::std::true_type>);
static_assert(asc::std::disjunction_v<asc::std::true_type, undefined_predicate<int>>);
static_assert(asc::std::__fold_and_v<>);
static_assert(!asc::std::__fold_and_v<true, false>);
static_assert(!asc::std::__fold_or_v<>);
static_assert(asc::std::__fold_or_v<false, true>);
static_assert(asc::std::__fold_and<true, true>::value);
static_assert(asc::std::__fold_or<false, true>::value);

static_assert(asc::std::is_abstract_v<abstract>);
static_assert(!asc::std::is_abstract_v<base>);
static_assert(asc::std::is_base_of_v<base, derived>);
static_assert(!asc::std::is_base_of_v<derived, base>);
static_assert(asc::std::is_class_v<base>);
static_assert(!asc::std::is_class_v<int>);
static_assert(!asc::std::__is_complete_v<incomplete>);
static_assert(asc::std::__is_complete_v<nonempty>);
static_assert(asc::std::is_const_v<const int>);
static_assert(!asc::std::is_const_v<const int&>);
static_assert(asc::std::__is_core_convertible<int, long>::value);
static_assert(!asc::std::__is_core_convertible<void, void>::value);
static_assert(asc::std::is_empty_v<empty>);
static_assert(!asc::std::is_empty_v<nonempty>);
static_assert(asc::std::is_enum_v<enumeration>);
static_assert(!asc::std::is_enum_v<int>);
static_assert(asc::std::is_final_v<final_type>);
static_assert(!asc::std::is_final_v<base>);
static_assert(asc::std::is_lvalue_reference_v<int&>);
static_assert(asc::std::is_rvalue_reference_v<int&&>);
static_assert(asc::std::is_reference_v<const int&>);
static_assert(!asc::std::is_reference_v<int>);
static_assert(asc::std::is_same_v<int, int>);
static_assert(!asc::std::is_same_v<int, const int>);
static_assert(asc::std::is_standard_layout_v<nonempty>);
static_assert(asc::std::is_trivial_v<nonempty>);
static_assert(!asc::std::is_trivial_v<nontrivial>);
static_assert(asc::std::is_trivially_assignable_v<int&, int>);
static_assert(!asc::std::is_trivially_assignable_v<const int&, int>);
static_assert(asc::std::is_trivially_constructible_v<int, int>);
static_assert(!asc::std::is_trivially_constructible_v<int&, int>);
static_assert(asc::std::is_trivially_copyable_v<nonempty>);
static_assert(!asc::std::is_trivially_copyable_v<nontrivial>);
static_assert(asc::std::is_unbounded_array_v<int[]>);
static_assert(!asc::std::is_unbounded_array_v<int[3]>);
static_assert(asc::std::is_union_v<union_type>);
static_assert(!asc::std::is_union_v<nonempty>);
static_assert(asc::std::_IsValidExpansion<member_type, asc::std::true_type>::value);
static_assert(!asc::std::_IsValidExpansion<member_type, int>::value);
static_assert(asc::std::is_volatile_v<volatile int>);
static_assert(!asc::std::is_volatile_v<volatile int&>);
static_assert(asc::std::negation_v<asc::std::false_type>);
static_assert(!asc::std::negation_v<asc::std::true_type>);
static_assert(asc::std::rank_v<int> == 0);
static_assert(asc::std::rank_v<int[][2][3]> == 3);
static_assert(asc::std::is_same_v<asc::std::remove_cv_t<const volatile int>, int>);
static_assert(asc::std::is_same_v<asc::std::remove_cv_t<const int* volatile>, const int*>);

CANN_ASC_STL_API constexpr int evaluate() noexcept
{
    return asc::std::conjunction_v<asc::std::true_type> && asc::std::rank_v<int[2][3]> == 2 ? 0 : 1;
}
}  // namespace asc_stl_type_traits_test
#endif
