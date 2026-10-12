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

#include <asc/execution>
#include <asc/launch>
namespace asc::detail {
template <class T>
CANN_ASC_STL_DEVICE_API void parallel_swap(T& left, T& right)
{
    T value = static_cast<T&&>(left);
    left = static_cast<T&&>(right);
    right = static_cast<T&&>(value);
}
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
template <class Input, class Output>
struct copy_operation {
    Input first;
    Input last;
    Output result;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (Input current = first; current != last; ++current, ++result)
            *result = *current;
    }
};
template <class Input, class Size, class Output>
struct copy_n_operation {
    Input first;
    Size count;
    Output result;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (Size index{}; index < count; ++index)
            result[index] = first[index];
    }
};
template <class Forward, class T, class Predicate>
struct replace_operation {
    Forward first;
    Forward last;
    Predicate predicate;
    T value;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (Forward current = first; current != last; ++current)
            if (predicate(*current))
                *current = value;
    }
};
template <class Input, class Output, class T, class Predicate>
struct replace_copy_operation {
    Input first;
    Input last;
    Output result;
    Predicate predicate;
    T value;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (Input current = first; current != last; ++current, ++result) {
            *result = predicate(*current) ? value : *current;
        }
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
template <class Bidirectional>
struct shift_right_operation {
    Bidirectional first;
    Bidirectional last;
    __SIZE_TYPE__ count;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        auto length = last - first;
        if (count >= static_cast<__SIZE_TYPE__>(length))
            return;
        Bidirectional source = last - static_cast<decltype(length)>(count);
        while (source != first) {
            --source;
            --last;
            *last = static_cast<decltype(*source)&&>(*source);
        }
    }
};
template <class Forward1, class Forward2>
struct swap_ranges_operation {
    Forward1 first;
    Forward1 last;
    Forward2 second;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (; first != last; ++first, ++second)
            parallel_swap(*first, *second);
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_TRANSFORM_H
