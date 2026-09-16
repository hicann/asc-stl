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

#ifndef ASC_STL_TEST_B013_SEMANTICS_H
#define ASC_STL_TEST_B013_SEMANTICS_H

#include <asc/__runtime/stream.h>
#include <asc/std/__algorithm/count.h>
#include <asc/std/__algorithm/fill_n.h>
#include <asc/std/__algorithm/find_end.h>
#include <asc/std/__algorithm/lexicographical_compare.h>
#include <asc/std/__algorithm/max_element.h>
#include <asc/std/__algorithm/min_element.h>
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__cstdlib/abs.h>
#include <asc/std/__cstdlib/div.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/reference_wrapper.h>
#include <asc/std/__functional/weak_result_type.h>
#include <asc/std/__string/constexpr_c_functions.h>
#include <asc/std/__tuple/tuple_leaf.h>
#include <asc/std/__variant/sfinae_helpers.h>
#include <asc/std/__variant/variant_access.h>
#include <asc/std/__variant/variant_base.h>
#include <asc/std/__variant/variant_match.h>
#include <asc/std/__variant/variant_traits.h>
#include <asc/std/__variant/variant_visit.h>
#include <asc/std/cstring>

namespace asc_stl_b013_test {

CANN_ASC_STL_API constexpr int add_one(int value) noexcept
{
    return value + 1;
}

CANN_ASC_STL_API int evaluate_algorithms() noexcept
{
    int values[5] = {1, 2, 1, 2, 3};
    int pattern[2] = {1, 2};
    int filled[3] = {};
    int failures = 0;
    failures += asc::std::count(values, values + 5, 2) != 2;
    failures += asc::std::fill_n(filled, 3, 7) != filled + 3;
    failures += filled[0] != 7 || filled[2] != 7;
    failures += asc::std::find_end(values, values + 5, pattern, pattern + 2) != values + 2;
    failures += !asc::std::lexicographical_compare(pattern, pattern + 2, values + 3, values + 5);
    failures += *asc::std::max_element(values, values + 5) != 3;
    failures += *asc::std::min_element(values, values + 5) != 1;  // NOLINT(build/include_what_you_use)
    failures += asc::std::__unwrap_iter(values + 1) != values + 1;
    failures += asc::std::__rewrap_iter(values, values + 2) != values + 2;
    return failures;
}

CANN_ASC_STL_API int evaluate_cstdlib() noexcept
{
    int failures = 0;
    failures += asc::std::abs(-7) != 7 || asc::std::labs(-9L) != 9L || asc::std::llabs(-11LL) != 11LL;
    const auto quotient = asc::std::div(17, 5);
    failures += quotient.quot != 3 || quotient.rem != 2;
    failures += asc::std::ldiv(19L, 4L).rem != 3L || asc::std::lldiv(23LL, 5LL).quot != 4LL;
    return failures;
}

CANN_ASC_STL_API int evaluate_functional() noexcept
{
    int failures = 0;
    int wrapped = 13;
    failures += &asc::std::identity{}(wrapped) != &wrapped;
    const auto reference = asc::std::ref(wrapped);
    failures += &reference.get() != &wrapped;
    const auto function = asc::std::ref(add_one);
    failures += function(4) != 5;
    return failures;
}

CANN_ASC_STL_API int evaluate_cstring() noexcept
{
    int failures = 0;
    char abc[4] = {'a', 'b', 'c', '\0'};
    char de[3] = {'d', 'e', '\0'};
    char abcde[6] = {'a', 'b', 'c', 'd', 'e', '\0'};
    char abcxx[6] = {'a', 'b', 'c', 'x', 'x', '\0'};
    char accepted[4] = {'a', 'b', 'c', '\0'};
    char rejected[2] = {'d', '\0'};
    char xe[3] = {'x', 'e', '\0'};
    char cd[3] = {'c', 'd', '\0'};
    char text[16] = {};
    asc::std::strcpy(text, abc);  // NOLINT(runtime/printf)
    asc::std::strcat(text, de);   // NOLINT(runtime/printf)
    failures += asc::std::strlen(text) != 5;
    failures += asc::std::strcmp(text, abcde) != 0 || asc::std::strncmp(text, abcxx, 3) != 0;
    failures += asc::std::strchr(text, 'c') != text + 2 || asc::std::strrchr(text, 'e') != text + 4;
    failures += asc::std::strspn(text, accepted) != 3 || asc::std::strcspn(text, rejected) != 3;
    failures += asc::std::strpbrk(text, xe) != text + 4 || asc::std::strstr(text, cd) != text + 2;
    char moved[6] = {1, 2, 3, 4, 5, 0};
    asc::std::memmove(moved + 1, moved, 4);
    failures += moved[1] != 1 || moved[4] != 4;
    failures += asc::std::memchr(moved, 3, 6) != moved + 3;
    failures += asc::std::memcmp(moved, moved, 6) != 0;
    return failures;
}

CANN_ASC_STL_API int evaluate_tuple_variant() noexcept
{
    int failures = 0;
    asc::std::__tuple_leaf<0, int> left(5);
    asc::std::__tuple_leaf<0, int> right(8);
    left.swap(right);
    failures += left.get() != 8 || right.get() != 5;
    failures += asc::std::variant_size_v<asc::std::variant<int, long>> != 2;
    failures += !__is_same(asc::std::variant_alternative_t<1, asc::std::variant<int, long>>, long);
    failures += asc::std::__variant_find_exact<long, int, long>::value != 1;
    using storage_type = asc::std::__variant_storage<0, int, long>;
    failures += sizeof(storage_type) == 0;
    asc::stream_ref stream{};
    (void)stream;
    return failures;
}

CANN_ASC_STL_API int evaluate_common() noexcept
{
    return evaluate_algorithms() + evaluate_cstdlib() + evaluate_functional() + evaluate_cstring() +
        evaluate_tuple_variant();
}

}  // namespace asc_stl_b013_test

#endif  // ASC_STL_TEST_B013_SEMANTICS_H
