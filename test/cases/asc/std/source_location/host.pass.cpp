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

#include <asc/std/source_location>
#include <asc/std/version>

#include <type_traits>

namespace {

constexpr bool strings_equal(const char* left, const char* right)
{
    while (*left != '\0' || *right != '\0') {
        if (*left != *right) {
            return false;
        }
        ++left;
        ++right;
    }
    return true;
}

}  // namespace

int main()
{
    static_assert(CANN_ASC_STL_HAS_SOURCE_LOCATION == 1);
    constexpr auto explicit_location = asc::std::source_location::current("manual.cpp", "manual", 123, 17);
    static_assert(explicit_location.line() == 123);
    static_assert(explicit_location.column() == 17);
    static_assert(strings_equal(explicit_location.file_name(), "manual.cpp"));
    static_assert(strings_equal(explicit_location.function_name(), "manual"));

    constexpr asc::std::uint_least32_t expected_line = __LINE__ + 1;
    constexpr auto current_location = asc::std::source_location::current();
    static_assert(current_location.line() == expected_line);
    static_assert(current_location.file_name()[0] != '\0');
    static_assert(strings_equal(current_location.function_name(), "main"));

    constexpr asc::std::source_location default_location{};
    static_assert(default_location.line() == 0);
    static_assert(default_location.column() == 0);
    static_assert(strings_equal(default_location.file_name(), ""));
    static_assert(strings_equal(default_location.function_name(), ""));
    constexpr auto copied_location = explicit_location;
    static_assert(copied_location.line() == 123);
    static_assert(std::is_copy_constructible_v<asc::std::source_location>);
    static_assert(std::is_move_constructible_v<asc::std::source_location>);
    static_assert(std::is_nothrow_destructible_v<asc::std::source_location>);
    return 0;
}
