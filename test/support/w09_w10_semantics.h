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

#ifndef ASC_STL_TEST_W09_W10_SEMANTICS_H
#define ASC_STL_TEST_W09_W10_SEMANTICS_H

#include <asc/iterator>
#include <asc/mdspan>
#include <asc/std/__ranges/subrange.h>
#include <asc/std/barrier>
#include <asc/std/chrono>
#include <asc/std/memory>
#include <asc/std/mutex>
#include <asc/std/variant>
#include "mdspan_slice_regression.h"

namespace asc_stl_w09_w10_test {

struct times_two {
    CANN_ASC_STL_API int operator()(int value) const noexcept
    {
        return value * 2;
    }
};

struct add_values {
    CANN_ASC_STL_API int operator()(int left, int right) const noexcept
    {
        return left + right;
    }
};

struct reverse_four {
    CANN_ASC_STL_API __SIZE_TYPE__ operator()(__SIZE_TYPE__ value) const noexcept
    {
        return 3 - value;
    }
};

struct mutex_probe {
    bool locked = false;
    CANN_ASC_STL_API void lock() noexcept
    {
        locked = true;
    }
    CANN_ASC_STL_API bool try_lock() noexcept
    {
        if (locked)
            return false;
        locked = true;
        return true;
    }
    CANN_ASC_STL_API void unlock() noexcept
    {
        locked = false;
    }
};

CANN_ASC_STL_API int evaluate_iterator()
{
    int values[6] = {2, 4, 6, 8, 10, 12};
    int indices[3] = {2, 0, 1};
    auto constant = asc::make_constant_iterator(7);
    auto counting = asc::make_counting_iterator(3);
    auto permutation = asc::make_permutation_iterator(values, indices);
    auto strided = asc::make_strided_iterator(values, 2);
    auto shuffled = asc::make_shuffle_iterator(reverse_four{}, static_cast<__SIZE_TYPE__>(0));
    auto transformed = asc::make_transform_iterator(values, times_two{});
    if (*constant != 7 || constant[9] != 7 || counting[4] != 7)
        return 1;
    if (*permutation != 6 || permutation[1] != 2 || strided[2] != 10)
        return 2;
    if (*shuffled != 3 || shuffled[2] != 1 || transformed[2] != 12)
        return 3;
    auto zipped = asc::make_zip_iterator(values, values + 1);
    auto tuple = *zipped;
    if (tuple.template get<0>() != 2 || tuple.template get<1>() != 4)
        return 4;
    auto zipped_sum = asc::make_zip_transform_iterator(add_values{}, values, values + 1);
    if (*zipped_sum != 6)
        return 5;
    int output = 0;
    auto output_iterator = asc::make_transform_output_iterator(&output, times_two{});
    *output_iterator = 5;
    if (output != 10)
        return 6;
    auto strided_end = strided + 3;
    if (strided_end - strided != 3 || strided[1] != 6 || *(strided_end - 1) != 10 || !(strided < strided_end) ||
        !(strided_end > strided) || !(strided <= strided_end) || !(strided_end >= strided) || strided_end == strided ||
        2 + strided != strided + 2)
        return 7;
    auto forward = strided;
    if (*forward++ != 2 || *forward != 6 || *++forward != 10 || *forward-- != 10 || *--forward != 2)
        return 8;
    forward += 2;
    forward -= 1;
    if (*forward != 6 || forward - strided != 1)
        return 9;
    auto reverse = asc::make_strided_iterator(values + 5, -2);
    auto reverse_end = reverse + 2;
    if (*reverse != 12 || reverse[1] != 8 || *reverse_end != 4 || reverse_end - reverse != 2 ||
        !(reverse < reverse_end) || !(reverse_end > reverse))
        return 10;
    return 0;
}

CANN_ASC_STL_API int evaluate_alignment_chrono()
{
    alignas(16) unsigned char storage[64]{};
    void* pointer = storage + 1;
    asc::std::size_t space = 63;
    if (asc::std::align(16, 8, pointer, space) == nullptr)
        return 10;
    if (reinterpret_cast<asc::std::uintptr_t>(pointer) % 16 != 0 || space != 48)
        return 11;
    void* unchanged = pointer;
    asc::std::size_t unchanged_space = 7;
    if (asc::std::align(8, 8, unchanged, unchanged_space) != nullptr)
        return 12;
    if (unchanged != pointer || unchanged_space != 7)
        return 13;
    if (asc::std::__is_valid_alignment(0) || asc::std::__is_valid_alignment(3))
        return 14;
    if (!asc::std::__is_valid_alignment(16))
        return 15;
    if (!asc::std::is_sufficiently_aligned<16>(storage))
        return 16;
    if (asc::std::is_sufficiently_aligned<16>(storage + 1))
        return 17;
    asc::std::chrono::duration<int, asc::std::ratio<1, 1000>> milliseconds(2500);
    const auto seconds = asc::std::chrono::duration_cast<asc::std::chrono::duration<int>>(milliseconds);
    if (seconds.count() != 2)
        return 18;
    namespace ch = ::asc::std::chrono;
    const ch::hh_mm_ss<ch::duration<int, asc::std::milli>> clock_parts{milliseconds};
    if (clock_parts.seconds().count() != 2 || clock_parts.subseconds().count() != 500 ||
        clock_parts.to_duration().count() != 2500)
        return 19;
    ch::month wrapped_month{12};
    ++wrapped_month;
    if (wrapped_month != ch::January)
        return 20;
    if (!ch::month_day{ch::February, ch::day{29}}.ok() || ch::month_day{ch::February, ch::day{30}}.ok())
        return 21;
    const ch::year_month_day leap_day = ch::year{2024} / ch::February / ch::day{29};
    if (!leap_day.ok() || (ch::year{2023} / ch::February / ch::day{29}).ok())
        return 22;
    if ((ch::year{2024} / (ch::February / ch::last)).day() != ch::day{29})
        return 23;
    if (((ch::year{2024} / (ch::February / ch::last)) + ch::months{1}).month() != ch::March)
        return 24;
    const ch::month_weekday second_monday{ch::March, ch::Monday[2]};
    if (!second_monday.ok() || second_monday.month() != ch::March || second_monday.weekday_indexed().index() != 2)
        return 25;
    const ch::month_weekday_last last_friday{ch::October, ch::Friday[ch::last]};
    if (!last_friday.ok() || last_friday.month() != ch::October || last_friday.weekday_last().weekday() != ch::Friday)
        return 26;
    return 0;
}

CANN_ASC_STL_API int evaluate_variant_pair()
{
    asc::std::variant<int, unsigned int> value(asc::std::in_place_index<0>, 9);
    if (!asc::std::holds_alternative<int>(value) || value.index() != 0)
        return 21;
    if (asc::std::get_if<int>(&value) == nullptr || *asc::std::get_if<int>(&value) != 9)
        return 22;
    value.emplace<1>(11u);
    if (!asc::std::holds_alternative<unsigned int>(value))
        return 23;
    asc::std::variant<int, unsigned int> source(asc::std::in_place_index<0>, 17);
    value = source;
    if (value.index() != 0 || asc::std::get<0>(value) != 17 || value.valueless_by_exception())
        return 24;
    source.emplace<1>(19u);
    value = asc::std::move(source);  // NOLINT(build/include_what_you_use)
    if (value.index() != 1 || asc::std::get<1>(value) != 19u || value.valueless_by_exception())
        return 25;
    value.emplace<int>(23);
    if (value.index() != 0 || asc::std::get<0>(value) != 23 || value.valueless_by_exception())
        return 26;
    return 0;
}

CANN_ASC_STL_API int evaluate_variant_nested()
{
    asc::std::variant<int, unsigned int, long> nested(asc::std::in_place_index<2>, 29L);
    asc::std::variant<int, unsigned int, long> nested_target(asc::std::in_place_index<0>, 0);
    nested_target = nested;
    if (nested_target.index() != 2 || asc::std::get<2>(nested_target) != 29L)
        return 27;
    nested.emplace<1>(31u);
    nested_target = asc::std::move(nested);  // NOLINT(build/include_what_you_use)
    if (nested_target.index() != 1 || asc::std::get<1>(nested_target) != 31u)
        return 28;
    nested_target.emplace<2>(37L);
    if (nested_target.index() != 2 || asc::std::get<2>(nested_target) != 37L || nested_target.valueless_by_exception())
        return 29;
    return 0;
}

CANN_ASC_STL_API int evaluate_memory_variant()
{
    alignas(int) unsigned char storage[sizeof(int)]{};
    int* object = asc::std::construct_at(reinterpret_cast<int*>(storage), 23);
    if (*object != 23)
        return 20;
    asc::std::destroy_at(object);
    const int pair_result = evaluate_variant_pair();
    if (pair_result != 0)
        return pair_result;
    return evaluate_variant_nested();
}

CANN_ASC_STL_API int evaluate_mutex()
{
    mutex_probe mutex;
    {
        asc::std::lock_guard<mutex_probe> guard(mutex);
        if (!mutex.locked)
            return 30;
    }
    asc::std::unique_lock<mutex_probe> lock(mutex, asc::std::defer_lock);
    if (!lock.try_lock() || !lock.owns_lock())
        return 31;
    lock.unlock();
    return mutex.locked ? 32 : 0;
}

CANN_ASC_STL_API int evaluate_mdspan()
{
    if (!asc_stl_mdspan_slice_test::evaluate())
        return 46;
    int values[12]{};
    using extents_type = asc::std::extents<asc::std::size_t, 3, asc::std::dynamic_extent>;
    extents_type extents(4);
    asc::std::mdspan<int, extents_type> right(values, extents);
    asc::std::array<asc::std::size_t, 2> index{2, 1};
    right[index] = 17;
    if (values[9] != 17 || right.size() != 12 || right.stride(0) != 4)
        return 40;
    asc::std::layout_left::mapping<extents_type> left(extents);
    if (left(2, 1) != 5 || left.required_span_size() != 12)
        return 41;
    asc::std::array<asc::std::size_t, 2> strides{5, 1};
    asc::std::layout_stride::mapping<extents_type> mapping(extents, strides);
    if (mapping(2, 1) != 11 || mapping.required_span_size() != 14)
        return 42;
    alignas(16) int aligned_values[4]{};
    asc::std::aligned_accessor<int, 16> accessor;
    accessor.access(aligned_values, 1) = 5;
    if (aligned_values[1] != 5)
        return 43;
    // subrange::size participates only in the sized category: size() is
    // available after sized construction.
    int storage_for_subrange[4]{0, 1, 2, 3};
    ::asc::std::ranges::subrange<int*> sized_subrange(storage_for_subrange, storage_for_subrange + 4, 4);
    if (sized_subrange.size() != 4)
        return 45;
    auto subview = asc::std::submdspan(right, asc::std::full_extent, asc::std::full_extent);
    subview[index] = 19;
    if (values[9] != 19 || subview.extent(0) != 3 || subview.extent(1) != 4)
        return 44;
    return 0;
}

CANN_ASC_STL_API int evaluate_extension_mdspan()
{
    using extents_type = asc::std::extents<asc::std::size_t, 2, 3>;
    extents_type extents;
    asc::steps<2> negative(-3, 1);
    asc::layout_stride_relaxed::mapping<extents_type, asc::steps<2>> reverse(extents, negative, 3);
    if (reverse(0, 2) != 5 || reverse(1, 2) != 2 || reverse.required_span_size() != 6)
        return 50;
    asc::steps<2> broadcast(0, 1);
    asc::layout_stride_relaxed::mapping<extents_type, asc::steps<2>> repeated(extents, broadcast, 0);
    if (repeated.is_unique() || repeated.required_span_size() != 3)
        return 51;
    using collision_extents = asc::std::extents<asc::std::size_t, 2, 2>;
    asc::layout_stride_relaxed::mapping<collision_extents, asc::steps<2>> collision(
        collision_extents{}, asc::steps<2>(1, 1), 0);
    if (collision.is_unique() || collision(1, 0) != collision(0, 1))
        return 52;
    asc::layout_stride_relaxed::mapping<collision_extents, asc::steps<2>> negative_collision(
        collision_extents{}, asc::steps<2>(-1, -1), 2);
    if (negative_collision.is_unique())
        return 53;
    return 0;
}

#if defined(CANN_ASC_STL_HAS_DLPACK) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
inline int evaluate_dlpack()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    int64_t shape[2] = {2, 3};
    int64_t stride_values[2] = {3, 1};
    DLTensor tensor{};
    tensor.data = values;
    tensor.device = DLDevice{kDLCPU, 0};
    tensor.ndim = 2;
    tensor.dtype = DLDataType{static_cast<uint8_t>(kDLInt), 32, 1};
    tensor.shape = shape;
    tensor.strides = stride_values;
    using extents_type = asc::std::dextents<asc::std::size_t, 2>;
    asc::host_mdspan<int, extents_type, asc::layout_stride_relaxed> view;
    if (!asc::to_host_mdspan<int, 2>(tensor, view))
        return 60;
    asc::std::array<asc::std::size_t, 2> index{1, 2};
    if (view[index] != 6)
        return 61;
    tensor.byte_offset = sizeof(int);
    using offset_extents = asc::std::dextents<asc::std::size_t, 1>;
    int64_t offset_shape[1] = {2};
    tensor.ndim = 1;
    tensor.shape = offset_shape;
    tensor.strides = nullptr;
    asc::host_mdspan<int, offset_extents, asc::layout_stride_relaxed> offset_view;
    if (!asc::to_host_mdspan<int, 1>(tensor, offset_view) || offset_view[0] != 2)
        return 65;
    tensor.byte_offset = 0;
    tensor.ndim = 2;
    tensor.shape = shape;
    tensor.strides = stride_values;
    asc::dlpack_tensor<2> result;
    if (!asc::to_dlpack_tensor(view, kDLCPU, 0, result))
        return 62;
    const DLTensor converted = result.get();
    if (converted.shape[0] != 2 || converted.shape[1] != 3 || converted.strides[0] != 3 ||
        converted.dtype.code != kDLInt || converted.dtype.bits != 32 || converted.dtype.lanes != 1)
        return 63;
    float float_values[2]{};
    using float_extents = asc::std::extents<asc::std::size_t, 2>;
    asc::host_mdspan<float, float_extents> float_view(float_values, float_extents{});
    asc::dlpack_tensor<1> float_result;
    if (!asc::to_dlpack_tensor(float_view, kDLCPU, 0, float_result) || float_result.get().dtype.code != kDLFloat)
        return 66;
    tensor.device.device_type = kDLExtDev;
    return asc::to_host_mdspan<int, 2>(tensor, view) ? 64 : 0;
}
#endif

}  // namespace asc_stl_w09_w10_test

#endif  // ASC_STL_TEST_W09_W10_SEMANTICS_H
