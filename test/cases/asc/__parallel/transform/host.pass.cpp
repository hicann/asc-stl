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

#include <asc/__algorithm/frontend.h>
#include <asc/std/iterator>

namespace {
struct forward {
    using value_type = int;
    using difference_type = __PTRDIFF_TYPE__;
    using pointer = int*;
    using reference = int&;
    using iterator_category = asc::std::forward_iterator_tag;
    int* current;
    int& operator*() const
    {
        return *current;
    }
    forward& operator++()
    {
        ++current;
        return *this;
    }
    forward operator++(int)
    {
        const auto previous = *this;
        ++*this;
        return previous;
    }
    bool operator==(forward other) const
    {
        return current == other.current;
    }
    bool operator!=(forward other) const
    {
        return current != other.current;
    }
};

struct bidirectional {
    using value_type = int;
    using difference_type = __PTRDIFF_TYPE__;
    using pointer = int*;
    using reference = int&;
    using iterator_category = asc::std::bidirectional_iterator_tag;
    int* current;
    int& operator*() const
    {
        return *current;
    }
    bidirectional& operator++()
    {
        ++current;
        return *this;
    }
    bidirectional& operator--()
    {
        --current;
        return *this;
    }
    bidirectional operator++(int)
    {
        const auto previous = *this;
        ++*this;
        return previous;
    }
    bidirectional operator--(int)
    {
        const auto previous = *this;
        --*this;
        return previous;
    }
    bool operator==(bidirectional other) const
    {
        return current == other.current;
    }
    bool operator!=(bidirectional other) const
    {
        return current != other.current;
    }
};

bool check_reverse(int count)
{
    int input[7] = {1, 2, 3, 4, 5, 6, 99};
    int copied[7] = {99, 99, 99, 99, 99, 99, 99};
    asc::detail::reverse_copy_operation<bidirectional, int*>{
        bidirectional{input}, bidirectional{input + count}, copied}();
    for (int index = 0; index < count; ++index) {
        if (copied[index] != count - index || input[index] != index + 1)
            return false;
    }
    if (copied[count] != 99)
        return false;
    asc::detail::reverse_operation<bidirectional>{bidirectional{input}, bidirectional{input + count}}();
    for (int index = 0; index < count; ++index) {
        if (input[index] != count - index)
            return false;
    }
    return input[count] == (count == 6 ? 99 : count + 1);
}

bool check_rotate_copy(int count, int middle)
{
    int input[8] = {61, 1, 2, 3, 4, 5, 6, 62};
    const int original[8] = {61, 1, 2, 3, 4, 5, 6, 62};
    int copied[8] = {99, 99, 99, 99, 99, 99, 99, 99};
    int pointer_copied[8] = {99, 99, 99, 99, 99, 99, 99, 99};
    asc::detail::rotate_copy_operation<forward, forward>{
        forward{input + 1}, forward{input + 1 + middle}, forward{input + 1 + count}, forward{copied + 1}}();
    asc::detail::rotate_copy_operation<int*, int*>{
        input + 1, input + 1 + middle, input + 1 + count, pointer_copied + 1}();
    for (int index = 0; index < 8; ++index) {
        int expected = 99;
        if (index >= 1 && index <= count) {
            int source = index - 1 + middle;
            if (source >= count)
                source -= count;
            expected = source + 1;
        }
        if (copied[index] != expected || pointer_copied[index] != expected || input[index] != original[index])
            return false;
    }
    return true;
}
}  // namespace

int main()
{
    static_assert(__is_trivially_copyable(asc::device_policy));
    static_assert(asc::std::bidirectional_iterator<bidirectional>);
    static_assert(!asc::std::random_access_iterator<bidirectional>);
    static_assert(asc::std::forward_iterator<forward>);
    static_assert(!asc::std::bidirectional_iterator<forward>);
    static_assert(!asc::std::random_access_iterator<forward>);
    for (int count = 0; count <= 6; ++count) {
        if (!check_reverse(count))
            return count + 1;
        for (int middle = 0; middle <= count; ++middle) {
            if (!check_rotate_copy(count, middle))
                return 8 + count;
        }
    }
    return 0;
}
