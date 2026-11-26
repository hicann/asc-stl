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

#include <asc/std/algorithm>

#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <utility>

#include "device_checks.h"

#define CHECK(condition)                                        \
    do {                                                        \
        if (!(condition)) {                                     \
            std::fprintf(stderr, "failed line %d\n", __LINE__); \
            return false;                                       \
        }                                                       \
    } while (false)
#define READ(name, ...) CHECK(asc::std::name(__VA_ARGS__) == std::name(__VA_ARGS__))
#define PAIR(name, ...)                                    \
    do {                                                   \
        const auto a = asc::std::name(__VA_ARGS__);        \
        const auto b = std::name(__VA_ARGS__);             \
        CHECK(a.first == b.first && a.second == b.second); \
    } while (false)

bool inspect(const int* p, int count)
{
    const int* e = p + count;
    const int pattern[] = {2, 1};
    const auto even = [](int v) { return v % 2 == 0; };
    const std::equal_to<int> eq;
    const std::less<int> less;
    READ(all_of, p, e, even);
    READ(any_of, p, e, even);
    READ(none_of, p, e, even);
    READ(count_if, p, e, even);
    READ(find_if, p, e, even);
    READ(find_if_not, p, e, even);
    READ(adjacent_find, p, e);
    READ(adjacent_find, p, e, eq);
    READ(is_partitioned, p, e, even);
    READ(is_sorted, p, e);
    READ(is_sorted, p, e, less);
    READ(is_sorted_until, p, e);
    READ(is_sorted_until, p, e, less);
    READ(is_heap, p, e);
    READ(is_heap, p, e, less);
    READ(is_heap_until, p, e);
    READ(is_heap_until, p, e, less);
    READ(min_element, p, e);
    READ(min_element, p, e, less);
    READ(max_element, p, e);
    READ(max_element, p, e, less);
    PAIR(minmax_element, p, e);
    PAIR(minmax_element, p, e, less);
    for (int x = -2; x <= 3; ++x) {
        READ(count, p, e, x);
        READ(find, p, e, x);
        READ(search_n, p, e, x, 1);
        READ(search_n, p, e, x, 1, eq);
    }
    for (int n = 0; n <= 2; ++n) {
        READ(search, p, e, pattern, pattern + n);
        READ(search, p, e, pattern, pattern + n, eq);
        READ(find_end, p, e, pattern, pattern + n);
        READ(find_end, p, e, pattern, pattern + n, eq);
        READ(find_first_of, p, e, pattern, pattern + n);
        READ(find_first_of, p, e, pattern, pattern + n, eq);
        READ(equal, p, e, pattern, pattern + n);
        READ(equal, p, e, pattern, pattern + n, eq);
        PAIR(mismatch, p, e, pattern, pattern + n);
        PAIR(mismatch, p, e, pattern, pattern + n, eq);
        READ(is_permutation, p, e, pattern, pattern + n);
        READ(is_permutation, p, e, pattern, pattern + n, eq);
        READ(lexicographical_compare, p, e, pattern, pattern + n);
        READ(lexicographical_compare, p, e, pattern, pattern + n, less);
    }
    const auto searcher = [=](const int* first, const int* last) {
        const auto match = std::find(first, last, 1);
        return std::make_pair(match, match == last ? match : match + 1);
    };
    READ(search, p, e, searcher);
    READ(equal, p, e, p);
    READ(equal, p, e, p, eq);
    PAIR(mismatch, p, e, p);
    PAIR(mismatch, p, e, p, eq);
    READ(is_permutation, p, e, p);
    READ(is_permutation, p, e, p, eq);
    return true;
}

using buffer = std::array<int, 20>;

// Invoke the same operation with independent output buffers. Compare the returned
// end iterator, all written elements, and the canaries outside the output range.
template <class Asc, class Ref>
bool writes(Asc asc, Ref ref)
{
    buffer a{}, b{};
    a.fill(81);
    b.fill(81);
    const auto end_a = asc(a.data() + 1);
    const auto end_b = ref(b.data() + 1);
    return end_a - a.data() == end_b - b.data() && a == b;
}

#define WRITE(name, ...) \
    CHECK(writes(        \
        [&](int* out) { return asc::std::name(__VA_ARGS__); }, [&](int* out) { return std::name(__VA_ARGS__); }))

bool copy_and_order(const int* p, int count)
{
    const int* e = p + count;
    const std::equal_to<int> eq;
    const std::less<int> less;
    const auto even = [](int v) { return v % 2 == 0; };
    const auto cube = [](int v) { return v * v * v; };
    WRITE(copy, p, e, out);
    WRITE(copy_n, p, count, out);
    WRITE(copy_backward, p, e, out + count);
    WRITE(move, p, e, out);
    WRITE(move_backward, p, e, out + count);
    WRITE(reverse_copy, p, e, out);
    WRITE(copy_if, p, e, out, even);
    WRITE(remove_copy, p, e, out, 2);
    WRITE(remove_copy_if, p, e, out, even);
    WRITE(replace_copy, p, e, out, 1, 42);
    WRITE(replace_copy_if, p, e, out, even, 42);
    WRITE(unique_copy, p, e, out);
    WRITE(unique_copy, p, e, out, eq);
    WRITE(transform, p, e, out, cube);
    WRITE(transform, p, e, p, out, std::plus<int>{});
    for (int mid = 0; mid <= count; ++mid) {
        WRITE(rotate_copy, p, p + mid, e, out);
        WRITE(partial_sort_copy, p, e, out, out + mid);
        WRITE(partial_sort_copy, p, e, out, out + mid, less);
    }
    int lo = -2, hi = 2;
    const std::greater<int> greater;
    READ(min, lo, hi);
    READ(max, lo, hi);
    READ(min, lo, hi, greater);
    READ(max, lo, hi, greater);
    PAIR(minmax, lo, hi);
    PAIR(minmax, lo, hi, greater);
    for (const int* i = p; i != e; ++i) {
        READ(clamp, *i, lo, hi);
        READ(clamp, *i, hi, lo, greater);
    }
    buffer sorted{};
    std::copy(p, e, sorted.begin());
    std::sort(sorted.begin(), sorted.begin() + count);
    const int* s = sorted.data();
    const int* last = s + count;
    const int keys[] = {-1, 0, 1, 1, 2};
    for (int key = -3; key <= 4; ++key) {
        READ(binary_search, s, last, key);
        READ(binary_search, s, last, key, less);
        READ(lower_bound, s, last, key);
        READ(lower_bound, s, last, key, less);
        READ(upper_bound, s, last, key);
        READ(upper_bound, s, last, key, less);
        PAIR(equal_range, s, last, key);
        PAIR(equal_range, s, last, key, less);
        auto before = [=](int x) { return x < key; };
        READ(partition_point, s, last, before);
    }
    for (int n = 0; n <= 5; ++n) {
        READ(includes, s, last, keys, keys + n);
        READ(includes, s, last, keys, keys + n, less);
        WRITE(merge, s, last, keys, keys + n, out);
        WRITE(merge, s, last, keys, keys + n, out, less);
        WRITE(set_difference, s, last, keys, keys + n, out);
        WRITE(set_difference, s, last, keys, keys + n, out, less);
        WRITE(set_intersection, s, last, keys, keys + n, out);
        WRITE(set_intersection, s, last, keys, keys + n, out, less);
        WRITE(set_union, s, last, keys, keys + n, out);
        WRITE(set_union, s, last, keys, keys + n, out, less);
        WRITE(set_symmetric_difference, s, last, keys, keys + n, out);
        WRITE(set_symmetric_difference, s, last, keys, keys + n, out, less);
    }
    int positive[10] = {}, negative[10] = {};
    const auto split = asc::std::partition_copy(p, e, positive, negative, even);
    int positives = 0, negatives = 0;
    for (const int* i = p; i != e; ++i) {
        CHECK(even(*i) ? positive[positives++] == *i : negative[negatives++] == *i);
    }
    CHECK(split.first == positive + positives && split.second == negative + negatives);
    return true;
}

bool mutate(const int* p, int n)
{
    const auto even = [](int x) { return x % 2 == 0; };
    buffer a{}, b{};
    const auto restore = [&]() {
        std::copy_n(p, n, a.begin());
        b = a;
    };
    auto* x = a.data();
    auto* y = b.data();
    restore();
    CHECK(asc::std::fill_n(x, n, 92) == x + n);
    asc::std::fill(y, y + n, 92);
    CHECK(a == b);
    int next_a = 0, next_b = 0;
    asc::std::generate(x, x + n, [&] { return ++next_a; });
    CHECK(asc::std::generate_n(y, n, [&] { return ++next_b; }) == y + n && a == b);
    asc::std::for_each(x, x + n, [](int& v) { v *= 2; });
    CHECK(asc::std::for_each_n(y, n, [](int& v) { v *= 2; }) == y + n && a == b);
    restore();
    asc::std::replace(x, x + n, 1, 40);
    std::replace(y, y + n, 1, 40);
    asc::std::replace_if(x, x + n, even, 3);
    std::replace_if(y, y + n, even, 3);
    CHECK(a == b);
    restore();
    const auto output = asc::std::remove(x, x + n, 1);
    const auto reference = std::remove(y, y + n, 1);
    CHECK(output - x == reference - y && std::equal(x, output, y));
    restore();
    const auto odds = asc::std::remove_if(x, x + n, even);
    CHECK(odds - x == std::remove_if(y, y + n, even) - y && std::equal(x, odds, y));
    restore();
    const auto unique = asc::std::unique(x, x + n);
    CHECK(unique - x == std::unique(y, y + n) - y && std::equal(x, unique, y));
    restore();
    const auto same = std::equal_to<int>{};
    const auto custom_unique = asc::std::unique(x, x + n, same);
    CHECK(custom_unique - x == std::unique(y, y + n, same) - y && std::equal(x, custom_unique, y));

    for (int k = 0; k <= n; ++k) {
        restore();
        CHECK(asc::std::rotate(x, x + k, x + n) - x == std::rotate(y, y + k, y + n) - y && a == b);
        restore();
        CHECK(asc::std::shift_left(x, x + n, k) == x + n - k && std::equal(x, x + n - k, y + k));
        restore();
        CHECK(asc::std::shift_right(x, x + n, k) == x + k && std::equal(x + k, x + n, y));
    }
    for (int mid = 0; mid <= n; ++mid) {
        restore();
        asc::std::partial_sort(x, x + mid, x + n, std::greater<int>{});
        std::sort(y, y + n, std::greater<int>{});
        CHECK(std::equal(x, x + mid, y) && std::is_permutation(x, x + n, y));
        restore();
        std::sort(x, x + mid);
        std::sort(x + mid, x + n);
        std::sort(y, y + n);
        asc::std::inplace_merge(x, x + mid, x + n);
        CHECK(a == b);
    }
    restore();
    asc::std::stable_sort(x, x + n);
    std::stable_sort(y, y + n);
    CHECK(a == b);
    restore();
    asc::std::reverse(x, x + n);
    std::reverse(y, y + n);
    CHECK(a == b);
    restore();
    const auto pivot = asc::std::partition(x, x + n, even);
    CHECK(pivot - x == std::count_if(y, y + n, even) && std::is_partitioned(x, x + n, even));
    CHECK(std::is_permutation(x, x + n, y));
    restore();
    CHECK(asc::std::stable_partition(x, x + n, even) - x == std::stable_partition(y, y + n, even) - y && a == b);
    return true;
}

int main()
{
    const int values[] = {2, -1, 1, 2, 1, 0, 0};
    for (int first = 0; first <= 7; ++first) {
        for (int n = 0; n <= 7 - first; ++n) {
            const int* p = values + first;
            if (!inspect(p, n) || !copy_and_order(p, n) || !mutate(p, n))
                return 1;
        }
    }
    return asc_stl_test_algorithm::check();
}
