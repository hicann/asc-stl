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

#ifndef ASC_STL_TEST_W13_W14_SEMANTICS_H
#define ASC_STL_TEST_W13_W14_SEMANTICS_H

#include <asc/__detail/attributes.h>
#include <asc/barrier>
#include <asc/bit>
#include <asc/latch>
#include <asc/semaphore>
#include <asc/utility>
#include <asc/std/bit>
#include <asc/std/cctype>
#include <asc/std/cerrno>
#include <asc/std/compare>
#include <asc/std/cwchar>
#include <asc/std/exception>
#include <asc/std/linalg>
#include <asc/std/numeric>
#include <asc/std/random>
#include <asc/std/system_error>
#include <asc/std/type_traits>

#include "cxx17_foundation_semantics.h"
#include "cxx17_container_semantics.h"
#include "cxx17_views_semantics.h"

namespace asc_stl_w13_w14_test {

struct add_index {
    CANN_ASC_STL_API void operator()(asc::detail::static_for_index<int, 0>, int* value) const
    {
        *value += 1;
    }
    template <int Index>
    CANN_ASC_STL_API void operator()(asc::detail::static_for_index<int, Index>, int* value) const
    {
        *value += Index + 1;
    }
};

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_utility_cctype()
{
    unsigned int failures = 0;
    failures += !asc::in_range(4, 1, 4) || asc::in_range(5, 1, 4);
    int sum = 0;
    asc::static_for<int, 0, 4>(add_index{}, &sum);
    failures += sum != 10;
    failures += !asc::std::isalpha('Q') || asc::std::tolower('Q') != 'q' || asc::std::isdigit('x');
    return failures;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_bit()
{
    unsigned int failures = 0;
    failures += asc::bit_reverse<__UINT32_TYPE__>(0x00000001U) != 0x80000000U;
    failures += asc::bitmask<__UINT64_TYPE__>(8, 16) != 0x00ffff00ULL;
    failures += asc::bitfield_extract<__UINT32_TYPE__>(0xdeadbeefU, 8, 12) != 0x0dbeU;
    failures += asc::bitfield_insert<__UINT32_TYPE__>(0xffff0000U, 0x123U, 4, 12) != 0xffff1230U;
    failures += asc::std::popcount(0xf0U) != 4 || asc::std::countl_zero(1U) != 31;
    failures += asc::std::byteswap(0x11223344U) != 0x44332211U;
    return failures;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_types()
{
    unsigned int failures = 0;
    failures |= !asc::std::is_same_v<asc::std::remove_const_t<const int>, int> ? 1U : 0U;
    failures |= !asc::std::is_error_condition_enum<asc::std::errc>::value ? 2U : 0U;
    failures |= static_cast<int>(asc::std::errc::invalid_argument) != 22 ? 4U : 0U;
    failures |= EDOM != 33 || EILSEQ != 84 || ERANGE != 34 ? 8U : 0U;
    failures |= !(asc::std::strong_ordering::less < nullptr) ? 16U : 0U;
    return failures;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_cwide_length()
{
    const wchar_t word[] = {L'a', L's', L'c', L'\0'};
    return asc::std::wcslen(word) != 3 ? 1U : 0U;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_cwide_search(const wchar_t* word)
{
    const wchar_t* found = asc::std::wcschr(word, L's');
    return found == nullptr || found[0] != L's' || found[1] != L'c' ? 2U : 0U;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_cwide_search()
{
    const wchar_t word[] = {L'a', L's', L'c', L'\0'};
    return evaluate_cwide_search(word);
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_cwide()
{
    return evaluate_cwide_length() | evaluate_cwide_search();
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_types_cwide()
{
    return evaluate_types() + evaluate_cwide();
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_foundation()
{
    return evaluate_utility_cctype() + evaluate_bit() + evaluate_types_cwide();
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_linalg()
{
    unsigned int failures = 0;
    int values[] = {1, 2, 3, 4, 5, 6};
    using shape = asc::std::extents<__SIZE_TYPE__, 2, 3>;
    asc::std::mdspan<int, shape> matrix(values, shape{});
    const auto scaled = asc::std::linalg::scaled(2, matrix);
    failures += scaled.accessor().access(scaled.data_handle(), scaled.mapping()(1, 2)) != 12;
    const auto transposed = asc::std::linalg::transposed(matrix);
    failures += transposed.extent(0) != 3 || transposed.extent(1) != 2;
    failures += transposed.accessor().access(transposed.data_handle(), transposed.mapping()(2, 1)) != 6;
    const auto twice = asc::std::linalg::transposed(transposed);
    failures += twice.extent(0) != 2 || twice.extent(1) != 3 ||
        twice.accessor().access(twice.data_handle(), twice.mapping()(1, 2)) != 6;
    transposed.accessor().access(transposed.data_handle(), transposed.mapping()(2, 1)) = 42;
    failures += values[5] != 42;
    asc::std::layout_left::mapping<shape> left_mapping(shape{});
    asc::std::mdspan<int, shape, asc::std::layout_left> left_matrix(values, left_mapping);
    const auto left_transposed = asc::std::linalg::transposed(left_matrix);
    failures += left_transposed.stride(0) != 2 || left_transposed.stride(1) != 1;
    int strided_values[] = {1, 2, 3, 4, 5, 6, 7, 8};
    asc::std::array<__SIZE_TYPE__, 2> strides{4, 1};
    asc::std::layout_stride::mapping<shape> stride_mapping(shape{}, strides);
    asc::std::mdspan<int, shape, asc::std::layout_stride> stride_matrix(strided_values, stride_mapping);
    const auto stride_transposed = asc::std::linalg::transposed(stride_matrix);
    failures += stride_transposed.stride(0) != 1 || stride_transposed.stride(1) != 4;
    failures +=
        stride_transposed.accessor().access(stride_transposed.data_handle(), stride_transposed.mapping()(2, 1)) != 7;
    asc::std::complex<float> complex_values[] = {{1.0F, 2.0F}, {3.0F, -4.0F}};
    using complex_shape = asc::std::extents<__SIZE_TYPE__, 1, 2>;
    asc::std::mdspan<asc::std::complex<float>, complex_shape> complex_matrix(complex_values, complex_shape{});
    const auto conjugated = asc::std::linalg::conjugated(complex_matrix);
    const auto value = conjugated.accessor().access(conjugated.data_handle(), conjugated.mapping()(0, 0));
    failures += value.real() != 1.0F || value.imag() != -2.0F;
    const auto restored = asc::std::linalg::conjugated(conjugated);
    failures += restored.accessor().access(restored.data_handle(), restored.mapping()(0, 1)).imag() != -4.0F;
    return failures;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_random()
{
    unsigned int failures = 0;
    asc::std::philox4x32 engine32;
    asc::std::philox4x64 engine64;
    __UINT32_TYPE__ value32 = 0;
    __UINT64_TYPE__ value64 = 0;
    engine32.discard(9999);
    engine64.discard(9999);
    value32 = engine32();
    value64 = engine64();
    failures += value32 != 1955073260U || value64 != 3409172418970261260ULL;
    asc::std::philox4x32 left(7), right(7);
    failures += left != right;
    (void)left();
    right.discard(1);
    failures += left != right;
    asc::std::philox4x32 counter_engine;
    asc::std::philox4x32 discard_engine;
    asc::std::array<asc::std::philox4x32::result_type, 4> counter{0, 0, 0, 100};
    counter_engine.set_counter(counter);
    discard_engine.discard(400);
    failures += counter_engine != discard_engine || counter_engine() != 940657802U;
    asc::std::uniform_real_distribution<float> distribution(2.0F, 5.0F);
    const auto parameters = distribution.param();
    failures += parameters.a() != 2.0F || parameters.b() != 5.0F;
    distribution.reset();
    distribution.param(asc::std::uniform_real_distribution<float>::param_type(1.0F, 3.0F));
    failures += distribution.a() != 1.0F || distribution.b() != 3.0F;
    asc::std::philox4x32 uniform_engine(19);
    const float sample = distribution(uniform_engine);
    failures += sample < 1.0F || sample >= 3.0F;
    failures += distribution != asc::std::uniform_real_distribution<float>(1.0F, 3.0F);
    asc::std::minstd_rand endpoint_engine(247665088);
    asc::std::uniform_real_distribution<float> endpoint_distribution(2.0F, 5.0F);
    const float endpoint_sample = endpoint_distribution(endpoint_engine);
    failures += endpoint_sample < 2.0F || endpoint_sample >= 5.0F;
    asc::std::minstd_rand narrow_engine(247665088);
    const float narrow_upper = __builtin_bit_cast(float, static_cast<__UINT32_TYPE__>(0x3F800001U));
    asc::std::uniform_real_distribution<float> narrow_distribution(1.0F, narrow_upper);
    const float narrow_sample = narrow_distribution(narrow_engine, narrow_distribution.param());
    failures += narrow_sample < 1.0F || narrow_sample >= narrow_upper;
    return failures;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_numeric()
{
    int values[] = {1, 2, 3, 4};
    int partial[4]{};
    unsigned int failures = 0;
    failures += asc::std::accumulate(values, values + 4, 0) != 10;
    asc::std::partial_sum(values, values + 4, partial);
    failures += partial[0] != 1 || partial[3] != 10;
    failures += asc::std::gcd(42, 30) != 6 || asc::std::lcm(6, 15) != 30;
    failures += asc::std::midpoint(2, 8) != 5;
    failures += asc::std::saturating_add(2147483647, 1) != 2147483647;
    failures += asc_stl_cxx17_foundation::evaluate() != 0;
    failures += asc_stl_cxx17_container_test::evaluate() != 0;
    failures += asc_stl_cxx17_views_test::evaluate() != 0;
    return failures;
}

CANN_ASC_STL_API unsigned int evaluate()
{
    return evaluate_foundation() + evaluate_linalg() + evaluate_random() + evaluate_numeric();
}

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class ResultPointer>
CANN_ASC_STL_SIMT_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_sync(
    ResultPointer result, unsigned int thread_count)
{
    auto& block_barrier = *reinterpret_cast<asc::barrier<asc::memory_scope::block>*>(&result[400]);
    auto& device_barrier = *reinterpret_cast<asc::barrier<asc::memory_scope::device>*>(&result[408]);
    auto& completion = *reinterpret_cast<asc::latch<asc::memory_scope::block>*>(&result[416]);
    auto& permits = *reinterpret_cast<asc::counting_semaphore<asc::memory_scope::block, 8>*>(&result[420]);
    auto& single = *reinterpret_cast<asc::barrier<asc::memory_scope::block>*>(&result[460]);
    if (threadIdx.x == 0) {
        ::new (static_cast<void*>(&result[400])) asc::barrier<asc::memory_scope::block>(thread_count);
        ::new (static_cast<void*>(&result[408])) asc::barrier<asc::memory_scope::device>(thread_count);
        ::new (static_cast<void*>(&result[416])) asc::latch<asc::memory_scope::block>(thread_count);
        ::new (static_cast<void*>(&result[420])) asc::counting_semaphore<asc::memory_scope::block, 8>(0);
        ::new (static_cast<void*>(&result[460])) asc::barrier<asc::memory_scope::block>(1);
        result[430] = 77;
        permits.release(thread_count);
    }
    asc_syncthreads();
    unsigned int failures = 0;
    for (unsigned int phase = 0; phase < 3; ++phase) {
        result[440 + threadIdx.x] += phase + 1;
        auto block_token = block_barrier.arrive();
        asc_syncthreads();
        block_barrier.wait(static_cast<asc::barrier_arrival_token&&>(block_token));
        if (threadIdx.x == 0) {
            unsigned int sum = 0;
            for (unsigned int index = 0; index < thread_count; ++index) {
                sum += result[440 + index];
            }
            failures += sum != thread_count * (phase + 1) * (phase + 2) / 2;
        }
        auto device_token = device_barrier.arrive();
        asc_syncthreads();
        device_barrier.wait(static_cast<asc::barrier_arrival_token&&>(device_token));
    }
    asc::atomic_ref<__UINT32_TYPE__, asc::memory_scope::block> observed(result[432]);
    (void)observed.fetch_add(result[430] == 77 ? 1U : 100U, asc::std::memory_order_relaxed);
    completion.count_down();
    asc_syncthreads();
    completion.wait();
    if (threadIdx.x == 0) {
        single.arrive_and_wait();
        bool acquired = true;
        for (unsigned int index = 0; index < thread_count; ++index) {
            acquired = permits.try_acquire() && acquired;
        }
        failures += result[432] != thread_count || !acquired || permits.try_acquire();
    }
    auto final_token = block_barrier.arrive();
    asc_syncthreads();
    block_barrier.wait(static_cast<asc::barrier_arrival_token&&>(final_token));
    return threadIdx.x == 0 ? failures : 0;
}
#endif

}  // namespace asc_stl_w13_w14_test

#endif  // ASC_STL_TEST_W13_W14_SEMANTICS_H
