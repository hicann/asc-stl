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

#ifndef ASC_STL_TEST_SUPPORT_B023_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_B023_SEMANTICS_H

#include <asc/__memory/pools.h>
#include <asc/algorithm>
#include <asc/std/__algorithm/in_fun_result.h>
#include <asc/std/__algorithm/is_heap.h>
#include <asc/std/__algorithm/is_sorted.h>
#include <asc/std/__algorithm/make_projected.h>
#include <asc/std/__algorithm/minmax.h>
#include <asc/std/__algorithm/ranges_for_each_n.h>
#include <asc/std/__algorithm/ranges_iterator_concept.h>
#include <asc/std/__algorithm/remove.h>
#include <asc/std/__algorithm/remove_if.h>
#include <asc/std/__algorithm/unwrap_range.h>
#include <asc/std/__execution/policy_dispatch.h>
#include <asc/std/__expected/expected_base.h>
#include <asc/std/__iterator/sortable.h>
#include <asc/std/__memory/runtime_assume_aligned.h>
#include <asc/std/__memory/uninitialized_algorithms.h>
#include <asc/std/__numeric/saturating_cast.h>
#include <asc/std/__numeric/saturating_div.h>
#include <asc/std/__numeric/saturating_mul.h>
#include <asc/std/__ranges/non_propagating_cache.h>
#include <asc/std/__ranges/rend.h>
#include <asc/std/__type_traits/aligned_union.h>
#include <asc/std/__type_traits/is_fundamental.h>
#include <asc/std/string_view>

namespace asc_stl_b023_test {

struct greater_than_two {
    CANN_ASC_STL_API constexpr bool operator()(int value) const noexcept
    {
        return value > 2;
    }
};
struct projected_less {
    CANN_ASC_STL_API constexpr bool operator()(int left, int right) const noexcept
    {
        return left < right;
    }
};
struct negate_projection {
    CANN_ASC_STL_API constexpr int operator()(int value) const noexcept
    {
        return -value;
    }
};
struct counter {
    int calls{};
    CANN_ASC_STL_API constexpr void operator()([[maybe_unused]] int value) noexcept
    {
        ++calls;
    }
};

struct bare_iterator {
    int* pointer;

    CANN_ASC_STL_API constexpr int& operator*() const noexcept
    {
        return *pointer;
    }
    CANN_ASC_STL_API constexpr bare_iterator& operator++() noexcept
    {
        ++pointer;
        return *this;
    }
    CANN_ASC_STL_API constexpr long operator-(const bare_iterator& other) const noexcept
    {
        return pointer - other.pointer;
    }
};

struct legacy_forward_traits {
    using difference_type = long;
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using iterator_category = asc::std::forward_iterator_tag;
};
static_assert(
    asc::std::is_same_v<asc::std::ranges::__iterator_concept<legacy_forward_traits>, asc::std::forward_iterator_tag>);

CANN_ASC_STL_API constexpr bool check_for_each_n()
{
    int values[] = {1, 2, 3};
    auto result = asc::std::ranges::for_each_n(bare_iterator{values}, 3, counter{});
    return result.in.pointer == values + 3 && result.fun.calls == 3;
}

CANN_ASC_STL_API constexpr int evaluate_core()
{
    int failures = 0;
    failures += !check_for_each_n();
    int values[] = {1, 2, 3, 2, 4};
    int* end = asc::std::remove(values, values + 5, 2);
    failures += end != values + 3 || values[0] != 1 || values[1] != 3 || values[2] != 4;
    int filtered[] = {1, 2, 3, 4};
    end = asc::std::remove_if(filtered, filtered + 4, greater_than_two{});
    failures += end != filtered + 2 || filtered[0] != 1 || filtered[1] != 2;
    const auto pair = asc::std::minmax(values[0], values[2]);
    failures += pair.first != 1 || pair.second != 4;
    const int heap[] = {9, 5, 8, 1, 2};
    failures += !asc::std::is_heap(heap, heap + 5);
    failures += asc::std::is_sorted(heap, heap + 5);
    const int sorted[] = {1, 2, 2, 4};
    failures += !asc::std::is_sorted(sorted, sorted + 4);

    failures += asc::std::saturating_cast<signed char>(300) != 127;
    failures += asc::std::saturating_cast<unsigned char>(-3) != 0;
    failures += asc::std::saturating_mul<int>(100000, 100000) != 2147483647;
    failures += asc::std::saturating_mul<int>(-100000, 100000) != (-2147483647 - 1);
    failures += asc::std::saturating_mul<unsigned>(4000000000U, 2U) != 0xffffffffU;
    failures += asc::std::saturating_div<int>((-2147483647 - 1), -1) != 2147483647;

    const char text_data[] = {'a', 's', 'c', '-', 's', 't', 'l', '-', 'd', 'e', 'v', 'i', 'c', 'e'};
    const char prefix[] = {'a', 's', 'c'};
    const char suffix[] = {'d', 'e', 'v', 'i', 'c', 'e'};
    const char needle[] = {'s', 't', 'l'};
    const char first_set[] = {'x', 'y', 'z', '-', 'd'};
    const char prefix_set[] = {'a', 's', 'c', '-'};
    asc::std::string_view text(text_data, 14);
    const char hash_input[] = {'a'};
    const auto hash_value = asc::std::hash<asc::std::string_view>{}(asc::std::string_view(hash_input, 1));
    failures += hash_value != (sizeof(asc::std::size_t) == 8 ? 0xaf63dc4c8601ec8cULL : 0xe40c292cU);
    failures += text.size() != 14 || !text.starts_with({prefix, 3}) || !text.ends_with({suffix, 6});
    failures += text.find({needle, 3}) != 4 || text.rfind('e') != 13;
    failures += text.find_first_of({first_set, 5}) != 3 || text.find_first_not_of({prefix_set, 4}) != 5;
    failures += text.find_last_of('s') != 4 || text.find_last_not_of({suffix, 6}) != 7;
    text.remove_prefix(4);
    text.remove_suffix(7);
    failures += text != asc::std::string_view(needle, 3);
    const char equal_text[] = {'s', 't', 'l', '\0'};
    const char lesser_text[] = {'s', 't', 'k', '\0'};
    const char greater_text[] = {'s', 't', 'm', '\0'};
    failures += !(text == equal_text) || !(equal_text == text) || text != equal_text || equal_text != text;
    failures += !(text < greater_text) || !(lesser_text < text);
    failures += !(text > lesser_text) || !(greater_text > text);
    failures += !(text <= equal_text) || !(equal_text <= text);
    failures += !(text >= equal_text) || !(equal_text >= text);

    projected_less predicate{};
    negate_projection projection{};
    auto projected = asc::std::__make_projected(predicate, projection);
    failures += !projected(3, 2);
    auto unwrapped = asc::std::__unwrap_range(sorted, sorted + 4);
    failures += unwrapped.first != sorted || unwrapped.second != sorted + 4;
    auto reverse_end = asc::std::ranges::rend(sorted);
    failures += reverse_end.base() != sorted;
    return failures;
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
CANN_ASC_STL_HOST_API int evaluate_host_only()
{
    int failures = 0;
    const asc::std::string_view text("stl");
    failures += !(text == "stl") || !("stl" == text) || text != "stl" || "stl" != text;
    failures += !(text < "stm") || !("stk" < text);
    failures += !(text > "stk") || !("stm" > text);
    failures += !(text <= "stl") || !("stl" <= text);
    failures += !(text >= "stl") || !("stl" >= text);
    failures += asc::std::__execution_detail::__policy_dispatch(
                    asc::std::execution::par, [] { return 23; }, [] { return 99; }) != 23;

    int first = 1;
    int second = 2;
    asc::detail::software_pool<2> pool;
    failures += !pool.register_block(&first, sizeof(first), alignof(int));
    failures += !pool.register_block(&second, sizeof(second), alignof(int));
    void* acquired = pool.acquire(sizeof(int), alignof(int), 0);
    failures += acquired != &first;
    failures += !pool.release(acquired, 7);
    failures += pool.acquire(sizeof(int), alignof(int), 6) != &second;
    failures += pool.statistics(6).available_blocks != 0;
    failures += pool.statistics(7).available_blocks != 1;

    using storage = asc::std::aligned_union_t<sizeof(int), int, long long>;
    failures += alignof(storage) < alignof(long long) || sizeof(storage) < sizeof(long long);
    alignas(int) unsigned char raw[sizeof(int) * 3]{};
    int source[] = {4, 5, 6};
    auto* output = reinterpret_cast<int*>(raw);
    failures += asc::std::uninitialized_copy(source, source + 3, output) != output + 3;
    failures += output[0] != 4 || output[2] != 6;
    asc::std::destroy(output, output + 3);

    int aligned = 7;
    failures += asc::std::__runtime_assume_aligned(&aligned, alignof(int)) != &aligned;

    asc::std::__expected_storage<int, long> good(asc::std::in_place, 8);
    asc::std::__expected_storage<int, long> bad(asc::std::unexpect, 9L);
    failures += !good.__has_val_ || good.__value() != 8 || bad.__has_val_ || bad.__error() != 9;

    asc::std::ranges::__non_propagating_cache<int> cache;
    cache.__emplace(11);
    failures += !cache.__has_value() || *cache != 11;
    asc::std::ranges::__non_propagating_cache<int> moved(static_cast<decltype(cache)&&>(cache));
    failures += cache.__has_value() || moved.__has_value();

    int input[] = {1, 2, 3};
    auto result = asc::std::ranges::for_each_n(input, 3, counter{});
    failures += result.in != input + 3 || result.fun.calls != 3;
    static_assert(asc::std::sortable<int*>);
    static_assert(asc::std::is_fundamental_v<int> && !asc::std::is_fundamental_v<int*>);
    return failures;
}
#endif

}  // namespace asc_stl_b023_test

#endif  // ASC_STL_TEST_SUPPORT_B023_SEMANTICS_H
