# asc::std::set::insert

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

Header: `<asc/std/set>`.

`asc::std::set::insert` inserts an element at the specified position and updates iterators according to the container's rules.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `set`](https://en.cppreference.com/w/cpp/header/set).

## Function Prototype

Member of: [`asc::std::set`](set.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::set; template parameters and other members are provided by the owning class.
pair<iterator, bool> insert(Key&& key);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::set; template parameters and other members are provided by the owning class.
pair<iterator, bool> insert(const Key& key);
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `key` | Input/Output | Provides a reference to the object used by "inserting an element at the specified position and updating iterators according to the container's rules"; the referenced object must be valid for the duration of the call. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `key` | Input | Provides a reference to the object used by "inserting an element at the specified position and updating iterators according to the container's rules"; the referenced object must be valid for the duration of the call. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `pair<iterator, bool>` | Returns the insertion position and whether a new element was added; the exact result form is determined by the selected prototype. |
| Prototype 2 | `pair<iterator, bool>` | Returns the insertion position and whether a new element was added; the exact result form is determined by the selected prototype. |

## Constraints

- In Host and AI Core SIMT programming, set<Key,Compare,A> uses an explicit GM arena.
- Construction from an allocator and from Compare+allocator.
- empty/size/begin/end/insert/find/count/clear.
- AVL balancing with a logarithmic-time insertion/lookup core.
- Duplicate-key rejection, ordered iteration, move, and destruction.
- Only the domain where capacity is sufficient and keys/comparators/allocators do not throw.
- Host and AI Core SIMT programming.

## Example

The following Host snippet uses an explicitly provided allocator; on the device side, an allocator callable at the target execution location must be used.

```cpp
#include <asc/std/set>
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
    using sequence = asc::std::set<int, ::std::less<int>, example_allocator<int>>;
    sequence values(example_allocator<int>{});
    values.insert(7);
    return values.size() == 1 && values.count(7) == 1 && *values.find(7) == 7;
}
```

## Related APIs

- [`asc::std::set`](set.md)
- [API list for this header](asc_std_set.md)
