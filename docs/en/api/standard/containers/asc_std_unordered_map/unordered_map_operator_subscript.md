# asc::std::unordered_map::`operator[]`

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

`asc::std::unordered_map::operator[]` looks up the mapped value by key: if the key already exists, it returns a reference to the corresponding mapped value; if the key does not exist, it inserts into the container an element consisting of that key and a default-constructed mapped value, and returns a reference to the newly inserted element's mapped value.

Insertion requires the mapped value type to be default-constructible and the container capacity to be sufficient; if the insertion fails or construction throws, the container contents remain unchanged.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `unordered_map`](https://en.cppreference.com/w/cpp/header/unordered_map).

## Function Prototype

Member of: [`asc::std::unordered_map`](unordered_map.md).

```cpp
// Excerpt of the declaration inside class asc::std::unordered_map; template parameters and other members are provided by the owning class.
T& operator[](const Key& key);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `key` | Input | Provides a reference to the object used to "look up the mapped value by key and insert an element when the key does not exist"; the referenced object must remain valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `T &` | Returns a reference to the corresponding mapped value if the key already exists; returns a reference to the newly inserted element's mapped value if the key does not exist. |

## Constraints

- In Host and AI Core SIMT programming, unordered_map<Key,T,Hash,Equal,A> requires an explicit GM arena.
- empty/size/bucket_count/begin/end/insert/find/count/`operator[]`/clear.
- The allocator rebinds for the bucket array and automatically rehashes at the default load-factor threshold.
- Collision chains, duplicate-key rejection, stable node addresses across rehash, old iterators remaining valid after move, and destruction.
- Only in domains with sufficient capacity and no exceptions thrown.
- Host and AI Core SIMT programming.
- This operation uses the container's selected `Hash` and `Equal` to locate the key; equivalent keys must produce the same hash, and the key-related state must remain valid. For the requirements on custom keys, ignored fields, and the object-bytes fallback, see the [unordered_map constraints](unordered_map.md).

## Example

The following Host snippet uses an explicitly provided allocator; on the device side, an allocator callable at the target execution location must be used.

```cpp
#include <asc/std/unordered_map>
#include <functional>
#include <memory>
#include <string>
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

decltype(auto) example(asc::std::unordered_map<int, int, ::std::hash<int>, ::std::equal_to<int>, example_allocator<::std::pair<const int, int>>>& values)
{
    return values[7];
}
```

## Related APIs

- [`asc::std::unordered_map`](unordered_map.md)
- [API list for this header](asc_std_unordered_map.md)
