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

#ifndef CANN_ASC_STL_ASC_STD___ATOMIC_BACKEND_H
#define CANN_ASC_STL_ASC_STD___ATOMIC_BACKEND_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__exception/terminate.h>
#include <asc/std/__atomic/memory_order.h>

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#include <simt_api/device_atomic_functions.h>
#include <simt_api/device_functions.h>
#include <simt_api/device_sync_functions.h>
#endif

namespace asc {
namespace detail {

// Residency constraint (real-iron finding, mirrored from the dev tree's
// device atomic layer): the asc_atomic builtins only operate on objects in
// device global memory. A stack- or private-address-space object is rejected
// by the backend even at native width ("Cannot cast between two non-generic
// address spaces"); per-core scratch is private to one core. Owning atomics
// and synchronization state must therefore live in global memory (kernel
// parameter storage, placement-new targets, or explicitly allocated buffers).
// A software path for local-memory atomics is a CANN backend follow-up.

template <class T>
inline constexpr bool is_scoped_atomic_integer_v = __is_same(T, __INT32_TYPE__) || __is_same(T, __UINT32_TYPE__) ||
    __is_same(T, __INT64_TYPE__) || __is_same(T, __UINT64_TYPE__);

CANN_ASC_STL_API constexpr std::memory_order atomic_failure_order(std::memory_order order) noexcept
{
    return order == std::memory_order_release ? std::memory_order_relaxed :
        order == std::memory_order_acq_rel    ? std::memory_order_acquire :
                                                order;
}

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()

CANN_ASC_STL_SIMT_API void atomic_compiler_barrier() noexcept
{
    asm volatile("" ::: "memory");
}

CANN_ASC_STL_SIMT_API void atomic_trap() noexcept
{
    ::asc::std::terminate();
}

// Memory-order awareness for the primitives below. The simt_api builtins are
// atomic per address but carry no cross-thread ordering (real-iron finding,
// mirrored by the dev tree's device atomic layer), so the ordered wrappers
// provide the requested ordering with full fences around the bare operation:
// relaxed runs bare, release is fence->op, acquire is op->fence, and
// acq_rel/seq_cst is fence->op->fence. This is the same mapping
// __atomic/atomic_ref.h applies through its fence_before/fence_after pair.

CANN_ASC_STL_SIMT_API bool atomic_order_has_release(std::memory_order order) noexcept
{
    return order == std::memory_order_release || order == std::memory_order_acq_rel ||
        order == std::memory_order_seq_cst;
}

CANN_ASC_STL_SIMT_API bool atomic_order_has_acquire(std::memory_order order) noexcept
{
    return order == std::memory_order_consume || order == std::memory_order_acquire ||
        order == std::memory_order_acq_rel || order == std::memory_order_seq_cst;
}

CANN_ASC_STL_SIMT_API void atomic_validate_load(std::memory_order order) noexcept
{
    if (order == std::memory_order_release || order == std::memory_order_acq_rel)
        atomic_trap();
}

CANN_ASC_STL_SIMT_API void atomic_validate_store(std::memory_order order) noexcept
{
    if (order == std::memory_order_consume || order == std::memory_order_acquire || order == std::memory_order_acq_rel)
        atomic_trap();
}

CANN_ASC_STL_SIMT_API void atomic_fence_before(std::memory_order order) noexcept
{
    if (!atomic_order_has_release(order))
        return;
    atomic_compiler_barrier();
    asc_threadfence();
    atomic_compiler_barrier();
}

template <class T>
CANN_ASC_STL_SIMT_API void atomic_fence_after(std::memory_order order, T* address) noexcept
{
    // Acquire caliber (deliberate divergence from the dev tree, documented
    // here as the product-wide rule): dev maps acquire to a bare
    // asc_threadfence; this tree additionally invalidates the D-cache line
    // for the touched address with asc_dcci_entire so subsequent loads
    // observe fresh data even when cores keep private cache copies, and the
    // dev tree itself records that asc_atomic updates are only guaranteed
    // visible at block granularity on real iron. threadfence + dcci is the
    // conservative superset of both claims; dropping the dcci is a CANN
    // backend follow-up that needs real-iron A/B evidence.
    if (!atomic_order_has_acquire(order))
        return;
    atomic_compiler_barrier();
    asc_threadfence();
    asc_dcci_entire(static_cast<void*>(address));
    atomic_compiler_barrier();
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_add(T* address, T value) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    return asc_atomic_add(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_sub(T* address, T value) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    return asc_atomic_sub(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_exchange(T* address, T value) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    return asc_atomic_exch(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_compare_exchange(T* address, T expected, T desired) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    return asc_atomic_cas(address, expected, desired);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_and(T* address, T value) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    return asc_atomic_and(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_or(T* address, T value) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    return asc_atomic_or(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_xor(T* address, T value) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    return asc_atomic_xor(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_min(T* address, T value) noexcept
{
    static_assert(is_scoped_atomic_integer_v<T>,
        "asc device atomics support exactly 32/64-bit signed and unsigned "
        "integers (widen the trait first if float min/max is ever added)");
    return asc_atomic_min(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_max(T* address, T value) noexcept
{
    static_assert(is_scoped_atomic_integer_v<T>,
        "asc device atomics support exactly 32/64-bit signed and unsigned "
        "integers (widen the trait first if float min/max is ever added)");
    return asc_atomic_max(address, value);
}

// Ordered counterparts of the primitives above: the bare operation dressed
// with the fences implied by the requested memory order. They carry distinct
// names because scoped_atomic.h passes the unordered forms around as
// function pointers, which same-name overloads would break.

template <class T>
CANN_ASC_STL_SIMT_API T atomic_ordered_add(T* address, T value, std::memory_order order) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    atomic_fence_before(order);
    const T old = asc_atomic_add(address, value);
    atomic_fence_after(order, address);
    return old;
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_ordered_sub(T* address, T value, std::memory_order order) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    atomic_fence_before(order);
    const T old = asc_atomic_sub(address, value);
    atomic_fence_after(order, address);
    return old;
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_ordered_exchange(T* address, T value, std::memory_order order) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    atomic_fence_before(order);
    const T old = asc_atomic_exch(address, value);
    atomic_fence_after(order, address);
    return old;
}

template <class T>
CANN_ASC_STL_SIMT_API bool atomic_ordered_compare_exchange(
    T* address, T& expected, T desired, std::memory_order success, std::memory_order failure) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    if (failure == std::memory_order_release || failure == std::memory_order_acq_rel)
        atomic_trap();
    atomic_fence_before(success);
    const T old = asc_atomic_cas(address, expected, desired);
    const bool changed = old == expected;
    if (!changed)
        expected = old;
    atomic_fence_after(changed ? success : failure, address);
    return changed;
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_ordered_and(T* address, T value, std::memory_order order) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    atomic_fence_before(order);
    const T old = asc_atomic_and(address, value);
    atomic_fence_after(order, address);
    return old;
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_ordered_or(T* address, T value, std::memory_order order) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    atomic_fence_before(order);
    const T old = asc_atomic_or(address, value);
    atomic_fence_after(order, address);
    return old;
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_ordered_xor(T* address, T value, std::memory_order order) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    atomic_fence_before(order);
    const T old = asc_atomic_xor(address, value);
    atomic_fence_after(order, address);
    return old;
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_ordered_min(T* address, T value, std::memory_order order) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    atomic_fence_before(order);
    const T old = asc_atomic_min(address, value);
    atomic_fence_after(order, address);
    return old;
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_ordered_max(T* address, T value, std::memory_order order) noexcept
{
    static_assert(
        is_scoped_atomic_integer_v<T>, "asc device atomics support exactly 32/64-bit signed and unsigned integers");
    atomic_fence_before(order);
    const T old = asc_atomic_max(address, value);
    atomic_fence_after(order, address);
    return old;
}

// Backoff controller for SIMT spin waits (barrier/latch/semaphore waits,
// contended retry loops). A bare spin can starve the thread that would
// satisfy the waited condition: the waiter monopolizes its execution slot
// while hammering the polled memory, and the SIMT execution model has no
// preemption to break the tie. The first polls stay tight; once the budget
// runs out, each further round pays a short dependent delay before polling
// again. There is no scheduler to yield to on the device, so the backoff
// only delays the next poll.
struct spin_backoff {
    int poll_count_{0};

    CANN_ASC_STL_SIMT_API bool poll()
    {
        return ++poll_count_ < 64;
    }

    CANN_ASC_STL_SIMT_API void backoff() const
    {
        for (int delay = 0; delay < 32; ++delay) {
            __asm__ __volatile__("" ::: "memory");
        }
    }
};

#endif

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

// Hosted backend: the single place the GCC/Clang __atomic_* builtins are
// spelled, so the three consumers (atomic.h, atomic_flag.h, atomic_ref.h)
// share one forwarding layer and cannot drift apart. Memory-order arguments
// are validated here with the same fail-fast policy the SIMT branch applies
// (an invalid order is a standard precondition violation, i.e. undefined
// behavior; the hosted answer is to terminate rather than pass garbage to
// the builtin). The enumerator-to-int cast is the one the memory_order.h
// static_asserts pin against the compiler's __ATOMIC_* values.

CANN_ASC_STL_API void atomic_validate_load(std::memory_order order) noexcept
{
    if (order == std::memory_order_release || order == std::memory_order_acq_rel)
        ::asc::std::terminate();
}

CANN_ASC_STL_API void atomic_validate_store(std::memory_order order) noexcept
{
    if (order == std::memory_order_consume || order == std::memory_order_acquire || order == std::memory_order_acq_rel)
        ::asc::std::terminate();
}

CANN_ASC_STL_API void atomic_validate_compare_exchange(std::memory_order failure) noexcept
{
    if (failure == std::memory_order_release || failure == std::memory_order_acq_rel)
        ::asc::std::terminate();
}

template <class T>
CANN_ASC_STL_API T atomic_load(const T* address, std::memory_order order) noexcept
{
    return __atomic_load_n(address, static_cast<int>(order));
}

template <class T, class V>
CANN_ASC_STL_API void atomic_store(T* address, V value, std::memory_order order) noexcept
{
    __atomic_store_n(address, value, static_cast<int>(order));
}

template <class T, class V>
CANN_ASC_STL_API T atomic_exchange(T* address, V value, std::memory_order order) noexcept
{
    return __atomic_exchange_n(address, value, static_cast<int>(order));
}

template <class T, class V>
CANN_ASC_STL_API bool atomic_compare_exchange(
    T* address, T& expected, V desired, bool weak, std::memory_order success, std::memory_order failure) noexcept
{
    return __atomic_compare_exchange_n(
        address, &expected, desired, weak, static_cast<int>(success), static_cast<int>(failure));
}

template <class T, class V>
CANN_ASC_STL_API T atomic_fetch_add(T* address, V value, std::memory_order order) noexcept
{
    return __atomic_fetch_add(address, value, static_cast<int>(order));
}

template <class T, class V>
CANN_ASC_STL_API T atomic_fetch_sub(T* address, V value, std::memory_order order) noexcept
{
    return __atomic_fetch_sub(address, value, static_cast<int>(order));
}

template <class T, class V>
CANN_ASC_STL_API T atomic_fetch_and(T* address, V value, std::memory_order order) noexcept
{
    return __atomic_fetch_and(address, value, static_cast<int>(order));
}

template <class T, class V>
CANN_ASC_STL_API T atomic_fetch_or(T* address, V value, std::memory_order order) noexcept
{
    return __atomic_fetch_or(address, value, static_cast<int>(order));
}

template <class T, class V>
CANN_ASC_STL_API T atomic_fetch_xor(T* address, V value, std::memory_order order) noexcept
{
    return __atomic_fetch_xor(address, value, static_cast<int>(order));
}

#endif

}  // namespace detail
}  // namespace asc

#endif  // CANN_ASC_STL_ASC_STD___ATOMIC_BACKEND_H
