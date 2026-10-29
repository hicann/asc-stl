# asc::std::unordered_set::count

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

`asc::std::unordered_set::count` returns the number of elements matching the key or target value.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `unordered_set`](https://en.cppreference.com/w/cpp/header/unordered_set).

## Function Prototype

Member of: [`asc::std::unordered_set`](unordered_set.md).

```cpp
// Excerpt of the declaration inside class asc::std::unordered_set; template parameters and other members are provided by the owning class.
size_type count(const Key& key) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `key` | Input | Provides a reference to the object used to "count the number of elements matching the key or target value"; the referenced object must remain valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `size_type` | Returns the number of elements matching the key or target value. |

## Constraints

- In Host and AI Core SIMT programming, unordered_set<Key,Hash,Equal,A> requires an explicit GM arena.
- empty/size/bucket_count/begin/end/insert/find/count/clear.
- The allocator rebinds for the bucket array and automatically rehashes at the default load-factor threshold.
- Collision chains, duplicate-key rejection, stable node addresses across rehash, old iterators remaining valid after move, and destruction.
- Only in domains with sufficient capacity and no exceptions thrown.
- Host and AI Core SIMT programming.
- This operation uses the container's selected `Hash` and `Equal` to locate the key; equivalent keys must produce the same hash, and the key-related state must remain valid. For the requirements on custom keys, ignored fields, and the object-bytes fallback, see the [unordered_set constraints](unordered_set.md).

## Example

The following Host snippet uses an explicitly provided allocator; on the device side, an allocator callable at the target execution location must be used.

```cpp
#include <asc/std/unordered_set>
#include <memory>
#include <functional>
#include <utility>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U>
    struct rebind {
        using other = example_allocator<U>;
    };
    example_allocator() = default;
    template <class U>
    example_allocator(const example_allocator<U>&) noexcept
    {}
};

bool example()
{
    using sequence = asc::std::unordered_set<int, ::std::hash<int>, ::std::equal_to<int>, example_allocator<int>>;
    sequence values(example_allocator<int>{});
    values.insert(7);
    return values.count(7) == 1 && values.count(8) == 0;
}
```

## Related APIs

- [`asc::std::unordered_set`](unordered_set.md)
- [API list for this header](asc_std_unordered_set.md)
