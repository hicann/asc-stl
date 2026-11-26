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

#ifndef ASC_STL_TEST_ITERATOR_DEVICE_CHECKS_H
#define ASC_STL_TEST_ITERATOR_DEVICE_CHECKS_H

#include <asc/std/iterator>

#include "adaptors_checks.h"

namespace asc_stl_test_iterator {
CANN_ASC_STL_API int check(int seed = 7)
{
    if (int result = check_adaptors(seed))
        return 20 + result;
    int values[] = {9, -3, seed, 4};
    auto reverse = asc::std::make_reverse_iterator(values + 4);
    asc::std::reverse_iterator<const int*> read = reverse;
    if (reverse.operator->() != values + 3 || *reverse++ != 4 || *reverse != 7 || *reverse-- != 7 || *reverse != 4 ||
        reverse[2] != -3 || *(2 + reverse) != -3)
        return 1;
    reverse += 2;
    if (reverse - read != 2 || !(reverse > read && reverse >= read && read < reverse && read <= reverse))
        return 2;
    reverse -= 1;
    read = reverse;
    if (read.base() != values + 3 || *(--reverse) != 4 || *(++reverse) != 7)
        return 3;
    asc::std::counted_iterator<int*> counted(values, 4);
    asc::std::counted_iterator<const int*> const_counted(counted);
    if (counted.operator->() != values || counted.count() != 4 || *counted++ != 9 || *counted != -3 ||
        *counted-- != -3 || *counted != 9)
        return 4;
    counted += 3;
    if (counted - const_counted != 3 || counted - asc::std::default_sentinel != -1 ||
        asc::std::default_sentinel - counted != 1 || (1 + counted) != asc::std::default_sentinel)
        return 5;
    counted -= 2;
    if (counted[2] != 4 || *(++counted) != 7 || *(--counted) != -3)
        return 6;
    auto moved = asc::std::make_move_iterator(values);
    if (*moved != 9 || *(moved + 2) != 7 || moved[3] != 4 || (moved + 4) - moved != 4)
        return 7;
    int* p = values;
    asc::std::advance(p, 3);
    if (asc::std::prev(p, 2) != values + 1 || asc::std::next(values + 0, 4) != values + 4 ||
        asc::std::distance(p, values + 0) != -3)
        return 8;
    if (asc::std::ranges::advance(p, -8, values + 0) != -5 || p != values ||
        asc::std::ranges::next(p, 7, values + 4) != values + 4)
        return 9;
    return 0;
}
}  // namespace asc_stl_test_iterator

#endif  // ASC_STL_TEST_ITERATOR_DEVICE_CHECKS_H
