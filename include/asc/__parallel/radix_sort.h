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

#ifndef CANN_ASC_STL_ASC___PARALLEL_RADIX_SORT_H
#define CANN_ASC_STL_ASC___PARALLEL_RADIX_SORT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>

namespace asc::detail {

// Element type a random-access iterator range yields, with cv stripped.
template <class Iterator>
using range_element = typename asc::std::remove_cvref<decltype(*asc::std::declval<Iterator&>())>::type;

// Below this element count the sort kernels keep the insertion path: the
// histogram/scatter machinery does not pay off for tiny ranges.
constexpr __SIZE_TYPE__ sort_insertion_threshold = 32;

// Sorts [first, last) by moving each element behind the last one that compares
// not-greater into the sorted prefix. Stable, O(n^2) comparisons; serves as
// the small-range and storage-less fallback of both sort kernels.
template <class Random, class Compare>
CANN_ASC_STL_DEVICE_API void insertion_sort_range(Random first, Random last, Compare compare)
{
    for (Random current = first + 1; current != last; ++current) {
        auto value = static_cast<decltype(*current)&&>(*current);
        Random position = current;
        while (position != first && compare(value, *(position - 1))) {
            *position = static_cast<decltype(*(position - 1))&&>(*(position - 1));
            --position;
        }
        *position = static_cast<decltype(value)&&>(value);
    }
}

// Maps an arithmetic key of at most eight bytes onto an unsigned bit pattern
// that preserves the natural ordering of the key type: signed integers flip
// their sign bit, IEEE-754 floating point keys flip every bit of negative
// values and set the sign bit of nonnegative ones.
template <class Element>
CANN_ASC_STL_DEVICE_API unsigned long long radix_key_pattern(const Element& value)
{
    static_assert(sizeof(Element) <= sizeof(unsigned long long), "radix key pattern must fit one pattern word");
    if constexpr (asc::std::is_floating_point<Element>::value) {
        unsigned long long bits = 0;
        const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
        for (__SIZE_TYPE__ index = 0; index < sizeof(Element); ++index) {
            bits |= static_cast<unsigned long long>(bytes[index]) << (8 * index);
        }
        const unsigned long long sign = 1ULL << (8 * sizeof(Element) - 1);
        return (bits & sign) != 0 ? ~bits : bits | sign;
    } else {
        // Conversion to the unsigned pattern wraps modulo 2^64, so the low
        // bytes are the two's-complement representation of the value.
        unsigned long long bits = static_cast<unsigned long long>(value);
        if (!asc::std::is_unsigned<Element>::value) {
            bits ^= 1ULL << (8 * sizeof(Element) - 1);
        }
        return bits;
    }
}

// Least-significant-digit radix sort over natural-order arithmetic keys: one
// pass per key byte, each pass histogramming the 8-bit digit, prefix-summing
// the histogram into scatter offsets and stably scattering the elements
// through the scratch buffer. Non-recursive; O(n) work per pass, one pass per
// key byte. Both scratch areas are carved out of the policy temporary storage
// by the sort frontend: histogram holds 256 counters and scratch holds one
// element copy per input element. Braced construction with only {first, last,
// compare} leaves the scratch pointers null and takes the insertion path, so
// storage-less callers keep working.
template <class Random, class Compare>
struct radix_sort_operation {
    using element = range_element<Random>;

    Random first;
    Random last;
    Compare compare;
    __SIZE_TYPE__* histogram;
    element* scratch;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
        if (count < 2) {
            return;
        }
        if (count < sort_insertion_threshold || histogram == nullptr || scratch == nullptr) {
            insertion_sort_range(first, last, compare);
            return;
        }
        static_assert(sizeof(element) <= sizeof(unsigned long long), "radix keys must fit one pattern word");
        for (__SIZE_TYPE__ pass = 0; pass < sizeof(element); ++pass) {
            for (__SIZE_TYPE__ digit = 0; digit < 256; ++digit) {
                histogram[digit] = 0;
            }
            for (__SIZE_TYPE__ index = 0; index < count; ++index) {
                const __SIZE_TYPE__ digit = (radix_key_pattern(first[index]) >> (8 * pass)) & 0xFF;
                ++histogram[digit];
            }
            __SIZE_TYPE__ total = 0;
            for (__SIZE_TYPE__ digit = 0; digit < 256; ++digit) {
                const __SIZE_TYPE__ occurrences = histogram[digit];
                histogram[digit] = total;
                total += occurrences;
            }
            for (__SIZE_TYPE__ index = 0; index < count; ++index) {
                const __SIZE_TYPE__ digit = (radix_key_pattern(first[index]) >> (8 * pass)) & 0xFF;
                scratch[histogram[digit]] = static_cast<decltype(first[index])&&>(first[index]);
                ++histogram[digit];
            }
            for (__SIZE_TYPE__ index = 0; index < count; ++index) {
                first[index] = static_cast<decltype(scratch[index])&&>(scratch[index]);
            }
        }
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_RADIX_SORT_H
