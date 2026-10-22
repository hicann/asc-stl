# asc::std::unordered_map

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 series products: Not supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 series products: Not supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference series products AI Core: Not supported
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas inference series products Vector Core: Not supported
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas training series products: Not supported
<!-- end id7 -->

## Description

Header: `<asc/std/unordered_map>`.

`asc::std::unordered_map` organizes key-value pairs into hash buckets.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `unordered_map`](https://en.cppreference.com/w/cpp/header/unordered_map).

## Declaration

```cpp
namespace asc::std {
template<class Key, class T, class Hash, class Equal, class Allocator> class unordered_map;
} // namespace asc::std
```

## Constraints

- In Host and AI Core SIMT programming, unordered_map<Key,T,Hash,Equal,A> requires an explicit GM arena.
- empty/size/bucket_count/begin/end/insert/find/count/`operator[]`/clear.
- The allocator rebinds for the bucket array and automatically rehashes at the default load-factor threshold.
- Collision chains, duplicate-key rejection, stable node addresses across rehash, old iterators remaining valid after move, and destruction.
- Only in domains with sufficient capacity and no exceptions thrown.
- Host and AI Core SIMT programming.
- `Hash` and `Equal` must be default-constructible, copyable, and able to handle the corresponding keys at the call location; this container requires these calls not to throw. `Equal` must constitute an equivalence relation on keys, and whenever `Equal(a, b)` holds, `Hash(a)` and `Hash(b)` must be the same.
- Hash only the key values that participate in the equality test; if a key contains padding, cached fields ignored by the equality test, or non-trivial state, an appropriate `Hash` must be explicitly provided. For the conditions of the generic object-bytes fallback, see the [hash description](../../utilities/asc_std_bitset/hash.md).
- While a key is in the container, the content the selected `Hash` or `Equal` depends on must not be modified; different keys with the same hash value are further distinguished by `Equal`.

## Example

The following Host example uses two equal keys with the same `id` but different `cache`; the custom hash processes only the `id` that participates in the equality test.

```cpp
#include <asc/memory>
#include <asc/std/functional>
#include <asc/std/unordered_map>
#include <asc/std/utility>

struct example_key {
    int id;
    int cache;
    friend bool operator==(const example_key& left, const example_key& right) noexcept
    {
        return left.id == right.id;
    }
};

struct example_hash {
    asc::std::size_t operator()(const example_key& value) const noexcept
    {
        return asc::std::hash<int>{}(value.id);
    }
};

struct example_equal {
    bool operator()(const example_key& left, const example_key& right) const noexcept
    {
        return left == right;
    }
};

bool example()
{
    alignas(64) unsigned char storage[16384] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    const example_key first{7, 1};
    const example_key second{7, 99};
    const example_hash key_hash;
    using allocator = asc::arena_allocator<asc::std::pair<const example_key, int>>;
    using map_type = asc::std::unordered_map<example_key, int, example_hash, example_equal, allocator>;
    map_type values(allocator{arena});
    values[first] = 42;
    values[second] = 99;
    const auto found = values.find(second);
    return first == second && first.cache != second.cache && key_hash(first) == key_hash(second)
        && values.size() == 1 && found != values.end()
        && found->first.id == 7 && found->first.cache == first.cache && found->second == 99;
}
```

## Related APIs

- [API list for this header](asc_std_unordered_map.md)
