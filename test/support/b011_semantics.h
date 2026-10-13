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

#ifndef CANN_ASC_STL_TEST_SUPPORT_B011_SEMANTICS_H
#define CANN_ASC_STL_TEST_SUPPORT_B011_SEMANTICS_H

#include <asc/memory>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__algorithm/find_first_of.h>
#include <asc/std/__algorithm/iter_swap.h>
#include <asc/std/__cmath/fma.h>
#include <asc/std/__cmath/gamma.h>
#include <asc/std/__cmath/hyperbolic_functions.h>
#include <asc/std/__cmath/inverse_hyperbolic_functions.h>
#include <asc/std/__cmath/inverse_trigonometric_functions.h>
#include <asc/std/__cmath/remainder.h>
#include <asc/std/__cmath/roots.h>
#include <asc/std/__cmath/rounding_functions.h>
#include <asc/std/__cmath/trigonometric_functions.h>
#include <asc/std/__floating_point/arithmetic.h>
#include <asc/std/__floating_point/cast.h>
#include <asc/std/__floating_point/constants.h>
#include <asc/std/__floating_point/conversion_rank_order.h>
#include <asc/std/__floating_point/decompose.h>
#include <asc/std/__floating_point/mask.h>
#include <asc/std/__floating_point/native_type.h>
#include <asc/std/__floating_point/overflow_handler.h>
#include <asc/std/__iterator/size.h>
#include <asc/std/__ranges/enable_view.h>
#include <asc/std/__type_traits/is_same.h>

namespace asc_stl_b011_test {

struct compare {
    CANN_ASC_STL_API constexpr bool operator()(int left, int right) const noexcept
    {
        return left == right;
    }
};
struct view : asc::std::ranges::view_base {};
struct interface_view : asc::std::ranges::view_interface<interface_view> {
    int values[3] = {4, 6, 8};
    CANN_ASC_STL_API constexpr int* begin() noexcept
    {
        return values;
    }
    CANN_ASC_STL_API constexpr const int* begin() const noexcept
    {
        return values;
    }
    CANN_ASC_STL_API constexpr int* end() noexcept
    {
        return values + 3;
    }
    CANN_ASC_STL_API constexpr const int* end() const noexcept
    {
        return values + 3;
    }
};

static_assert(asc::std::ranges::enable_view<view>);
static_assert(asc::std::ranges::enable_view<interface_view>);
static_assert(!asc::std::ranges::enable_view<int>);
static_assert(asc::std::is_same_v<asc::std::__comp_ref_type<compare>, compare&>);
static_assert(asc::std::size("abc") == 4);
static_assert(asc::std::ssize("abc") == 4);
static_assert(asc::std::__fp_sign_mask_of_v<float> == 0x80000000U);
static_assert(asc::std::__fp_exp_mask_of_v<float> == 0x7F800000U);
static_assert(asc::std::__fp_get_exp(1.0F) == 0);
static_assert(asc::std::__fp_set_exp(1.0F, 2) == 4.0F);
static_assert(asc::std::__fp_neg(2.0F) == -2.0F);
static_assert(asc::std::__fp_cast<double>(2.0F) == 2.0);
static_assert(asc::std::__fp_has_native_type_v<asc::std::__fp_format::__binary32>);
static_assert(asc::std::__fp_conv_rank_order_v<float, double> == asc::std::__fp_conv_rank_order::__less);
static_assert(asc::std::__fp_is_implicit_conversion_v<float, double>);
static_assert(asc::std::__fp_is_explicit_conversion_v<double, float>);
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
static_assert(asc::std::is_same_v<decltype(asc::std::sin(1)), float>);  // 设备：整型经 float 重载
#else
static_assert(asc::std::is_same_v<decltype(asc::std::sin(1)), double>);  // 宿主：整型提升对齐标准
#endif
static_assert(asc::std::is_same_v<decltype(asc::std::fma(1, 2.0F, 3.0F)), float>);
static_assert(asc::std::is_same_v<decltype(asc::std::atan2(1.0F, 2.0F)), float>);
static_assert(asc::std::is_same_v<decltype(asc::std::remquo(1.0L, 2.0L, static_cast<int*>(nullptr))), float>);
static_assert(asc::std::is_same_v<decltype(asc::std::lrint(1.0F)), long>);
static_assert(asc::std::is_same_v<decltype(asc::std::llround(1.0)), long long>);
static_assert(asc::std::__fp_max<float>() > 3.0e38F);
static_assert(asc::std::__fp_min<float>() > 0.0F);
static_assert(asc::std::__fp_lowest<float>() < -3.0e38F);
static_assert(
    asc::std::__fp_overflow_handler<asc::std::__fp_overflow_handler_kind::__sat_finite>::__handle_overflow<float>() ==
    asc::std::__fp_max<float>());
static_assert(asc::memory_space_of_v<asc::gm_span<int>> == asc::memory_space::global);
static_assert(asc::aligned_size(17U, 8U) == 24U);
static_assert(asc::is_aligned(24U, 8U));

CANN_ASC_STL_API constexpr int evaluate_constexpr() noexcept
{
    int values[] = {7, 3, 9, 5};
    int sought[] = {2, 5};
    auto found = asc::std::find_first_of(values, values + 4, sought, sought + 2, compare{});
    asc::std::iter_swap(values, values + 1);
    interface_view range{};
    const interface_view& const_range = range;
    const bool interface_ok = !range.empty() && range.data() == range.begin() && range.size() == 3 &&
        range.front() == 4 && range.back() == 8 && range[1] == 6 && !const_range.empty() &&
        const_range.data() == const_range.begin() && const_range.size() == 3 && const_range.front() == 4 &&
        const_range.back() == 8 && const_range[1] == 6;
    return found == values + 3 && values[0] == 3 && values[1] == 7 && interface_ok ? 0 : 1;
}

static_assert(evaluate_constexpr() == 0);

CANN_ASC_STL_API unsigned evaluate_runtime_failures() noexcept
{
#if !CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
    alignas(16) unsigned char storage[64] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    asc::arena_allocator<int> allocator(arena);
    int* allocated = allocator.allocate(4);
    const auto first_used = arena.used();
    const bool arena_ok = allocated != nullptr && asc::is_aligned(allocated, alignof(int)) && first_used >= 16 &&
        arena.remaining() + first_used == arena.capacity();
    asc::gm_span<int> span(allocated, 4);
    if (allocated != nullptr) {
        span[0] = 11;
        span[1] = 13;
    }
    const bool alias_ok = span.data() == allocated && span.size() == 4 && span.first(2)[1] == 13 &&
        span.subspan(1, 2).data() == allocated + 1;
    asc::temporary_storage_ref temporary(storage, sizeof(storage), asc::memory_space::local);
    const bool storage_ok = temporary.data() == storage && temporary.size_bytes() == sizeof(storage) &&
        temporary.space() == asc::memory_space::local;
    arena.reset();
    const bool lifecycle_ok = arena.used() == 0 && allocator == asc::arena_allocator<int>(arena);
    int quotient = 0;
    const float nan = asc::std::__fp_nan<float>();
    const float infinity = asc::std::__fp_inf<float>();
    const float sin_nan = asc::std::sin(nan);
    const float sqrt_nan = asc::std::sqrt(-1.0F);
    const bool trig_ok = asc::std::sin(0.0F) == 0.0F && asc::std::sinf(0.0F) == 0.0F && asc::std::cos(0.0F) == 1.0F &&
        asc::std::cosf(0.0F) == 1.0F && asc::std::tan(0.0F) == 0.0F && asc::std::tanf(0.0F) == 0.0F &&
        asc::std::asin(0.0F) == 0.0F && asc::std::asinf(0.0F) == 0.0F && asc::std::acos(1.0F) == 0.0F &&
        asc::std::acosf(1.0F) == 0.0F && asc::std::atan(0.0F) == 0.0F && asc::std::atanf(0.0F) == 0.0F &&
        asc::std::atan2(0.0F, 1.0F) == 0.0F && asc::std::atan2f(0.0F, 1.0F) == 0.0F;
    const bool hyperbolic_ok = asc::std::sinh(0.0F) == 0.0F && asc::std::sinhf(0.0F) == 0.0F &&
        asc::std::cosh(0.0F) == 1.0F && asc::std::coshf(0.0F) == 1.0F && asc::std::tanh(0.0F) == 0.0F &&
        asc::std::tanhf(0.0F) == 0.0F && asc::std::asinh(0.0F) == 0.0F && asc::std::asinhf(0.0F) == 0.0F &&
        asc::std::acosh(1.0F) == 0.0F && asc::std::acoshf(1.0F) == 0.0F && asc::std::atanh(0.0F) == 0.0F &&
        asc::std::atanhf(0.0F) == 0.0F;
    const bool roots_gamma_ok = asc::std::sqrt(9.0F) == 3.0F && asc::std::sqrtf(9.0F) == 3.0F &&
        asc::std::cbrt(8.0F) == 2.0F && asc::std::cbrtf(8.0F) == 2.0F && asc::std::tgamma(1.0F) == 1.0F &&
        asc::std::tgammaf(1.0F) == 1.0F && asc::std::lgamma(1.0F) == 0.0F && asc::std::lgammaf(1.0F) == 0.0F;
    const bool remainder_ok = asc::std::remainder(5.0F, 2.0F) == 1.0F && asc::std::remainderf(5.0F, 2.0F) == 1.0F &&
        asc::std::remquo(5.0F, 2.0F, &quotient) == 1.0F && asc::std::remquof(5.0F, 2.0F, &quotient) == 1.0F &&
        asc::std::nextafter(0.0F, 1.0F) > 0.0F && asc::std::nextafterf(0.0F, 1.0F) > 0.0F;
    const bool rounding_ok = asc::std::floor(2.75F) == 2.0F && asc::std::floorf(2.75F) == 2.0F &&
        asc::std::ceil(2.25F) == 3.0F && asc::std::ceilf(2.25F) == 3.0F && asc::std::trunc(-2.75F) == -2.0F &&
        asc::std::truncf(-2.75F) == -2.0F && asc::std::round(2.5F) == 3.0F && asc::std::roundf(-2.5F) == -3.0F &&
        asc::std::rint(2.0F) == 2.0F && asc::std::rintf(2.0F) == 2.0F && asc::std::nearbyint(2.0F) == 2.0F &&
        asc::std::nearbyintf(2.0F) == 2.0F && asc::std::lrint(2.0F) == 2L && asc::std::lrintf(2.0F) == 2L &&
        asc::std::llrint(2.0F) == 2LL && asc::std::llrintf(2.0F) == 2LL && asc::std::lround(2.5F) == 3L &&
        asc::std::lroundf(2.5F) == 3L && asc::std::llround(2.5F) == 3LL && asc::std::llroundf(2.5F) == 3LL;
    const bool sin_nan_ok = sin_nan != sin_nan;
    const bool sqrt_nan_ok = sqrt_nan != sqrt_nan;
    const bool sqrt_infinity_ok = asc::std::sqrt(infinity) == infinity;
    const bool round_signed_zero_ok = asc::std::__fp_get_storage(asc::std::round(-0.0F)) == 0x80000000U;
    const bool floor_signed_zero_ok = asc::std::__fp_get_storage(asc::std::floor(-0.0F)) == 0x80000000U;
    const bool precision_ok = asc::std::fma(2.0F, 3.0F, 1.0F) == 7.0F && asc::std::fmaf(2.0F, 3.0F, 1.0F) == 7.0F;
#else
    const bool arena_ok = true;
    const bool alias_ok = true;
    const bool storage_ok = true;
    const bool lifecycle_ok = true;
#endif
    unsigned failures = 0;
    failures |= evaluate_constexpr() == 0 ? 0U : 1U;
    failures |= arena_ok ? 0U : 2U;
    failures |= alias_ok ? 0U : 4U;
    failures |= storage_ok ? 0U : 8U;
    failures |= lifecycle_ok ? 0U : 16U;
#if !CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
    failures |= trig_ok ? 0U : 32U;
    failures |= hyperbolic_ok ? 0U : 64U;
    failures |= roots_gamma_ok ? 0U : 128U;
    failures |= remainder_ok ? 0U : 256U;
    failures |= rounding_ok ? 0U : 512U;
    failures |= sin_nan_ok ? 0U : 1024U;
    failures |= sqrt_nan_ok ? 0U : 2048U;
    failures |= sqrt_infinity_ok ? 0U : 4096U;
    failures |= round_signed_zero_ok ? 0U : 8192U;
    failures |= floor_signed_zero_ok ? 0U : 16384U;
    failures |= precision_ok ? 0U : 32768U;
#endif
    return failures;
}

CANN_ASC_STL_API int evaluate_runtime() noexcept
{
    return evaluate_runtime_failures() == 0 ? 0 : 1;
}

}  // namespace asc_stl_b011_test

#endif  // CANN_ASC_STL_TEST_SUPPORT_B011_SEMANTICS_H
