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

#pragma once

#include <asc/std/cwchar>
#include <asc/std/new>

namespace asc_stl_test_cwchar {

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int private_conversions(int seed)
{
    wchar_t local[] = {L'A', static_cast<wchar_t>(L'B' + seed - 7), 0};
    if (asc::std::wcslen(local) != 2 || asc::std::wcschr(local, L'B') != local + 1)
        return 1;
    char text[] = {static_cast<char>('Z' + seed - 7), 0};
    wchar_t wc = 0;
    asc::std::mbstate_t state{};
    if (asc::std::mbrtowc(&wc, text, 1, &state) != 1 || wc != L'Z')
        return 2;
    const char* input = text;
    wchar_t wide[2] = {L'!', L'!'};
    return asc::std::mbsrtowcs(wide, &input, 2, &state) != 1 || input || wide[0] != L'Z' || wide[1] != 0;
}

struct buffers {
    wchar_t word[4] = {L'a', L'b', L'a', 0};
    wchar_t needle[3] = {L'a', L'b', 0};
    wchar_t empty[1] = {0};
    wchar_t buf[9] = {0, 0, 0, 0, 0, 0, 0, 0, L'!'};
    wchar_t tokens[5] = {L'x', L',', L',', L'y', 0};
    wchar_t separators[2] = {L',', 0};
    wchar_t* cursor = nullptr;
    asc::std::mbstate_t state{};
    char text[3] = {'A', 'B', 0};
    char output[4] = {'?', '?', '?', '!'};
    const char* input = nullptr;
    const wchar_t* wide = nullptr;
    wchar_t wc = 0;
};

CANN_ASC_STL_API int check(int seed, void* workspace)
{
    auto* storage = static_cast<buffers*>(workspace);
    ::new (workspace) buffers{};
    auto& word = storage->word;
    const wchar_t* read = word;
    const auto& needle = storage->needle;
    const auto& empty = storage->empty;
    word[2] = static_cast<wchar_t>(L'a' + seed - 7);
    if (asc::std::wcslen(word) != 3 || asc::std::wcscmp(word, needle) <= 0 || asc::std::wcsncmp(word, needle, 2) ||
        asc::std::wcscoll(word, needle) <= 0 || asc::std::wcschr(word, 0) != word + 3 ||
        asc::std::wcschr(read, L'b') != read + 1 || asc::std::wcsrchr(word, L'a') != word + 2 ||
        asc::std::wcsrchr(read, L'z') != nullptr || asc::std::wcsstr(word, empty) != word ||
        asc::std::wcsstr(read, needle) != read || asc::std::wcspbrk(word, empty) != nullptr ||
        asc::std::wcspbrk(read, needle + 1) != read + 1 || asc::std::wcsspn(word, needle) != 3 ||
        asc::std::wcscspn(word, needle + 1) != 1)
        return 1;
    auto& buf = storage->buf;
    if (asc::std::wcscpy(buf, word) != buf || asc::std::wcscat(buf, needle) != buf ||
        asc::std::wcsncat(buf, needle, 1) != buf || buf[5] != L'a' || buf[6] != 0 ||
        asc::std::wcsncpy(buf, needle, 5) != buf || buf[4] != 0 || buf[8] != L'!')
        return 2;
    if (asc::std::wmemset(buf, L'!', 6) != buf || asc::std::wmemcpy(buf, word, 4) != buf ||
        asc::std::wmemmove(buf + 1, buf, 4) != buf + 1 || asc::std::wmemcmp(buf + 1, word, 4) ||
        asc::std::wmemchr(buf, L'b', 5) != buf + 2 || asc::std::wmemchr(read, L'b', 1) || buf[5] != L'!')
        return 3;
    auto& cursor = storage->cursor;
    auto& tokens = storage->tokens;
    const auto& separators = storage->separators;
    if (asc::std::wcstok(tokens, separators, &cursor) != tokens ||
        asc::std::wcstok(nullptr, separators, &cursor) != tokens + 3 || asc::std::wcstok(nullptr, separators, &cursor))
        return 4;
    if (asc::std::wcsxfrm(buf, needle, 5) != 2 || asc::std::wcscmp(buf, needle) || asc::std::btowc('A') != L'A' ||
        asc::std::wctob(L'B') != 'B')
        return 5;
    auto& state = storage->state;
    auto& text = storage->text;
    auto& output = storage->output;
    auto& input = storage->input;
    auto& wc = storage->wc;
    input = text;
    if (!asc::std::mbsinit(&state) || asc::std::mbrlen(text, 1, &state) != 1 ||
        asc::std::mbrtowc(&wc, text, 1, &state) != 1 || wc != L'A' || asc::std::wcrtomb(output, wc, &state) != 1 ||
        output[0] != 'A' || asc::std::mbsrtowcs(buf, &input, 3, &state) != 2 || input || buf[1] != L'B')
        return 6;
    auto& wide = storage->wide;
    wide = buf;
    if (asc::std::wcsrtombs(output, &wide, 3, &state) != 2 || wide || output[1] != 'B' || output[2] || output[3] != '!')
        return 7;

    const auto error = static_cast<__SIZE_TYPE__>(-1);
    const auto incomplete = static_cast<__SIZE_TYPE__>(-2);
    if (asc::std::mbrlen(text, 0, &state) != incomplete || asc::std::mbrtowc(nullptr, nullptr, 0, &state) != 0 ||
        asc::std::wcrtomb(nullptr, L'X', &state) != 1 || asc::std::wcsxfrm(nullptr, needle, 0) != 2)
        return 8;
    input = text;
    wide = word;
    if (asc::std::mbsrtowcs(nullptr, &input, 0, &state) != 2 || input != text ||
        asc::std::wcsrtombs(nullptr, &wide, 0, &state) != 3 || wide != word ||
        asc::std::mbsrtowcs(buf, &input, 1, &state) != 1 || input != text + 1 || buf[0] != L'A' ||
        asc::std::wcsrtombs(output, &wide, 1, &state) != 1 || wide != word + 1 || output[0] != 'a')
        return 9;
    text[1] = static_cast<char>(0xff);
    word[1] = static_cast<wchar_t>(0x100);
    if (asc::std::mbsrtowcs(buf, &input, 2, &state) != error || input != text + 1)
        return 10;
    state = {};
    if (asc::std::wcsrtombs(output, &wide, 2, &state) != error || wide != word + 1)
        return 11;
    state = {};
    if (asc::std::wcrtomb(output, word[1], &state) != error)
        return 12;
    return private_conversions(seed) ? 13 : 0;
}

}  // namespace asc_stl_test_cwchar
