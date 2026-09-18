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
#ifndef ASC_STL_TEST_B018_SEMANTICS_H
#define ASC_STL_TEST_B018_SEMANTICS_H
#include <asc/std/__algorithm/adjacent_find.h>
#include <asc/std/__algorithm/half_positive.h>
#include <asc/std/__charconv/from_chars_result.h>
#include <asc/std/__chrono/day.h>
#include <asc/std/__chrono/month.h>
#include <asc/std/__chrono/time_point.h>
#include <asc/std/__chrono/year.h>
#include <asc/std/__expected/unexpect.h>
#include <asc/std/__expected/unexpected.h>
#include <asc/std/__iterator/back_insert_iterator.h>
#include <asc/std/__iterator/front_insert_iterator.h>
#include <asc/std/__iterator/insert_iterator.h>
#include <asc/std/__iterator/move_sentinel.h>
#include <asc/std/__memory/allocator_traits.h>
#include <asc/std/__random/generate_canonical.h>
#include <asc/std/__ranges/rbegin.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__variant/visit.h>
#include <asc/std/array>
#include <asc/std/span>

namespace asc_stl_b018_test {
struct clock {
    using duration = asc::std::chrono::duration<int>;
};
struct generator {
    using result_type = unsigned int;
    unsigned int value = 0;
    CANN_ASC_STL_API static constexpr result_type min() noexcept
    {
        return 0;
    }
    CANN_ASC_STL_API static constexpr result_type max() noexcept
    {
        return 15;
    }
    CANN_ASC_STL_API result_type operator()() noexcept
    {
        return value++ & 15U;
    }
};
struct maximum_generator {
    using result_type = unsigned int;
    CANN_ASC_STL_API static constexpr result_type min() noexcept
    {
        return 0;
    }
    CANN_ASC_STL_API static constexpr result_type max() noexcept
    {
        return ~result_type{};
    }
    CANN_ASC_STL_API result_type operator()() noexcept
    {
        return max();
    }
};
struct plus_one {
    CANN_ASC_STL_API constexpr int operator()(int value) const noexcept
    {
        return value + 1;
    }
};
struct tiny_view : asc::std::ranges::view_interface<tiny_view> {
    int* first{};
    int* last{};
    CANN_ASC_STL_API constexpr tiny_view(int* first_value, int* last_value) noexcept
        : first(first_value), last(last_value)
    {}
    CANN_ASC_STL_API constexpr int* begin() const noexcept
    {
        return first;
    }
    CANN_ASC_STL_API constexpr int* end() const noexcept
    {
        return last;
    }
};
struct tiny_container {
    using value_type = int;
    using iterator = int*;
    int values[6]{};
    unsigned int used{};
    CANN_ASC_STL_API void push_back(int value) noexcept
    {
        values[used++] = value;
    }
    CANN_ASC_STL_API void push_front(int value) noexcept
    {
        for (unsigned int index = used; index != 0; --index) {
            values[index] = values[index - 1];
        }
        values[0] = value;
        ++used;
    }
    CANN_ASC_STL_API iterator insert(iterator position, int value) noexcept
    {
        const auto offset = static_cast<unsigned int>(position - values);
        for (unsigned int index = used; index != offset; --index) {
            values[index] = values[index - 1];
        }
        values[offset] = value;
        ++used;
        return values + offset;
    }
};
template <class T>
struct tiny_allocator {
    using value_type = T;
    using pointer = T*;
    template <class U>
    struct rebind {
        using other = tiny_allocator<U>;
    };
    T* storage{};
    CANN_ASC_STL_API T* allocate(unsigned long) noexcept
    {
        return storage;
    }
    CANN_ASC_STL_API T* allocate(unsigned long, const void*) noexcept
    {
        return storage;
    }
    CANN_ASC_STL_API void deallocate(T*, unsigned long) noexcept
    {}
};
CANN_ASC_STL_API int evaluate_common() noexcept
{
    int failures = 0;
    asc::std::array<int, 4> values{{1, 2, 2, 4}};
    failures += values.size() != 4 || asc::std::get<1>(values) != 2;
    failures += asc::std::adjacent_find(values.begin(), values.end()) != values.begin() + 1;
    failures += asc::std::__half_positive(7) != 3;
    asc::std::span<int, 4> fixed(values);
    asc::std::span<int> dynamic(values.data(), values.size());
    failures += fixed.size_bytes() != 4 * sizeof(int) || dynamic.last(1)[0] != 4;
    failures += asc::std::as_bytes(fixed).size() != 4 * sizeof(int);

    asc::std::chrono::day day(31);
    asc::std::chrono::month month(12);
    asc::std::chrono::year year(2024);
    failures += !day.ok() || !month.ok() || !year.ok() || !year.is_leap();
    asc::std::chrono::time_point<clock> point(clock::duration(7));
    point += clock::duration(2);
    failures += point.time_since_epoch().count() != 9;

    asc::std::unexpected<int> error(5);
    failures += error.error() != 5;
    asc::std::variant<int, unsigned int> variant(3);
    failures += asc::std::visit(plus_one{}, variant) != 4;
    asc::std::move_sentinel<int*> sentinel(values.end());
    failures += sentinel.base() != values.end();

    tiny_view view{values.data(), values.data() + values.size()};
    failures += view.empty() || view.front() != 1 || view.back() != 4 || view.size() != 4;
    failures += *asc::std::ranges::rbegin(values) != 4;
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    asc::std::span<int> range_span(view);
    failures += range_span.size() != 4 || range_span.data() != values.data();
#endif
    tiny_container container{};
    *asc::std::back_inserter(container) = 2;
    *asc::std::front_inserter(container) = 1;
    *asc::std::inserter(container, container.values + 1) = 3;
    failures += container.used != 3 || container.values[0] != 1 || container.values[1] != 3 || container.values[2] != 2;
    int allocated = 0;
    tiny_allocator<int> allocator{&allocated};
    using traits = asc::std::allocator_traits<tiny_allocator<int>>;
    int* allocation = traits::allocate(allocator, 1);
    traits::construct(allocator, allocation, 9);
    failures += allocation != &allocated || allocated != 9 || traits::max_size(allocator) == 0;
    traits::destroy(allocator, allocation);
    traits::deallocate(allocator, allocation, 1);
    generator random{};
    const float sample = asc::std::generate_canonical<float, 8>(random);
    failures += sample < 0.0F || sample >= 1.0F;
    maximum_generator maximum_random{};
    const float maximum_sample = asc::std::generate_canonical<float, 24>(maximum_random);
    failures += maximum_sample < 0.0F || maximum_sample >= 1.0F;
    asc::std::from_chars_result parsed{nullptr, asc::std::errc{}};
    failures += parsed.ptr != nullptr;
    return failures;
}
}  // namespace asc_stl_b018_test
#endif
