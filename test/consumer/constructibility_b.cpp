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
#include <asc/std/numbers>
#include <asc/std/__floating_point/storage.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_implicitly_default_constructible.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__type_traits/is_nothrow_convertible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_nothrow_destructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/add_pointer.h>

#include "core_consumers.h"

namespace {
struct consumer_type_b {
    int value;
};
}  // namespace

int asc_stl_constructibility_consumer_b()
{
    static_assert(asc::std::is_same_v<asc::std::add_pointer_t<const consumer_type_b>, const consumer_type_b*>);
    static_assert(asc::std::is_same_v<asc::std::decay_t<consumer_type_b[2]>, consumer_type_b*>);
    static_assert(asc::std::is_same_v<asc::std::common_type_t<consumer_type_b, consumer_type_b>, consumer_type_b>);
    static_assert(asc::std::is_convertible_v<const consumer_type_b*, const consumer_type_b*>);
    static_assert(!asc::std::is_copy_assignable_v<const consumer_type_b>);
    static_assert(asc::std::is_nothrow_copy_constructible_v<int>);
    static_assert(asc::std::is_nothrow_move_constructible_v<consumer_type_b>);
    static_assert(asc::std::is_nothrow_move_assignable_v<int&>);
    static_assert(asc::std::bit_cast<float>(0x40490FDBu) == 3.14159274f);
    static_assert(asc::std::__fp_from_storage<float>(0x40490FDBu) == 3.14159274f);
    static_assert(asc::std::numbers::sqrt2 == 1.414213562373095048801688724209698079);
    static_assert(asc::std::inv_sqrt3_v<float> == 0.577350269189625764509148780501957456f);
    consumer_type_b instance{9};
    return asc::std::is_default_constructible_v<consumer_type_b> && instance.value == 9 ? 0 : 1;
}
