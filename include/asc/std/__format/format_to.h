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

#ifndef CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_TO_H
#define CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_TO_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__format/format_string.h>
#include <asc/std/__format/formatters/bool.h>
#include <asc/std/__format/formatters/char.h>
#include <asc/std/__format/formatters/int.h>
#include <asc/std/__format/formatters/str.h>
#include <asc/std/__format/output_buffer.h>

#if CANN_ASC_STL_DETAIL_HAS_CXX20()

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __format_detail {

CANN_ASC_STL_API constexpr void render_tail(
    output_buffer& buffer, input_pointer format, __SIZE_TYPE__ size, __SIZE_TYPE__ position) noexcept
{
    while (position < size) {
        if (position + 1 < size && format[position] == '{' && format[position + 1] == '{') {
            buffer.put('{');
            position += 2;
        } else if (position + 1 < size && format[position] == '}' && format[position + 1] == '}') {
            buffer.put('}');
            position += 2;
        } else {
            buffer.put(format[position++]);
        }
    }
}

// Loop scanner for one argument: copies literal text with escape handling up
// to the next replacement field, consumes exactly that field and writes its
// argument. The comma fold in render_all invokes this once per argument as a
// sibling call, so the call depth stays constant regardless of the argument
// count (AI Core device paths must not recurse).
template <class Argument>
CANN_ASC_STL_API constexpr void render_one(output_buffer& buffer, input_pointer format, __SIZE_TYPE__ size,
    __SIZE_TYPE__& position, Argument&& argument) noexcept
{
    while (position < size) {
        const char current = format[position++];
        if (current == '{' && position < size && format[position] == '{') {
            ++position;
            buffer.put('{');
            continue;
        }
        if (current == '}' && position < size && format[position] == '}') {
            ++position;
            buffer.put('}');
            continue;
        }
        if (current != '{') {
            buffer.put(current);
            continue;
        }
        unsigned int base = 10;
        bool upper = false;
        if (position + 2 < size && format[position] == ':') {
            const char presentation = format[position + 1];
            position += 2;
            base = presentation == 'x' || presentation == 'X' ?
                16U :
                (presentation == 'o' ? 8U : (presentation == 'b' ? 2U : 10U));
            upper = presentation == 'X';
        }
        while (position < size && format[position] != '}') {
            ++position;
        }
        if (position < size) {
            ++position;
        }
        write_argument(buffer, static_cast<Argument&&>(argument), base, upper);
        return;
    }
}

template <class... Args>
CANN_ASC_STL_API constexpr output_buffer render_all(
    char* output, __SIZE_TYPE__ capacity, format_string<Args...> format, Args&&... args) noexcept
{
    output_buffer buffer{output, capacity, 0};
    const input_pointer text = format.data();
    const __SIZE_TYPE__ size = format.size();
    __SIZE_TYPE__ position = 0;
    ((render_one(buffer, text, size, position, static_cast<Args&&>(args))), ...);
    render_tail(buffer, text, size, position);
    return buffer;
}

}  // namespace __format_detail

// Writes the formatted arguments into the caller-owned buffer and returns one
// past the last written character; the buffer is not bounded, the caller
// guarantees capacity.
template <class... Args>
CANN_ASC_STL_API constexpr char* format_to(char* output, format_string<Args...> format, Args&&... args) noexcept
{
    const auto result =
        __format_detail::render_all(output, static_cast<__SIZE_TYPE__>(-1), format, static_cast<Args&&>(args)...);
    return output + result.total;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_DETAIL_HAS_CXX20()

#endif  // CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_TO_H
