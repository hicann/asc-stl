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

#ifndef ASC_STL_TEST_STRING_CHARACTER_TRAITS_H
#define ASC_STL_TEST_STRING_CHARACTER_TRAITS_H

#include <asc/std/string>

namespace asc_stl_test_string {
template <class Char>
CANN_ASC_STL_API bool check_code_units(int seed)
{
    using tr = asc::std::char_traits<Char>;
    const Char n = static_cast<Char>(seed);
    const Char raw[] = {n, Char(4), n, Char(0)};
    Char copy[6]{};
    if (tr::copy(copy, raw, 4) != copy || tr::length(copy) != 3 || tr::find(copy, 3, Char(4)) != copy + 1 ||
        tr::find(copy, 3, Char(8)) != nullptr || tr::compare(raw, copy, 4) != 0)
        return false;
    if (tr::move(copy + 1, copy, 3) != copy + 1 || copy[1] != n || copy[2] != Char(4) ||
        tr::move(copy, copy + 1, 3) != copy || copy[0] != n || copy[1] != Char(4))
        return false;
    tr::assign(copy[0], Char(1));
    if (!tr::lt(copy[0], n) || !tr::eq(copy[1], Char(4)) || tr::compare(copy, raw, 1) >= 0 ||
        tr::assign(copy, 3, n) != copy || copy[0] != n || copy[1] != n || copy[2] != n)
        return false;
    return tr::eq_int_type(tr::to_int_type(n), tr::to_int_type(tr::to_char_type(tr::to_int_type(n))));
}
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int check_character_traits(int seed)
{
    if (!check_code_units<char>(seed) || !check_code_units<char16_t>(seed) || !check_code_units<char32_t>(seed) ||
        !check_code_units<wchar_t>(seed))
        return 1;
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
    if (!check_code_units<char8_t>(seed))
        return 2;
#endif
    const char16_t high[] = {char16_t(256)};
    const char16_t low[] = {char16_t(255)};
    return asc::std::char_traits<char16_t>::compare(low, high, 1) < 0 &&
            asc::std::char_traits<char>::lt(static_cast<char>(127), static_cast<char>(128)) ?
        0 :
        3;
}
}  // namespace asc_stl_test_string

#endif  // ASC_STL_TEST_STRING_CHARACTER_TRAITS_H
