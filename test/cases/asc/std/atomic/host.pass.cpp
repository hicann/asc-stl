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

#include "../../../../support/b022_semantics.h"

namespace {
template <class T, class = int>
struct has_wait : asc::std::false_type {};
template <class T>
struct has_wait<T, decltype(static_cast<void (asc::std::atomic<T>::*)() const>(&asc::std::atomic<T>::wait))>
    : asc::std::true_type {};

template <class T, class = int>
struct has_notify_one : asc::std::false_type {};
template <class T>
struct has_notify_one<T, decltype(static_cast<void (asc::std::atomic<T>::*)()>(&asc::std::atomic<T>::notify_one))>
    : asc::std::true_type {};
}  // namespace

int main()
{
    static_assert(CANN_ASC_STL_ATOMIC_BOOL_LOCK_FREE == 2);
    static_assert(CANN_ASC_STL_ATOMIC_CHAR_LOCK_FREE == 2);
    static_assert(CANN_ASC_STL_ATOMIC_CHAR16_T_LOCK_FREE == 2);
    static_assert(CANN_ASC_STL_ATOMIC_CHAR32_T_LOCK_FREE == 2);
    static_assert(CANN_ASC_STL_ATOMIC_WCHAR_T_LOCK_FREE == 2);
    static_assert(CANN_ASC_STL_ATOMIC_SHORT_LOCK_FREE == 2);
    static_assert(CANN_ASC_STL_ATOMIC_INT_LOCK_FREE == 2);
    static_assert(CANN_ASC_STL_ATOMIC_LONG_LOCK_FREE == 2);
    static_assert(CANN_ASC_STL_ATOMIC_LLONG_LOCK_FREE == 2);
    static_assert(CANN_ASC_STL_ATOMIC_POINTER_LOCK_FREE == 0);
    static_assert(asc::std::atomic_int8_t::is_always_lock_free);
    static_assert(asc::std::atomic_uint_least64_t::is_always_lock_free);
    static_assert(asc::std::atomic_intmax_t::is_always_lock_free);
    static_assert(asc::std::atomic_signed_lock_free::is_always_lock_free);
    static_assert(asc::std::atomic_unsigned_lock_free::is_always_lock_free);
    static_assert(asc::std::memory_order_relaxed == 0 && asc::std::memory_order_seq_cst == 5);
#if defined(ATOMIC_INT_LOCK_FREE) || defined(ATOMIC_VAR_INIT) || defined(ATOMIC_FLAG_INIT)
#error "unprefixed ATOMIC_* macros must not be defined"
#endif
    static_assert(!has_wait<int>::value, "atomic wait is excluded from this delivery");
    static_assert(!has_notify_one<int>::value, "atomic notify is excluded from this delivery");
    return asc_stl_b022_test::evaluate_all();
}
