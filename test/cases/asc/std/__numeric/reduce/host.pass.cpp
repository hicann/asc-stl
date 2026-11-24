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

#include <asc/std/__functional/operations.h>
#include <asc/std/__numeric/adjacent_difference.h>
#include <asc/std/__numeric/device_policy.h>
#include <asc/std/__numeric/inclusive_scan.h>
#include <asc/std/__numeric/partial_sum.h>
#include <asc/std/__numeric/reduce.h>
#include <asc/std/__numeric/transform_inclusive_scan.h>
#include <asc/std/__numeric/transform_reduce.h>

#include <cassert>
#include <string>

int main()
{
    constexpr int data[6]{1, 2, 3, 4, 5, 6};

    // reduce: empty range returns the init value; the value_type form starts
    // from a default-constructed accumulator.
    assert(asc::std::reduce(data, data) == 0);
    assert(asc::std::reduce(data, data, 10) == 10);
    assert(asc::std::reduce(data, data + 6) == 21);
    assert(asc::std::reduce(data, data + 6, 100) == 121);
    assert(asc::std::reduce(data, data + 6, 1, [](int total, int value) { return total * value; }) == 720);

    // transform_reduce: inner-product, two-range and unary forms.
    assert(asc::std::transform_reduce(data, data, data, 5) == 5);
    assert(asc::std::transform_reduce(data, data + 3, data, 0) == 14);
    assert(asc::std::transform_reduce(data, data + 6, data, 0) == 91);
    assert(asc::std::transform_reduce(
               data, data + 3, data, 0, [](int total, int value) { return total + value; },
               [](int left, int right) { return left * right + 1; }) == 17);
    assert(asc::std::transform_reduce(
               data, data + 4, 0, [](int total, int value) { return total + value; },
               [](int value) { return value * value; }) == 30);

    // inclusive_scan: empty range, init-free and init forms.
    int scanned[6]{};
    assert(asc::std::inclusive_scan(data, data, scanned) == scanned);
    assert(asc::std::inclusive_scan(data, data + 6, scanned) == scanned + 6);
    assert(scanned[0] == 1 && scanned[1] == 3 && scanned[2] == 6 && scanned[3] == 10 && scanned[4] == 15 &&
        scanned[5] == 21);
    assert(asc::std::inclusive_scan(data, data + 5, scanned, [](int total, int value) { return total * value; }) ==
        scanned + 5);
    assert(scanned[0] == 1 && scanned[1] == 2 && scanned[2] == 6 && scanned[3] == 24 && scanned[4] == 120);
    assert(asc::std::inclusive_scan(
               data, data + 5, scanned, [](int total, int value) { return total * value; }, 2) == scanned + 5);
    assert(scanned[0] == 2 && scanned[1] == 4 && scanned[2] == 12 && scanned[3] == 48 && scanned[4] == 240);

    // transform_inclusive_scan: the first output folds the transform of the
    // first element, with or without an initial value.
    assert(asc::std::transform_inclusive_scan(
               data, data + 4, scanned, [](int total, int value) { return total + value; },
               [](int value) { return value * 2; }) == scanned + 4);
    assert(scanned[0] == 2 && scanned[1] == 6 && scanned[2] == 12 && scanned[3] == 20);
    assert(asc::std::transform_inclusive_scan(
               data, data + 4, scanned, [](int total, int value) { return total + value; },
               [](int value) { return value * 2; }, 10) == scanned + 4);
    assert(scanned[0] == 12 && scanned[1] == 16 && scanned[2] == 22 && scanned[3] == 30);

    const unsigned char bytes[]{200, 100, 60};
    assert(asc::std::transform_inclusive_scan(
               bytes, bytes + 3, scanned, asc::std::plus<int>{},
               [](unsigned char value) { return static_cast<int>(value); }, int{0}) == scanned + 3);
    assert(scanned[0] == 200 && scanned[1] == 300 && scanned[2] == 360);

    // partial_sum keeps the classic prefix behaviour.
    assert(asc::std::partial_sum(data, data, scanned) == scanned);
    assert(asc::std::partial_sum(data, data + 5, scanned) == scanned + 5);
    assert(scanned[0] == 1 && scanned[1] == 3 && scanned[2] == 6 && scanned[3] == 10 && scanned[4] == 15);
    assert(asc::std::partial_sum(data, data + 5, scanned, [](int total, int value) { return total * value; }) ==
        scanned + 5);
    assert(scanned[0] == 1 && scanned[1] == 2 && scanned[2] == 6 && scanned[3] == 24 && scanned[4] == 120);

    // adjacent_difference keeps the first element unchanged.
    const int sequence[5]{10, 6, 7, 9, 4};
    int differences[5]{};
    assert(asc::std::adjacent_difference(sequence, sequence, differences) == differences);
    assert(asc::std::adjacent_difference(sequence, sequence + 5, differences) == differences + 5);
    assert(differences[0] == 10 && differences[1] == -4 && differences[2] == 1 && differences[3] == 2 &&
        differences[4] == -5);
    assert(asc::std::adjacent_difference(sequence, sequence + 3, differences,
               [](int current, int previous) { return current * previous; }) == differences + 3);
    assert(differences[0] == 10 && differences[1] == 60 && differences[2] == 42);

    // A non-integral accumulation type exercises the generic folds.
    const std::string words[3]{"a", "b", "c"};
    assert(asc::std::reduce(words, words + 3, std::string("x")) == "xabc");

    // Constant expressions cover the sequential baseline.
    static_assert(asc::std::reduce(data, data + 6) == 21);
    static_assert(asc::std::reduce(data, data + 3, 0) == 6);
    return 0;
}
