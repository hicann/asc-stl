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

#ifndef ASC_STL_TEST_SUPPORT_STD_FEATURE_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_STD_FEATURE_SEMANTICS_H

#include <asc/std/version>
#include <asc/std/algorithm>
#include <asc/std/array>
#include <asc/std/bit>
#include <asc/std/cstddef>
#include <asc/std/functional>
#include <asc/std/iterator>
#include <asc/std/memory>
#include <asc/std/numeric>
#include <asc/std/new>
#include <asc/std/source_location>
#include <asc/std/tuple>
#include <asc/std/type_traits>
#include <asc/std/utility>

namespace std_feature_tests {

struct incomplete;
struct aggregate {
    int value;
};
struct final_type final {};
enum class scoped : unsigned { value = 42 };
enum unscoped { value = 7 };
struct throwing_conversion {
    operator int() noexcept(false);
};
struct immovable {
    immovable() = default;
    immovable(const immovable&) = delete;
    immovable& operator=(const immovable&) = delete;
};
struct function {
    CANN_ASC_STL_API constexpr int operator()(int x) const noexcept
    {
        return x + 3;
    }
};
struct object {
    int value;
    CANN_ASC_STL_API constexpr int add(int x) const noexcept
    {
        return value + x;
    }
};
struct pointer {
    using element_type = int;
    int* p;
    CANN_ASC_STL_API constexpr int* operator->() const noexcept
    {
        return p;
    }
};
struct from_tuple {
    int value;
    CANN_ASC_STL_API constexpr explicit from_tuple(int x, int y) : value(x + y)
    {}
};
struct nondefault {
    nondefault() = delete;
    int value;
};

static_assert(asc::std::bool_constant<true>{}());
static_assert(asc::std::integral_constant<int, 42>{}() == 42);
static_assert(asc::std::is_same_v<asc::std::void_t<int, incomplete>, void>);
static_assert(asc::std::conjunction_v<asc::std::true_type>);
static_assert(!asc::std::conjunction_v<asc::std::false_type, incomplete>);
static_assert(asc::std::disjunction_v<asc::std::true_type, incomplete>);
static_assert(asc::std::negation_v<asc::std::false_type>);
static_assert(asc::std::is_bounded_array_v<int[2]> && !asc::std::is_bounded_array_v<int[]>);
static_assert(asc::std::is_unbounded_array_v<const int[]> && !asc::std::is_unbounded_array_v<int[2]>);
static_assert(asc::std::is_same_v<asc::std::type_identity_t<const int&>, const int&>);
static_assert(asc::std::is_same_v<asc::std::remove_cvref_t<const int (&)[2]>, int[2]>);
static_assert(asc::std::is_null_pointer_v<decltype(nullptr)> && !asc::std::is_null_pointer_v<void*>);
static_assert(asc::std::is_scoped_enum_v<scoped> && !asc::std::is_scoped_enum_v<unscoped>);
static_assert(!asc::std::is_scoped_enum_v<int>);
static_assert(asc::std::is_nothrow_convertible_v<int, long> && asc::std::is_nothrow_convertible_v<void, void>);
static_assert(!asc::std::is_nothrow_convertible_v<throwing_conversion, int>);
static_assert(!asc::std::is_nothrow_convertible_v<void, int>);
static_assert(asc::std::is_swappable_v<int> && asc::std::is_nothrow_swappable_v<int>);
static_assert(!asc::std::is_swappable_v<immovable> && !asc::std::is_swappable_v<void>);
static_assert(asc::std::is_invocable_v<function, int> && !asc::std::is_invocable_v<function>);
static_assert(asc::std::is_invocable_r_v<long, function, int>);
static_assert(asc::std::is_nothrow_invocable_v<function, int>);
static_assert(asc::std::is_same_v<asc::std::invoke_result_t<function, int>, int>);
static_assert(asc::std::is_same_v<asc::std::unwrap_reference_t<asc::std::reference_wrapper<int>>, int&>);
static_assert(asc::std::is_same_v<asc::std::unwrap_ref_decay_t<const asc::std::reference_wrapper<int>&>, int&>);
static_assert(asc::std::is_same_v<asc::std::make_index_sequence<3>, asc::std::index_sequence<0, 1, 2>>);
static_assert(asc::std::is_same_v<asc::std::tuple_element_t<1, const asc::std::tuple<int, long>>, const long>);
static_assert(asc::std::to_underlying(scoped::value) == 42u);
static_assert(asc::std::cmp_less(-1, 0u) && !asc::std::cmp_equal(-1, ~0u));
static_assert(asc::std::cmp_greater(0u, -1) && asc::std::cmp_not_equal(1u, 2));
static_assert(asc::std::cmp_less_equal(1u, 1) && asc::std::cmp_greater_equal(1, 1u));
static_assert(!asc::std::in_range<unsigned>(-1) && asc::std::in_range<int>(42u));
static_assert(asc::std::gcd(-24, 18) == 6 && asc::std::gcd(0, 0) == 0);
static_assert(asc::std::lcm(-6, 4) == 12 && asc::std::lcm(0, 42) == 0);
static_assert(asc::std::countl_zero(0u) == asc::std::numeric_limits<unsigned>::digits);
static_assert(asc::std::countr_zero(0u) == asc::std::numeric_limits<unsigned>::digits);
static_assert(asc::std::countl_one(~0u) == asc::std::numeric_limits<unsigned>::digits);
static_assert(asc::std::countr_one(7u) == 3 && asc::std::popcount(0xa5u) == 4);
static_assert(asc::std::rotl(1u, -1) == (1u << (asc::std::numeric_limits<unsigned>::digits - 1)));
static_assert(asc::std::rotr(2u, -1) == 4u);
static_assert(asc::std::bit_floor(19u) == 16u && asc::std::bit_ceil(19u) == 32u);
static_assert(asc::std::bit_ceil(0u) == 1u && asc::std::bit_width(0u) == 0);
static_assert(asc::std::bit_width(8u) == 4 && asc::std::has_single_bit(8u));
static_assert(asc::std::endian::native == asc::std::endian::little);
static_assert(asc::std::to_integer<int>((asc::std::byte{3} << 2) | asc::std::byte{1}) == 13);
static_assert(asc::std::to_integer<int>(~asc::std::byte{0}) == 255);
static_assert(noexcept(asc::std::unreachable()));
#if defined(CANN_ASC_STL_LIB_is_aggregate)
static_assert(asc::std::is_aggregate_v<aggregate> && !asc::std::is_aggregate_v<int>);
#endif
#if defined(CANN_ASC_STL_LIB_is_final)
static_assert(asc::std::is_final_v<final_type> && !asc::std::is_final_v<aggregate>);
#endif
#if defined(CANN_ASC_STL_LIB_has_unique_object_representations)
static_assert(asc::std::has_unique_object_representations_v<unsigned char>);
static_assert(!asc::std::has_unique_object_representations_v<float>);
#endif
#if defined(CANN_ASC_STL_LIB_is_constant_evaluated)
static_assert(asc::std::is_constant_evaluated());
#endif
#if defined(CANN_ASC_STL_LIB_bit_cast)
static_assert(asc::std::bit_cast<unsigned>(1.0f) == 0x3f800000u);
static_assert(asc::std::bit_cast<nondefault>(42).value == 42);
#endif

template <class T>
CANN_ASC_STL_API constexpr bool bit_semantics()
{
    constexpr int digits = asc::std::numeric_limits<T>::digits;
    constexpr T ones = static_cast<T>(~T{0});
    return asc::std::countl_zero(T{0}) == digits && asc::std::countr_zero(T{0}) == digits &&
        asc::std::countl_one(ones) == digits && asc::std::countr_one(T{7}) == 3 && asc::std::popcount(ones) == digits &&
        asc::std::rotl(T{1}, -1) == static_cast<T>(T{1} << (digits - 1)) && asc::std::rotr(T{2}, -1) == T{4} &&
        asc::std::bit_floor(T{19}) == T{16} && asc::std::bit_ceil(T{19}) == T{32} && asc::std::bit_width(T{8}) == 4;
}
static_assert(bit_semantics<unsigned char>());
static_assert(bit_semantics<unsigned short>());
static_assert(bit_semantics<unsigned>());
static_assert(bit_semantics<unsigned long>());
static_assert(bit_semantics<unsigned long long>());
#if CANN_ASC_STL_DETAIL_HAS_INT128()
static_assert(bit_semantics<__uint128_t>());
#endif

CANN_ASC_STL_API constexpr bool utility_semantics()
{
    int value = 3;
    const int& cv = asc::std::as_const(value);
    if (&cv != &value || asc::std::exchange(value, 9) != 3 || value != 9)
        return false;
    if (asc::std::addressof(value) != &value || asc::std::to_address(pointer{&value}) != &value)
        return false;
    int data[4] = {1, 2, 3, 4};
    auto array = asc::std::to_array(data);
    auto moved = asc::std::to_array(asc::std::move(data));
    if (array[2] != 3 || moved[3] != 4 || asc::std::ssize(array) != 4 || asc::std::ssize(data) != 4)
        return false;
    if (*asc::std::make_reverse_iterator(data + 4) != 4)
        return false;
    if (asc::std::shift_left(data, data + 4, 2) != data + 2 || data[0] != 3 || data[1] != 4)
        return false;
    if (asc::std::shift_right(data, data + 2, 1) != data + 1 || data[1] != 3)
        return false;
    if (asc::std::clamp(value, 1, 4) != 4)
        return false;
    return true;
}

CANN_ASC_STL_API constexpr bool callable_semantics()
{
    object o{7};
    if (asc::std::invoke(&object::value, o) != 7 || asc::std::invoke(&object::value, &o) != 7)
        return false;
    if (asc::std::invoke(&object::add, o, 2) != 9 || asc::std::invoke(&object::add, &o, 2) != 9)
        return false;
    if (asc::std::invoke(&object::add, asc::std::ref(o), 2) != 9)
        return false;
    if (asc::std::invoke(&object::value, asc::std::ref(o)) != 7)
        return false;
    if (asc::std::invoke_r<long>(function{}, 4) != 7)
        return false;
    asc::std::invoke_r<void>(function{}, 4);
    auto nf = asc::std::not_fn(function{});
    const auto cnf = nf;
    // NOLINTNEXTLINE(build/include_what_you_use)
    if (!nf(-3) || !cnf(-3) || !asc::std::move(nf)(-3) || !asc::std::move(cnf)(-3))
        return false;
    return true;
}

CANN_ASC_STL_API constexpr bool tuple_semantics()
{
    asc::std::tuple<int, long> tuple{2, 4};
    if (asc::std::get<long>(tuple) != 4 || asc::std::apply(function{}, asc::std::tuple<int>{2}) != 5)
        return false;
    if (asc::std::make_from_tuple<from_tuple>(tuple).value != 6)
        return false;
    asc::std::pair<int, long> pair{3, 4};
    if (asc::std::get<long>(pair) != 4)
        return false;
    return true;
}

CANN_ASC_STL_API constexpr bool semantics()
{
    return utility_semantics() && callable_semantics() && tuple_semantics();
}

CANN_ASC_STL_API constexpr bool numeric_semantics()
{
    int values[4] = {};
    int out[4] = {};
    asc::std::iota(values, values + 4, 1);
    if (asc::std::accumulate(values, values + 4, 0) != 10)
        return false;
    if (asc::std::inner_product(values, values + 4, values, 0) != 30)
        return false;
    if (asc::std::reduce(values, values + 4) != 10)
        return false;
    if (asc::std::transform_reduce(values, values + 4, values, 0) != 30)
        return false;
    asc::std::partial_sum(values, values + 4, out);
    if (out[3] != 10)
        return false;
    asc::std::adjacent_difference(values, values + 4, out);
    if (out[0] != 1 || out[3] != 1)
        return false;
    asc::std::inclusive_scan(values, values + 4, out);
    if (out[3] != 10)
        return false;
    asc::std::exclusive_scan(values, values + 4, out, 0);
    if (out[3] != 6)
        return false;
    asc::std::transform_inclusive_scan(values, values + 4, out, asc::std::plus<>{}, function{}, 0);
    if (out[3] != 22)
        return false;
    asc::std::transform_exclusive_scan(values, values + 4, out, 0, asc::std::plus<>{}, function{});
    if (out[3] != 15)
        return false;
    if (asc::std::equal(values, values + 4, values, values + 3))
        return false;
    if (asc::std::mismatch(values, values + 4, values, values + 3).first != values + 3)
        return false;
    if (!asc::std::is_permutation(values, values + 4, values, values + 4))
        return false;
    return asc::std::launder(values) == values;
}

struct generator {
    using result_type = unsigned;
    unsigned state = 0;
    CANN_ASC_STL_API static constexpr unsigned min()
    {
        return 0;
    }
    CANN_ASC_STL_API static constexpr unsigned max()
    {
        return 255;
    }
    CANN_ASC_STL_API unsigned operator()()
    {
        return state = (state * 5 + 1) & 255;
    }
};

CANN_ASC_STL_API bool storage_semantics()
{
    int source[3] = {3, 4, 5};
    alignas(int) unsigned char storage[sizeof(source)];
    int* destination = reinterpret_cast<int*>(storage);
    auto result = asc::std::uninitialized_move_n(source, 3, destination);
    bool ok = result.first == source + 3 && result.second == destination + 3 && destination[2] == 5;
    asc::std::destroy(destination, destination + 3);
    asc::std::uninitialized_value_construct(destination, destination + 3);
    ok = ok && destination[0] == 0 && destination[2] == 0;
    ok = ok && asc::std::destroy_n(destination, 3) == destination + 3;
    asc::std::uninitialized_default_construct_n(destination, 3);
    asc::std::destroy_n(destination, 3);
    asc::std::uninitialized_fill_n(destination, 3, 7);
    ok = ok && destination[0] == 7 && destination[2] == 7;
    asc::std::destroy_n(destination, 3);
    asc::std::uninitialized_copy_n(source, 3, destination);
    ok = ok && destination[0] == 3 && destination[2] == 5;
    asc::std::destroy_at(destination);
    asc::std::destroy(destination + 1, destination + 3);
    int sample[2] = {};
    generator random;
    auto end = asc::std::sample(source, source + 3, sample, 2, random);
    return ok && end == sample + 2 && sample[0] >= 3 && sample[1] <= 5 && sample[0] < sample[1];
}

#if defined(CANN_ASC_STL_LIB_source_location)
CANN_ASC_STL_API constexpr bool source_location_semantics(
    asc::std::source_location where = asc::std::source_location::current())
{
    return where.line() != 0 && where.file_name()[0] != '\0';
}
static_assert(source_location_semantics());
static_assert(asc::std::source_location{}.line() == 0);
#endif

}  // namespace std_feature_tests

#endif  // ASC_STL_TEST_SUPPORT_STD_FEATURE_SEMANTICS_H
