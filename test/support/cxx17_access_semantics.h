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

#ifndef ASC_STL_TEST_CXX17_ACCESS_SEMANTICS_H
#define ASC_STL_TEST_CXX17_ACCESS_SEMANTICS_H

#include <asc/std/ranges>
#include <asc/std/type_traits>

namespace asc_stl_cxx17_access_test {
struct move_cursor {
    using value_type = int;
    using difference_type = __PTRDIFF_TYPE__;
    using iterator_category = asc::std::input_iterator_tag;
    using iterator_concept = asc::std::input_iterator_tag;
    int* pointer = nullptr;
    CANN_ASC_STL_API move_cursor() = default;
    CANN_ASC_STL_API move_cursor(move_cursor&&) = default;
    move_cursor(const move_cursor&) = delete;
    CANN_ASC_STL_API move_cursor& operator=(move_cursor&&) = default;
    move_cursor& operator=(const move_cursor&) = delete;
    CANN_ASC_STL_API int& operator*() const
    {
        return *pointer;
    }
    CANN_ASC_STL_API move_cursor& operator++()
    {
        ++pointer;
        return *this;
    }
    CANN_ASC_STL_API void operator++(int)
    {
        ++*this;
    }
};
struct member_range {
    move_cursor position;
    CANN_ASC_STL_API move_cursor& rbegin()
    {
        return position;
    }
};
struct adl_range {
    move_cursor position;
};
CANN_ASC_STL_API move_cursor& rbegin(adl_range& range)
{
    return range.position;
}
struct sized_range {
    int values[3] = {1, 2, 3};
    CANN_ASC_STL_API bool size() const
    {
        return true;
    }
    CANN_ASC_STL_API int* begin()
    {
        return values;
    }
    CANN_ASC_STL_API int* end()
    {
        return values + 3;
    }
};
CANN_ASC_STL_API unsigned int size(sized_range&)
{
    return 7;
}
struct bool_size_only {
    CANN_ASC_STL_API bool size() const
    {
        return true;
    }
};

CANN_ASC_STL_API int evaluate()
{
    namespace s = asc::std;
    namespace r = asc::std::ranges;
    static_assert(s::input_or_output_iterator<move_cursor>);
    static_assert(!s::is_copy_constructible_v<move_cursor>);
    static_assert(!s::is_invocable_v<decltype(r::rbegin), member_range&>);
    static_assert(!s::is_invocable_v<decltype(r::rbegin), adl_range&>);
    static_assert(!s::is_invocable_v<decltype(r::size), int>);
    static_assert(!s::is_invocable_v<decltype(r::size), bool_size_only&>);
    sized_range input;
    return r::size(input) != 7 || r::ssize(input) != 7;
}
}  // namespace asc_stl_cxx17_access_test

#endif  // ASC_STL_TEST_CXX17_ACCESS_SEMANTICS_H
