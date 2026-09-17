/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_MEMORY_TEMPORARY_BUFFER_H
#define CANN_ASC_STL_STD_DETAIL_MEMORY_TEMPORARY_BUFFER_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__memory/construct_at.h>
#include <asc/std/__new/allocate.h>
#include <asc/std/__type_traits/alignment_of.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/climits>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// Three-tier design (mirrors __new/allocate.h, which declares both host and device):
// (1) Host: delegates to host operator new/delete (including the align_val_t
//     overloads).
// (2) SIMT device (devkit >= 9.2): delegates to the compiler-provided device
//     new/delete override through the SIMT branch of __new/allocate.h
//     (dpp_alloc/dpp_dealloc, pluggable runtime). The device override has no
//     align_val_t form: over-aligned requests (device-side max_align_t == 8,
//     measured on real hardware) return an empty buffer, mirroring the
//     unaligned-new branch; the halve-and-retry loop relies on dpp_alloc
//     returning 0 on exhaustion.
// (3) Mixed/vector-kernel device: no definition (a call produces a clear link
//     diagnostic).
// Ordering: a SIMT translation unit contains both host and device contexts, so the
// SIMT device context must be tested first (same as allocate.h/gamma.h).
#if CANN_ASC_STL_DETAIL_HAS_DEVICE_HEAP()
// Self-contained version query: SIMT builds do not necessarily -include the devkit version header.
#if defined(__has_include)
#if __has_include(<version/asc_devkit_version.h>)
#include <version/asc_devkit_version.h>
#elif __has_include(<ascendc/asc_devkit_version.h>)
#include <ascendc/asc_devkit_version.h>
#endif
#endif
#if defined(ASC_DEVKIT_VERSION_NUM) && ASC_DEVKIT_VERSION_NUM >= 90200000
#define CANN_ASC_STL_DETAIL_TEMPBUF_SIMT 1
#endif
#elif CANN_ASC_STL_DETAIL_HOSTED()
#define CANN_ASC_STL_DETAIL_TEMPBUF_HOST 1
#include <asc/std/__host_stdlib/new>
#endif

#if CANN_ASC_STL_DETAIL_TEMPBUF_HOST

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_HOST_API pair<_Tp*, ptrdiff_t> get_temporary_buffer(ptrdiff_t __n) noexcept
{
    pair<_Tp*, ptrdiff_t> __r(nullptr, 0);
    const ptrdiff_t __m = (~ptrdiff_t(0) ^ ptrdiff_t(ptrdiff_t(1) << (sizeof(ptrdiff_t) * CHAR_BIT - 1))) / sizeof(_Tp);
    if (__n > __m) {
        __n = __m;
    }
    while (__n > 0) {
#if CANN_ASC_STL_DETAIL_ACCL_HAS_ALIGNED_ALLOCATION()
        if (__is_overaligned_for_new(alignof(_Tp))) {
            ::asc::std::align_val_t __al = ::asc::std::align_val_t(::asc::std::alignment_of<_Tp>::value);
            __r.first = static_cast<_Tp*>(::operator new(__n * sizeof(_Tp), __al));
        } else {
            __r.first = static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
        }
#else   // ^^^ HAS_ALIGNED_ALLOCATION ^^^ / vvv !aligned ^^^
        if (__is_overaligned_for_new(alignof(_Tp))) {
            // Since aligned operator new is unavailable, return an empty
            // buffer rather than one with invalid alignment.
            return __r;
        }

        __r.first = static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
#endif  // !CANN_ASC_STL_DETAIL_ACCL_HAS_ALIGNED_ALLOCATION()

        if (__r.first) {
            __r.second = __n;
            break;
        }
        __n /= 2;
    }
    return __r;
}

template <class _Tp>
CANN_ASC_STL_HOST_API void return_temporary_buffer(_Tp* __p) noexcept
{
    ::asc::std::__asc_deallocate_unsized(static_cast<void*>(__p), alignof(_Tp));
}

struct __return_temporary_buffer {
    template <class _Tp>
    CANN_ASC_STL_HOST_API void operator()(_Tp* __p) const noexcept
    {
        ::asc::std::return_temporary_buffer(__p);
    }
};

#elif CANN_ASC_STL_DETAIL_TEMPBUF_SIMT

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API pair<_Tp*, ptrdiff_t> get_temporary_buffer(ptrdiff_t __n) noexcept
{
    pair<_Tp*, ptrdiff_t> __r(nullptr, 0);  // NOLINT(build/include_what_you_use)
    const ptrdiff_t __m = (~ptrdiff_t(0) ^ ptrdiff_t(ptrdiff_t(1) << (sizeof(ptrdiff_t) * CHAR_BIT - 1))) / sizeof(_Tp);
    if (__n > __m) {
        __n = __m;
    }
    while (__n > 0) {
        if (__is_overaligned_for_new(alignof(_Tp))) {
            // The device new override has no align_val_t form (dpp_alloc takes no alignment
            // argument): over-aligned requests return an empty buffer instead of a misaligned one.
            return __r;
        }
        __r.first = static_cast<_Tp*>(::asc::std::__asc_operator_new(__n * sizeof(_Tp)));
        if (__r.first) {
            __r.second = __n;
            break;
        }
        __n /= 2;  // dpp_alloc signals exhaustion by returning 0: halve and retry
    }
    return __r;
}

template <class _Tp>
CANN_ASC_STL_API void return_temporary_buffer(_Tp* __p) noexcept
{
    ::asc::std::__asc_deallocate_unsized(static_cast<void*>(__p), alignof(_Tp));
}

struct __return_temporary_buffer {
    template <class _Tp>
    CANN_ASC_STL_API void operator()(_Tp* __p) const noexcept
    {
        ::asc::std::return_temporary_buffer(__p);
    }
};

#else
// Mixed/vector-kernel device: no definition (a call produces a clear link diagnostic instead of a silent wrong value).
#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MEMORY_TEMPORARY_BUFFER_H
