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

#include <asc/std/__concepts/same_as.h>
#include <asc/std/__cstddef/byte.h>
#include <asc/std/__fwd/array.h>
#include <asc/std/__fwd/span.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_referenceable.h>
#include <asc/std/__type_traits/is_signed_integer.h>
#include <asc/std/__type_traits/is_trivially_default_constructible.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/__type_traits/make_nbit_int.h>
#include <asc/std/__type_traits/promote.h>
#include <asc/std/__type_traits/underlying_type.h>
#include <asc/std/__utility/convert_to_integral.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/priority_tag.h>
#include <asc/std/__utility/to_underlying.h>
#include <asc/std/cstddef>

int asc_stl_core_consumer_a()
{
    static_assert(asc::std::same_as<int, int>);
    static_assert(asc::std::to_integer<int>(asc::std::byte{0x21} | asc::std::byte{0x82}) == (0x21 | 0x82));
    static_assert(asc::std::dynamic_extent == static_cast<asc::std::size_t>(-1));
    static_assert(asc::std::is_integral_v<long long>);
    static_assert(!asc::std::is_integral_v<double>);
    static_assert(asc::std::is_floating_point_v<const float>);
    static_assert(asc::std::is_function_v<void()>);
    static_assert(asc::std::is_pointer_v<int*>);
    static_assert(asc::std::__is_referenceable<int>::value);
    static_assert(!asc::std::__is_referenceable<void>::value);
    static_assert(sizeof(asc::std::__make_nbit_int_t<32>) == 4);
    static_assert(asc::std::is_same_v<asc::std::__promote_t<int, float>, double>);
    static_assert(asc::std::is_same_v<asc::std::make_index_sequence<2>, asc::std::index_sequence<0, 1>>);
    static_assert(asc::std::is_same_v<asc::std::__make_tuple_indices_t<2>, asc::std::__tuple_indices<0, 1>>);
    static_assert(asc::std::tuple_size_v<asc::std::make_index_sequence<3>> == 3);
    static_assert(asc::std::is_same_v<asc::std::nullptr_t, decltype(nullptr)>);
    static_assert(asc::std::is_same_v<asc::std::size_t, ::size_t>);
    return asc::std::to_integer<int>(~asc::std::byte{0x00}) == 255 ? 0 : 1;
}
