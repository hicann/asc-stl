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

#ifndef CANN_ASC_STL_ASC___BIT_OPERATIONS_H
#define CANN_ASC_STL_ASC___BIT_OPERATIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Host debug builds surface out-of-domain arguments through assert; device
// and release builds keep the silent clamp documented below.
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <asc/std/cassert>
#endif

// Bit extension backend for the later public <asc/bit> facade. The four
// primitives accept the supported unsigned integer types, are implemented
// with standard bit operations, and run in Host, ordinary AICore and pure
// SIMT. The public semantics do not depend on any single device instruction;
// a compiler may optimize them onto equivalents when available.
namespace asc::detail {

// The shift-loop is the deliberately portable default.  The dev-side
// reference additionally gates a hardware __brev path (pure SIMT on 950PR/DT
// with devkit >= 90200000, mixed vector cores always fall back), but that
// gate stays dark on every released devkit because the __brev lowering is
// still broken there, and this tree carries no 950-arch/devkit capability
// vocabulary to express it safely.  Wiring the intrinsic path requires the
// capability macros plus on-target CCE validation first; until then the loop
// below is the single implementation for every execution space.
template <class T>
CANN_ASC_STL_API constexpr T bit_reverse_impl(T value) noexcept
{
    T result = 0;
    for (int index = 0; index < static_cast<int>(sizeof(T)) * 8; ++index) {
        result = static_cast<T>(result << 1);
        result = static_cast<T>(result | (value & T{1}));
        value = static_cast<T>(value >> 1);
    }
    return result;
}

template <class T>
CANN_ASC_STL_API constexpr T bitmask_low_impl(int bits) noexcept
{
    return bits <= 0 ? T{0} :
                       static_cast<T>(bits >= static_cast<int>(sizeof(T)) * 8 ? static_cast<T>(~T{0}) :
                                                                                static_cast<T>((T{1} << bits) - 1));
}

template <class T>
CANN_ASC_STL_API constexpr T bitfield_extract_impl(T value, int position, int width) noexcept
{
    const int total = static_cast<int>(sizeof(T)) * 8;
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // The clamps below are a release/device safety net, not part of the
    // documented domain: debug Host builds fail fast on out-of-domain
    // arguments instead of silently returning a zero field.
    assert(width >= 0);
    assert(position >= 0 && position < total);
    assert(width <= total - position);
#endif
    if (width <= 0 || position < 0 || position >= total) {
        return T{0};
    }
    if (position + width > total) {
        width = total - position;
    }
    return static_cast<T>((value >> position) & bitmask_low_impl<T>(width));
}

template <class T>
CANN_ASC_STL_API constexpr T bitfield_insert_impl(T destination, T source, int position, int width) noexcept
{
    const int total = static_cast<int>(sizeof(T)) * 8;
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // Same debug fail-fast contract as bitfield_extract_impl.
    assert(width >= 0);
    assert(position >= 0 && position < total);
    assert(width <= total - position);
#endif
    if (width <= 0 || position < 0 || position >= total) {
        return destination;
    }
    if (position + width > total) {
        width = total - position;
    }
    const T mask = static_cast<T>(bitmask_low_impl<T>(width) << position);
    return static_cast<T>((destination & static_cast<T>(~mask)) | static_cast<T>((source << position) & mask));
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___BIT_OPERATIONS_H
