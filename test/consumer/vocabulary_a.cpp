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
#include <asc/std/cstddef>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/add_rvalue_reference.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_extended_arithmetic.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_primary_template.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/is_unsigned.h>

int asc_stl_vocabulary_consumer_b();

int asc_stl_vocabulary_consumer_a()
{
    static_assert(asc::std::__is_asc_std_tuple<asc::std::tuple<int, float>>);
    static_assert(asc::std::__is_asc_std_optional_v<asc::std::optional<double>>);
    static_assert(asc::std::__is_asc_std_pair<asc::std::pair<int, char>>);
    static_assert(asc::std::__is_asc_std_complex_v<const asc::std::complex<float>>);
    static_assert(asc::std::__is_asc_std_reference_wrapper_v<asc::std::reference_wrapper<int>>);
    static_assert(asc::std::__is_asc_std_char_traits_v<asc::std::char_traits<char>>);
    static_assert(asc::std::is_same_v<asc::std::add_lvalue_reference_t<int>, int&>);
    static_assert(asc::std::is_same_v<asc::std::add_rvalue_reference_t<int>, int&&>);
    static_assert(asc::std::is_same_v<asc::std::__copy_cvref_t<const int&&, long>, const long&&>);
    static_assert(asc::std::is_arithmetic_v<long double>);
    static_assert(asc::std::__is_integer_v<long>);
    static_assert(asc::std::__is_extended_arithmetic_v<float>);
    static_assert(asc::std::is_signed_v<int>);
    static_assert(!asc::std::is_unsigned_v<int>);
    static_assert(asc::std::is_trivially_copy_assignable_v<int>);
    static_assert(asc::std::is_trivially_copy_constructible_v<double>);
    static_assert(asc::std::is_trivially_move_assignable_v<int>);
    static_assert(asc::std::is_trivially_move_constructible_v<float>);
    static_assert(!asc::std::__is_primary_asc_template<int*>::value);
    static_assert(asc::std::__fp_format_of_v<float> == asc::std::__fp_format::__binary32);
    static_assert(asc::std::variant_npos == ~static_cast<asc::std::size_t>(0));
    return asc_stl_vocabulary_consumer_b() == 0 ? 0 : 1;
}
