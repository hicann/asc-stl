# asc::std::unordered_map::insert

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

`asc::std::unordered_map::insert` inserts an element at the specified position and updates iterators according to the container's rules.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `unordered_map`](https://en.cppreference.com/w/cpp/header/unordered_map).

## Function Prototype

Member of: [`asc::std::unordered_map`](unordered_map.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::unordered_map; template parameters and other members are provided by the owning class.
pair<iterator, bool> insert(const value_type& value);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::unordered_map; template parameters and other members are provided by the owning class.
pair<iterator, bool> insert(value_type&& value);
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The key-value pair to be inserted (using the container's own value_type, with first as the key and second as the value member); the target bucket is located by the key's hash value, a new element is copy-constructed when the key does not exist, and nothing is inserted when the key already exists. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The key-value pair to be inserted; the target bucket is located by the key's hash value, a new element is constructed by moving when the key does not exist, and when the key already exists nothing is inserted and the source object is not consumed. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `pair<iterator, bool>` | Returns the insertion position and whether a new element was added; the concrete result form is determined by the selected prototype. |
| Prototype 2 | `pair<iterator, bool>` | Returns the insertion position and whether a new element was added; the concrete result form is determined by the selected prototype. |

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
    using entry_type = asc::std::unordered_map<int, int, ::std::hash<int>, ::std::equal_to<int>, example_allocator<::std::pair<const int, int>>>::value_type;
    entry_type entry(7, 9);
    return values.insert(entry);
}
```

## Related APIs

- [`asc::std::unordered_map`](unordered_map.md)
- [API list for this header](asc_std_unordered_map.md)
