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
#include <asc/std/cstddef>

int asc_stl_type_transform_consumer_b();

namespace {
struct member_host {};
}  // namespace

int asc_stl_type_transform_consumer_a()
{
    static_assert(asc::std::is_same_v<asc::std::remove_reference_t<const int&&>, const int>);
    static_assert(asc::std::is_same_v<asc::std::remove_extent_t<int[3][5]>, int[5]>);
    static_assert(asc::std::is_same_v<asc::std::remove_all_extents_t<int[3][5]>, int>);
    static_assert(asc::std::is_same_v<asc::std::remove_cvref_t<const int&>, int>);
    static_assert(asc::std::is_same_v<asc::std::__copy_cv_t<const int, long>, const long>);
    static_assert(asc::std::is_same_v<asc::std::__make_const_lvalue_ref<int&&>, const int&>);
    static_assert(asc::std::extent_v<int[3][5], 1> == 5);
    static_assert(asc::std::is_array_v<int[3]>);
    static_assert(!asc::std::is_array_v<int*>);
    static_assert(asc::std::is_void_v<const void>);
    static_assert(!asc::std::is_void_v<void*>);
    static_assert(asc::std::is_null_pointer_v<asc::std::nullptr_t>);
    static_assert(asc::std::is_member_function_pointer_v<int (member_host::*)(double)>);
    static_assert(!asc::std::is_member_object_pointer_v<int (member_host::*)(double)>);
    static_assert(asc::std::is_member_pointer_v<int member_host::*>);
    static_assert(asc::std::is_scalar_v<int>);
    static_assert(!asc::std::is_scalar_v<int[3]>);
    static_assert(asc::std::is_destructible_v<int[3]>);
    static_assert(!asc::std::is_destructible_v<void()>);
    static_assert(asc::std::is_trivially_destructible_v<int>);
    static_assert(asc::std::is_same_v<asc::std::make_signed_t<unsigned long>, long>);
    static_assert(asc::std::is_same_v<asc::std::make_unsigned_t<long long>, unsigned long long>);
    static_assert(asc::std::__type_list<int, long>::__size == 2);
    static_assert(asc::std::__is_included_in_v<long, int, long>);
    static_assert(asc::std::__fp_exp_nbits_v<asc::std::__fp_format::__binary64> == 11);
    static_assert(asc::std::__fp_is_subset_of_v<float, double>);
    int value = 5;
    int& kept = asc::std::forward<int&>(value);  // NOLINT(build/include_what_you_use)
    const int& borrowed = asc::std::forward_like<const long&>(value);
    return (&kept == &value && &borrowed == &value) ? asc_stl_type_transform_consumer_b() : 1;
}
