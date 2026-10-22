# asc::std::map::`operator[]`

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

Header: `<asc/std/map>`.

`asc::std::map::operator[]` looks up the mapped value by key: if the key already exists, it returns a reference to the corresponding mapped value; if the key does not exist, it inserts into the container an element consisting of that key and a default-constructed mapped value, and returns a reference to the newly inserted element's mapped value.

Insertion requires the mapped value type to be default-constructible; if node allocation or element construction fails or throws, the container contents remain unchanged.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `map`](https://en.cppreference.com/w/cpp/header/map).

## Function Prototype

Member of: [`asc::std::map`](map.md).

```cpp
// Excerpt of the declaration inside class asc::std::map; template parameters and other members are provided by the owning class.
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

- In Host and AI Core SIMT programming, map<Key,T,Compare,A> requires an explicit GM arena.
- Construction with allocator, and with Compare+allocator.
- empty/size/begin/end/insert/find/count/`operator[]`/clear.
- AVL balancing with a logarithmic insertion/lookup core.
- Duplicate keys are rejected; ordered iteration, move, and destruction.
- Only in domains with sufficient capacity and non-throwing key/value, comparison, and allocator operations.
- Host and AI Core SIMT programming.

## Example

The following Host snippet uses an explicitly provided allocator; on the device side, an allocator callable at the target execution location must be used.

```cpp
#include <asc/std/map>
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

decltype(auto) example(asc::std::map<int, int, ::std::less<int>, example_allocator<::std::pair<const int, int>>>& values)
{
    return values[7];
}
```

## Related APIs

- [`asc::std::map`](map.md)
- [API list for this header](asc_std_map.md)
