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

#ifndef CANN_ASC_STL_ASC_STD___ATOMIC_ATOMIC_FLAG_H
#define CANN_ASC_STL_ASC_STD___ATOMIC_ATOMIC_FLAG_H

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

class atomic_flag {
public:
    atomic_flag(const atomic_flag&) = delete;
    atomic_flag& operator=(const atomic_flag&) = delete;

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API atomic_flag() noexcept = default;

    CANN_ASC_STL_SIMT_API bool test(memory_order = memory_order_seq_cst) const noexcept
    {
        return ::asc::detail::atomic_add(const_cast<unsigned int*>(&value_), 0U) != 0U;
    }

    CANN_ASC_STL_SIMT_API bool test_and_set(memory_order = memory_order_seq_cst) noexcept
    {
        return ::asc::detail::atomic_exchange(&value_, 1U) != 0U;
    }

    CANN_ASC_STL_SIMT_API void clear(memory_order = memory_order_seq_cst) noexcept
    {
        (void)::asc::detail::atomic_exchange(&value_, 0U);
    }
#elif !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    atomic_flag() noexcept = default;

    bool test(memory_order order = memory_order_seq_cst) const noexcept
    {
        return __atomic_load_n(&value_, static_cast<int>(order)) != 0U;
    }

    bool test_and_set(memory_order order = memory_order_seq_cst) noexcept
    {
        return __atomic_exchange_n(&value_, 1U, static_cast<int>(order)) != 0U;
    }

    void clear(memory_order order = memory_order_seq_cst) noexcept
    {
        __atomic_store_n(&value_, 0U, static_cast<int>(order));
    }
#else
    atomic_flag() = delete;
#endif

private:
    unsigned int value_{};
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ATOMIC_ATOMIC_FLAG_H
