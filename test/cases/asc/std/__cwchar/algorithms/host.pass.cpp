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

#include <asc/std/__cwchar/algorithms.h>
#include <asc/std/__cwchar/fixed_c_locale.h>
#include <asc/std/__cwchar/types.h>

#include <cassert>

int main()
{
    const wchar_t* text = L"hello";
    assert(asc::std::wcslen(text) == 5);
    assert(asc::std::wcslen(L"") == 0);
    assert(asc::std::wcscmp(L"abc", L"abd") < 0);
    assert(asc::std::wcscmp(L"abc", L"abc") == 0);
    assert(asc::std::wcscmp(L"abz", L"abc") > 0);
    assert(asc::std::wcsncmp(L"abc", L"abd", 2) == 0);
    assert(asc::std::wcsncmp(L"abc", L"abd", 3) < 0);
    assert(asc::std::wcsncmp(L"abc", L"ab", 5) > 0);

    wchar_t buffer[16]{};
    assert(asc::std::wcscpy(buffer, L"ab") == buffer);
    assert(asc::std::wcsncpy(buffer, L"xyz", 2) == buffer && asc::std::wcsncmp(buffer, L"xy", 2) == 0);
    assert(asc::std::wcscat(buffer, L"cd") == buffer && asc::std::wcscmp(buffer, L"xycd") == 0);
    assert(asc::std::wcsncat(buffer, L"efg", 1) == buffer && asc::std::wcscmp(buffer, L"xycde") == 0);

    assert(*asc::std::wcschr(L"abc", L'b') == L'b');
    assert(asc::std::wcschr(L"abc", L'z') == nullptr);
    wchar_t mutable_search[] = L"abc";
    *asc::std::wcschr(mutable_search, L'b') = L'B';
    assert(asc::std::wcscmp(mutable_search, L"aBc") == 0);
    assert(*asc::std::wcsrchr(L"abcb", L'b') == L'b');
    assert(asc::std::wcsrchr(L"abc", L'z') == nullptr);

    assert(asc::std::wcsspn(L"aabc", L"ab") == 3);
    assert(asc::std::wcscspn(L"ab_cd", L"_") == 2);
    assert(*asc::std::wcspbrk(L"abcd", L"cb") == L'b');
    assert(asc::std::wcspbrk(L"abcd", L"z") == nullptr);
    assert(asc::std::wcsstr(L"foobar", L"bar") != nullptr);
    assert(asc::std::wcsstr(L"foobar", L"baz") == nullptr);
    assert(asc::std::wcsstr(L"foobar", L"") != nullptr);

    assert(*asc::std::wmemchr(L"abcd", L'c', 4) == L'c');
    assert(asc::std::wmemchr(L"abcd", L'e', 4) == nullptr);
    assert(asc::std::wmemcmp(L"aa", L"ab", 2) < 0);
    assert(asc::std::wmemcmp(L"ab", L"ab", 2) == 0);
    assert(asc::std::wmemset(buffer, L'x', 3) == buffer);
    assert(asc::std::wmemcmp(buffer, L"xxx", 3) == 0);
    wchar_t overlap[8] = L"12345";
    assert(asc::std::wmemmove(overlap + 1, overlap, 4) == overlap + 1);
    assert(asc::std::wcscmp(overlap, L"11234") == 0);
    wchar_t reverse[8] = L"12345";
    assert(asc::std::wmemmove(reverse, reverse + 1, 4) == reverse);
    assert(asc::std::wcscmp(reverse, L"23455") == 0);
    assert(asc::std::wmemcpy(buffer, L"ab", 2) == buffer);

    // Fixed-C-locale collation, transformation and tokenization.
    assert(asc::std::wcscoll(L"abc", L"abd") < 0);
    assert(asc::std::wcscoll(L"abc", L"abc") == 0);
    wchar_t xfrm[8];
    assert(asc::std::wcsxfrm(xfrm, L"abc", 8) == 3 && asc::std::wcscmp(xfrm, L"abc") == 0);
    wchar_t tokenize[] = L"a,,b";
    wchar_t* state = nullptr;
    wchar_t* first_token = asc::std::wcstok(tokenize, L",", &state);
    wchar_t* second_token = asc::std::wcstok(nullptr, L",", &state);
    assert(asc::std::wcscmp(first_token, L"a") == 0);
    assert(second_token && asc::std::wcscmp(second_token, L"b") == 0);
    assert(asc::std::wcstok(nullptr, L",", &state) == nullptr);

    // Fixed-C-locale conversions with pure integer and character semantics.
    assert(asc::std::btowc('x') == static_cast<asc::std::wint_t>(L'x'));
    assert(asc::std::btowc(-1) == WEOF);
    assert(asc::std::wctob(static_cast<asc::std::wint_t>(L'x')) == 'x');
    assert(asc::std::wctob(static_cast<asc::std::wint_t>(0x100)) == -1);
    asc::std::mbstate_t conversion{};
    assert(asc::std::mbsinit(&conversion) != 0);
    wchar_t wide = 0;
    assert(asc::std::mbrtowc(&wide, "z", 1, &conversion) == 1 && wide == L'z');
    assert(asc::std::mbrtowc(&wide, "\x80", 1, &conversion) == static_cast<__SIZE_TYPE__>(-1));
    assert(asc::std::mbrtowc(&wide, "ab", 0, &conversion) == static_cast<__SIZE_TYPE__>(-2));
    const char* narrow = "hi";
    assert(asc::std::mbrlen("h", 1, &conversion) == 1);
    assert(asc::std::mbsrtowcs(nullptr, &narrow, 0, &conversion) == 2);
    char bytes[8];
    const wchar_t* wide_source = L"ok";
    assert(asc::std::wcrtomb(bytes, L'k', &conversion) == 1);
    assert(asc::std::wcsrtombs(bytes, &wide_source, 8, &conversion) == 2);
    return 0;
}
