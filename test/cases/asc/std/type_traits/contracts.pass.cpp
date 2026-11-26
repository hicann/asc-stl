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

#include <asc/std/type_traits>
#include <type_traits>
#include "compiler_traits.h"

struct aggregate {
    int value;
};
struct abstract {
    virtual void invoke() = 0;
    virtual ~abstract() = default;
};
struct move_only {
    move_only() = default;
    move_only(move_only&&) = default;
};
enum class kind : unsigned char { one };
union choice {
    int a;
    char b;
};

template <class T>
constexpr bool properties()
{
    static_assert(asc::std::is_arithmetic<T>::value == std::is_arithmetic_v<T> &&
        asc::std::is_arithmetic_v<T> == std::is_arithmetic_v<T>);
    static_assert(asc::std::is_array<T>::value == std::is_array_v<T> && asc::std::is_array_v<T> == std::is_array_v<T>);
    static_assert(asc::std::is_class<T>::value == std::is_class_v<T> && asc::std::is_class_v<T> == std::is_class_v<T>);
    static_assert(asc::std::is_compound<T>::value == std::is_compound_v<T> &&
        asc::std::is_compound_v<T> == std::is_compound_v<T>);
    static_assert(asc::std::is_const<T>::value == std::is_const_v<T> && asc::std::is_const_v<T> == std::is_const_v<T>);
    static_assert(asc::std::is_enum<T>::value == std::is_enum_v<T> && asc::std::is_enum_v<T> == std::is_enum_v<T>);
    static_assert(asc::std::is_floating_point<T>::value == std::is_floating_point_v<T> &&
        asc::std::is_floating_point_v<T> == std::is_floating_point_v<T>);
    static_assert(asc::std::is_function<T>::value == std::is_function_v<T> &&
        asc::std::is_function_v<T> == std::is_function_v<T>);
    static_assert(asc::std::is_fundamental<T>::value == std::is_fundamental_v<T> &&
        asc::std::is_fundamental_v<T> == std::is_fundamental_v<T>);
    static_assert(asc::std::is_integral<T>::value == std::is_integral_v<T> &&
        asc::std::is_integral_v<T> == std::is_integral_v<T>);
    static_assert(asc::std::is_lvalue_reference<T>::value == std::is_lvalue_reference_v<T> &&
        asc::std::is_lvalue_reference_v<T> == std::is_lvalue_reference_v<T>);
    static_assert(asc::std::is_member_function_pointer<T>::value == std::is_member_function_pointer_v<T> &&
        asc::std::is_member_function_pointer_v<T> == std::is_member_function_pointer_v<T>);
    static_assert(asc::std::is_member_object_pointer<T>::value == std::is_member_object_pointer_v<T> &&
        asc::std::is_member_object_pointer_v<T> == std::is_member_object_pointer_v<T>);
    static_assert(asc::std::is_member_pointer<T>::value == std::is_member_pointer_v<T> &&
        asc::std::is_member_pointer_v<T> == std::is_member_pointer_v<T>);
    static_assert(asc::std::is_null_pointer<T>::value == std::is_null_pointer_v<T> &&
        asc::std::is_null_pointer_v<T> == std::is_null_pointer_v<T>);
    static_assert(
        asc::std::is_object<T>::value == std::is_object_v<T> && asc::std::is_object_v<T> == std::is_object_v<T>);
    static_assert(
        asc::std::is_pointer<T>::value == std::is_pointer_v<T> && asc::std::is_pointer_v<T> == std::is_pointer_v<T>);
    static_assert(asc::std::is_reference<T>::value == std::is_reference_v<T> &&
        asc::std::is_reference_v<T> == std::is_reference_v<T>);
    static_assert(asc::std::is_rvalue_reference<T>::value == std::is_rvalue_reference_v<T> &&
        asc::std::is_rvalue_reference_v<T> == std::is_rvalue_reference_v<T>);
    static_assert(
        asc::std::is_scalar<T>::value == std::is_scalar_v<T> && asc::std::is_scalar_v<T> == std::is_scalar_v<T>);
    static_assert(
        asc::std::is_signed<T>::value == std::is_signed_v<T> && asc::std::is_signed_v<T> == std::is_signed_v<T>);
    static_assert(asc::std::is_union<T>::value == std::is_union_v<T> && asc::std::is_union_v<T> == std::is_union_v<T>);
    static_assert(asc::std::is_unsigned<T>::value == std::is_unsigned_v<T> &&
        asc::std::is_unsigned_v<T> == std::is_unsigned_v<T>);
    static_assert(asc::std::is_void<T>::value == std::is_void_v<T> && asc::std::is_void_v<T> == std::is_void_v<T>);
    static_assert(asc::std::is_volatile<T>::value == std::is_volatile_v<T> &&
        asc::std::is_volatile_v<T> == std::is_volatile_v<T>);
    static_assert(asc::std::is_abstract<T>::value == std::is_abstract_v<T> &&
        asc::std::is_abstract_v<T> == std::is_abstract_v<T>);
    static_assert(asc::std::is_aggregate<T>::value == std::is_aggregate_v<T> &&
        asc::std::is_aggregate_v<T> == std::is_aggregate_v<T>);
    static_assert(asc::std::is_copy_assignable<T>::value == std::is_copy_assignable_v<T> &&
        asc::std::is_copy_assignable_v<T> == std::is_copy_assignable_v<T>);
    static_assert(asc::std::is_copy_constructible<T>::value == std::is_copy_constructible_v<T> &&
        asc::std::is_copy_constructible_v<T> == std::is_copy_constructible_v<T>);
    static_assert(asc::std::is_default_constructible<T>::value == std::is_default_constructible_v<T> &&
        asc::std::is_default_constructible_v<T> == std::is_default_constructible_v<T>);
    static_assert(asc::std::is_destructible<T>::value == std::is_destructible_v<T> &&
        asc::std::is_destructible_v<T> == std::is_destructible_v<T>);
    static_assert(asc::std::is_empty<T>::value == std::is_empty_v<T> && asc::std::is_empty_v<T> == std::is_empty_v<T>);
    static_assert(asc::std::is_final<T>::value == std::is_final_v<T> && asc::std::is_final_v<T> == std::is_final_v<T>);
    static_assert(asc::std::is_move_assignable<T>::value == std::is_move_assignable_v<T> &&
        asc::std::is_move_assignable_v<T> == std::is_move_assignable_v<T>);
    static_assert(asc::std::is_move_constructible<T>::value == std::is_move_constructible_v<T> &&
        asc::std::is_move_constructible_v<T> == std::is_move_constructible_v<T>);
    static_assert(asc::std::is_nothrow_copy_assignable<T>::value == std::is_nothrow_copy_assignable_v<T> &&
        asc::std::is_nothrow_copy_assignable_v<T> == std::is_nothrow_copy_assignable_v<T>);
    static_assert(asc::std::is_nothrow_copy_constructible<T>::value == std::is_nothrow_copy_constructible_v<T> &&
        asc::std::is_nothrow_copy_constructible_v<T> == std::is_nothrow_copy_constructible_v<T>);
    static_assert(asc::std::is_nothrow_default_constructible<T>::value == std::is_nothrow_default_constructible_v<T> &&
        asc::std::is_nothrow_default_constructible_v<T> == std::is_nothrow_default_constructible_v<T>);
    static_assert(asc::std::is_nothrow_destructible<T>::value == std::is_nothrow_destructible_v<T> &&
        asc::std::is_nothrow_destructible_v<T> == std::is_nothrow_destructible_v<T>);
    static_assert(asc::std::is_nothrow_move_assignable<T>::value == std::is_nothrow_move_assignable_v<T> &&
        asc::std::is_nothrow_move_assignable_v<T> == std::is_nothrow_move_assignable_v<T>);
    static_assert(asc::std::is_nothrow_move_constructible<T>::value == std::is_nothrow_move_constructible_v<T> &&
        asc::std::is_nothrow_move_constructible_v<T> == std::is_nothrow_move_constructible_v<T>);
    static_assert(asc::std::is_polymorphic<T>::value == std::is_polymorphic_v<T> &&
        asc::std::is_polymorphic_v<T> == std::is_polymorphic_v<T>);
    static_assert(asc::std::is_standard_layout<T>::value == std::is_standard_layout_v<T> &&
        asc::std::is_standard_layout_v<T> == std::is_standard_layout_v<T>);
    static_assert(asc::std::is_swappable<T>::value == std::is_swappable_v<T> &&
        asc::std::is_swappable_v<T> == std::is_swappable_v<T>);
    static_assert(asc::std::is_nothrow_swappable<T>::value == std::is_nothrow_swappable_v<T> &&
        asc::std::is_nothrow_swappable_v<T> == std::is_nothrow_swappable_v<T>);
    static_assert(
        asc::std::is_trivial<T>::value == std::is_trivial_v<T> && asc::std::is_trivial_v<T> == std::is_trivial_v<T>);
    static_assert(asc::std::is_trivially_copy_assignable<T>::value == std::is_trivially_copy_assignable_v<T> &&
        asc::std::is_trivially_copy_assignable_v<T> == std::is_trivially_copy_assignable_v<T>);
    static_assert(asc::std::is_trivially_copy_constructible<T>::value == std::is_trivially_copy_constructible_v<T> &&
        asc::std::is_trivially_copy_constructible_v<T> == std::is_trivially_copy_constructible_v<T>);
    static_assert(asc::std::is_trivially_copyable<T>::value == std::is_trivially_copyable_v<T> &&
        asc::std::is_trivially_copyable_v<T> == std::is_trivially_copyable_v<T>);
    static_assert(
        asc::std::is_trivially_default_constructible<T>::value == std::is_trivially_default_constructible_v<T> &&
        asc::std::is_trivially_default_constructible_v<T> == std::is_trivially_default_constructible_v<T>);
    static_assert(asc::std::is_trivially_destructible<T>::value == std::is_trivially_destructible_v<T> &&
        asc::std::is_trivially_destructible_v<T> == std::is_trivially_destructible_v<T>);
    static_assert(asc::std::is_trivially_move_assignable<T>::value == std::is_trivially_move_assignable_v<T> &&
        asc::std::is_trivially_move_assignable_v<T> == std::is_trivially_move_assignable_v<T>);
    static_assert(asc::std::is_trivially_move_constructible<T>::value == std::is_trivially_move_constructible_v<T> &&
        asc::std::is_trivially_move_constructible_v<T> == std::is_trivially_move_constructible_v<T>);
    static_assert(asc::std::has_virtual_destructor<T>::value == std::has_virtual_destructor_v<T> &&
        asc::std::has_virtual_destructor_v<T> == std::has_virtual_destructor_v<T>);
    static_assert(
        asc::std::has_unique_object_representations<T>::value == std::has_unique_object_representations_v<T> &&
        asc::std::has_unique_object_representations_v<T> == std::has_unique_object_representations_v<T>);
    static_assert(asc::std::rank<T>::value == std::rank_v<T> && asc::std::rank_v<T> == std::rank_v<T>);
    static_assert(asc::std::extent<T>::value == std::extent_v<T> && asc::std::extent_v<T> == std::extent_v<T>);
    static_assert(std::is_same_v<typename asc::std::add_const<T>::type, std::add_const_t<T>>);
    static_assert(std::is_same_v<asc::std::add_const_t<T>, std::add_const_t<T>>);
    static_assert(std::is_same_v<typename asc::std::add_cv<T>::type, std::add_cv_t<T>>);
    static_assert(std::is_same_v<asc::std::add_cv_t<T>, std::add_cv_t<T>>);
    static_assert(std::is_same_v<typename asc::std::add_lvalue_reference<T>::type, std::add_lvalue_reference_t<T>>);
    static_assert(std::is_same_v<asc::std::add_lvalue_reference_t<T>, std::add_lvalue_reference_t<T>>);
    static_assert(std::is_same_v<typename asc::std::add_pointer<T>::type, std::add_pointer_t<T>>);
    static_assert(std::is_same_v<asc::std::add_pointer_t<T>, std::add_pointer_t<T>>);
    static_assert(std::is_same_v<typename asc::std::add_rvalue_reference<T>::type, std::add_rvalue_reference_t<T>>);
    static_assert(std::is_same_v<asc::std::add_rvalue_reference_t<T>, std::add_rvalue_reference_t<T>>);
    static_assert(std::is_same_v<typename asc::std::add_volatile<T>::type, std::add_volatile_t<T>>);
    static_assert(std::is_same_v<asc::std::add_volatile_t<T>, std::add_volatile_t<T>>);
    static_assert(std::is_same_v<typename asc::std::decay<T>::type, std::decay_t<T>>);
    static_assert(std::is_same_v<asc::std::decay_t<T>, std::decay_t<T>>);
    static_assert(std::is_same_v<typename asc::std::remove_all_extents<T>::type, std::remove_all_extents_t<T>>);
    static_assert(std::is_same_v<asc::std::remove_all_extents_t<T>, std::remove_all_extents_t<T>>);
    static_assert(std::is_same_v<typename asc::std::remove_const<T>::type, std::remove_const_t<T>>);
    static_assert(std::is_same_v<asc::std::remove_const_t<T>, std::remove_const_t<T>>);
    static_assert(std::is_same_v<typename asc::std::remove_cv<T>::type, std::remove_cv_t<T>>);
    static_assert(std::is_same_v<asc::std::remove_cv_t<T>, std::remove_cv_t<T>>);
    static_assert(std::is_same_v<typename asc::std::remove_extent<T>::type, std::remove_extent_t<T>>);
    static_assert(std::is_same_v<asc::std::remove_extent_t<T>, std::remove_extent_t<T>>);
    static_assert(std::is_same_v<typename asc::std::remove_pointer<T>::type, std::remove_pointer_t<T>>);
    static_assert(std::is_same_v<asc::std::remove_pointer_t<T>, std::remove_pointer_t<T>>);
    static_assert(std::is_same_v<typename asc::std::remove_reference<T>::type, std::remove_reference_t<T>>);
    static_assert(std::is_same_v<asc::std::remove_reference_t<T>, std::remove_reference_t<T>>);
    static_assert(std::is_same_v<typename asc::std::remove_volatile<T>::type, std::remove_volatile_t<T>>);
    static_assert(std::is_same_v<asc::std::remove_volatile_t<T>, std::remove_volatile_t<T>>);
    return true;
}

static_assert(properties<void>());
static_assert(properties<int>());
static_assert(properties<const volatile int>());
static_assert(properties<unsigned char>());
static_assert(properties<double>());
static_assert(properties<const int*>());
static_assert(properties<int&>());
static_assert(properties<int&&>());
static_assert(properties<int[2][3]>());
static_assert(properties<int(double)>());
static_assert(properties<int aggregate::*>());
static_assert(properties<abstract>());
static_assert(properties<aggregate>());
static_assert(properties<kind>());
static_assert(properties<move_only>());
static_assert(properties<choice>());
static_assert(properties<decltype(nullptr)>());

int main()
{
    return 0;
}
