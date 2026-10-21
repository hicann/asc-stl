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

#ifndef ASC_STL_TEST_NARROW_ATOMIC_CAS_SEMANTICS_H
#define ASC_STL_TEST_NARROW_ATOMIC_CAS_SEMANTICS_H

#include <asc/__detail/attributes.h>
#include <asc/std/atomic>
#include <asc/std/new>

namespace asc_stl_narrow_atomic_cas_test {

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION() || !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class T>
struct goldens {
    T minimum;
    T maximum;
    T minimum_plus_one;
    T maximum_minus_one;
    T all_bits;
};

template <class Pointer, class T>
CANN_ASC_STL_HOST_SIMT_API unsigned check_strong(Pointer value, T expected, T desired)
{
    const T original = expected;
    const bool changed = value->compare_exchange_strong(
        expected, desired, asc::std::memory_order_acq_rel, asc::std::memory_order_acquire);
    return !changed || expected != original || value->load(asc::std::memory_order_acquire) != desired;
}

template <class Pointer, class T>
CANN_ASC_STL_HOST_SIMT_API unsigned check_weak(Pointer value, T expected, T desired)
{
    const T original = expected;
    const bool changed = value->compare_exchange_weak(expected, desired, asc::std::memory_order_acq_rel);
    return !changed || expected != original || value->load(asc::std::memory_order_acquire) != desired;
}

template <class Pointer, class T>
CANN_ASC_STL_HOST_SIMT_API unsigned check_arithmetic(Pointer value, goldens<T> expected)
{
    value->store(expected.maximum, asc::std::memory_order_relaxed);
    unsigned failures = value->fetch_add(T{1}, asc::std::memory_order_release) != expected.maximum;
    failures += value->load(asc::std::memory_order_acquire) != expected.minimum;
    failures += check_strong(value, expected.minimum, T{3});
    value->store(expected.minimum, asc::std::memory_order_relaxed);
    failures += value->fetch_sub(T{1}, asc::std::memory_order_acq_rel) != expected.minimum;
    failures += value->load(asc::std::memory_order_acquire) != expected.maximum;
    failures += check_weak(value, expected.maximum, T{7});
    return failures;
}

template <class Pointer, class T>
CANN_ASC_STL_HOST_SIMT_API unsigned check_failure(Pointer value, goldens<T> expected)
{
    value->store(expected.maximum, asc::std::memory_order_relaxed);
    unsigned failures = value->fetch_add(T{1}, asc::std::memory_order_relaxed) != expected.maximum;
    T compared = T{5};
    failures +=
        value->compare_exchange_strong(compared, T{9}, asc::std::memory_order_acq_rel, asc::std::memory_order_acquire);
    failures += compared != expected.minimum || value->load() != expected.minimum;
    failures += check_strong(value, compared, T{9});
    value->store(expected.minimum, asc::std::memory_order_relaxed);
    failures += value->fetch_sub(T{1}, asc::std::memory_order_relaxed) != expected.minimum;
    compared = T{5};
    failures +=
        value->compare_exchange_weak(compared, T{9}, asc::std::memory_order_seq_cst, asc::std::memory_order_relaxed);
    failures += compared != expected.maximum || value->load() != expected.maximum;
    failures += check_weak(value, compared, T{9});
    return failures;
}

template <class Pointer, class T>
CANN_ASC_STL_HOST_SIMT_API unsigned check_bitwise(Pointer value, goldens<T> expected)
{
    value->store(expected.maximum, asc::std::memory_order_relaxed);
    unsigned failures = value->fetch_add(T{1}, asc::std::memory_order_relaxed) != expected.maximum;
    failures += value->fetch_or(T{1}, asc::std::memory_order_acq_rel) != expected.minimum;
    failures += check_strong(value, expected.minimum_plus_one, T{3});
    value->store(expected.maximum, asc::std::memory_order_relaxed);
    failures += value->fetch_add(T{1}, asc::std::memory_order_relaxed) != expected.maximum;
    failures += value->fetch_and(expected.all_bits, asc::std::memory_order_acq_rel) != expected.minimum;
    failures += check_weak(value, expected.minimum, T{4});
    value->store(expected.minimum, asc::std::memory_order_relaxed);
    failures += value->fetch_sub(T{1}, asc::std::memory_order_relaxed) != expected.minimum;
    failures += value->fetch_xor(T{1}, asc::std::memory_order_acq_rel) != expected.maximum;
    failures += check_strong(value, expected.maximum_minus_one, T{6});
    return failures;
}

template <class Pointer, class T>
CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned check_all(Pointer value, goldens<T> expected)
{
    return check_arithmetic(value, expected) + check_failure(value, expected) + check_bitwise(value, expected);
}
#endif

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
CANN_ASC_STL_HOST_API unsigned evaluate_host()
{
    asc::std::atomic<__UINT8_TYPE__> u8{0};
    asc::std::atomic<__INT8_TYPE__> i8{0};
    asc::std::atomic<__UINT16_TYPE__> u16{0};
    asc::std::atomic<__INT16_TYPE__> i16{0};
    unsigned failures = check_all(&u8, goldens<__UINT8_TYPE__>{0, 255, 1, 254, 255});
    failures += check_all(&i8, goldens<__INT8_TYPE__>{-128, 127, -127, 126, -1});
    failures += check_all(&u16, goldens<__UINT16_TYPE__>{0, 65535, 1, 65534, 65535});
    failures += check_all(&i16, goldens<__INT16_TYPE__>{-32768, 32767, -32767, 32766, -1});
    return failures;
}
#endif

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class OutputPointer, class T>
CANN_ASC_STL_SIMT_API unsigned check_device_cell(OutputPointer address, goldens<T> expected)
{
    using atomic_type = asc::std::atomic<T>;
    static_assert(sizeof(atomic_type) == sizeof(__INT32_TYPE__));
    static_assert(alignof(atomic_type) <= alignof(__INT32_TYPE__));
    // Caller-owned, aligned GM storage; explicitly start and end each object.
    auto* value = ::new (static_cast<void*>(address)) atomic_type(T{});
    const unsigned failures = check_all(value, expected);
    value->~atomic_type();
    return failures;
}

template <class OutputPointer>
CANN_ASC_STL_SIMT_API unsigned evaluate_device(OutputPointer storage)
{
    unsigned failures = check_device_cell(storage, goldens<__UINT8_TYPE__>{0, 255, 1, 254, 255});
    failures += check_device_cell(storage + 1, goldens<__INT8_TYPE__>{-128, 127, -127, 126, -1});
    failures += check_device_cell(storage + 2, goldens<__UINT16_TYPE__>{0, 65535, 1, 65534, 65535});
    failures += check_device_cell(storage + 3, goldens<__INT16_TYPE__>{-32768, 32767, -32767, 32766, -1});
    return failures;
}
#endif

}  // namespace asc_stl_narrow_atomic_cas_test

#endif  // ASC_STL_TEST_NARROW_ATOMIC_CAS_SEMANTICS_H
