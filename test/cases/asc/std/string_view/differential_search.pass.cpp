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

#include <asc/std/string_view>

#include <string_view>

namespace {
using view = asc::std::string_view;
using reference = std::string_view;

template <class Search>
bool compare_search(Search search)
{
    const char* inputs[] = {"", "a", "abbab", "xxxx", "yxax"};
    for (const char* lhs : inputs) {
        const view haystack(lhs);
        const reference ref(lhs);
        for (const char* needle : inputs) {
            const reference pattern(needle);
            for (unsigned n = 0; n <= pattern.size(); ++n) {
                for (unsigned pos = 0; pos <= haystack.size() + 1; ++pos) {
                    if (search(haystack, needle, pos, n) != search(ref, needle, pos, n) ||
                        search(haystack, needle, view::npos, n) != search(ref, needle, reference::npos, n))
                        return false;
                }
            }
        }
    }
    return true;
}
}  // namespace

int main()
{
    const auto find_counted = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.find(needle, pos, count);
    };
    const auto find_view = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.find(decltype(haystack)(needle, count), pos);
    };
    const auto find_cstr = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.find(needle, pos);
    };
    const auto find_char = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.find(*needle, pos);
    };
    if (!compare_search(find_counted) || !compare_search(find_view) || !compare_search(find_cstr) ||
        !compare_search(find_char))
        return 1;
    const auto rfind_counted = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.rfind(needle, pos, count);
    };
    const auto rfind_view = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.rfind(decltype(haystack)(needle, count), pos);
    };
    const auto rfind_cstr = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.rfind(needle, pos);
    };
    const auto rfind_char = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.rfind(*needle, pos);
    };
    if (!compare_search(rfind_counted) || !compare_search(rfind_view) || !compare_search(rfind_cstr) ||
        !compare_search(rfind_char))
        return 2;
    const auto find_first_of_counted = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.find_first_of(needle, pos, count);
    };
    const auto find_first_of_view = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.find_first_of(decltype(haystack)(needle, count), pos);
    };
    const auto find_first_of_cstr = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.find_first_of(needle, pos);
    };
    const auto find_first_of_char = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.find_first_of(*needle, pos);
    };
    if (!compare_search(find_first_of_counted) || !compare_search(find_first_of_view) ||
        !compare_search(find_first_of_cstr) || !compare_search(find_first_of_char))
        return 3;
    const auto find_last_of_counted = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.find_last_of(needle, pos, count);
    };
    const auto find_last_of_view = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.find_last_of(decltype(haystack)(needle, count), pos);
    };
    const auto find_last_of_cstr = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.find_last_of(needle, pos);
    };
    const auto find_last_of_char = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.find_last_of(*needle, pos);
    };
    if (!compare_search(find_last_of_counted) || !compare_search(find_last_of_view) ||
        !compare_search(find_last_of_cstr) || !compare_search(find_last_of_char))
        return 4;
    const auto find_first_not_of_counted = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.find_first_not_of(needle, pos, count);
    };
    const auto find_first_not_of_view = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.find_first_not_of(decltype(haystack)(needle, count), pos);
    };
    const auto find_first_not_of_cstr = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.find_first_not_of(needle, pos);
    };
    const auto find_first_not_of_char = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.find_first_not_of(*needle, pos);
    };
    if (!compare_search(find_first_not_of_counted) || !compare_search(find_first_not_of_view) ||
        !compare_search(find_first_not_of_cstr) || !compare_search(find_first_not_of_char))
        return 5;
    const auto find_last_not_of_counted = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.find_last_not_of(needle, pos, count);
    };
    const auto find_last_not_of_view = [](auto haystack, const char* needle, auto pos, unsigned count) {
        return haystack.find_last_not_of(decltype(haystack)(needle, count), pos);
    };
    const auto find_last_not_of_cstr = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.find_last_not_of(needle, pos);
    };
    const auto find_last_not_of_char = [](auto haystack, const char* needle, auto pos, unsigned) {
        return haystack.find_last_not_of(*needle, pos);
    };
    if (!compare_search(find_last_not_of_counted) || !compare_search(find_last_not_of_view) ||
        !compare_search(find_last_not_of_cstr) || !compare_search(find_last_not_of_char))
        return 6;
    return 0;
}
