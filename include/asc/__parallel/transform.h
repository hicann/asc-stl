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

#ifndef CANN_ASC_STL_ASC___PARALLEL_TRANSFORM_H
#define CANN_ASC_STL_ASC___PARALLEL_TRANSFORM_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// BiSheng's optimized pure-SIMT lowering can stall on these value-based
// operations. Keep the workaround local to them; predicate overloads retain
// their normal optimization path. CANN_ASC_STL_DISABLE_BISHENG_WORKAROUND
// drops both attributes for A/B measurement after a compiler upgrade; the
// guard below must be re-pinned to the exact BiSheng version that reproduces
// the stall (and removed once that version is out of support) - define it
// with -D only, never in-tree.
#if !defined(CANN_ASC_STL_DISABLE_BISHENG_WORKAROUND) && \
    (defined(__CCE__) || defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__))
#define CANN_ASC_STL_DETAIL_REPLACE_NOINLINE __attribute__((noinline))
#define CANN_ASC_STL_DETAIL_REPLACE_COPY_NOINLINE __attribute__((optnone, noinline))
#else
#define CANN_ASC_STL_DETAIL_REPLACE_NOINLINE
#define CANN_ASC_STL_DETAIL_REPLACE_COPY_NOINLINE
#endif

namespace asc::detail {
template <class T>
CANN_ASC_STL_DEVICE_API void parallel_swap(T& left, T& right)
{
    T value = static_cast<T&&>(left);
    left = static_cast<T&&>(right);
    right = static_cast<T&&>(value);
}
// transform_operation stays as the sequential reference body of the
// element-wise copy/transform family: the runtime semantics suite (cannsim
// kernel) pins its exact braced layout. The copy/replace/swap frontends no
// longer keep serial twins here; they submit through the grid-stride channel
// at the bottom of this file.
template <class Input, class Output, class UnaryOperation>
struct transform_operation {
    Input first;
    Input last;
    Output result;
    UnaryOperation operation;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (Input current = first; current != last; ++current, ++result)
            *result = operation(*current);
    }
};
template <class Bidirectional>
struct reverse_operation {
    Bidirectional first;
    Bidirectional last;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        while (first != last) {
            --last;
            if (first == last)
                break;
            parallel_swap(*first, *last);
            ++first;
        }
    }
};
template <class Bidirectional, class Output>
struct reverse_copy_operation {
    Bidirectional first;
    Bidirectional last;
    Output result;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        while (first != last) {
            --last;
            *result = *last;
            ++result;
        }
    }
};
template <class Forward>
struct rotate_operation {
    Forward first;
    Forward middle;
    Forward last;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        // Swap-relay rotation (not move-relay): each step exchanges the two
        // ranges element-wise, re-anchoring on whichever side is exhausted
        // first, until the write cursor catches the read cursor.
        if (first == middle || middle == last)
            return;
        Forward write = first;
        Forward read = middle;
        while (write != read) {
            parallel_swap(*write, *read);
            ++write;
            ++read;
            if (read == last)
                read = middle;
            else if (write == middle)
                middle = read;
        }
    }
};
template <class Forward, class Output>
struct rotate_copy_operation {
    Forward first;
    Forward middle;
    Forward last;
    Output result;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (Forward current = middle; current != last; ++current, ++result)
            *result = *current;
        for (Forward current = first; current != middle; ++current, ++result)
            *result = *current;
    }
};
template <class Forward>
struct shift_left_operation {
    Forward first;
    Forward last;
    __SIZE_TYPE__ count;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        Forward source = first;
        for (__SIZE_TYPE__ index = 0; index < count && source != last; ++index)
            ++source;
        for (; source != last; ++source, ++first)
            *first = static_cast<decltype(*source)&&>(*source);
    }
};
template <class Random>
struct shift_right_operation {
    Random first;
    Random last;
    __SIZE_TYPE__ count;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        // Random access by contract (the length and target cursors below are
        // computed with iterator arithmetic), so the parameter is named for
        // the actual requirement.
        auto length = last - first;
        if (count >= static_cast<__SIZE_TYPE__>(length))
            return;
        Random source = last - static_cast<decltype(length)>(count);
        while (source != first) {
            --source;
            --last;
            *last = static_cast<decltype(*source)&&>(*source);
        }
    }
};
// Grid-stride companions of the element-wise operations, shaped for the
// coordinate-parameterized kernel: each device thread visits the elements
// whose linear index is congruent to its thread index modulo the total thread
// count, so every element is still read and written exactly once while the
// launch spans the whole grid. copy/copy_n share one body through the count
// parameter; the value-based replace twins carry the BiSheng lowering
// workaround attributes on their hot paths, mirroring the historical serial
// twins they replaced.
template <class Input, class Output, class UnaryOperation>
struct grid_strided_transform_operation {
    Input first;
    __SIZE_TYPE__ count;
    Output result;
    UnaryOperation operation;
    CANN_ASC_STL_DEVICE_API void operator()(__SIZE_TYPE__ index, __SIZE_TYPE__ stride)
    {
        for (; index < count; index += stride) {
            result[index] = operation(first[index]);
        }
    }
};
template <class Input, class Output>
struct grid_strided_copy_operation {
    Input first;
    __SIZE_TYPE__ count;
    Output result;
    CANN_ASC_STL_DEVICE_API void operator()(__SIZE_TYPE__ index, __SIZE_TYPE__ stride)
    {
        for (; index < count; index += stride)
            result[index] = first[index];
    }
};
template <class Forward, class T>
struct grid_strided_replace_value_operation {
    Forward first;
    __SIZE_TYPE__ count;
    T old_value;
    T new_value;
    CANN_ASC_STL_DEVICE_API CANN_ASC_STL_DETAIL_REPLACE_NOINLINE void operator()(
        __SIZE_TYPE__ index, __SIZE_TYPE__ stride)
    {
        for (; index < count; index += stride)
            if (first[index] == old_value)
                first[index] = new_value;
    }
};
template <class Forward, class T, class Predicate>
struct grid_strided_replace_operation {
    Forward first;
    __SIZE_TYPE__ count;
    Predicate predicate;
    T value;
    CANN_ASC_STL_DEVICE_API void operator()(__SIZE_TYPE__ index, __SIZE_TYPE__ stride)
    {
        for (; index < count; index += stride)
            if (predicate(first[index]))
                first[index] = value;
    }
};
template <class Input, class Output, class T, class Predicate>
struct grid_strided_replace_copy_operation {
    Input first;
    __SIZE_TYPE__ count;
    Output result;
    Predicate predicate;
    T value;
    CANN_ASC_STL_DEVICE_API void operator()(__SIZE_TYPE__ index, __SIZE_TYPE__ stride)
    {
        for (; index < count; index += stride)
            result[index] = predicate(first[index]) ? value : first[index];
    }
};
template <class Input, class Output, class T, class Predicate>
struct grid_strided_replace_copy_equal_operation {
    Input first;
    __SIZE_TYPE__ count;
    Output result;
    Predicate predicate;
    T value;
    CANN_ASC_STL_DEVICE_API CANN_ASC_STL_DETAIL_REPLACE_COPY_NOINLINE void operator()(
        __SIZE_TYPE__ index, __SIZE_TYPE__ stride)
    {
        for (; index < count; index += stride)
            result[index] = predicate(first[index]) ? value : first[index];
    }
};
template <class Forward1, class Forward2>
struct grid_strided_swap_ranges_operation {
    Forward1 first;
    __SIZE_TYPE__ count;
    Forward2 second;
    CANN_ASC_STL_DEVICE_API void operator()(__SIZE_TYPE__ index, __SIZE_TYPE__ stride)
    {
        for (; index < count; index += stride)
            parallel_swap(first[index], second[index]);
    }
};
}  // namespace asc::detail

#undef CANN_ASC_STL_DETAIL_REPLACE_NOINLINE
#undef CANN_ASC_STL_DETAIL_REPLACE_COPY_NOINLINE

#endif  // CANN_ASC_STL_ASC___PARALLEL_TRANSFORM_H
