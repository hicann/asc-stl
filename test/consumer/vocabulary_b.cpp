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

#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/is_primary_template.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_extended_arithmetic.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/add_rvalue_reference.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__fwd/reference_wrapper.h>
#include <asc/std/__fwd/pair.h>
#include <asc/std/__fwd/optional.h>
#include <asc/std/__fwd/iterator.h>
#include <asc/std/__fwd/hash.h>
#include <asc/std/__fwd/fp.h>
#include <asc/std/__fwd/complex.h>
#include <asc/std/__fwd/char_traits.h>
#include <asc/std/__floating_point/format.h>

namespace {

struct consumer_nontrivial_assign {
    int value;
    consumer_nontrivial_assign& operator=(const consumer_nontrivial_assign& other)
    {
        value = other.value + 1;
        return *this;
    }
};

}  // namespace

int asc_stl_vocabulary_consumer_b()
{
    static_assert(!asc::std::__is_asc_std_tuple<long>);
    static_assert(!asc::std::__is_asc_std_optional_v<long>);
    static_assert(!asc::std::__is_asc_std_pair<long>);
    static_assert(!asc::std::__is_asc_std_complex_v<long>);
    static_assert(!asc::std::__is_asc_std_reference_wrapper_v<long>);
    static_assert(!asc::std::__is_asc_std_char_traits_v<long>);
    static_assert(asc::std::is_same_v<asc::std::add_lvalue_reference_t<void>, void>);
    static_assert(asc::std::is_same_v<asc::std::add_rvalue_reference_t<void>, void>);
    static_assert(asc::std::is_same_v<asc::std::__copy_cvref_t<volatile int&, long>, volatile long&>);
    static_assert(!asc::std::is_arithmetic_v<void*>);
    static_assert(!asc::std::__is_integer_v<bool>);
    static_assert(!asc::std::__is_extended_arithmetic_v<void>);
    static_assert(!asc::std::is_signed_v<unsigned int>);
    static_assert(asc::std::is_unsigned_v<unsigned int>);
    static_assert(!asc::std::is_trivially_copy_assignable_v<consumer_nontrivial_assign>);
    static_assert(asc::std::__fp_format_of_v<double> == asc::std::__fp_format::__binary64);
    static_assert(asc::std::__fp_format_of_v<int> == asc::std::__fp_format::__invalid);
    return (asc::std::is_trivially_move_constructible_v<int> && asc::std::is_trivially_copy_constructible_v<char>) ? 0 :
                                                                                                                     1;
}
