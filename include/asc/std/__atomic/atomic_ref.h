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

#ifndef CANN_ASC_STL_ASC_STD___ATOMIC_ATOMIC_REF_H
#define CANN_ASC_STL_ASC_STD___ATOMIC_ATOMIC_REF_H

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

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __atomic_ref_detail {

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
CANN_ASC_STL_SIMT_API bool has_release(memory_order order) noexcept
{
    return order == memory_order_release || order == memory_order_acq_rel || order == memory_order_seq_cst;
}

CANN_ASC_STL_SIMT_API bool has_acquire(memory_order order) noexcept
{
    return order == memory_order_consume || order == memory_order_acquire || order == memory_order_acq_rel ||
        order == memory_order_seq_cst;
}

CANN_ASC_STL_SIMT_API void validate_load(memory_order order) noexcept
{
    if (order == memory_order_release || order == memory_order_acq_rel)
        ::asc::detail::atomic_trap();
}

CANN_ASC_STL_SIMT_API void validate_store(memory_order order) noexcept
{
    if (order == memory_order_consume || order == memory_order_acquire || order == memory_order_acq_rel)
        ::asc::detail::atomic_trap();
}

CANN_ASC_STL_SIMT_API void fence_before(memory_order order) noexcept
{
    if (!has_release(order))
        return;
    ::asc::detail::atomic_compiler_barrier();
    asc_threadfence();
    ::asc::detail::atomic_compiler_barrier();
}

template <class T>
CANN_ASC_STL_SIMT_API void fence_after(memory_order order, T* address) noexcept
{
    if (!has_acquire(order))
        return;
    ::asc::detail::atomic_compiler_barrier();
    asc_threadfence();
    asc_dcci_entire(static_cast<void*>(address));
    ::asc::detail::atomic_compiler_barrier();
}

#endif

CANN_ASC_STL_API constexpr memory_order failure_order(memory_order order) noexcept
{
    return order == memory_order_release ? memory_order_relaxed :
        order == memory_order_acq_rel    ? memory_order_acquire :
                                           order;
}

}  // namespace __atomic_ref_detail

template <class T>
class atomic_ref {
    static_assert(::asc::detail::is_scoped_atomic_integer_v<T>,
        "asc::std::atomic_ref supports exactly 32/64-bit signed and unsigned integers");

public:
    static constexpr bool is_always_lock_free = true;

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API explicit atomic_ref(T& value) noexcept : address_(&value)
    {}
    atomic_ref(const atomic_ref&) noexcept = default;
    atomic_ref& operator=(const atomic_ref&) = delete;

    CANN_ASC_STL_SIMT_API bool is_lock_free() const noexcept
    {
        return true;
    }

    CANN_ASC_STL_SIMT_API T load(memory_order order = memory_order_seq_cst) const noexcept
    {
        __atomic_ref_detail::validate_load(order);
        __atomic_ref_detail::fence_before(order);
        const T old = ::asc::detail::atomic_add(address_, T{});
        __atomic_ref_detail::fence_after(order, address_);
        return old;
    }

    CANN_ASC_STL_SIMT_API void store(T value, memory_order order = memory_order_seq_cst) const noexcept
    {
        __atomic_ref_detail::validate_store(order);
        __atomic_ref_detail::fence_before(order);
        (void)::asc::detail::atomic_exchange(address_, value);
        __atomic_ref_detail::fence_after(order, address_);
    }

    CANN_ASC_STL_SIMT_API T exchange(T value, memory_order order = memory_order_seq_cst) const noexcept
    {
        __atomic_ref_detail::fence_before(order);
        const T old = ::asc::detail::atomic_exchange(address_, value);
        __atomic_ref_detail::fence_after(order, address_);
        return old;
    }

    CANN_ASC_STL_SIMT_API bool compare_exchange_strong(
        T& expected, T desired, memory_order success, memory_order failure) const noexcept
    {
        if (failure == memory_order_release || failure == memory_order_acq_rel)
            ::asc::detail::atomic_trap();
        __atomic_ref_detail::fence_before(success);
        const T old = ::asc::detail::atomic_compare_exchange(address_, expected, desired);
        const bool changed = old == expected;
        if (!changed)
            expected = old;
        __atomic_ref_detail::fence_after(changed ? success : failure, address_);
        return changed;
    }

    CANN_ASC_STL_SIMT_API bool compare_exchange_strong(
        T& expected, T desired, memory_order order = memory_order_seq_cst) const noexcept
    {
        return compare_exchange_strong(expected, desired, order, __atomic_ref_detail::failure_order(order));
    }

    CANN_ASC_STL_SIMT_API bool compare_exchange_weak(
        T& expected, T desired, memory_order success, memory_order failure) const noexcept
    {
        return compare_exchange_strong(expected, desired, success, failure);
    }

    CANN_ASC_STL_SIMT_API bool compare_exchange_weak(
        T& expected, T desired, memory_order order = memory_order_seq_cst) const noexcept
    {
        return compare_exchange_strong(expected, desired, order);
    }

    CANN_ASC_STL_SIMT_API T fetch_add(T value, memory_order order = memory_order_seq_cst) const noexcept
    {
        __atomic_ref_detail::fence_before(order);
        const T old = ::asc::detail::atomic_add(address_, value);
        __atomic_ref_detail::fence_after(order, address_);
        return old;
    }

    CANN_ASC_STL_SIMT_API T fetch_sub(T value, memory_order order = memory_order_seq_cst) const noexcept
    {
        __atomic_ref_detail::fence_before(order);
        const T old = ::asc::detail::atomic_sub(address_, value);
        __atomic_ref_detail::fence_after(order, address_);
        return old;
    }
#elif !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    explicit atomic_ref(T& value) noexcept : address_(&value)
    {}
    atomic_ref(const atomic_ref&) noexcept = default;
    atomic_ref& operator=(const atomic_ref&) = delete;

    bool is_lock_free() const noexcept
    {
        return __atomic_always_lock_free(sizeof(T), address_);
    }

    T load(memory_order order = memory_order_seq_cst) const noexcept
    {
        return __atomic_load_n(address_, static_cast<int>(order));
    }

    void store(T value, memory_order order = memory_order_seq_cst) const noexcept
    {
        __atomic_store_n(address_, value, static_cast<int>(order));
    }

    T exchange(T value, memory_order order = memory_order_seq_cst) const noexcept
    {
        return __atomic_exchange_n(address_, value, static_cast<int>(order));
    }

    bool compare_exchange_strong(T& expected, T desired, memory_order success, memory_order failure) const noexcept
    {
        return __atomic_compare_exchange_n(
            address_, &expected, desired, false, static_cast<int>(success), static_cast<int>(failure));
    }

    bool compare_exchange_strong(T& expected, T desired, memory_order order = memory_order_seq_cst) const noexcept
    {
        return compare_exchange_strong(expected, desired, order, __atomic_ref_detail::failure_order(order));
    }

    bool compare_exchange_weak(T& expected, T desired, memory_order success, memory_order failure) const noexcept
    {
        return __atomic_compare_exchange_n(
            address_, &expected, desired, true, static_cast<int>(success), static_cast<int>(failure));
    }

    bool compare_exchange_weak(T& expected, T desired, memory_order order = memory_order_seq_cst) const noexcept
    {
        return compare_exchange_weak(expected, desired, order, __atomic_ref_detail::failure_order(order));
    }

    T fetch_add(T value, memory_order order = memory_order_seq_cst) const noexcept
    {
        return __atomic_fetch_add(address_, value, static_cast<int>(order));
    }

    T fetch_sub(T value, memory_order order = memory_order_seq_cst) const noexcept
    {
        return __atomic_fetch_sub(address_, value, static_cast<int>(order));
    }
#else
    explicit atomic_ref(T&) = delete;
#endif

private:
    T* address_{};
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ATOMIC_ATOMIC_REF_H
