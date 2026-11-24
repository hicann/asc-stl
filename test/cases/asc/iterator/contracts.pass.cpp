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

#include <asc/iterator>
#include <asc/iterator>  // NOLINT(build/include)
#include <asc/functional>
#include <asc/type_traits>
#include <cstdio>
#include <forward_list>
#include <iterator>
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <utility>

#include "../../../support/iterator_adaptors.h"

namespace iterator_tuple_probe {

struct pair {
    int first;
    int second;
};
template <std::size_t N>
int& get(pair& value) noexcept
{
    return N == 0 ? value.first : value.second;
}
template <std::size_t N>
const int& get(const pair& value) noexcept
{
    return N == 0 ? value.first : value.second;
}
template <std::size_t N>
int&& get(pair&& value) noexcept
{
    return std::move(get<N>(value));
}

}  // namespace iterator_tuple_probe

namespace asc::std {
template <>
struct tuple_size<iterator_tuple_probe::pair> : integral_constant<size_t, 2> {};
template <size_t N>
struct tuple_element<N, iterator_tuple_probe::pair> {
    using type = int;
};
}  // namespace asc::std

namespace {

template <class T, class = void>
struct has_decrement : asc::std::false_type {};
template <class T>
struct has_decrement<T, asc::std::void_t<decltype(--asc::std::declval<T&>())>> : asc::std::true_type {};
template <class T, class = void>
struct has_subscript : asc::std::false_type {};
template <class T>
struct has_subscript<T, asc::std::void_t<decltype(asc::std::declval<const T&>()[0])>> : asc::std::true_type {};

int single_pass()
{
    std::istringstream input("2 4 6");
    auto it = asc::make_transform_iterator(std::istream_iterator<int>(input), asc_stl_iterator_test::twice{});
    auto old = it++;
    if (*old != 4 || *it != 8 || *it++ != 8 || *it != 12) {
        return 70;
    }
    if constexpr (has_decrement<decltype(it)>::value || has_subscript<decltype(it)>::value) {
        return 71;
    }
    std::istringstream index_input("2 0 1");
    int data[3] = {11, 22, 33};
    auto permutation = asc::make_permutation_iterator(data, std::istream_iterator<int>(index_input));
    *permutation++ = 44;
    if (data[2] != 44 || *permutation != 11) {
        return 72;
    }
    std::istringstream left("1 2"), right("10 20");
    auto zip = asc::make_zip_iterator(std::istream_iterator<int>(left), std::istream_iterator<int>(right));
    asc::std::tuple<int, int> old_pair = *zip++;
    if (asc::std::get<0>(old_pair) != 1 || asc::std::get<1>(old_pair) != 10 || (*zip).template get<1>() != 20) {
        return 73;
    }
    return 0;
}

int weaker_bases()
{
    std::forward_list<int> input{2, 4, 6};
    auto forward = asc::make_transform_iterator(input.begin(), asc_stl_iterator_test::twice{});
    static_assert(!has_decrement<decltype(forward)>::value);
    static_assert(!has_subscript<decltype(forward)>::value);
    auto copy = forward;
    ++copy;
    if (*forward != 4 || *copy != 8) {
        return 74;
    }
    std::list<int> list{3, 5, 7};
    auto bidirectional = asc::make_transform_iterator(list.begin(), asc_stl_iterator_test::twice{});
    static_assert(has_decrement<decltype(bidirectional)>::value);
    static_assert(!has_subscript<decltype(bidirectional)>::value);
    ++bidirectional;
    if (*bidirectional-- != 10 || *bidirectional != 6) {
        return 75;
    }
    auto mixed = asc::make_zip_iterator(input.begin(), list.begin());
    static_assert(!has_decrement<decltype(mixed)>::value);
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
    static_assert(asc::std::forward_iterator<decltype(forward)>);
    static_assert(asc::std::bidirectional_iterator<decltype(bidirectional)>);
    static_assert(asc::std::forward_iterator<decltype(mixed)>);
#endif
    return 0;
}

int output_handles()
{
    std::vector<int> output;
    auto destination = asc::make_transform_output_iterator(std::back_inserter(output), asc_stl_iterator_test::twice{});
    *destination++ = 3;
    auto zip = asc::make_zip_iterator(std::back_inserter(output), asc::make_discard_iterator());
    *zip++ = asc::std::tuple<int, int>{7, 77};
    if (output.size() != 2 || output[0] != 6 || output[1] != 7) {
        return 76;
    }
    int values[3] = {};
    auto stateful = [calls = 0, &values](std::ptrdiff_t index, int value) mutable { values[index] = value + ++calls; };
    auto tab = asc::make_tabulate_output_iterator(stateful);
    auto saved = *tab;
    saved = 10;
    saved = 20;
    *++tab = 30;
    if (values[0] != 22 || values[1] != 31) {
        return 77;
    }
    return 0;
}

struct mutable_only {
    int operator()(int value)
    {
        return value;
    }
};
using read_only = asc::transform_output_iterator<asc_stl_iterator_test::twice, const int*>;
static_assert(!asc::std::is_assignable_v<typename read_only::reference, int>);
using readonly_zip = asc::zip_iterator<const int*, int*>;
static_assert(!asc::std::is_assignable_v<typename readonly_zip::reference, asc::std::tuple<int, int>>);
using pointer_zip = asc::zip_iterator<int*, int*>;
static_assert(!asc::std::is_assignable_v<typename pointer_zip::reference, asc::std::tuple<int>>);
using value_zip = asc::zip_iterator<asc::counting_iterator<int>, int*>;
static_assert(!asc::std::is_assignable_v<typename value_zip::reference, asc::std::tuple<int, int>>);
static_assert(!asc::detail::iterator_detail::valid_read<mutable_only, int*>::value);

int state_and_const()
{
    int input[2] = {2, 4};
    const int shift = 9;
    auto function = [shift](int value) noexcept { return value + shift; };
    auto iterator = asc::make_transform_iterator(input, function);
    decltype(iterator) unbound;
    decltype(iterator) other_unbound;
    if (unbound != other_unbound || unbound == iterator) {
        return 78;
    }
    unbound = iterator;
    other_unbound = unbound;
    if (*other_unbound != 11 || *++unbound != 13) {
        return 79;
    }
    auto writable = asc::make_transform_iterator(input, asc_stl_iterator_test::identity{});
    const auto fixed = writable;
    *fixed = 12;
    asc::transform_iterator<asc_stl_iterator_test::identity, const int*> constant(writable);
    if (*constant != 12 || fixed != constant || input[0] != 12) {
        return 80;
    }
    auto stride = asc::make_strided_iterator(input, 2);
    asc::strided_iterator<const int*> const_stride(stride);
    if (const_stride - stride != 0 || const_stride != stride) {
        return 81;
    }
    asc::zip_iterator<const int*, const int*> cz(asc::make_zip_iterator(input, input + 1));
    return (*cz).template get<0>() == 12 ? 0 : 82;
}

struct move_out {
    std::unique_ptr<int>&& operator()(std::unique_ptr<int>&& value) const noexcept
    {
        return std::move(value);
    }
};

int movable_values()
{
    std::unique_ptr<int> first[2];
    first[0] = std::make_unique<int>(3);
    first[1] = std::make_unique<int>(7);
    auto zip = asc::make_zip_iterator(first, first + 1);
    auto moved = asc::std::iter_move(zip);
    asc::std::tuple<std::unique_ptr<int>, std::unique_ptr<int>> values = std::move(moved);
    if (first[0] || first[1] || *asc::std::get<0>(values) != 3 || *asc::std::get<1>(values) != 7) {
        return 83;
    }
    std::unique_ptr<int> destination;
    auto output = asc::make_transform_output_iterator(&destination, move_out{});
    *output = std::make_unique<int>(11);
    if (!destination || *destination != 11) {
        return 84;
    }
    auto rw = asc::make_transform_input_output_iterator(&destination, asc_stl_iterator_test::identity{}, move_out{});
    auto value = asc::std::iter_move(rw);
    if (destination || !value || *value != 11) {
        return 85;
    }
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
    static_assert(asc::std::indirectly_readable<decltype(zip)>);
    static_assert(asc::std::indirectly_movable_storable<decltype(rw), decltype(rw)>);
#endif
    return 0;
}

struct qualified_call {
    int operator()(int&) & noexcept
    {
        return 1;
    }
    int operator()(int&) const& noexcept
    {
        return 2;
    }
    int operator()(int&) && noexcept
    {
        return 3;
    }
    int operator()(int&) const&& noexcept
    {
        return 4;
    }
};

int tuple_forwarding()
{
    int value = 9;
    asc::std::tuple<int&> tuple(value);
    auto f = asc::make_zip_function(qualified_call{});
    const auto cf = f;
    if (f(tuple) != 1 || cf(tuple) != 2 || std::move(f)(tuple) != 3 || std::move(cf)(tuple) != 4) {
        return 86;
    }
    auto consume = asc::make_zip_function([](std::unique_ptr<int> x) { return *x; });
    asc::std::tuple<std::unique_ptr<int>> owning(std::make_unique<int>(19));
    if (consume(std::move(owning)) != 19 || asc::std::get<0>(owning)) {
        return 87;
    }
    auto expanded = asc::make_zip_function(asc_stl_iterator_test::add_pair{});
    iterator_tuple_probe::pair custom{3, 11};
    if (expanded(custom) != 14 || expanded(std::move(custom)) != 14) {
        return 94;
    }
    return 0;
}

struct noncopy_input {
    using value_type = std::unique_ptr<int>;
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;
    pointer data;
    std::size_t* position;
    reference operator*() const noexcept
    {
        return data[*position];
    }
    noncopy_input& operator++() noexcept
    {
        ++*position;
        return *this;
    }
    void operator++(int) noexcept
    {
        ++*this;
    }
};

int single_pass_noncopy()
{
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
    std::unique_ptr<int> data[2];
    data[0] = std::make_unique<int>(3);
    data[1] = std::make_unique<int>(7);
    std::size_t position = 0;
    auto input = asc::make_transform_iterator(noncopy_input{data, &position}, asc_stl_iterator_test::identity{});
    static_assert(asc::std::input_iterator<decltype(input)>);
    static_assert(asc::std::is_same_v<decltype(input++), void>);
    input++;
    return position == 1 && **input == 7 ? 0 : 95;
#else
    return 0;
#endif
}

struct throw_read {
    int operator()(int) const
    {
        throw std::runtime_error("read");
    }
};
struct throw_copy {
    bool* fail;
    explicit throw_copy(bool* flag) noexcept : fail(flag)
    {}
    throw_copy(const throw_copy& other) : fail(other.fail)
    {
        if (*fail) {
            throw std::runtime_error("copy");
        }
    }
    int operator()(int value) const noexcept
    {
        return value;
    }
};

struct move_may_throw {
    using value_type = int;
    using reference = int&;
    using pointer = int*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    int* position;
    static bool fail;
    // Implicit by design: exercise the base-iterator converting constructor.
    // NOLINTNEXTLINE(runtime/explicit)
    move_may_throw(int* value) noexcept : position(value)
    {}
    move_may_throw(const move_may_throw&) noexcept = default;
    move_may_throw(move_may_throw&& other) : position(other.position)
    {
        if (fail) {
            throw std::runtime_error("iterator move");
        }
    }
    int& operator*() const noexcept
    {
        return *position;
    }
    move_may_throw& operator++() noexcept
    {
        ++position;
        return *this;
    }
    move_may_throw operator++(int)
    {
        auto copy = *this;
        ++*this;
        return copy;
    }
    bool operator==(const move_may_throw& other) const noexcept
    {
        return position == other.position;
    }
};
bool move_may_throw::fail = false;

int conversion_exceptions()
{
    int value = 3;
    auto source = asc::make_transform_output_iterator(&value, asc_stl_iterator_test::twice{});
    using target = asc::transform_output_iterator<asc_stl_iterator_test::twice, move_may_throw>;
    static_assert(noexcept(target(source)));
    move_may_throw::fail = true;
    target converted(source);
    move_may_throw::fail = false;
    *converted = 4;
    if (value != 8) {
        return 92;
    }
    auto positions = asc::make_zip_iterator(&value, &value);
    using zipped = asc::zip_iterator<move_may_throw, int*>;
    static_assert(!noexcept(zipped(positions)));
    move_may_throw::fail = true;
    try {
        zipped converted_zip(positions);
        (void)converted_zip;
        return 93;
    } catch (const std::runtime_error&) {
    }
    move_may_throw::fail = false;
    return 0;
}

int exceptions()
{
    int data[2] = {3, 5};
    auto read = asc::make_transform_iterator(data, throw_read{});
    static_assert(!noexcept(*read));
    try {
        (void)*read;
        return 88;
    } catch (const std::runtime_error&) {
    }
    bool fail = false;
    auto copy = asc::make_transform_iterator(data, throw_copy(&fail));
    static_assert(!noexcept(copy + 1));
    fail = true;
    try {
        auto next = copy + 1;
        (void)next;
        return 89;
    } catch (const std::runtime_error&) {
    }
    int calls = 0;
    auto output = asc::make_transform_output_iterator(data, [&calls](int) -> int {
        ++calls;
        throw std::runtime_error("write");
    });
    static_assert(!noexcept(*output = 9));
    try {
        *output = 9;
        return 90;
    } catch (const std::runtime_error&) {
    }
    return calls == 1 && data[0] == 3 ? 0 : 91;
}

}  // namespace

int main()
{
    const int results[] = {asc_stl_iterator_test::evaluate(), single_pass(), weaker_bases(), output_handles(),
        state_and_const(), movable_values(), tuple_forwarding(), exceptions(), conversion_exceptions(),
        single_pass_noncopy()};
    for (int code : results) {
        if (code) {
            std::fprintf(stderr, "iterator contract failure %d\n", code);
            return code;
        }
    }
    return 0;
}
