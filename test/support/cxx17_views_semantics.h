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

#ifndef ASC_STL_TEST_CXX17_VIEWS_SEMANTICS_H
#define ASC_STL_TEST_CXX17_VIEWS_SEMANTICS_H

#include <asc/std/__ranges/movable_box.h>
#include <asc/std/ranges>
#include <asc/std/span>
#include <asc/std/string_view>
#include <asc/std/type_traits>

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && CANN_ASC_STL_DETAIL_HAS_CXX20()
#include <ranges>
#endif

#include "cxx17_views_fixtures.h"

namespace asc_stl_cxx17_views_test {

CANN_ASC_STL_API int evaluate_storage()
{
    asc::std::ranges::__movable_box<reconstructible> left(asc::std::in_place, 3);
    asc::std::ranges::__movable_box<reconstructible> right(asc::std::in_place, 7);
    left = right;
    if (left->value != 7 || right->value != 7)
        return 1;
    left = asc::std::move(right);
    if (left->value != 7)
        return 2;
    asc::std::ranges::__movable_box<move_reconstructible> first(asc::std::in_place, 11);
    asc::std::ranges::__movable_box<move_reconstructible> second(asc::std::in_place, 13);
    first = asc::std::move(second);
    return first.__has_value() && first->value == 13 && second->value == -1 ? 0 : 3;
}

CANN_ASC_STL_API int evaluate_factory_constraints()
{
    using array = int(&)[4];
    using function_reference = void (&)();
    using forward_range = noncommon_range<asc::std::forward_iterator_tag>&;
    using bidirectional_range = noncommon_range<asc::std::bidirectional_iterator_tag>&;
    using asc::std::is_invocable_v;
    namespace views = asc::std::ranges::views;
    static_assert(is_invocable_v<decltype(views::filter), array, count_even>);
    static_assert(!is_invocable_v<decltype(views::filter), array, invalid_argument>);
    static_assert(!is_invocable_v<decltype(views::filter), array, void_operation>);
    static_assert(!is_invocable_v<decltype(views::filter), invalid_argument, count_even>);
    static_assert(is_invocable_v<decltype(views::transform), array, non_const_twice>);
    static_assert(!is_invocable_v<decltype(views::transform), array, invalid_argument>);
    static_assert(!is_invocable_v<decltype(views::transform), array, void_operation>);
    static_assert(!is_invocable_v<decltype(views::transform), invalid_argument, non_const_twice>);
    static_assert(is_invocable_v<decltype(views::take), array, int>);
    static_assert(is_invocable_v<decltype(views::drop), array, int>);
    static_assert(!is_invocable_v<decltype(views::take), invalid_argument, int>);
    static_assert(!is_invocable_v<decltype(views::drop), invalid_argument, int>);
    static_assert(!is_invocable_v<decltype(views::take), array, invalid_argument>);
    static_assert(!is_invocable_v<decltype(views::drop), array, invalid_argument>);
    static_assert(is_invocable_v<decltype(views::reverse), bidirectional_range>);
    static_assert(!is_invocable_v<decltype(views::reverse), forward_range>);
    static_assert(!is_invocable_v<decltype(views::reverse), invalid_argument>);
    static_assert(is_invocable_v<decltype(views::single), int>);
    static_assert(is_invocable_v<decltype(views::single), function_reference>);
    static_assert(!is_invocable_v<decltype(views::single), void>);
    static_assert(!is_invocable_v<decltype(views::single), immovable_value&>);
    static_assert(is_invocable_v<decltype(views::repeat), int, int>);
    static_assert(!is_invocable_v<decltype(views::repeat), void, int>);
    static_assert(!is_invocable_v<decltype(views::repeat), function_reference, int>);
    static_assert(!is_invocable_v<decltype(views::repeat), immovable_value&, int>);
    static_assert(!is_invocable_v<decltype(views::repeat), int, invalid_argument>);
    static_assert(!is_invocable_v<decltype(views::filter(invalid_argument{})), array>);
    static_assert(!is_invocable_v<decltype(views::transform(invalid_argument{})), array>);
    static_assert(!is_invocable_v<decltype(views::take(invalid_argument{})), array>);
    static_assert(!is_invocable_v<decltype(views::drop(invalid_argument{})), array>);
    static_assert(!is_invocable_v<decltype(views::take(2)), invalid_argument>);
    static_assert(!is_invocable_v<decltype(views::drop(2)), invalid_argument>);
    static_assert(!is_invocable_v<decltype(views::filter(count_even{})), invalid_argument>);
    static_assert(!is_invocable_v<decltype(views::transform(non_const_twice{})), invalid_argument>);
    static_assert(!is_invocable_v<decltype(views::take_while), array, invalid_argument>);
    static_assert(!is_invocable_v<decltype(views::drop_while), array, invalid_argument>);
    static_assert(!is_invocable_v<decltype(views::take_while), invalid_argument, count_even>);
    static_assert(!is_invocable_v<decltype(views::drop_while), invalid_argument, count_even>);
    return 0;
}

CANN_ASC_STL_API int evaluate_count_captures()
{
    int values[] = {1, 2, 3, 4};
    using array = int(&)[4];
    using asc::std::is_invocable_v;
    auto take = asc::std::ranges::views::take(move_only_count(2));
    auto drop = asc::std::ranges::views::drop(move_only_count(1));
    using closure = decltype(take);
    static_assert(is_invocable_v<closure&, array> && is_invocable_v<const closure&, array>);
    static_assert(is_invocable_v<closure&&, array> && is_invocable_v<const closure&&, array>);
    const auto prefix = take(values);
    const auto suffix = drop(values);
    if (prefix.size() != 2 || *(prefix.end() - 1) != 2 || suffix.size() != 3 || *suffix.begin() != 2)
        return 100;
    if (asc::std::move(take)(values).size() != 2)
        return 104;
    const auto constant = asc::std::ranges::views::take(move_only_count(3));
    if (constant(values).size() != 3 || asc::std::move(constant)(values).size() != 3)
        return 101;
    auto mutable_take = asc::std::ranges::views::take(mutable_count(2));
    using mutable_closure = decltype(mutable_take);
    static_assert(is_invocable_v<mutable_closure&, array>);
    static_assert(!is_invocable_v<const mutable_closure&, array>);
    static_assert(!is_invocable_v<mutable_closure&&, array>);
    if (mutable_take(values).size() != 2)
        return 102;
    const auto selection =
        asc::std::ranges::views::drop(move_only_count(1)) | asc::std::ranges::views::take(move_only_count(2));
    const auto middle = values | selection;
    if (middle.size() != 2 || *middle.begin() != 2 || *(middle.end() - 1) != 3)
        return 105;
    auto rvalue_drop = asc::std::ranges::views::drop(rvalue_count(2));
    using rvalue_closure = decltype(rvalue_drop);
    static_assert(!is_invocable_v<rvalue_closure&, array>);
    static_assert(!is_invocable_v<const rvalue_closure&, array>);
    static_assert(is_invocable_v<rvalue_closure&&, array>);
    static_assert(!is_invocable_v<const rvalue_closure&&, array>);
    auto consumed = asc::std::move(rvalue_drop)(values);
    return consumed.size() == 2 && *consumed.begin() == 3 ? 0 : 103;
}

CANN_ASC_STL_API int evaluate_explicit_copy_boundaries()
{
    using array = int(&)[4];
    using asc::std::is_invocable_v;
    namespace views = asc::std::ranges::views;
    static_assert(is_invocable_v<decltype(views::single), explicit_copy_operation>);
    static_assert(!is_invocable_v<decltype(views::single), explicit_copy_operation&>);
    static_assert(is_invocable_v<decltype(views::transform), array, explicit_copy_operation>);
    const auto transform = views::transform(explicit_copy_operation{});
    static_assert(!is_invocable_v<decltype(transform)&, array>);
    static_assert(!is_invocable_v<decltype(transform)&&, array>);
    (void)transform;
    return 0;
}

CANN_ASC_STL_API int evaluate_input_take()
{
    int values[] = {3, 5, 7, 11};
    int position = 0;
    single_pass_range source{values, &position, 4};
    auto selected = asc::std::ranges::views::take(source, 2);
    auto last = selected.end();
    if (position != 0)
        return 10;
    int sum = 0;
    int count = 0;
    for (auto iter = selected.begin(); iter != last; ++iter) {
        sum += *iter;
        ++count;
    }
    return sum == 8 && count == 2 && position == 2 ? 0 : 11;
}

CANN_ASC_STL_API int evaluate_predicate_caches()
{
    int values[] = {1, 2, 3, 4};
    int calls = 0;
    auto filtered = asc::std::ranges::views::filter(values, count_even{&calls});
    if (*filtered.begin() != 2 || calls != 2)
        return 20;
    (void)filtered.begin();
    if (calls != 2)
        return 21;
    auto copied = filtered;
    (void)copied.begin();
    if (calls != 4)
        return 22;
    auto moved = asc::std::move(copied);
    (void)moved.begin();
    if (calls != 6)
        return 23;
    calls = 0;
    auto dropped = asc::std::ranges::views::drop_while(values, count_less_than_three{&calls});
    if (*dropped.begin() != 3 || calls != 3)
        return 24;
    (void)dropped.begin();
    auto second = dropped;
    (void)second.begin();
    return calls == 6 ? 0 : 25;
}

CANN_ASC_STL_API int evaluate_filter_transform()
{
#if CANN_ASC_STL_DETAIL_COMPILER_PURE_SIMT
    // Exercise runtime view operations independently of the constant-array
    // reverse-loop issue in the CANN SIMT compilation/simulation chain.
    // Keep the original fixture in Host/SIMD; see this directory's README.
    volatile int first_value = 1;
    const int input = first_value;
    item values[] = {{input, false}, {input + 1, true}, {input + 2, false}, {input + 3, true}};
#else
    item values[] = {{1, false}, {2, true}, {3, false}, {4, true}};
#endif
    auto filtered = asc::std::ranges::views::filter(values, &item::enabled);
    auto current = filtered.begin();
    using current_type = decltype(current);
    static_assert(asc::std::is_same_v<decltype(current++), current_type>);
    if (current->value != 2)
        return 30;
    if ((current++)->value != 2)
        return 30;
    if (current->value != 4)
        return 30;
    auto end = filtered.end();
    if ((--end)->value != 4)
        return 31;
    if ((--end)->value != 2)
        return 31;
    auto projection = asc::std::ranges::views::transform(values, &item::value);
    static_assert(asc::std::is_same_v<decltype(*projection.begin()), int&>);
    if (projection.end() - projection.begin() != 4 || projection.begin()[2] != 3)
        return 32;
    projection.begin()[1] = 9;
    if (values[1].value != 9)
        return 33;
    int numbers[] = {1, 2, 3};
    auto mutable_call = asc::std::ranges::views::transform(numbers, non_const_twice{});
    static_assert(!has_const_begin<decltype(mutable_call)>);
    static_assert(asc::std::is_same_v<typename decltype(mutable_call.begin())::iterator_concept,
        asc::std::random_access_iterator_tag>);
    return *(mutable_call.begin() + 2) == 6 && *mutable_call.begin()++ == 2 ? 0 : 34;
}

template <class Category>
CANN_ASC_STL_API int evaluate_reverse_cache()
{
    int values[] = {2, 3, 5, 7};
    int increments = 0;
    noncommon_range<Category> source{values, values + 4, &increments};
    auto reversed = asc::std::ranges::views::reverse(source);
    if (*reversed.begin() != 7 || increments != 4)
        return 40;
    (void)reversed.begin();
    if (increments != 4)
        return 41;
    auto copy = reversed;
    (void)copy.begin();
    return increments == 8 ? 0 : 42;
}

CANN_ASC_STL_API int evaluate_subrange_advance()
{
    int values[] = {2, 3, 5, 7};
    using iterator = cursor<asc::std::bidirectional_iterator_tag>;
    using sentinel = unsized_end<iterator>;
    using sized = asc::std::ranges::subrange<iterator, sentinel, asc::std::ranges::subrange_kind::sized>;
    sized range(iterator(values, nullptr), sentinel{values + 4}, 4);
    range.advance(10);
    if (!range.empty() || range.size() != 0)
        return 50;
    range.advance(-2);
    if (*range.begin() != 5 || range.size() != 2)
        return 51;
    auto previous = range.prev();
    if (*previous.begin() != 3 || previous.size() != 3 || range.size() != 2)
        return 52;
    using unsized = asc::std::ranges::subrange<iterator, sentinel>;
    static_assert(!has_size<unsized>);
    return 0;
}

CANN_ASC_STL_API int evaluate_move_only_subrange()
{
    int values[] = {2, 3, 5, 7};
    using range_type = asc::std::ranges::subrange<move_only_cursor, unsized_end<move_only_cursor>>;
    static_assert(!has_const_begin<range_type>);
    range_type range(move_only_cursor(values), unsized_end<move_only_cursor>{values + 4});
    auto advanced = asc::std::move(range).next(2);  // NOLINT(build/include_what_you_use)
    auto first = advanced.begin();
    return *first == 5 && first != advanced.end() ? 0 : 53;
}

CANN_ASC_STL_API int evaluate_factory_dispatch()
{
    int values[] = {1, 2, 3, 4};
    asc::std::span<int, 4> original(values);
    auto taken = asc::std::ranges::views::take(original, 2);
    auto dropped = asc::std::ranges::views::drop(original, 2);
    static_assert(asc::std::is_same_v<decltype(taken), asc::std::span<int>>);
    static_assert(asc::std::is_same_v<decltype(dropped), asc::std::span<int>>);
    if (taken.size() != 2 || taken[1] != 2 || dropped.size() != 2 || dropped[0] != 3)
        return 60;
    auto common = asc::std::ranges::views::common(original);
    static_assert(asc::std::is_same_v<decltype(common), decltype(original)>);
    char text_storage[] = {'a', 'b', 'c', 'd'};
    asc::std::string_view text(text_storage, 4);
    static_assert(asc::std::is_same_v<decltype(asc::std::ranges::views::take(text, 2)), asc::std::string_view>);
    static_assert(asc::std::is_same_v<decltype(asc::std::ranges::views::drop(text, 2)), asc::std::string_view>);
    const auto text_head = asc::std::ranges::views::take(text, 2);
    const auto text_tail = asc::std::ranges::views::drop(text, 3);
    if (text_head.size() != 2 || text_head[0] != 'a' || text_head[1] != 'b' || text_tail.size() != 1 ||
        text_tail[0] != 'd')
        return 61;
    if (!asc::std::ranges::views::take(text, 0).empty() || !asc::std::ranges::views::drop(text, 10).empty() ||
        asc::std::ranges::views::take(text, 10).size() != 4)
        return 64;
    auto integers = asc::std::ranges::views::iota(2, 7);
    decltype(integers) rebuilt(integers.begin(), integers.end());
    auto prefix = asc::std::ranges::views::take(integers, 3);
    auto suffix = asc::std::ranges::views::drop(integers, 3);
    if (rebuilt.size() != 5 || prefix.size() != 3 || *prefix.begin() != 2 || *suffix.begin() != 5)
        return 62;
    auto repeated = asc::std::ranges::views::repeat(11, 4);
    return asc::std::ranges::views::take(repeated, 2).size() == 2 &&
            asc::std::ranges::views::drop(repeated, 1).size() == 3 ?
        0 :
        63;
}

CANN_ASC_STL_API int evaluate_counted_and_common()
{
    int values[] = {1, 2, 3, 4};
    using iterator = cursor<asc::std::forward_iterator_tag>;
    auto counted = asc::std::ranges::views::counted(iterator(values, nullptr), 3);
    if (counted.size() != 3)
        return 70;
    int sum = 0;
    for (int value : counted)
        sum += value;
    noncommon_range<asc::std::forward_iterator_tag> source{values, values + 4, nullptr};
    auto common = asc::std::ranges::views::common(source);
    static_assert(asc::std::is_same_v<decltype(common.begin()), decltype(common.end())>);
    for (int value : common)
        sum += value;
    return sum == 16 ? 0 : 71;
}

CANN_ASC_STL_API int evaluate_reconstructible_values()
{
    auto single = asc::std::ranges::views::single(reconstructible(3));
    auto other_single = asc::std::ranges::views::single(reconstructible(7));
    static_assert(asc::std::is_copy_assignable_v<decltype(single)>);
    single = other_single;
    if (single.begin()->value != 7)
        return 80;
    auto repeated = asc::std::ranges::views::repeat(reconstructible(11), 2);
    auto other_repeat = asc::std::ranges::views::repeat(reconstructible(13), 3);
    static_assert(asc::std::is_copy_assignable_v<decltype(repeated)>);
    repeated = other_repeat;
    return repeated.size() == 3 && (*repeated.begin()).value == 13 ? 0 : 81;
}

CANN_ASC_STL_API int evaluate_reconstructible_callables()
{
    int values[] = {1, 2, 3, 4};
    auto transformed = asc::std::ranges::views::transform(values, nonassign_operation(3));
    auto other_transform = asc::std::ranges::views::transform(values, nonassign_operation(7));
    static_assert(asc::std::is_copy_assignable_v<decltype(transformed)>);
    transformed = other_transform;
    if (*transformed.begin() != 8)
        return 82;
    auto filtered = asc::std::ranges::views::filter(values, nonassign_predicate(3));
    auto other_filter = asc::std::ranges::views::filter(values, nonassign_predicate(2));
    static_assert(asc::std::is_copy_assignable_v<decltype(filtered)>);
    filtered = other_filter;
    auto current = filtered.begin();
    if (*current != 1 || ++current != filtered.end())
        return 83;
    auto taken = asc::std::ranges::views::take_while(values, nonassign_predicate(3));
    auto other_take = asc::std::ranges::views::take_while(values, nonassign_predicate(2));
    static_assert(asc::std::is_copy_assignable_v<decltype(taken)>);
    taken = other_take;
    auto first = taken.begin();
    if (*first != 1 || ++first != taken.end())
        return 84;
    auto dropped = asc::std::ranges::views::drop_while(values, nonassign_predicate(3));
    auto other_drop = asc::std::ranges::views::drop_while(values, nonassign_predicate(2));
    static_assert(asc::std::is_copy_assignable_v<decltype(dropped)>);
    (void)dropped.begin();
    dropped = other_drop;
    return *dropped.begin() == 2 ? 0 : 85;
}

CANN_ASC_STL_API int evaluate_iota_boundaries()
{
    constexpr int minimum = -2147483647 - 1;
    asc::std::ranges::iota_view<int, int> low(minimum, minimum + 3);
    asc::std::ranges::iota_view<int, int> wide(minimum, 2147483647);
    if (low.size() != 3U || wide.size() != 4294967295U)
        return 90;
    asc::std::ranges::iota_view<short, short> narrow(static_cast<short>(-3), static_cast<short>(2));
    if (narrow.size() != 5)
        return 91;
    asc::std::ranges::iota_view<int, long> heterogeneous(minimum, static_cast<long>(minimum) + 3);
    static_assert(asc::std::is_same_v<decltype(heterogeneous.end() - heterogeneous.begin()),
        typename decltype(heterogeneous.begin())::difference_type>);
    if (heterogeneous.end() - heterogeneous.begin() != 3 || heterogeneous.begin() - heterogeneous.end() != -3)
        return 92;
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && CANN_ASC_STL_DETAIL_HAS_CXX20()
    using standard_short_size = decltype(::std::ranges::iota_view<short, short>(short{}, short{}).size());
    using standard_int_size = decltype(::std::ranges::iota_view<int, int>(0, 0).size());
    static_assert(asc::std::is_same_v<decltype(narrow.size()), standard_short_size>);
    static_assert(asc::std::is_same_v<decltype(low.size()), standard_int_size>);
    if (narrow.size() != ::std::ranges::iota_view<short, short>(static_cast<short>(-3), static_cast<short>(2)).size())
        return 93;
#endif
    return 0;
}

CANN_ASC_STL_API int evaluate()
{
    const int results[] = {evaluate_storage(), evaluate_input_take(), evaluate_predicate_caches(),
        evaluate_filter_transform(), evaluate_reverse_cache<asc::std::bidirectional_iterator_tag>(),
        evaluate_reverse_cache<asc::std::random_access_iterator_tag>(), evaluate_subrange_advance(),
        evaluate_move_only_subrange(), evaluate_factory_dispatch(), evaluate_counted_and_common(),
        evaluate_reconstructible_values(), evaluate_reconstructible_callables(), evaluate_iota_boundaries(),
        evaluate_factory_constraints(), evaluate_count_captures(), evaluate_explicit_copy_boundaries()};
    for (int result : results) {
        if (result != 0)
            return result;
    }
    return 0;
}

}  // namespace asc_stl_cxx17_views_test

#endif  // ASC_STL_TEST_CXX17_VIEWS_SEMANTICS_H
