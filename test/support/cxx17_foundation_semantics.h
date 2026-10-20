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
#ifndef CANN_ASC_STL_TEST_CXX17_FOUNDATION_SEMANTICS_H
#define CANN_ASC_STL_TEST_CXX17_FOUNDATION_SEMANTICS_H

#include <asc/std/concepts>
#include <asc/std/algorithm>
#include <asc/std/iterator>
#include <asc/std/functional>
#include <asc/std/ranges>
#include <asc/std/__type_traits/integral_constant_like.h>
#include <asc/std/type_traits>

namespace asc_stl_cxx17_foundation {
namespace s = ::asc::std;

struct base {};
struct derived : base {};
struct unrelated {};
struct predicate {
    CANN_ASC_STL_API constexpr bool operator()(int value) const
    {
        return value > 0;
    }
};
struct relation {
    CANN_ASC_STL_API constexpr bool operator()(int left, int right) const
    {
        return left < right;
    }
};
struct immobile {
    immobile() = default;
    immobile(const immobile&) = delete;
    immobile& operator=(const immobile&) = delete;
};

struct throwing_destructor {
    CANN_ASC_STL_API ~throwing_destructor() noexcept(false)
    {}
};
struct deleted_explicit_bool {
    CANN_ASC_STL_API operator int() const;
    CANN_ASC_STL_API explicit operator bool() const = delete;
    CANN_ASC_STL_API bool operator!() const
    {
        return false;
    }
};
struct deleted_explicit_long {
    CANN_ASC_STL_API operator int() const;
    CANN_ASC_STL_API explicit operator long() const = delete;
};
struct invalid_predicate_result {
    CANN_ASC_STL_API deleted_explicit_bool operator()(int) const;
};
static_assert(s::is_move_constructible_v<throwing_destructor>);
static_assert(!s::swappable<throwing_destructor>);
static_assert(s::is_convertible_v<deleted_explicit_long, long>);
static_assert(!s::convertible_to<deleted_explicit_long, long>);
static_assert(!s::common_reference_with<deleted_explicit_long, long>);
static_assert(s::is_convertible_v<deleted_explicit_bool, bool>);
static_assert(!s::predicate<invalid_predicate_result, int>);

static_assert(s::same_as<int, int> && !s::same_as<int, const int>);
static_assert(s::different_from<int, long> && !s::different_from<int, const int&>);
static_assert(s::integral<int> && s::signed_integral<int> && s::unsigned_integral<unsigned>);
static_assert(s::floating_point<float> && !s::integral<float>);
static_assert(s::derived_from<derived, base> && !s::derived_from<base, derived>);
static_assert(!s::derived_from<int&, int> && !s::derived_from<void, void>);
static_assert(s::convertible_to<int, long> && !s::convertible_to<void, int>);
static_assert(s::common_reference_with<int&, const int&> && !s::common_reference_with<int, unrelated>);
static_assert(s::common_with<int, long> && !s::common_with<int, unrelated>);
static_assert(s::assignable_from<int&, int> && !s::assignable_from<int, int>);
static_assert(s::destructible<int> && !s::destructible<void>);
static_assert(s::constructible_from<int, int> && !s::constructible_from<void>);
static_assert(s::default_initializable<int> && !s::default_initializable<int&>);
static_assert(s::move_constructible<int> && s::copy_constructible<int> && !s::copy_constructible<void>);
static_assert(s::movable<int> && s::copyable<int> && !s::movable<void> && !s::copyable<immobile>);
static_assert(s::semiregular<int> && s::regular<int> && !s::semiregular<void>);
static_assert(s::swappable<int> && s::swappable_with<int&, int&> && !s::swappable<immobile>);
static_assert(s::equality_comparable<int> && s::equality_comparable_with<int, long>);
static_assert(!s::equality_comparable<void> && !s::equality_comparable_with<int, unrelated>);
static_assert(s::totally_ordered<int> && s::totally_ordered_with<int, long>);
static_assert(!s::totally_ordered<void> && !s::totally_ordered_with<int, unrelated>);
static_assert(s::invocable<predicate, int> && s::regular_invocable<predicate, int>);
static_assert(s::predicate<predicate, int> && !s::predicate<unrelated, int>);
static_assert(s::relation<relation, int, int> && s::equivalence_relation<relation, int, int>);
static_assert(s::strict_weak_order<relation, int, int> && !s::relation<unrelated, int, int>);

// Check all iterator/range public predicates in both modes, including invalid
// associated types that must produce false rather than hard diagnostics.
using bounded_pointer = decltype(s::__make_bounded_iter(
    static_cast<int*>(nullptr), static_cast<int*>(nullptr), static_cast<int*>(nullptr)));
static_assert(s::contiguous_iterator<bounded_pointer>);
static_assert(s::contiguous_iterator<s::__wrap_iter<int*>>);
static_assert(s::same_as<s::_ITER_CONCEPT<bounded_pointer>, s::contiguous_iterator_tag>);

using projected_identity = s::projected<int*, s::identity>;
static_assert(s::same_as<decltype(*s::declval<projected_identity&>()), int&>);
static_assert(s::same_as<s::iter_rvalue_reference_t<projected_identity>, int&&>);
static_assert(s::indirectly_readable<projected_identity>);
static_assert(!s::indirectly_readable<s::projected<int*, unrelated>>);

static_assert(s::indirectly_readable<int*> && !s::indirectly_readable<void>);
static_assert(s::indirectly_writable<int*, int> && !s::indirectly_writable<const int*, int>);
static_assert(s::weakly_incrementable<int*> && !s::weakly_incrementable<void>);
static_assert(s::incrementable<int*> && !s::incrementable<void>);
static_assert(s::input_or_output_iterator<int*> && !s::input_or_output_iterator<void>);
static_assert(s::sentinel_for<int*, int*> && !s::sentinel_for<void, int*>);
static_assert(s::sized_sentinel_for<int*, int*> && !s::sized_sentinel_for<void, void>);
static_assert(s::input_iterator<int*> && !s::input_iterator<void>);
static_assert(s::output_iterator<int*, int> && !s::output_iterator<void, int>);
static_assert(s::forward_iterator<int*> && !s::forward_iterator<void>);
static_assert(s::bidirectional_iterator<int*> && !s::bidirectional_iterator<void>);
static_assert(s::random_access_iterator<int*> && !s::random_access_iterator<void>);
static_assert(s::contiguous_iterator<int*> && !s::contiguous_iterator<void>);
static_assert(s::indirectly_unary_invocable<predicate, int*> && !s::indirectly_unary_invocable<void, void>);
static_assert(
    s::indirectly_regular_unary_invocable<predicate, int*> && !s::indirectly_regular_unary_invocable<void, void>);
static_assert(s::indirect_unary_predicate<predicate, int*> && !s::indirect_unary_predicate<void, void>);
static_assert(s::indirect_binary_predicate<relation, int*, int*> && !s::indirect_binary_predicate<void, void, void>);
static_assert(s::indirect_equivalence_relation<relation, int*, int*> && !s::indirect_equivalence_relation<void, void>);
static_assert(s::indirect_strict_weak_order<relation, int*, int*> && !s::indirect_strict_weak_order<void, void>);
static_assert(s::indirectly_movable<int*, int*> && !s::indirectly_movable<void, void>);
static_assert(s::indirectly_movable_storable<int*, int*> && !s::indirectly_movable_storable<void, void>);
static_assert(s::indirectly_copyable<int*, int*> && !s::indirectly_copyable<void, void>);
static_assert(s::indirectly_copyable_storable<int*, int*> && !s::indirectly_copyable_storable<void, void>);
static_assert(s::indirectly_swappable<int*> && !s::indirectly_swappable<void>);
static_assert(s::indirectly_comparable<int*, int*, relation> && !s::indirectly_comparable<void, void, void>);
static_assert(s::permutable<int*> && !s::permutable<void>);
static_assert(s::mergeable<int*, int*, int*> && !s::mergeable<void, void, void>);
static_assert(s::sortable<int*> && !s::sortable<void>);

namespace r = ::asc::std::ranges;
struct simple_view : r::view_base {
    int* first = nullptr;
    int* last = nullptr;
    CANN_ASC_STL_API constexpr int* begin() const
    {
        return first;
    }
    CANN_ASC_STL_API constexpr int* end() const
    {
        return last;
    }
};
struct non_const_view : r::view_base {
    int* first = nullptr;
    int* last = nullptr;
    CANN_ASC_STL_API constexpr int* begin()
    {
        return first;
    }
    CANN_ASC_STL_API constexpr int* end()
    {
        return last;
    }
};
static_assert(r::range<int[3]> && !r::range<void>);
static_assert(r::borrowed_range<int (&)[3]> && !r::borrowed_range<int[3]>);
static_assert(r::sized_range<int[3]> && !r::sized_range<void>);
static_assert(r::input_range<int[3]> && !r::input_range<void>);
static_assert(r::output_range<int[3], int> && !r::output_range<void, int>);
static_assert(r::forward_range<int[3]> && !r::forward_range<void>);
static_assert(r::bidirectional_range<int[3]> && !r::bidirectional_range<void>);
static_assert(r::random_access_range<int[3]> && !r::random_access_range<void>);
static_assert(r::contiguous_range<int[3]> && !r::contiguous_range<void>);
static_assert(r::common_range<int[3]> && !r::common_range<void>);
static_assert(r::view<simple_view> && !r::view<void>);
static_assert(r::viewable_range<simple_view> && !r::viewable_range<void>);
static_assert(r::__simple_view<simple_view> && !r::__simple_view<non_const_view> && !r::__simple_view<void>);
static_assert(s::__integral_constant_like<s::integral_constant<int, 3>>);
static_assert(!s::__integral_constant_like<int> && !s::__integral_constant_like<void>);
static_assert(s::is_same_v<r::subrange<int*>, r::subrange<int*, int*, r::subrange_kind::sized>>);

CANN_ASC_STL_DETAIL_TEMPLATE(class T)
CANN_ASC_STL_DETAIL_REQUIRES(s::integral<T>)
CANN_ASC_STL_API constexpr T constrained_identity(T value)
{
    return value;
}

template <class T, class = void>
struct can_constrain : s::false_type {};
template <class T>
struct can_constrain<T, s::void_t<decltype(constrained_identity(s::declval<T>()))>> : s::true_type {};
static_assert(can_constrain<int>::value && !can_constrain<float>::value);

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class T>
    requires s::integral<T>
CANN_ASC_STL_API constexpr int subsumption(T)
{
    return 1;
}
template <class T>
    requires s::signed_integral<T>
CANN_ASC_STL_API constexpr int subsumption(T)
{
    return 2;
}
static_assert(subsumption(1) == 2 && subsumption(1U) == 1);
#endif

// A distinct sentinel exercises the non-sized navigation path.
struct sentinel {
    int* last = nullptr;
    friend CANN_ASC_STL_API constexpr bool operator==(int* it, sentinel end)
    {
        return it == end.last;
    }
    friend CANN_ASC_STL_API constexpr bool operator==(sentinel end, int* it)
    {
        return it == end.last;
    }
    friend CANN_ASC_STL_API constexpr bool operator!=(int* it, sentinel end)
    {
        return it != end.last;
    }
    friend CANN_ASC_STL_API constexpr bool operator!=(sentinel end, int* it)
    {
        return it != end.last;
    }
};
static_assert(s::is_constructible_v<s::move_iterator<const int*>, s::move_iterator<int*>>);
static_assert(!s::is_constructible_v<s::move_iterator<int*>, s::move_iterator<double*>>);
static_assert(!s::is_constructible_v<s::counted_iterator<int*>, s::counted_iterator<double*>>);
static_assert(!s::is_constructible_v<s::move_sentinel<int*>, s::move_sentinel<double*>>);

template <class T, class U, class = void>
struct has_member_assignment : s::false_type {};
template <class T, class U>
struct has_member_assignment<T, U,
    s::void_t<decltype(s::declval<T&>().template operator= <int*>(s::declval<const U&>()))>> : s::true_type {};
static_assert(has_member_assignment<s::move_sentinel<const int*>, s::move_sentinel<int*>>::value);

CANN_ASC_STL_API constexpr int navigation()
{
    int values[5] = {1, 2, 3, 4, 5};
    auto iter = values;
    r::advance(iter, 2);
    if (iter != values + 2)
        return 1;
    r::advance(iter, values + 4);
    if (iter != values + 4)
        return 2;
    iter = values;
    if (r::advance(iter, 8, values + 5) != 3 || iter != values + 5)
        return 3;
    if (r::advance(iter, -8, values) != -3 || iter != values)
        return 4;
    r::advance(iter, sentinel{values + 3});
    if (iter != values + 3)
        return 5;
    if (r::distance(values, values + 5) != 5 || r::distance(values) != 5)
        return 6;
    if (r::distance(values, sentinel{values + 5}) != 5)
        return 7;
    if (r::next(values) != values + 1 || r::next(values, 2) != values + 2)
        return 8;
    if (r::next(values, sentinel{values + 5}) != values + 5)
        return 9;
    if (r::next(values, 8, sentinel{values + 5}) != values + 5)
        return 10;
    if (r::prev(values + 5) != values + 4 || r::prev(values + 5, 2) != values + 3)
        return 11;
    if (r::prev(values + 5, 8, values) != values)
        return 12;
    return 0;
}
static_assert(navigation() == 0);

namespace adl_swap {
struct iterator {
    using value_type = int;
    using difference_type = long;
    using pointer = const int*;
    using reference = const int&;
    using iterator_category = s::bidirectional_iterator_tag;
    int* storage = nullptr;
    int* calls = nullptr;
    CANN_ASC_STL_API constexpr const int& operator*() const
    {
        return *storage;
    }
    CANN_ASC_STL_API constexpr iterator& operator++()
    {
        ++storage;
        return *this;
    }
    CANN_ASC_STL_API constexpr iterator operator++(int)
    {
        auto old = *this;
        ++*this;
        return old;
    }
    CANN_ASC_STL_API constexpr iterator& operator--()
    {
        --storage;
        return *this;
    }
    CANN_ASC_STL_API constexpr iterator operator--(int)
    {
        auto old = *this;
        --*this;
        return old;
    }
    friend CANN_ASC_STL_API constexpr bool operator==(const iterator& left, const iterator& right)
    {
        return left.storage == right.storage;
    }
    friend CANN_ASC_STL_API constexpr bool operator!=(const iterator& left, const iterator& right)
    {
        return left.storage != right.storage;
    }
    friend CANN_ASC_STL_API constexpr void iter_swap(const iterator& left, const iterator& right) noexcept
    {
        int old = *left.storage;
        *left.storage = *right.storage;
        *right.storage = old;
        if (left.calls != nullptr)
            ++*left.calls;
    }
};
struct sentinel {
    int* last = nullptr;
    friend CANN_ASC_STL_API constexpr bool operator==(const iterator& iter, sentinel end)
    {
        return iter.storage == end.last;
    }
    friend CANN_ASC_STL_API constexpr bool operator==(sentinel end, const iterator& iter)
    {
        return iter.storage == end.last;
    }
    friend CANN_ASC_STL_API constexpr bool operator!=(const iterator& iter, sentinel end)
    {
        return iter.storage != end.last;
    }
    friend CANN_ASC_STL_API constexpr bool operator!=(sentinel end, const iterator& iter)
    {
        return iter.storage != end.last;
    }
};
struct read_only {
    using value_type = int;
    using difference_type = long;
    using pointer = const int*;
    using reference = const int&;
    using iterator_category = s::input_iterator_tag;
    const int* storage = nullptr;
    CANN_ASC_STL_API constexpr const int& operator*() const
    {
        return *storage;
    }
};
}  // namespace adl_swap
static_assert(s::indirectly_readable<adl_swap::iterator>);
static_assert(!s::indirectly_writable<adl_swap::iterator, int>);
static_assert(s::indirectly_swappable<adl_swap::iterator>);
static_assert(!s::indirectly_swappable<const int*> && !s::indirectly_swappable<adl_swap::read_only>);

template <class Callable, class Void, class... Args>
struct can_call : s::false_type {};
template <class Callable, class... Args>
struct can_call<Callable, s::void_t<decltype(s::declval<Callable>()(s::declval<Args>()...))>, Args...> : s::true_type {
};
static_assert(!can_call<r::equal_to, void, int, unrelated>::value);
static_assert(!can_call<r::not_equal_to, void, int, unrelated>::value);
static_assert(!can_call<r::less, void, int, unrelated>::value);
static_assert(!can_call<r::less_equal, void, int, unrelated>::value);
static_assert(!can_call<r::greater, void, int, unrelated>::value);
static_assert(!can_call<r::greater_equal, void, int, unrelated>::value);
static_assert(!can_call<r::__find_if_fn, void, int*, int*, unrelated>::value);
static_assert(!can_call<r::__find_if_not_fn, void, int*, int*, unrelated>::value);
static_assert(!can_call<r::__find_if_fn, void, int, int, predicate>::value);
static_assert(!can_call<r::__for_each_n::__fn, void, int*, long, unrelated>::value);
static_assert(!can_call<r::__min_element_fn, void, int*, int*, unrelated>::value);
static_assert(!can_call<r::__min_fn, void, int, int, unrelated>::value);

struct record {
    int value;
    bool keep;
    CANN_ASC_STL_API constexpr bool selected() const
    {
        return keep;
    }
};
// Member pointers use INVOKE rather than direct function-call syntax.
using selected_member = decltype(&record::selected);
using keep_member = decltype(&record::keep);
static_assert(s::invocable<selected_member, record&> && s::predicate<selected_member, record&>);
static_assert(s::predicate<selected_member, record*>);
static_assert(s::predicate<selected_member, s::reference_wrapper<record>>);
static_assert(s::predicate<keep_member, record&> && s::predicate<keep_member, record*>);
static_assert(s::predicate<keep_member, s::reference_wrapper<record>>);
static_assert(!s::invocable<selected_member, unrelated&> && !s::predicate<selected_member, unrelated&>);
static_assert(!s::predicate<keep_member, unrelated&>);
static_assert(s::indirect_unary_predicate<selected_member, record*>);
static_assert(s::indirect_unary_predicate<keep_member, record*>);

struct above_two {
    CANN_ASC_STL_API constexpr bool operator()(int value) const
    {
        return value > 2;
    }
};
struct add_ten {
    CANN_ASC_STL_API constexpr void operator()(int& value) const
    {
        value += 10;
    }
};
struct bare_iterator {
    using difference_type = long;
    record* value;
    CANN_ASC_STL_API constexpr record& operator*() const
    {
        return *value;
    }
    CANN_ASC_STL_API constexpr bare_iterator& operator++()
    {
        ++value;
        return *this;
    }
};
static_assert(!s::input_iterator<bare_iterator>);
static_assert(can_call<r::__for_each_n::__fn, void, bare_iterator, long, add_ten, int record::*>::value);

CANN_ASC_STL_API constexpr int algorithm_constraints()
{
    int left = 1;
    int right = 2;
    int calls = 0;
    r::__iter_swap::__iter_swap_fn{}(adl_swap::iterator{&left, &calls}, adl_swap::iterator{&right, &calls});
    if (left != 2 || right != 1 || calls != 1)
        return 1;
    record values[3] = {{3, false}, {1, true}, {4, true}};
    if (r::__find_if_fn{}(values, values + 3, &record::selected) != values + 1)
        return 2;
    if (r::__find_if_fn{}(values, above_two{}, &record::value) != values)
        return 3;
    if (r::__find_if_not_fn{}(values, values + 3, &record::selected) != values)
        return 4;
    if (r::__find_if_not_fn{}(values, above_two{}, &record::value) != values + 1)
        return 5;
    if (r::__min_element_fn{}(values, values + 3, r::less{}, &record::value) != values + 1)
        return 6;
    if (r::__min_element_fn{}(values, r::less{}, &record::value) != values + 1)
        return 7;
    if (r::__min_fn{}(values, r::less{}, &record::value).value != 1)
        return 8;
    if (&r::__min_fn{}(values[0], values[1], r::less{}, &record::value) != values + 1)
        return 9;
    auto result = r::__for_each_n::__fn{}(bare_iterator{values}, 2, add_ten{}, &record::value);
    if (result.in.value != values + 2 || values[0].value != 13 || values[1].value != 11 || values[2].value != 4)
        return 10;
    return 0;
}
static_assert(algorithm_constraints() == 0);

using adl_reverse_iterator = s::reverse_iterator<adl_swap::iterator>;
using adl_move_iterator = s::move_iterator<adl_swap::iterator>;
using adl_counted_iterator = s::counted_iterator<adl_swap::iterator>;
using adl_common_iterator = s::common_iterator<adl_swap::iterator, adl_swap::sentinel>;
static_assert(s::indirectly_swappable<adl_reverse_iterator>);
static_assert(s::indirectly_swappable<adl_move_iterator>);
static_assert(s::indirectly_swappable<adl_counted_iterator>);
static_assert(s::indirectly_swappable<adl_common_iterator>);

CANN_ASC_STL_API int wrapper_swaps()
{
    int left = 1;
    int right = 2;
    int calls = 0;
    adl_swap::iterator first{&left, &calls};
    adl_swap::iterator second{&right, &calls};
    r::__iter_swap::__iter_swap_fn{}(adl_move_iterator{first}, adl_move_iterator{second});
    r::__iter_swap::__iter_swap_fn{}(adl_counted_iterator{first, 1}, adl_counted_iterator{second, 1});
    r::__iter_swap::__iter_swap_fn{}(adl_common_iterator{first}, adl_common_iterator{second});
    r::__iter_swap::__iter_swap_fn{}(adl_reverse_iterator{adl_swap::iterator{&left + 1, &calls}},
        adl_reverse_iterator{adl_swap::iterator{&right + 1, &calls}});
    return calls != 4 || left != 1 || right != 2;
}

CANN_ASC_STL_API int evaluate()
{
    return navigation() + algorithm_constraints() + wrapper_swaps() + constrained_identity(0);
}
}  // namespace asc_stl_cxx17_foundation

#endif  // CANN_ASC_STL_TEST_CXX17_FOUNDATION_SEMANTICS_H
