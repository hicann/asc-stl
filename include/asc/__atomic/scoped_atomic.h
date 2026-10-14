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

#ifndef CANN_ASC_STL_ASC___ATOMIC_SCOPED_ATOMIC_H
#define CANN_ASC_STL_ASC___ATOMIC_SCOPED_ATOMIC_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__atomic/backend.h>
#include <asc/std/__atomic/memory_order.h>

namespace asc {

enum class memory_scope { block, device };

namespace detail {

template <class T>
inline constexpr bool is_exact_scoped_atomic_integer_v = __is_same(T, __INT32_TYPE__) ||
    __is_same(T, __UINT32_TYPE__) || __is_same(T, __INT64_TYPE__) || __is_same(T, __UINT64_TYPE__);

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()

CANN_ASC_STL_SIMT_API void validate_load_order(std::memory_order order) noexcept
{
    if (order == std::memory_order_release || order == std::memory_order_acq_rel) {
        atomic_trap();
    }
}

CANN_ASC_STL_SIMT_API void validate_store_order(std::memory_order order) noexcept
{
    if (order == std::memory_order_consume || order == std::memory_order_acquire ||
        order == std::memory_order_acq_rel) {
        atomic_trap();
    }
}

CANN_ASC_STL_SIMT_API bool has_release(std::memory_order order) noexcept
{
    return order == std::memory_order_release || order == std::memory_order_acq_rel ||
        order == std::memory_order_seq_cst;
}

CANN_ASC_STL_SIMT_API bool has_acquire(std::memory_order order) noexcept
{
    return order == std::memory_order_consume || order == std::memory_order_acquire ||
        order == std::memory_order_acq_rel || order == std::memory_order_seq_cst;
}

// Strength rank used to enforce the standard compare-exchange rule that the
// failure order must not be stronger than the success order.
CANN_ASC_STL_SIMT_API int order_strength(std::memory_order order) noexcept
{
    if (order == std::memory_order_seq_cst) {
        return 4;
    }
    if (order == std::memory_order_acq_rel) {
        return 3;
    }
    if (order == std::memory_order_release) {
        return 2;
    }
    if (order == std::memory_order_acquire || order == std::memory_order_consume) {
        return 1;
    }
    return 0;
}

CANN_ASC_STL_SIMT_API void validate_exchange_orders(std::memory_order success, std::memory_order failure) noexcept
{
    if (failure == std::memory_order_release || failure == std::memory_order_acq_rel ||
        order_strength(failure) > order_strength(success)) {
        atomic_trap();
    }
}

CANN_ASC_STL_SIMT_API void scoped_thread_fence(memory_scope scope) noexcept
{
    // CANN 9.2's pure-SIMT block-fence lowering crashes when followed by a
    // compiler barrier. A device fence provides stronger ordering and keeps
    // the required hardware MEMBAR without relying on a private compiler flag.
    // Consequence: memory_scope::block currently executes at device strength
    // (never weaker, so correctness is preserved) even though the registry
    // documents block and device as two scopes. Per-scope dispatch is to be
    // restored once the CANN block-fence lowering is fixed; until then this
    // deviation lives here on purpose.
    (void)scope;
    asc_threadfence();
}

template <memory_scope Scope>
CANN_ASC_STL_SIMT_API void fence_before(std::memory_order order) noexcept
{
    if (!has_release(order)) {
        return;
    }
    atomic_compiler_barrier();
    scoped_thread_fence(Scope);
    atomic_compiler_barrier();
}

template <memory_scope Scope, class T>
CANN_ASC_STL_SIMT_API void fence_after(std::memory_order order, T* address) noexcept
{
    if (!has_acquire(order)) {
        return;
    }
    atomic_compiler_barrier();
    scoped_thread_fence(Scope);
    asc_dcci_entire(static_cast<void*>(address));
    atomic_compiler_barrier();
}

template <memory_scope Scope, class Operation, class T>
CANN_ASC_STL_SIMT_API T ordered_rmw(Operation operation, T* address, T operand, std::memory_order order) noexcept
{
    fence_before<Scope>(order);
    const T old = operation(address, operand);
    fence_after<Scope>(order, address);
    return old;
}

#endif

}  // namespace detail

template <class T, memory_scope Scope = memory_scope::device>
class atomic_ref {
    static_assert(detail::is_exact_scoped_atomic_integer_v<T>,
        "asc::atomic_ref supports exactly 32/64-bit signed and unsigned integers");

public:
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API explicit atomic_ref(T& object) noexcept : address_(&object)
    {}

    CANN_ASC_STL_SIMT_API T load(std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        detail::validate_load_order(order);
        // The backend exposes no load-only primitive, so every load goes
        // through an atomic_add RMW: even a relaxed load pays the full
        // read-modify-write path, and fence_after invalidates the entire data
        // cache on acquire.  Both costs are accepted deliberately; a native
        // load (dev dispatches through __atomic_load_dispatch) and an
        // address-line-targeted invalidation are CANN backend follow-ups.
        return detail::ordered_rmw<Scope>(detail::atomic_add<T>, address_, T{}, order);
    }

    CANN_ASC_STL_SIMT_API void store(T desired, std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        detail::validate_store_order(order);
        (void)detail::ordered_rmw<Scope>(detail::atomic_exchange<T>, address_, desired, order);
    }

    CANN_ASC_STL_SIMT_API T exchange(T desired, std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        return detail::ordered_rmw<Scope>(detail::atomic_exchange<T>, address_, desired, order);
    }

    CANN_ASC_STL_SIMT_API bool compare_exchange_strong(
        T& expected, T desired, std::memory_order success, std::memory_order failure) const noexcept
    {
        detail::validate_exchange_orders(success, failure);
        detail::fence_before<Scope>(success);
        const T old = detail::atomic_compare_exchange(address_, expected, desired);
        const bool changed = old == expected;
        if (!changed) {
            expected = old;
        }
        detail::fence_after<Scope>(changed ? success : failure, address_);
        return changed;
    }

    CANN_ASC_STL_SIMT_API bool compare_exchange_strong(
        T& expected, T desired, std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        // Standard single-order form: derive the failure order from the
        // combined order through the backend helper (acq_rel degrades to
        // acquire, release to relaxed).
        return compare_exchange_strong(expected, desired, order, detail::atomic_failure_order(order));
    }

    CANN_ASC_STL_SIMT_API T fetch_add(T operand, std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        return detail::ordered_rmw<Scope>(detail::atomic_add<T>, address_, operand, order);
    }

    CANN_ASC_STL_SIMT_API T fetch_sub(T operand, std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        return detail::ordered_rmw<Scope>(detail::atomic_sub<T>, address_, operand, order);
    }

    CANN_ASC_STL_SIMT_API T fetch_and(T operand, std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        return detail::ordered_rmw<Scope>(detail::atomic_and<T>, address_, operand, order);
    }

    CANN_ASC_STL_SIMT_API T fetch_or(T operand, std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        return detail::ordered_rmw<Scope>(detail::atomic_or<T>, address_, operand, order);
    }

    CANN_ASC_STL_SIMT_API T fetch_xor(T operand, std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        return detail::ordered_rmw<Scope>(detail::atomic_xor<T>, address_, operand, order);
    }

    CANN_ASC_STL_SIMT_API T fetch_min(T operand, std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        return detail::ordered_rmw<Scope>(detail::atomic_min<T>, address_, operand, order);
    }

    CANN_ASC_STL_SIMT_API T fetch_max(T operand, std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        return detail::ordered_rmw<Scope>(detail::atomic_max<T>, address_, operand, order);
    }
#else
    explicit atomic_ref(T&) = delete;
#endif

private:
    T* address_;
};

template <class T, memory_scope Scope = memory_scope::device>
class atomic {
    static_assert(detail::is_exact_scoped_atomic_integer_v<T>,
        "asc::atomic supports exactly 32/64-bit signed and unsigned integers");

public:
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API atomic() noexcept = default;
    CANN_ASC_STL_SIMT_API explicit atomic(T desired) noexcept : value_(desired)
    {}
    atomic(const atomic&) = delete;
    atomic& operator=(const atomic&) = delete;

    CANN_ASC_STL_SIMT_API T load(std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        return reference().load(order);
    }
    CANN_ASC_STL_SIMT_API void store(T desired, std::memory_order order = std::memory_order_seq_cst) noexcept
    {
        reference().store(desired, order);
    }
    CANN_ASC_STL_SIMT_API T exchange(T desired, std::memory_order order = std::memory_order_seq_cst) noexcept
    {
        return reference().exchange(desired, order);
    }
    CANN_ASC_STL_SIMT_API bool compare_exchange_strong(
        T& expected, T desired, std::memory_order success, std::memory_order failure) noexcept
    {
        return reference().compare_exchange_strong(expected, desired, success, failure);
    }
    CANN_ASC_STL_SIMT_API bool compare_exchange_strong(
        T& expected, T desired, std::memory_order order = std::memory_order_seq_cst) noexcept
    {
        return reference().compare_exchange_strong(expected, desired, order);
    }
#define CANN_ASC_STL_SCOPED_ATOMIC_FETCH(name)                                                                    \
    CANN_ASC_STL_SIMT_API T fetch_##name(T operand, std::memory_order order = std::memory_order_seq_cst) noexcept \
    {                                                                                                             \
        return reference().fetch_##name(operand, order);                                                          \
    }
    CANN_ASC_STL_SCOPED_ATOMIC_FETCH(add)
    CANN_ASC_STL_SCOPED_ATOMIC_FETCH(sub)
    CANN_ASC_STL_SCOPED_ATOMIC_FETCH(and)
    CANN_ASC_STL_SCOPED_ATOMIC_FETCH(or)
    CANN_ASC_STL_SCOPED_ATOMIC_FETCH(xor)
    CANN_ASC_STL_SCOPED_ATOMIC_FETCH(min)
    CANN_ASC_STL_SCOPED_ATOMIC_FETCH(max)
#undef CANN_ASC_STL_SCOPED_ATOMIC_FETCH
#else
    atomic() = delete;
    explicit atomic(T) = delete;
#endif

private:
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API atomic_ref<T, Scope> reference() const noexcept
    {
        return atomic_ref<T, Scope>(const_cast<T&>(value_));
    }
#endif
    T value_{};
};

template <class T>
class relaxed_atomic_ref {
    static_assert(detail::is_exact_scoped_atomic_integer_v<T>,
        "asc::relaxed_atomic_ref supports exactly 32/64-bit signed and unsigned integers");

public:
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API explicit relaxed_atomic_ref(T& object) noexcept : address_(&object)
    {}
    CANN_ASC_STL_SIMT_API T load() const noexcept
    {
        return detail::atomic_add(address_, T{});
    }
    CANN_ASC_STL_SIMT_API void store(T desired) const noexcept
    {
        (void)detail::atomic_exchange(address_, desired);
    }
    CANN_ASC_STL_SIMT_API T exchange(T desired) const noexcept
    {
        return detail::atomic_exchange(address_, desired);
    }
    CANN_ASC_STL_SIMT_API bool compare_exchange_strong(T& expected, T desired) const noexcept
    {
        const T old = detail::atomic_compare_exchange(address_, expected, desired);
        if (old == expected) {
            return true;
        }
        expected = old;
        return false;
    }
    CANN_ASC_STL_SIMT_API T fetch_add(T operand) const noexcept
    {
        return detail::atomic_add(address_, operand);
    }
    CANN_ASC_STL_SIMT_API T fetch_sub(T operand) const noexcept
    {
        return detail::atomic_sub(address_, operand);
    }
#else
    explicit relaxed_atomic_ref(T&) = delete;
#endif

private:
    T* address_;
};

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
CANN_ASC_STL_SIMT_API void atomic_thread_fence(std::memory_order order, memory_scope scope) noexcept
{
    if (order == std::memory_order_relaxed) {
        return;
    }
    if (order != std::memory_order_release) {
        detail::atomic_trap();
    }
    detail::atomic_compiler_barrier();
    detail::scoped_thread_fence(scope);
    detail::atomic_compiler_barrier();
}
#else
inline void atomic_thread_fence(std::memory_order, memory_scope) = delete;
#endif

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___ATOMIC_SCOPED_ATOMIC_H
