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

#ifndef ASC_STL_TEST_ITERATOR_ADAPTORS_H
#define ASC_STL_TEST_ITERATOR_ADAPTORS_H

#include <asc/std/iterator>

namespace asc_stl_test_iterator {
struct entry {
    int value;
};

CANN_ASC_STL_API int check_adaptors(int seed)
{
    namespace s = asc::std;
    entry elements[] = {{seed}, {2}, {-1}};
    auto first = s::make_move_iterator(elements + 0);
    s::move_iterator<const entry*> read;
    read = first;
    s::move_iterator<const entry*> at(read);
    auto end = s::make_move_iterator(elements + 3);
    s::move_sentinel<entry*> sentinel(elements + 3);
    s::move_sentinel<const entry*> const_end(sentinel);
    const_end = sentinel;
    if (at->value != 7 || const_end.base() != elements + 3 || first == sentinel || first - const_end != -3 ||
        const_end - read != 3 || !(first < end && first <= read && end > read && end >= first && end != first))
        return 1;
    if ((first++)->value != seed || first->value != 2 || (--first)->value != seed || (++first)->value != 2 ||
        (first--)->value != 2)
        return 2;
    first += 2;
    if (first->value != -1 || (first - 1)->value != 2 || (1 + first) != end)
        return 3;
    first -= 1;
    s::iter_swap(first, end - 1);
    if (elements[1].value != -1 || elements[2].value != 2 ||
        static_cast<decltype(first)&&>(first).base() != elements + 1)
        return 4;

    using counted = s::counted_iterator<entry*>;
    using common = s::common_iterator<counted, s::default_sentinel_t>;
    const s::default_sentinel_t stop{};
    counted remaining(elements, 3);
    const s::unreachable_sentinel_t never{};
    if (remaining == never || never == remaining || !(never != remaining) || !(remaining != never))
        return 5;
    common i(remaining), bound(stop);
    common copied = bound;
    copied = i;
    if (bound - i != 3 || i == bound || copied->value != seed || (*copied++).value != seed)
        return 6;
    ++copied;
    if (copied->value != 2 || ++copied != bound || !(bound == copied))
        return 7;
    counted empty(elements, 0);
    return empty == stop && stop == empty && !(stop != empty) && !(empty != stop) ? 0 : 8;
}
}  // namespace asc_stl_test_iterator

#endif  // ASC_STL_TEST_ITERATOR_ADAPTORS_H
