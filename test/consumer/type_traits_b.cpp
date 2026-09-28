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
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/rank.h>
#include <asc/std/__type_traits/negation.h>
#include <asc/std/__type_traits/is_volatile.h>
#include <asc/std/__type_traits/is_valid_expansion.h>
#include <asc/std/__type_traits/is_union.h>
#include <asc/std/__type_traits/is_unbounded_array.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>
#include <asc/std/__type_traits/is_trivially_constructible.h>
#include <asc/std/__type_traits/is_trivially_assignable.h>
#include <asc/std/__type_traits/is_trivial.h>
#include <asc/std/__type_traits/is_standard_layout.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_final.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/is_core_convertible.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_complete.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_abstract.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/conjunction.h>

int asc_stl_type_traits_consumer_b()
{
    static_assert(asc::std::disjunction_v<asc::std::false_type, asc::std::true_type>);
    static_assert(asc::std::is_reference_v<int&&>);
    static_assert(asc::std::is_unbounded_array_v<int[]>);
    return 0;
}
