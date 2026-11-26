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

#include <asc/std/map>
#include <asc/std/set>
#include <asc/std/unordered_map>
#include <asc/std/unordered_set>

#include <cstddef>
#include <iostream>
#include <map>
#include <set>
#include <utility>

#include "support/counting_allocator.h"

namespace {

using asc_stl_allocation_test::allocation_counts;
using asc_stl_allocation_test::counting_allocator;

struct order {
    bool descending;

    bool operator()(int left, int right) const
    {
        return descending ? left > right : left < right;
    }
};

using ordered_set = asc::std::set<int, order, counting_allocator<int>>;
using ordered_allocator = counting_allocator<asc::std::pair<const int, int>>;  // NOLINT(build/include_what_you_use)
using ordered_map = asc::std::map<int, int, order, ordered_allocator>;
using entry = ordered_map::value_type;

bool check_ordered_containers(bool descending, int phase)
{
    const order compare{descending};
    allocation_counts from_set, from_map, to_set, to_map;
    {
        ordered_set actual_set(compare, counting_allocator<int>(from_set));
        ordered_map actual_map(compare, ordered_allocator(from_map));
        std::set<int, order> expected_set(compare);
        std::map<int, int, order> expected_map(compare);

        // Both directions and alternating keys exercise different AVL rotations.
        for (int i = 0; i != 171; ++i) {
            const int key = (37 * i + phase) % 97 - 48;
            const int value = key * 3 - i;
            const auto test_set = actual_set.insert(key);
            const auto ref_set = expected_set.insert(key);
            const auto test_map = actual_map.insert(entry(key, value));
            const auto ref_map = expected_map.emplace(key, value);
            if (test_set.second != ref_set.second || *test_set.first != *ref_set.first ||
                test_map.second != ref_map.second || test_map.first->first != ref_map.first->first ||
                test_map.first->second != ref_map.first->second || actual_set.size() != expected_set.size() ||
                actual_map.size() != expected_map.size())
                return false;
        }

        for (int key = -55; key <= 55; ++key) {
            if (actual_map.count(key) != expected_map.count(key) || actual_set.count(key) != expected_set.count(key))
                return false;
            if (expected_map.count(key) != 0) {
                ++actual_map[key];
                ++expected_map[key];
            }
        }

        ordered_set moved_set(compare, counting_allocator<int>(to_set));
        ordered_map moved_map(compare, ordered_allocator(to_map));
        moved_set.insert(-99);
        moved_map.insert(entry(-99, 0));
        const auto first_key = actual_set.begin();
        const auto first_value = actual_map.begin();
        moved_set = std::move(actual_set);
        moved_map = std::move(actual_map);
        if (moved_set.begin() != first_key || moved_map.begin() != first_value || !actual_set.empty() ||
            !actual_map.empty() || to_set.outstanding() != 0 || to_map.outstanding() != 0)
            return false;

        auto found_key = moved_set.begin();
        auto found_value = moved_map.begin();
        for (auto expected = expected_map.begin(); expected != expected_map.end(); ++expected) {
            if (found_key == moved_set.end() || found_value == moved_map.end() || *found_key != expected->first ||
                found_value->first != expected->first || found_value->second != expected->second)
                return false;
            ++found_key;
            ++found_value;
        }
        if (found_key != moved_set.end() || found_value != moved_map.end())
            return false;

        moved_set.clear();
        moved_map.clear();
        if (!moved_set.empty() || !moved_map.empty() || from_set.outstanding() != 0 || from_map.outstanding() != 0)
            return false;
        actual_set.insert(7);
        actual_map[7] = 11;
        const auto reused_key = actual_set.find(7);
        const auto reused_value = actual_map.find(7);
        if (reused_key == actual_set.end() || reused_value == actual_map.end() || *reused_key != 7 ||
            reused_value->second != 11)
            return false;
    }
    return from_set.outstanding() == 0 && from_map.outstanding() == 0 && to_set.outstanding() == 0 &&
        to_map.outstanding() == 0;
}

struct key_with_tag {
    int key;
    int tag;

    key_with_tag(int logical_key, int identity) : key(logical_key), tag(identity)
    {}
    key_with_tag(const key_with_tag&) = default;
    key_with_tag(key_with_tag&& other) noexcept : key(other.key), tag(other.tag)
    {
        other.tag = -1;
    }
};
struct key_hash {
    std::size_t operator()(const key_with_tag& key) const noexcept
    {
        return static_cast<unsigned>(key.key) % 4;
    }
};
struct key_equal {
    bool operator()(const key_with_tag& left, const key_with_tag& right) const noexcept
    {
        return left.key == right.key;
    }
};

using hashed_allocator =
    counting_allocator<asc::std::pair<const key_with_tag, int>>;  // NOLINT(build/include_what_you_use)
using hashed_map = asc::std::unordered_map<key_with_tag, int, key_hash, key_equal, hashed_allocator>;
using unordered_entry = hashed_map::value_type;
using hashed_set = asc::std::unordered_set<key_with_tag, key_hash, key_equal, counting_allocator<key_with_tag>>;

bool check_hashed_containers()
{
    allocation_counts set_counts, map_counts, moved_counts;
    {
        hashed_set actual_set{counting_allocator<key_with_tag>(set_counts)};
        hashed_map actual_map{hashed_allocator(map_counts)};
        const auto start_buckets = actual_set.bucket_count();
        const auto set_first = actual_set.insert(key_with_tag{0, 51}).first;
        const auto map_first = actual_map.insert(unordered_entry(key_with_tag{0, 61}, 15)).first;
        const auto* key_address = &*set_first;
        const auto* value_address = &*map_first;
        for (int i = 1; i <= 97; ++i) {
            if (!actual_set.insert(key_with_tag{i, i + 100}).second ||
                !actual_map.insert(unordered_entry(key_with_tag{i, i + 200}, i * 7)).second)
                return false;
        }
        const auto rehashed_key = actual_set.find(key_with_tag{0, 0});
        const auto rehashed_value = actual_map.find(key_with_tag{0, 0});
        if (rehashed_key == actual_set.end() || rehashed_value == actual_map.end() ||
            actual_set.bucket_count() <= start_buckets || actual_map.bucket_count() <= start_buckets ||
            actual_set.size() != 98 || actual_map.size() != 98 || &*rehashed_key != key_address ||
            &*rehashed_value != value_address)
            return false;

        for (int i = 0; i <= 97; ++i) {
            key_with_tag duplicate(i, 500);
            const auto existing = actual_set.insert(std::move(duplicate));
            const auto mapped = actual_map.find(key_with_tag{i, -12});
            if (existing.second || duplicate.tag != 500 || mapped == actual_map.end() ||
                existing.first->tag != (i == 0 ? 51 : i + 100) || mapped->first.tag != (i == 0 ? 61 : i + 200) ||
                mapped->second != (i == 0 ? 15 : 7 * i))
                return false;
        }
        if (actual_set.count(key_with_tag{98, 0}) != 0 || actual_map.count(key_with_tag{-1, 0}) != 0)
            return false;

        hashed_map moved{hashed_allocator(moved_counts)};
        moved[key_with_tag{-1, 1}] = 9;
        moved = std::move(actual_map);
        const auto moved_value = moved.find(key_with_tag{0, 0});
        if (moved_value == moved.end() || !actual_map.empty() || moved_counts.outstanding() != 0 ||
            &*moved_value != value_address || moved[key_with_tag{97, 0}] != 679)
            return false;
        const auto allocations = map_counts.allocated;
        const auto buckets = moved.bucket_count();
        moved.clear();
        actual_set.clear();
        if (!moved.empty() || !actual_set.empty() || moved.begin() != moved.end() ||
            actual_set.begin() != actual_set.end() || moved.bucket_count() != buckets)
            return false;
        moved[key_with_tag{15, 70}] = 3;
        if (moved.size() != 1 || moved[key_with_tag{15, 0}] != 3 || map_counts.allocated != allocations + 1)
            return false;
    }
    return set_counts.outstanding() == 0 && map_counts.outstanding() == 0 && moved_counts.outstanding() == 0;
}

}  // namespace

int main()
{
    if (!check_ordered_containers(false, 0) || !check_ordered_containers(true, 17)) {
        std::cerr << "Ordered container content or ownership mismatch\n";
        return 1;
    }
    if (!check_hashed_containers()) {
        std::cerr << "Collision, rehash or allocator lifetime mismatch\n";
        return 2;
    }
    return 0;
}
