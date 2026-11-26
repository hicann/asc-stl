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

#ifndef ASC_STL_TEST_COUNTED_ORDER_SEMANTICS_H
#define ASC_STL_TEST_COUNTED_ORDER_SEMANTICS_H

#include <asc/std/iterator>

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && CANN_ASC_STL_DETAIL_HAS_CXX20()
#include <iterator>
#endif

namespace asc_stl_counted_order_test {

CANN_ASC_STL_API int evaluate_order(
    const asc::std::counted_iterator<int*>& first, const asc::std::counted_iterator<int*>& later)
{
    if (!(first.base() < later.base()) || later - first != 2 || first - later != -2) {
        return 111;
    }
    if (!(first < later) || !(first <= later) || !(later > first) || !(later >= first)) {
        return 112;
    }
    if (later < first || later <= first || first > later || first >= later) {
        return 113;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate_equality(const asc::std::counted_iterator<int*>& first,
    const asc::std::counted_iterator<int*>& later, const asc::std::counted_iterator<int*>& same,
    const asc::std::counted_iterator<const int*>& const_later)
{
    if (!(first == same) || first != same || first < same || first > same || !(first <= same) || !(first >= same)) {
        return 114;
    }
    if (!(later == const_later) || later != const_later || later - const_later != 0 || !(first < const_later) ||
        !(const_later > first) || !(first <= const_later) || !(const_later >= first)) {
        return 115;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate_endpoint(const asc::std::counted_iterator<int*>& first,
    const asc::std::counted_iterator<int*>& later, const asc::std::counted_iterator<int*>& last)
{
    if (!(later < last) || !(last > later) || !(last >= last) || !(last <= last) || last - first != 4 ||
        first - last != -4 || !(last == asc::std::default_sentinel)) {
        return 116;
    }
    return 0;
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && CANN_ASC_STL_DETAIL_HAS_CXX20()
CANN_ASC_STL_HOST_API int evaluate_standard_order(
    int* values, const asc::std::counted_iterator<int*>& first, const asc::std::counted_iterator<int*>& later)
{
    const std::counted_iterator<int*> standard_first(values, 4);
    const std::counted_iterator<int*> standard_later(values + 2, 2);
    if ((first < later) != (standard_first < standard_later) ||
        (first <= later) != (standard_first <= standard_later) ||
        (first > later) != (standard_first > standard_later) ||
        (first >= later) != (standard_first >= standard_later) ||
        (first == later) != (standard_first == standard_later) ||
        (later - first) != (standard_later - standard_first)) {
        return 117;
    }
    return 0;
}
#endif

CANN_ASC_STL_API int evaluate()
{
    int values[4] = {2, 4, 6, 8};
    const asc::std::counted_iterator<int*> first(values, 4);
    const asc::std::counted_iterator<int*> later(values + 2, 2);
    const asc::std::counted_iterator<int*> last(values + 4, 0);
    const auto same = first;
    const asc::std::counted_iterator<const int*> const_later(later);
    const int order_result = evaluate_order(first, later);
    if (order_result != 0)
        return order_result;
    const int equality_result = evaluate_equality(first, later, same, const_later);
    if (equality_result != 0)
        return equality_result;
    const int endpoint_result = evaluate_endpoint(first, later, last);
    if (endpoint_result != 0)
        return endpoint_result;
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && CANN_ASC_STL_DETAIL_HAS_CXX20()
    return evaluate_standard_order(values, first, later);
#else
    return 0;
#endif
}

}  // namespace asc_stl_counted_order_test

#endif  // ASC_STL_TEST_COUNTED_ORDER_SEMANTICS_H
