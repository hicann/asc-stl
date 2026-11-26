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

#ifndef ASC_STL_TEST_INSERT_ITERATOR_SEMANTICS_H
#define ASC_STL_TEST_INSERT_ITERATOR_SEMANTICS_H

#include <asc/std/iterator>
#include <asc/std/type_traits>

namespace asc_stl_insert_iterator_test {

struct buffer {
    using value_type = int;
    using iterator = int*;

    int values[8]{1, 4};
    int size = 2;
    CANN_ASC_STL_API constexpr int* begin()
    {
        return values;
    }
    CANN_ASC_STL_API constexpr int* end()
    {
        return values + size;
    }

    CANN_ASC_STL_API constexpr void push_back(int value)
    {
        values[size++] = value;
    }

    CANN_ASC_STL_API constexpr void push_front(int value)
    {
        insert(begin(), value);
    }

    CANN_ASC_STL_API constexpr iterator insert(iterator pos, int value)
    {
        for (auto i = values + size; i != pos; --i) {
            *i = *(i - 1);
        }
        *pos = value;
        ++size;
        return pos;
    }
};

CANN_ASC_STL_API constexpr bool inserted_in_order(int seed = 0)
{
    buffer target{};
    target.values[0] += seed;
    target.values[1] += seed;
    asc::std::insert_iterator<buffer> output(target, target.begin() + 1);
    static_assert(asc::std::is_same_v<decltype(output++), decltype(output)&>);
    if (&output++ != &output || target.size != 2) {
        return false;
    }
    *output++ = seed + 2;
    *output++ = seed + 3;
    return target.size == 4 && target.values[0] == seed + 1 && target.values[1] == seed + 2 &&
        target.values[2] == seed + 3 && target.values[3] == seed + 4;
}
static_assert(inserted_in_order());

CANN_ASC_STL_API int evaluate_adaptors(int seed)
{
    if (!inserted_in_order(seed))
        return 1;
    buffer target{};
    auto back = asc::std::back_inserter(target);
    *back++ = seed + 4;
    *++back = seed + 5;
    auto front = asc::std::front_inserter(target);
    *front++ = seed + 2;
    *++front = seed + 1;
    if (target.size != 6 || target.values[0] != seed + 1 || target.values[1] != seed + 2 ||
        target.values[4] != seed + 4 || target.values[5] != seed + 5)
        return 2;
    const int* first = target.begin();
    const int* last = target.end();
    asc::std::counted_iterator<const int*> counted(first, 6);
    auto middle = counted + 4;
    if (middle[1] != seed + 5 || middle.count() != 2 || (middle--).base() != first + 4)
        return 3;
    middle = counted;
    middle += 6;
    if (middle != asc::std::default_sentinel_t{} || middle.base() != last || (middle - 1).base() != last - 1)
        return 4;
    middle -= 2;
    if (*(middle++) != seed + 4 || *--middle != seed + 4)
        return 5;
    asc::std::reverse_iterator<const int*> reverse(last);
    auto cursor = reverse + 1;
    if (*reverse != seed + 5 || cursor.base() != last - 1 || cursor[3] != seed + 2)
        return 6;
    cursor += 1;
    cursor -= 1;
    if ((cursor++).base() != last - 1 || (--cursor).base() != last - 1 || (cursor - 1).base() != last)
        return 7;
    asc::std::move_iterator<const int*> moved(first);
    auto selected = moved + 4;
    if (selected[1] != seed + 5 || selected.operator->() != first + 4 || (selected--).base() != first + 4)
        return 8;
    selected += 1;
    selected -= 1;
    if ((selected++).base() != first + 3 || (--selected).base() != first + 3 || (selected - 1).base() != first + 2)
        return 9;
    selected = moved;
    if (selected.base() != first || (++selected).base() != first + 1)
        return 10;
    asc::std::move_sentinel<const int*> sentinel;
    sentinel = asc::std::move_sentinel<int*>(target.end());
    if (sentinel.base() != last)
        return 11;
    return 0;
}

}  // namespace asc_stl_insert_iterator_test

#endif  // ASC_STL_TEST_INSERT_ITERATOR_SEMANTICS_H
