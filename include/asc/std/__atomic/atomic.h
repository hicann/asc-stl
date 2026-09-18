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

#ifndef CANN_ASC_STL_ASC_STD___ATOMIC_ATOMIC_H
#define CANN_ASC_STL_ASC_STD___ATOMIC_ATOMIC_H

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
namespace detail {

// The owning atomic supports exactly the standard integer and character types.
// bool/8/16-bit values live in a 32-bit cell; 32/64-bit values dispatch by the
// signed bit pattern of the value type. Any other T leaves the primary template
// unaugmented so that the static_assert below rejects it.
template <class T>
struct owned_atomic_storage {
    static_assert(sizeof(T) == 0, "asc::std::atomic supports exactly the standard integer and character types");
};

template <>
struct owned_atomic_storage<bool> {
    using type = __UINT32_TYPE__;
};
template <>
struct owned_atomic_storage<char> {
#if defined(__CHAR_UNSIGNED__)
    using type = __UINT32_TYPE__;
#else
    using type = __INT32_TYPE__;
#endif
};
template <>
struct owned_atomic_storage<signed char> {
    using type = __INT32_TYPE__;
};
template <>
struct owned_atomic_storage<unsigned char> {
    using type = __UINT32_TYPE__;
};
template <>
struct owned_atomic_storage<short> {
    using type = __INT32_TYPE__;
};
template <>
struct owned_atomic_storage<unsigned short> {
    using type = __UINT32_TYPE__;
};
template <>
struct owned_atomic_storage<int> {
    using type = __INT32_TYPE__;
};
template <>
struct owned_atomic_storage<unsigned int> {
    using type = __UINT32_TYPE__;
};
template <>
struct owned_atomic_storage<long> {
    using type = __INT64_TYPE__;
};
template <>
struct owned_atomic_storage<unsigned long> {
    using type = __UINT64_TYPE__;
};
template <>
struct owned_atomic_storage<long long> {
    using type = __INT64_TYPE__;
};
template <>
struct owned_atomic_storage<unsigned long long> {
    using type = __UINT64_TYPE__;
};
template <>
struct owned_atomic_storage<wchar_t> {
    using type = __INT32_TYPE__;
};
template <>
struct owned_atomic_storage<char16_t> {
    using type = __UINT32_TYPE__;
};
template <>
struct owned_atomic_storage<char32_t> {
    using type = __UINT32_TYPE__;
};
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
template <>
struct owned_atomic_storage<char8_t> {
    using type = __UINT32_TYPE__;
};
#endif

}  // namespace detail
}  // namespace asc

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
class atomic {
public:
    using value_type = T;
    using storage_type = typename ::asc::detail::owned_atomic_storage<T>::type;

    atomic(const atomic&) = delete;
    atomic& operator=(const atomic&) = delete;

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API atomic() noexcept = default;
    CANN_ASC_STL_SIMT_API constexpr atomic(T value) noexcept : storage_(static_cast<storage_type>(value))
    {}

    CANN_ASC_STL_SIMT_API bool is_lock_free() const noexcept
    {
        return true;
    }

    CANN_ASC_STL_SIMT_API T load(memory_order = memory_order_seq_cst) const noexcept
    {
        return static_cast<T>(::asc::detail::atomic_add(const_cast<storage_type*>(&storage_), storage_type()));
    }

    CANN_ASC_STL_SIMT_API void store(T value, memory_order = memory_order_seq_cst) noexcept
    {
        (void)::asc::detail::atomic_exchange(&storage_, static_cast<storage_type>(value));
    }

    CANN_ASC_STL_SIMT_API T exchange(T value, memory_order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(::asc::detail::atomic_exchange(&storage_, static_cast<storage_type>(value)));
    }

    CANN_ASC_STL_SIMT_API bool compare_exchange_weak(T& expected, T desired, memory_order, memory_order) noexcept
    {
        return compare_exchange_strong(expected, desired, memory_order_seq_cst, memory_order_seq_cst);
    }

    CANN_ASC_STL_SIMT_API bool compare_exchange_weak(T& expected, T desired, memory_order) noexcept
    {
        return compare_exchange_strong(expected, desired, memory_order_seq_cst);
    }

    CANN_ASC_STL_SIMT_API bool compare_exchange_strong(T& expected, T desired, memory_order, memory_order) noexcept
    {
        const storage_type old = ::asc::detail::atomic_compare_exchange(
            &storage_, static_cast<storage_type>(expected), static_cast<storage_type>(desired));
        if (old == static_cast<storage_type>(expected)) {
            return true;
        }
        expected = static_cast<T>(old);
        return false;
    }

    CANN_ASC_STL_SIMT_API bool compare_exchange_strong(T& expected, T desired, memory_order) noexcept
    {
        return compare_exchange_strong(expected, desired, memory_order_seq_cst, memory_order_seq_cst);
    }

    CANN_ASC_STL_SIMT_API T fetch_add(T value, memory_order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(::asc::detail::atomic_add(&storage_, static_cast<storage_type>(value)));
    }

    CANN_ASC_STL_SIMT_API T fetch_sub(T value, memory_order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(::asc::detail::atomic_sub(&storage_, static_cast<storage_type>(value)));
    }

    CANN_ASC_STL_SIMT_API T fetch_and(T value, memory_order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(::asc::detail::atomic_and(&storage_, static_cast<storage_type>(value)));
    }

    CANN_ASC_STL_SIMT_API T fetch_or(T value, memory_order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(::asc::detail::atomic_or(&storage_, static_cast<storage_type>(value)));
    }

    CANN_ASC_STL_SIMT_API T fetch_xor(T value, memory_order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(::asc::detail::atomic_xor(&storage_, static_cast<storage_type>(value)));
    }
#elif !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    atomic() noexcept = default;
    // NOLINTNEXTLINE(runtime/explicit)
    constexpr atomic(T value) noexcept : storage_(static_cast<storage_type>(value))
    {}

    bool is_lock_free() const noexcept
    {
        return true;
    }

    T load(memory_order order = memory_order_seq_cst) const noexcept
    {
        return static_cast<T>(__atomic_load_n(&storage_, static_cast<int>(order)));
    }

    void store(T value, memory_order order = memory_order_seq_cst) noexcept
    {
        __atomic_store_n(&storage_, static_cast<storage_type>(value), static_cast<int>(order));
    }

    T exchange(T value, memory_order order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(
            __atomic_exchange_n(&storage_, static_cast<storage_type>(value), static_cast<int>(order)));
    }

    bool compare_exchange_weak(T& expected, T desired, memory_order success, memory_order failure) noexcept
    {
        return compare_exchange_strong(expected, desired, success, failure);
    }

    bool compare_exchange_weak(T& expected, T desired, memory_order order) noexcept
    {
        return compare_exchange_strong(expected, desired, order, order);
    }

    bool compare_exchange_strong(T& expected, T desired, memory_order success, memory_order failure) noexcept
    {
        storage_type expected_storage = static_cast<storage_type>(expected);
        const bool swapped = __atomic_compare_exchange_n(&storage_, &expected_storage,
            static_cast<storage_type>(desired), false, static_cast<int>(success), static_cast<int>(failure));
        if (!swapped) {
            expected = static_cast<T>(expected_storage);
        }
        return swapped;
    }

    bool compare_exchange_strong(T& expected, T desired, memory_order order) noexcept
    {
        return compare_exchange_strong(expected, desired, order, order);
    }

    T fetch_add(T value, memory_order order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(__atomic_fetch_add(&storage_, static_cast<storage_type>(value), static_cast<int>(order)));
    }

    T fetch_sub(T value, memory_order order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(__atomic_fetch_sub(&storage_, static_cast<storage_type>(value), static_cast<int>(order)));
    }

    T fetch_and(T value, memory_order order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(__atomic_fetch_and(&storage_, static_cast<storage_type>(value), static_cast<int>(order)));
    }

    T fetch_or(T value, memory_order order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(__atomic_fetch_or(&storage_, static_cast<storage_type>(value), static_cast<int>(order)));
    }

    T fetch_xor(T value, memory_order order = memory_order_seq_cst) noexcept
    {
        return static_cast<T>(__atomic_fetch_xor(&storage_, static_cast<storage_type>(value), static_cast<int>(order)));
    }
#else
    atomic() = delete;
    explicit atomic(T) = delete;
#endif

    static constexpr bool is_always_lock_free = true;

private:
    storage_type storage_{};
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ATOMIC_ATOMIC_H
