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

#ifndef ASC_STL_TEST_CXX17_CONTAINER_SEMANTICS_H
#define ASC_STL_TEST_CXX17_CONTAINER_SEMANTICS_H

#include <asc/std/__memory/allocate_at_least.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__memory/voidify.h>
#include <asc/std/array>
#include <asc/std/cstdalign>
#include <asc/std/cstdbool>
#include <asc/std/format>
#include <asc/std/span>
#include <asc/std/__iterator/bounded_iter.h>
#include <asc/std/new>
#include <asc/std/type_traits>

namespace asc_stl_cxx17_container_test {

struct copy_value {
    int value;
    CANN_ASC_STL_API constexpr explicit copy_value(int input) noexcept : value(input)
    {}
};

struct move_value {
    int value;
    CANN_ASC_STL_API constexpr explicit move_value(int input) noexcept : value(input)
    {}
    move_value(const move_value&) = delete;
    CANN_ASC_STL_API constexpr move_value(move_value&& other) noexcept : value(other.value)
    {
        other.value = 0;
    }
};

template <class T>
struct fancy_pointer {
    using element_type = T;
    T* value;
    CANN_ASC_STL_API static constexpr fancy_pointer pointer_to(T& object) noexcept
    {
        return {&object};
    }
};

CANN_ASC_STL_API constexpr bool evaluate_pointer_constexpr()
{
    int value = 19;
    const auto pointer = asc::std::pointer_traits<fancy_pointer<int>>::pointer_to(value);
    return pointer.value == &value && asc::std::__voidify(value) == static_cast<void*>(&value);
}

template <class Count = asc::std::size_t>
struct member_allocator {
    using value_type = int;
    int* storage;
    int plain_calls = 0;
    int member_calls = 0;
    CANN_ASC_STL_API int* allocate(asc::std::size_t)
    {
        ++plain_calls;
        return storage;
    }
    CANN_ASC_STL_API asc::std::allocation_result<int*> allocate_at_least(Count count)
    {
        ++member_calls;
        return {storage, count + 3};
    }
};

struct ordinary_allocator {
    using value_type = int;
    int* storage;
    int calls = 0;
    CANN_ASC_STL_API int* allocate(asc::std::size_t)
    {
        ++calls;
        return storage;
    }
};

CANN_ASC_STL_API int evaluate_to_array()
{
    const int source[3] = {2, 5, 9};
    auto copied = asc::std::to_array(source);
    static_assert(asc::std::is_same_v<decltype(copied), asc::std::array<int, 3>>);
    if (copied[0] != 2 || copied[2] != 9)
        return 1;
    copy_value nondefault[2] = {copy_value(11), copy_value(13)};
    auto constructed = asc::std::to_array(nondefault);
    if (constructed[0].value != 11 || constructed[1].value != 13)
        return 2;
    move_value movable[2] = {move_value(17), move_value(23)};
    auto moved = asc::std::to_array(static_cast<move_value(&&)[2]>(movable));
    if (moved[0].value != 17 || moved[1].value != 23 || movable[0].value != 0 || movable[1].value != 0)
        return 3;
    return 0;
}

CANN_ASC_STL_API int evaluate_allocation_facilities()
{
    int storage[8] = {};
    member_allocator<> member{storage};
    const auto granted = asc::std::allocate_at_least(member, 2);
    if (granted.ptr != storage || granted.count != 5 || member.member_calls != 1 || member.plain_calls != 0)
        return 4;
    ordinary_allocator ordinary{storage};
    const auto fallback = asc::std::allocate_at_least(ordinary, 2);
    if (fallback.ptr != storage || fallback.count != 2 || ordinary.calls != 1)
        return 5;
    member_allocator<asc::std::size_t&> lvalue_member{storage};
    const auto lvalue_granted = asc::std::allocate_at_least(lvalue_member, 2);
    if (lvalue_granted.count != 5 || lvalue_member.member_calls != 1 || lvalue_member.plain_calls != 0)
        return 7;
    member_allocator<asc::std::size_t&&> rvalue_only{storage};
    const auto rvalue_fallback = asc::std::allocate_at_least(rvalue_only, 2);
    if (rvalue_fallback.count != 2 || rvalue_only.member_calls != 0 || rvalue_only.plain_calls != 1)
        return 8;
    return 0;
}

CANN_ASC_STL_API int evaluate_format_and_pointer_facilities()
{
    char buffer[3] = {};
    asc::std::format_to_n_result<char*> result{buffer, 3};
    static_assert(asc::std::is_same_v<decltype(asc::std::destroying_delete), const asc::std::destroying_delete_t>);
#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
#ifndef __alignas_is_defined
#error "C++17 cstdalign compatibility macro is required"
#endif
#ifndef __bool_true_false_are_defined
#error "C++17 cstdbool compatibility macro is required"
#endif
    static_assert(__alignas_is_defined == 1 && __bool_true_false_are_defined == 1);
#endif
    return result.out != buffer || result.size != 3 || !evaluate_pointer_constexpr() ? 6 : 0;
}

CANN_ASC_STL_API int evaluate_facilities()
{
    const int array = evaluate_to_array();
    if (array != 0)
        return array;
    const int allocation = evaluate_allocation_facilities();
    if (allocation != 0)
        return allocation;
    return evaluate_format_and_pointer_facilities();
}

template <bool Borrowed>
struct range_view {
    int* first;
    asc::std::size_t count;
    CANN_ASC_STL_API constexpr int* begin() const noexcept
    {
        return first;
    }
    CANN_ASC_STL_API constexpr int* end() const noexcept
    {
        return first + count;
    }
    CANN_ASC_STL_API constexpr int* data() const noexcept
    {
        return first;
    }
    CANN_ASC_STL_API constexpr asc::std::size_t size() const noexcept
    {
        return count;
    }
};

struct sized_sentinel {
    int* last{};
};
CANN_ASC_STL_API constexpr bool operator==(int* first, sized_sentinel last) noexcept
{
    return first == last.last;
}
CANN_ASC_STL_API constexpr bool operator==(sized_sentinel last, int* first) noexcept
{
    return first == last;
}
CANN_ASC_STL_API constexpr bool operator!=(int* first, sized_sentinel last) noexcept
{
    return !(first == last);
}
CANN_ASC_STL_API constexpr bool operator!=(sized_sentinel last, int* first) noexcept
{
    return !(last == first);
}
CANN_ASC_STL_API constexpr asc::std::ptrdiff_t operator-(sized_sentinel last, int* first) noexcept
{
    return last.last - first;
}
CANN_ASC_STL_API constexpr asc::std::ptrdiff_t operator-(int* first, sized_sentinel last) noexcept
{
    return first - last.last;
}

struct count_sentinel : sized_sentinel {
    CANN_ASC_STL_API constexpr operator asc::std::size_t() const noexcept
    {
        return 2;
    }
};

struct unsized_sentinel {
    int* last{};
};
CANN_ASC_STL_API constexpr bool operator==(int* first, unsized_sentinel last) noexcept
{
    return first == last.last;
}
CANN_ASC_STL_API constexpr bool operator==(unsized_sentinel last, int* first) noexcept
{
    return first == last;
}
CANN_ASC_STL_API constexpr bool operator!=(int* first, unsized_sentinel last) noexcept
{
    return !(first == last);
}
CANN_ASC_STL_API constexpr bool operator!=(unsized_sentinel last, int* first) noexcept
{
    return !(last == first);
}

struct base_element {
    int value;
};
struct derived_element : base_element {};

}  // namespace asc_stl_cxx17_container_test

namespace asc {
namespace std {
namespace ranges {
template <>
inline constexpr bool enable_borrowed_range<asc_stl_cxx17_container_test::range_view<true>> = true;
}  // namespace ranges
}  // namespace std
}  // namespace asc

namespace asc_stl_cxx17_container_test {

CANN_ASC_STL_API constexpr bool evaluate_span_constraints()
{
    using asc::std::is_constructible_v;
    using asc::std::span;
    static_assert(is_constructible_v<span<int>, int*, asc::std::size_t>);
    static_assert(!is_constructible_v<span<int>, const int*, asc::std::size_t>);
    static_assert(!is_constructible_v<span<base_element>, derived_element*, asc::std::size_t>);
    static_assert(!is_constructible_v<span<int>, int, int>);
    static_assert(is_constructible_v<span<int>, int*, sized_sentinel>);
    static_assert(!is_constructible_v<span<int>, int*, unsized_sentinel>);
    static_assert(is_constructible_v<span<int>, range_view<false>&>);
    static_assert(!is_constructible_v<span<int>, range_view<false>>);
    static_assert(is_constructible_v<span<const int>, range_view<false>>);
    static_assert(is_constructible_v<span<int>, range_view<true>>);
    static_assert(!is_constructible_v<span<int>, int>);
    static_assert(!is_constructible_v<span<int>, const asc::std::array<int, 4>&>);
    static_assert(is_constructible_v<span<const int>, const asc::std::array<int, 4>&>);
    static_assert(!is_constructible_v<span<int, 3>, int(&)[4]>);
    static_assert(!is_constructible_v<span<int, 3>, asc::std::array<int, 4>&>);
    static_assert(!is_constructible_v<span<int, 3>, span<int, 4>>);
    static_assert(!is_constructible_v<span<int>, span<const int>>);
    return true;
}

CANN_ASC_STL_API int evaluate_span_deduction()
{
    int values[4] = {3, 5, 7, 11};
    range_view<false> range{values, 4};
    asc::std::span from_range(range);
    asc::std::span from_sentinel(values, sized_sentinel{values + 4});
    asc::std::span from_constant(values, asc::std::integral_constant<asc::std::size_t, 4>{});
    asc::std::span from_count(values, 4);
    static_assert(asc::std::is_same_v<decltype(from_range), asc::std::span<int>>);
    static_assert(asc::std::is_same_v<decltype(from_sentinel), asc::std::span<int>>);
    static_assert(asc::std::is_same_v<decltype(from_constant), asc::std::span<int, 4>>);
    static_assert(asc::std::is_same_v<decltype(from_count), asc::std::span<int>>);
    asc::std::span from_builtin(values);
    static_assert(asc::std::is_same_v<decltype(from_builtin), asc::std::span<int, 4>>);
    asc::std::array<int, 2> mutable_array{{19, 23}};
    asc::std::span from_mutable_array(mutable_array);
    static_assert(asc::std::is_same_v<decltype(from_mutable_array), asc::std::span<int, 2>>);
    const asc::std::array<int, 2> array{{13, 17}};
    asc::std::span from_array(array);
    static_assert(asc::std::is_same_v<decltype(from_array), asc::std::span<const int, 2>>);
    if (from_range.data() != values || from_range.size() != 4 || from_sentinel.back() != 11)
        return 1;
    if (from_constant.size() != 4 || from_constant[1] != 5 || from_count.size() != 4 || from_array.back() != 17)
        return 2;
    from_builtin[0] = 29;
    from_mutable_array[1] = 31;
    if (values[0] != 29 || mutable_array[1] != 31)
        return 3;
    return 0;
}

CANN_ASC_STL_API int evaluate_span_construction()
{
    int values[4] = {3, 5, 7, 11};
    range_view<false> range{values, 4};
    asc::std::span<int, 4> fixed(range);
    asc::std::span<const int> readonly(range_view<false>{values, 4});
    asc::std::span<int> borrowed(range_view<true>{values, 4});
    asc::std::span<int, 4> bounded(values, sized_sentinel{values + 4});
    asc::std::span<int> counted(values, count_sentinel{{values + 4}});
    if (fixed.data() != values || readonly.size() != 4 || borrowed[2] != 7 || bounded.back() != 11)
        return 1;
    if (counted.size() != 2 || counted.back() != 5)
        return 2;
    const auto first = asc::std::__make_bounded_iter(values, values, values + 4);
    const auto last = asc::std::__make_bounded_iter(values + 4, values, values + 4);
    asc::std::span<int> from_iterator(first, 4);
    asc::std::span<int, 4> from_iterator_sentinel(first, last);
    if (from_iterator.size() != 4 || from_iterator.data() != values || from_iterator_sentinel.back() != 11)
        return 3;
    from_iterator[0] = 19;
    return values[0] != 19 ? 4 : 0;
}

CANN_ASC_STL_API int evaluate()
{
    const int facilities = evaluate_facilities();
    if (facilities != 0)
        return 100 + facilities;
    const int deduction = evaluate_span_deduction();
    if (deduction != 0)
        return 200 + deduction;
    const int construction = evaluate_span_construction();
    return construction == 0 && evaluate_span_constraints() ? 0 : 300 + construction;
}

}  // namespace asc_stl_cxx17_container_test

#endif  // ASC_STL_TEST_CXX17_CONTAINER_SEMANTICS_H
