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

#include <asc/std/cctype>
#include <asc/std/cstring>
#include <asc/std/cwchar>
#include <asc/std/cwctype>

#include <array>
#include <cctype>
#include <climits>
#include <clocale>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <iostream>

namespace {

namespace ast = asc::std;

constexpr int sign(int value)
{
    return (value > 0) - (value < 0);
}

bool check_bytes()
{
    std::array<unsigned char, 37> original{};
    for (std::size_t i = 0; i < original.size(); ++i)
        original[i] = static_cast<unsigned char>(17 * i + 127);
    for (std::size_t source = 1; source < 10; ++source) {
        for (std::size_t target = 1; target < 10; ++target) {
            for (std::size_t count = 0; count <= 27; ++count) {
                auto actual = original;
                auto expected = original;
                std::memmove(expected.data() + target, expected.data() + source, count);
                if (ast::memmove(actual.data() + target, actual.data() + source, count) != actual.data() + target ||
                    actual != expected)
                    return false;
            }
        }
    }

    auto actual = original;
    auto expected = original;
    std::memset(expected.data() + 1, 0x17f, original.size() - 2);
    if (ast::memset(actual.data() + 1, 0x17f, original.size() - 2) != actual.data() + 1 || actual != expected)
        return false;
    for (std::size_t count = 0; count < original.size(); ++count) {
        if (ast::memcpy(actual.data(), original.data(), count) != actual.data() ||
            ast::memcmp(actual.data(), original.data(), count) != 0)
            return false;
        for (int value : {0, 0x7f, 0x80, 0xff, 0x17f}) {
            if (ast::memchr(original.data(), value, count) != std::memchr(original.data(), value, count) ||
                ast::memchr(actual.data(), value, count) != std::memchr(actual.data(), value, count))
                return false;
        }
    }
    const unsigned char lower[] = {7, 0x7f, 0xff};
    const unsigned char upper[] = {7, 0x80, 0};
    return ast::memcmp(lower, upper, 0) == 0 && ast::memcmp(lower, upper, 1) == 0 && ast::memcmp(lower, upper, 3) < 0 &&
        ast::memcmp(upper, lower, 3) > 0;
}

bool check_strings()
{
    const char source[] = "abbacaba";
    const char needle[] = "aba";
    const char accepted[] = "ab";
    const char excluded[] = "cx";
    for (std::size_t count = 0; count <= 12; ++count) {
        std::array<char, 16> actual{};
        actual.fill('#');
        auto expected = actual;
        std::strncpy(expected.data() + 1, source, count);
        if (ast::strncpy(actual.data() + 1, source, count) != actual.data() + 1 || actual != expected)
            return false;
        actual[0] = expected[0] = 'Q';
        actual[1] = expected[1] = '\0';
        std::strncat(expected.data(), source, count);
        if (ast::strncat(actual.data(), source, count) != actual.data() || actual != expected)
            return false;
        for (const char* other : {"abbacabb", "abbac", "c", source}) {
            if (sign(ast::strncmp(source, other, count)) != sign(std::strncmp(source, other, count)))
                return false;
        }
    }
    for (int ch : {'a', 'b', 'c', 'z', '\0'}) {
        if (ast::strchr(source, ch) != std::strchr(source, ch) || ast::strrchr(source, ch) != std::strrchr(source, ch))
            return false;
    }
    for (const char* pattern : {needle, accepted, excluded, ""}) {
        if (ast::strstr(source, pattern) != std::strstr(source, pattern) ||
            ast::strpbrk(source, pattern) != std::strpbrk(source, pattern) ||
            ast::strspn(source, pattern) != std::strspn(source, pattern) ||
            ast::strcspn(source, pattern) != std::strcspn(source, pattern))
            return false;
    }
    return true;
}

bool check_wide_memory()
{
    const std::array<wchar_t, 12> original{L'x', L'a', L'\x3a9', 0, L'\x4e2d', L'a', L'\x80'};
    for (std::size_t count = 0; count <= original.size() - 2; ++count) {
        for (std::size_t source : {std::size_t{0}, std::size_t{2}}) {
            auto actual = original;
            auto expected = original;
            std::wmemmove(expected.data() + 2 - source, expected.data() + source, count);
            if (ast::wmemmove(actual.data() + 2 - source, actual.data() + source, count) !=
                    actual.data() + 2 - source ||
                actual != expected ||
                sign(ast::wmemcmp(original.data(), actual.data(), count)) !=
                    sign(std::wmemcmp(original.data(), expected.data(), count)))
                return false;
            for (wchar_t target : {L'a', L'z', L'\x4e2d', L'\0'}) {
                if (ast::wmemchr(actual.data(), target, count) != std::wmemchr(actual.data(), target, count) ||
                    ast::wmemchr(original.data(), target, count) != std::wmemchr(original.data(), target, count))
                    return false;
            }
        }
    }
    const wchar_t left[] =
        L"a\x3a9"
        L"a";
    const wchar_t right[] = L"a\x4e2d";
    return ast::wcsncmp(left, right, 1) == 0 && ast::wcsncmp(left, right, 2) < 0 &&
        ast::wcschr(left, L'\0') == left + 3 && ast::wcsrchr(left, L'a') == left + 2 &&
        ast::wcsstr(left, L"") == left && ast::wcsstr(left, L"xyz") == nullptr;
}

bool check_c_locale()
{
    if (std::setlocale(LC_CTYPE, "C") == nullptr)
        return false;
    for (int value = 0; value <= UCHAR_MAX; ++value) {
        const auto wide = static_cast<std::wint_t>(value);
        if (static_cast<bool>(ast::isalnum(value)) != static_cast<bool>(std::isalnum(value)) ||
            static_cast<bool>(ast::iscntrl(value)) != static_cast<bool>(std::iscntrl(value)) ||
            static_cast<bool>(ast::isprint(value)) != static_cast<bool>(std::isprint(value)) ||
            static_cast<bool>(ast::isspace(value)) != static_cast<bool>(std::isspace(value)) ||
            static_cast<bool>(ast::isxdigit(value)) != static_cast<bool>(std::isxdigit(value)) ||
            ast::tolower(value) != std::tolower(value) || ast::toupper(value) != std::toupper(value) ||
            static_cast<bool>(ast::iswalpha(wide)) != static_cast<bool>(std::iswalpha(wide)) ||
            static_cast<bool>(ast::iswblank(wide)) != static_cast<bool>(std::iswblank(wide)) ||
            static_cast<bool>(ast::iswgraph(wide)) != static_cast<bool>(std::iswgraph(wide)) ||
            static_cast<bool>(ast::iswpunct(wide)) != static_cast<bool>(std::iswpunct(wide)) ||
            ast::towlower(wide) != std::towlower(wide) || ast::towupper(wide) != std::towupper(wide))
            return false;
    }
    return !ast::isspace(EOF) && ast::toupper(EOF) == EOF && ast::towupper(WEOF) == WEOF;
}

}  // namespace

int main()
{
    if (!check_bytes() || !check_strings() || !check_wide_memory() || !check_c_locale()) {
        std::cerr << "Byte, string, or C locale reference mismatch\n";
        return 1;
    }
    return 0;
}
