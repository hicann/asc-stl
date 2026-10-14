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

#ifndef CANN_ASC_STL_ASC___WORK_QUEUE_CURSOR_H
#define CANN_ASC_STL_ASC___WORK_QUEUE_CURSOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__atomic/backend.h>

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
#include <c_api/scalar_compute/scalar_compute.h>
#endif

namespace asc::detail {

// Some ordinary-AICore compiler revisions lower a uint64_t relational
// comparison through the signed 64-bit predicate.  Compare the two words
// explicitly so indices at and above 2^63 retain unsigned ordering.
// Regression anchor: this workaround was required by the ordinary-AICore
// toolchain revisions the product was validated on (the signed-predicate
// lowering).  When a newer toolchain is adopted, re-probe a plain `<` on
// values straddling 2^63 before simplifying this back.
CANN_ASC_STL_API constexpr bool work_uint64_less(__UINT64_TYPE__ lhs, __UINT64_TYPE__ rhs) noexcept
{
    const __UINT32_TYPE__ lhs_high = static_cast<__UINT32_TYPE__>(lhs >> 32);
    const __UINT32_TYPE__ rhs_high = static_cast<__UINT32_TYPE__>(rhs >> 32);
    return lhs_high < rhs_high ||
        (lhs_high == rhs_high && static_cast<__UINT32_TYPE__>(lhs) < static_cast<__UINT32_TYPE__>(rhs));
}

// Stop of the chunk claimed at current: "cursor + grain size must not
// overflow" is a documented caller precondition of the queue, and a violated
// one must not wrap into an inverted chunk (a wrapped stop is small, passes
// the less-than test and yields end < begin).  A stop that cannot be
// represented saturates to the maximum instead, where the end bound wins the
// clamp exactly as the unrepresentable true stop would - the final chunk
// then still covers [current, end).
CANN_ASC_STL_API constexpr __UINT64_TYPE__ work_saturating_stop(
    __UINT64_TYPE__ current, __UINT64_TYPE__ grain_size) noexcept
{
    constexpr __UINT64_TYPE__ maximum = ~static_cast<__UINT64_TYPE__>(0);
    return current > maximum - grain_size ? maximum : current + grain_size;
}

// Caller-owned global-memory work cursor for dynamic work claiming.  The cell
// must live in caller-owned GM storage; a claim advances the cursor by the
// grain size with a relaxed fetch-add and is then clamped to the end bound.
// The member claim is callable on Host and in pure SIMT (adapter/builtin).
// Ordinary AICore cannot lower a generic fetch-add on global memory, so its
// core claim goes through the __gm__-qualified cell via work_cursor_try_claim.
struct work_cursor {
    __UINT64_TYPE__ next;
    __UINT64_TYPE__ end;
    __UINT64_TYPE__ grain_size;

    CANN_ASC_STL_API constexpr work_cursor() noexcept : next(0), end(0), grain_size(1)
    {}
    CANN_ASC_STL_API constexpr work_cursor(__UINT64_TYPE__ first, __UINT64_TYPE__ last, __UINT64_TYPE__ grain) noexcept
        : next(first), end(last), grain_size(grain > 0 ? grain : 1)
    {}

    CANN_ASC_STL_HOST_SIMT_API bool try_claim(__UINT64_TYPE__& claimed_begin, __UINT64_TYPE__& claimed_end) noexcept
    {
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
        const __UINT64_TYPE__ current = atomic_add(&next, grain_size);
#else
        const __UINT64_TYPE__ current = __atomic_fetch_add(&next, grain_size, __ATOMIC_RELAXED);
#endif
        if (!work_uint64_less(current, end)) {
            return false;
        }
        claimed_begin = current;
        const __UINT64_TYPE__ claimed_stop = work_saturating_stop(current, grain_size);
        claimed_end = work_uint64_less(claimed_stop, end) ? claimed_stop : end;
        return true;
    }
};

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
// Ordinary-AICore core claim: the caller owns the cursor in global memory, so
// the atomic advances the __gm__-qualified cell through the CANN scalar
// atomic.  The bound and grain travel by value, so a claim never re-reads the
// immutable fields sharing the cursor's cache line with the atomic cell -
// only the cell itself is touched - and the clamping contract (including the
// saturating stop above) matches the member claim exactly.
CANN_ASC_STL_DEVICE_API bool work_cursor_try_claim(__gm__ work_cursor* cursor, __UINT64_TYPE__ grain_size,
    __UINT64_TYPE__ end, __UINT64_TYPE__& claimed_begin, __UINT64_TYPE__& claimed_end) noexcept
{
    const __UINT64_TYPE__ current = asc_atomic_add(&cursor->next, grain_size);
    if (!work_uint64_less(current, end)) {
        return false;
    }
    claimed_begin = current;
    const __UINT64_TYPE__ claimed_stop = work_saturating_stop(current, grain_size);
    claimed_end = work_uint64_less(claimed_stop, end) ? claimed_stop : end;
    return true;
}
#endif

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___WORK_QUEUE_CURSOR_H
