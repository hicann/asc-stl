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

#include <asc/std/format>
#include <asc/std/string>
#include <asc/std/string_view>

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>

namespace {

namespace ast = asc::std;

struct allocation_state {
    unsigned allocations = 0;
    unsigned deallocations = 0;
};

template <class T>
struct counting_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    allocation_state* state;
    template <class U>
    struct rebind {
        using other = counting_allocator<U>;
    };
    T* allocate(size_type count)
    {
        ++state->allocations;
        return std::allocator<T>{}.allocate(count);
    }
    void deallocate(T* data, size_type count)
    {
        ++state->deallocations;
        std::allocator<T>{}.deallocate(data, count);
    }
};

using text = ast::basic_string<char, ast::char_traits<char>, counting_allocator<char>>;
static_assert(std::is_same_v<text::allocator_type, counting_allocator<char>>);
static_assert(std::is_same_v<text::traits_type, ast::char_traits<char>> && std::is_same_v<text::value_type, char>);
static_assert(std::is_same_v<text::reference, char&> && std::is_same_v<text::const_reference, const char&>);
static_assert(std::is_same_v<text::pointer, char*> && std::is_same_v<text::const_pointer, const char*>);
static_assert(std::is_same_v<text::iterator, char*> && std::is_same_v<text::const_iterator, const char*>);
static_assert(std::is_same_v<text::size_type, std::size_t>);

bool same_string(const text& library, const std::string& host)
{
    return library.length() == host.length() &&
        library.end() - library.begin() == static_cast<std::ptrdiff_t>(host.size()) &&
        std::string_view(library.begin(), library.length()) == std::string_view(host.data(), host.size()) &&
        library.c_str()[library.length()] == '\0' &&
        (host.empty() || (library.front() == host.front() && library[library.length() - 1] == host.back()));
}

bool check_string_state()
{
    allocation_state stats;
    {
        const counting_allocator<char> alloc{&stats};
        text library("", alloc);
        std::string host;
        if (!same_string(library, host) || library.get_allocator().state != &stats) {
            return false;
        }
        for (int length = 0; length < 96; ++length) {
            char letter = static_cast<char>('a' + length % 26);
            library.push_back(letter);
            host.push_back(letter);
            if (!same_string(library, host) || library.capacity() < library.length()) {
                return false;
            }
        }
        library += library.c_str() + 41;
        host += host.substr(41);
        library += '!';
        host += '!';
        library[0] = 'A';
        host[0] = 'A';
        if (!same_string(library, host) || &library[0] != library.begin()) {
            return false;
        }
        library.clear();
        host.clear();
        if (!same_string(library, host) || library.begin() != library.end()) {
            return false;
        }
        library += "reused";
        host += "reused";
        if (!same_string(library, host)) {
            return false;
        }
    }
    return stats.allocations != 0 && stats.allocations == stats.deallocations;
}

static_assert(std::is_same_v<ast::u32string_view, ast::basic_string_view<char32_t>>);
static_assert(std::is_same_v<ast::wstring_view, ast::basic_string_view<wchar_t>>);
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
static_assert(std::is_same_v<ast::u8string_view, ast::basic_string_view<char8_t>>);
#endif

bool check_views()
{
    using ast::literals::string_view_literals::operator""sv;
    const auto embedded = "ab\0c"sv;
    if (embedded.size() != 4 || embedded[2] != '\0') {
        return false;
    }
    const char* const inputs[] = {"", "a", "aa", "ab", "b", "same-prefix-a", "same-prefix-b"};
    for (const char* left : inputs) {
        for (const char* right : inputs) {
            const ast::basic_string_view<char> a(left);
            const ast::basic_string_view<char> b(right);
            const std::string_view x(left);
            const std::string_view y(right);
            if ((a == b) != (x == y) || (a != b) != (x != y) || (a < b) != (x < y) || (a <= b) != (x <= y) ||
                (a > b) != (x > y) || (a >= b) != (x >= y)) {
                return false;
            }
        }
    }
    return ast::u32string_view(U"\u6d4b\u8bd5").size() == 2 && ast::wstring_view(L"\u6d4b\u8bd5").size() == 2;
}

#if CANN_ASC_STL_DETAIL_HAS_CXX20()
bool check_format_wrapper()
{
    constexpr ast::basic_format_string<char, int> converted{"[{}]"};
    static_assert(converted.size() == 4);
    char output[6]{'#', '#', '#', '#', '#', '#'};
    const auto full = ast::format_to_n(output, 5, converted, 17);
    if (full.out != output + 4 || full.size != 4 || std::string_view(output, 4) != "[17]" || output[4] != '#') {
        return false;
    }
    const auto truncated = ast::format_to_n(output, 2, converted, -12);
    return truncated.out == output + 2 && truncated.size == 5 && output[0] == '[' && output[1] == '-';
}
#endif

}  // namespace

int main()
{
    if (!check_string_state() || !check_views()) {
        return 1;
    }
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
    return check_format_wrapper() ? 0 : 2;
#else
    return 0;
#endif
}
