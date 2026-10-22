# asc::std::unordered_set::insert

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

Header: `<asc/std/unordered_set>`.

`asc::std::unordered_set::insert` inserts an element at the specified position and updates iterators according to the container's rules.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `unordered_set`](https://en.cppreference.com/w/cpp/header/unordered_set).

## Function Prototype

Member of: [`unordered_set`](unordered_set.md). The return type is summarized as auto in the signature: the actual result object has first of iterator type and second of bool type, and is not asc::std::pair.

### Prototype 1

```cpp
auto insert(const Key& key);
```

### Prototype 2

```cpp
auto insert(Key&& key);
```

## Parameters

### Parameters of Prototype 1

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `key` | Input | The key to be inserted; a new element is copy-constructed when the key does not exist, and nothing is inserted when it already exists. |

### Parameters of Prototype 2

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `key` | Input | The key to be inserted; a new element is move-constructed when the key does not exist and the source object may be moved; the source is not consumed when the key already exists. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `Result object with first/second` | first points to the element with the key, and second indicates whether it was newly inserted; for a duplicate key, second is false. first borrows the container and must not be used after the container or element is destroyed. |
| Prototype 2 | `Result object with first/second` | first points to the element with the key, and second indicates whether it was newly inserted; for a duplicate key, second is false. first borrows the container and must not be used after the container or element is destroyed. |

## Constraints

- In Host and AI Core SIMT programming, unordered_set<Key,Hash,Equal,A> requires an explicit GM arena.
- empty/size/bucket_count/begin/end/insert/find/count/clear.
- The allocator rebinds for the bucket array and automatically rehashes at the default load-factor threshold.
- Collision chains, duplicate-key rejection, stable node addresses across rehash, old iterators remaining valid after move, and destruction.
- Only in domains with sufficient capacity and no exceptions thrown.
- Host and AI Core SIMT programming.
- This operation uses the container's selected `Hash` and `Equal` to locate the key; equivalent keys must produce the same hash, and the key-related state must remain valid. For the requirements on custom keys, ignored fields, and the object-bytes fallback, see the [unordered_set constraints](unordered_set.md).

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/unordered_set>
#include <functional>
#include <memory>
#include <utility>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

bool example()
{
    using set_type = asc::std::unordered_set<int, ::std::hash<int>, ::std::equal_to<int>, example_allocator<int>>;
    set_type values{example_allocator<int>{}};
    const auto inserted = values.insert(7);
    const auto duplicate = values.insert(7);
    return inserted.second && !duplicate.second && *inserted.first == 7 && values.size() == 1;
}
```

## Related APIs

- [`asc::std::unordered_set`](unordered_set.md)
- [API list for this header](asc_std_unordered_set.md)
