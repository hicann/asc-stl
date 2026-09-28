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

#include <asc/std/cstddef>
#include <asc/std/__utility/to_underlying.h>
#include <asc/std/__utility/priority_tag.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/convert_to_integral.h>
#include <asc/std/__type_traits/underlying_type.h>
#include <asc/std/__type_traits/promote.h>
#include <asc/std/__type_traits/make_nbit_int.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/__type_traits/is_trivially_default_constructible.h>
#include <asc/std/__type_traits/is_signed_integer.h>
#include <asc/std/__type_traits/is_referenceable.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__fwd/span.h>
#include <asc/std/__fwd/array.h>
#include <asc/std/__cstddef/byte.h>
#include <asc/std/__concepts/same_as.h>

namespace {

enum consumer_enum : int { consumer_two = 2 };

}  // namespace

struct consumer_pair_like {
    int first;
    int second;
};

namespace asc {
namespace std {

template <>
struct tuple_size<consumer_pair_like> : integral_constant<size_t, 2> {};

}  // namespace std
}  // namespace asc

int asc_stl_core_consumer_b()
{
    static_assert(asc::std::same_as<double, double>);
    static_assert(!asc::std::same_as<double, float>);
    static_assert(asc::std::to_integer<int>(asc::std::byte{0x0f} & asc::std::byte{0x06}) == (0x0f & 0x06));
    static_assert(asc::std::__is_asc_std_span_v<asc::std::span<int, 2>>);
    static_assert(!asc::std::__is_asc_std_array_v<int>);
    static_assert(asc::std::is_integral_v<char>);
    static_assert(asc::std::is_pointer_v<void*>);
    static_assert(asc::std::is_trivially_default_constructible_v<int>);
    static_assert(asc::std::__is_unsigned_integer_v<unsigned long>);
    static_assert(asc::std::__is_signed_integer_v<short>);
    static_assert(asc::std::is_same_v<asc::std::underlying_type_t<consumer_enum>, int>);
    static_assert(asc::std::to_underlying(consumer_two) == 2);
    static_assert(asc::std::__convert_to_integral(2.5) == 2);
    static_assert(asc::std::__convert_to_integral(9) == 9);
    static_assert(asc::std::is_same_v<asc::std::make_integer_sequence<int, 1>, asc::std::integer_sequence<int, 0>>);
    static_assert(!asc::std::__is_extended_floating_point_v<float>);
    static_assert(asc::std::tuple_size_v<consumer_pair_like> == 2);
    static_assert(asc::std::tuple_size_v<const consumer_pair_like> == 2);
    static_assert(offsetof(consumer_pair_like, second) == sizeof(int));
    return 0;
}
