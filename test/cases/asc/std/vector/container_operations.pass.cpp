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

#include <asc/std/bitset>
#include <asc/std/deque>
#include <asc/std/forward_list>
#include <asc/std/inplace_vector>
#include <asc/std/list>
#include <asc/std/map>
#include <asc/std/set>
#include <asc/std/unordered_map>
#include <asc/std/unordered_set>
#include <asc/std/vector>

#include <cstddef>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

namespace {

namespace ast = asc::std;

template <class T>
struct allocator : std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    template <class U>
    struct rebind {
        using other = allocator<U>;
    };
    allocator() = default;
    template <class U>
    allocator(const allocator<U>&) noexcept
    {}
};

using vector = ast::vector<int, allocator<int>>;
using inplace = ast::inplace_vector<int, 8>;
using deque = ast::deque<int, allocator<int>>;
using list = ast::list<int, allocator<int>>;
using forward_list = ast::forward_list<int, allocator<int>>;
using set = ast::set<int, std::less<int>, allocator<int>>;
using map = ast::map<int, int, std::less<int>, allocator<ast::pair<const int, int>>>;
using hash_set = ast::unordered_set<int, std::hash<int>, std::equal_to<int>, allocator<int>>;

struct colliding_hash {
    std::size_t operator()(int) const noexcept
    {
        return 0;
    }
};
using hash_map = ast::unordered_map<int, int, colliding_hash, std::equal_to<int>, allocator<ast::pair<const int, int>>>;

template <class C>
constexpr bool check_sequence_types()
{
    return std::is_same_v<typename C::value_type, int> && std::is_same_v<typename C::reference, int&> &&
        std::is_same_v<typename C::const_reference, const int&> && std::is_same_v<typename C::size_type, ast::size_t> &&
        std::is_same_v<decltype(std::declval<C&>().begin()), typename C::iterator> &&
        std::is_same_v<decltype(*std::declval<typename C::iterator&>()), int&>;
}
static_assert(check_sequence_types<vector>() && check_sequence_types<inplace>() && check_sequence_types<deque>());
static_assert(check_sequence_types<list>() && check_sequence_types<forward_list>());

template <class C>
constexpr bool check_contiguous_types()
{
    return std::is_same_v<typename C::pointer, int*> && std::is_same_v<typename C::const_pointer, const int*> &&
        std::is_same_v<typename C::difference_type, ast::ptrdiff_t> &&
        std::is_same_v<decltype(std::declval<const C&>().begin()), typename C::const_iterator> &&
        std::is_same_v<decltype(*std::declval<typename C::const_iterator&>()), const int&>;
}
static_assert(check_contiguous_types<vector>() && check_contiguous_types<inplace>());
static_assert(std::is_same_v<vector::allocator_type, allocator<int>>);
static_assert(std::is_same_v<deque::allocator_type, allocator<int>>);
static_assert(std::is_same_v<deque::difference_type, ast::ptrdiff_t>);
static_assert(std::is_same_v<list::allocator_type, allocator<int>>);
static_assert(std::is_same_v<forward_list::allocator_type, allocator<int>>);
static_assert(std::is_same_v<set::value_type, int>);
static_assert(std::is_same_v<decltype(std::declval<map::value_type>().first), const int> &&
    std::is_same_v<decltype(std::declval<map::value_type>().second), int>);
static_assert(std::is_same_v<decltype(std::declval<hash_map::value_type>().first), const int> &&
    std::is_same_v<decltype(std::declval<hash_map::value_type>().second), int>);
static_assert(std::is_same_v<set::size_type, ast::size_t> && std::is_same_v<hash_set::size_type, ast::size_t>);
static_assert(std::is_same_v<map::size_type, ast::size_t> && std::is_same_v<hash_map::size_type, ast::size_t>);
static_assert(std::is_same_v<ast::bitset<4>::const_reference, bool>);
static_assert(std::is_base_of_v<ast::bitset<0>::base, ast::bitset<0>>);
static_assert(std::is_base_of_v<ast::bitset<65>::base, ast::bitset<65>>);

struct absent {};
[[maybe_unused]] absent erase(...)
{
    return {};
}
[[maybe_unused]] absent erase_if(...)
{
    return {};
}
struct always_true {
    bool operator()(int value) const
    {
        return value != 0;
    }
};
static_assert(std::is_same_v<decltype(erase(std::declval<inplace&>(), 1)), absent>);
static_assert(std::is_same_v<decltype(erase_if(std::declval<inplace&>(), always_true{})), absent>);

bool check_forward_list()
{
    forward_list values(allocator<int>{});
    for (int trial = 0; trial < 3; ++trial) {
        values.push_front(4);
        values.push_front(7);
        values.push_front(-3);
        auto first = values.begin();
        if (values.empty() || first == values.end() || *first != -3 || *++first != 7) {
            return false;
        }
        values.pop_front();
        if (*values.begin() != 7 || ++values.begin() == values.end()) {
            return false;
        }
        values.clear();
        values.clear();
        if (!values.empty() || values.begin() != values.end()) {
            return false;
        }
    }
    return true;
}

bool check_hash_lookup_and_reset()
{
    hash_map values(allocator<ast::pair<const int, int>>{});
    if (!values.empty() || values.find(0) != values.end()) {
        return false;
    }
    for (int key = 0; key < 23; ++key) {
        values.insert(hash_map::value_type(key, 3 * key + 1));
    }
    values.insert(hash_map::value_type(11, -99));
    for (int key = 0; key < 23; ++key) {
        const auto found = values.find(key);
        if (found == values.end() || found->first != key || found->second != 3 * key + 1) {
            return false;
        }
    }
    if (values.size() != 23 || values.find(-1) != values.end() || values.find(23) != values.end()) {
        return false;
    }
    values.clear();
    if (!values.empty() || values.find(11) != values.end()) {
        return false;
    }
    values.insert(hash_map::value_type(11, 7));
    return values.find(11)->second == 7;
}

bool check_sets()
{
    set ordered(allocator<int>{});
    hash_set hashed(allocator<int>{});
    for (auto key : {4, 1, 4, -3}) {
        ordered.insert(key);
        hashed.insert(key);
    }
    if (ordered.empty() || hashed.empty() || ordered.size() != 3 || hashed.size() != 3) {
        return false;
    }
    ordered.clear();
    hashed.clear();
    if (!ordered.empty() || !hashed.empty() || ordered.begin() != ordered.end() || hashed.begin() != hashed.end()) {
        return false;
    }
    ordered.insert(4);
    hashed.insert(4);
    return ordered.find(4) != ordered.end() && hashed.find(4) != hashed.end();
}

bool check_inplace_assignment_and_erase()
{
    inplace original;
    const int initial[] = {2, 3, 2, 5, 8, 2};
    for (auto value : initial) {
        original.unchecked_push_back(value);
    }
    inplace copied;
    copied.unchecked_push_back(-4);
    copied = original;
    const auto even_twos = [](int value) { return value == 2; };
    if (copied.size() != original.size() || copied.erase_if(even_twos) != 3 || copied.size() != 3) {
        return false;
    }
    if (copied[0] != 3 || copied[1] != 5 || copied[2] != 8 || original.size() != 6) {
        return false;
    }
    const auto above_five = [](int value) { return value > 5; };
    const auto misses = [](int value) { return value == 99; };
    if (copied.erase_if(above_five) != 1 || copied.erase_if(misses) != 0) {
        return false;
    }
    inplace moved;
    moved = std::move(copied);
    return moved.size() == 2 && moved[0] == 3 && moved[1] == 5;
}

}  // namespace

int main()
{
    if (!check_forward_list()) {
        return 1;
    }
    if (!check_hash_lookup_and_reset()) {
        return 2;
    }
    if (!check_sets()) {
        return 3;
    }
    return check_inplace_assignment_and_erase() ? 0 : 4;
}
