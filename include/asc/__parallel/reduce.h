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

#ifndef CANN_ASC_STL_ASC___PARALLEL_REDUCE_H
#define CANN_ASC_STL_ASC___PARALLEL_REDUCE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {
// Sequential-semantics baseline: the reductions below are strict left folds,
// so their results (including floating-point rounding) are run-to-run
// deterministic without relying on associativity. Parallelization path
// (later runtime work, kept as an anchor): fixed-shape two-phase reduction -
// each block folds its slice serially left-to-right into a partial slot, a
// second pass combines the partials in ascending block order. Both the shape
// and the combination order stay fixed, keeping float results deterministic;
// free atomic accumulation must stay out because its result depends on thread
// arrival order.
template <class Input, class T, class BinaryOperation, class UnaryOperation>
struct transform_reduce_operation {
    Input first;
    Input last;
    T init;
    T* output;
    BinaryOperation binary;
    UnaryOperation unary;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        T value = init;
        for (; first != last; ++first)
            value = binary(value, unary(*first));
        *output = value;
    }
};
template <class Input, class T, class BinaryOperation>
struct reduce_operation {
    Input first;
    Input last;
    T init;
    T* output;
    BinaryOperation operation;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        T value = init;
        for (; first != last; ++first)
            value = operation(value, *first);
        *output = value;
    }
};
template <class Input, class Predicate>
struct count_operation {
    Input first;
    Input last;
    __SIZE_TYPE__* output;
    Predicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        __SIZE_TYPE__ value{};
        for (; first != last; ++first)
            if (predicate(*first))
                ++value;
        *output = value;
    }
};
template <class Input, class Predicate>
struct bool_reduce_operation {
    Input first;
    Input last;
    unsigned int* output;
    Predicate predicate;
    bool require_all;
    bool invert;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        // Deliberately no short circuit: the whole range is scanned even once
        // the accumulator is decided. A parallel evaluation cannot stop on the
        // first deciding element anyway, and for pure predicates the trailing
        // evaluations are unobservable, so the full scan keeps the serial and
        // the future parallel contract identical.
        bool value = require_all;
        for (; first != last; ++first) {
            bool current = predicate(*first);
            if (invert)
                current = !current;
            value = require_all ? value && current : value || current;
        }
        *output = value ? 1U : 0U;
    }
};
template <class Input1, class Input2, class BinaryPredicate>
struct equal_operation {
    Input1 first1;
    Input1 last1;
    Input2 first2;
    Input2 last2;
    unsigned int* output;
    BinaryPredicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        while (first1 != last1 && first2 != last2) {
            if (!predicate(*first1, *first2)) {
                *output = 0;
                return;
            }
            ++first1;
            ++first2;
        }
        *output = first1 == last1 && first2 == last2 ? 1U : 0U;
    }
};
template <class Forward, class Compare>
struct extremum_operation {
    Forward first;
    Forward last;
    __SIZE_TYPE__* output;
    Compare compare;
    bool maximum;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        if (first == last) {
            *output = 0;
            return;
        }
        // The comparison direction is selected once before the loop instead
        // of per element; strict comparison keeps the first extremum, matching
        // std::min_element/std::max_element.
        Forward best = first;
        __SIZE_TYPE__ best_index{};
        __SIZE_TYPE__ index = 1;
        if (maximum) {
            for (++first; first != last; ++first, ++index) {
                if (compare(*best, *first)) {
                    best = first;
                    best_index = index;
                }
            }
        } else {
            for (++first; first != last; ++first, ++index) {
                if (compare(*first, *best)) {
                    best = first;
                    best_index = index;
                }
            }
        }
        *output = best_index;
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_REDUCE_H
