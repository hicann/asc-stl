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
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_nothrow_destructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_convertible.h>
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/is_implicitly_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__floating_point/storage.h>
#include <asc/std/numbers>

#include "core_consumers.h"

namespace {
struct consumer_type {
    int value;
};
}  // namespace

int asc_stl_constructibility_consumer_a()
{
    static_assert(asc::std::is_same_v<asc::std::add_pointer_t<consumer_type>, consumer_type*>);
    static_assert(asc::std::is_same_v<asc::std::decay_t<consumer_type&>, consumer_type>);
    static_assert(asc::std::is_same_v<asc::std::common_type_t<int, double>, double>);
    static_assert(asc::std::is_constructible_v<consumer_type, int>);
    static_assert(asc::std::is_copy_constructible_v<consumer_type>);
    static_assert(asc::std::is_move_assignable_v<consumer_type>);
    static_assert(asc::std::is_nothrow_default_constructible_v<int>);
    static_assert(asc::std::is_nothrow_convertible_v<int, float>);
    static_assert(asc::std::is_object_v<consumer_type>);
    static_assert(asc::std::is_nothrow_destructible_v<consumer_type>);
    static_assert(asc::std::bit_cast<asc::std::uint32_t>(1.0f) == 0x3F800000u);
    static_assert(asc::std::__fp_get_storage(1.0f) == 0x3F800000u);
    static_assert(asc::std::pi_v<float> == 3.14159265358979323846f);
    static_assert(asc::std::numbers::ln2 == 0.693147180559945309417232121458176568);
    static_assert(asc::std::__is_implicitly_default_constructible<consumer_type>::value);
    consumer_type instance{5};
    return asc::std::is_assignable_v<consumer_type&, consumer_type&&> && instance.value == 5 ? 0 : 1;
}
