# asc::std::uninitialized_fill

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

Header: `<asc/std/memory>`.

`asc::std::uninitialized_fill` constructs objects with the given value in an uninitialized storage range.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<class ForwardIterator, class T> void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | The iterator type pointing to the uninitialized target storage; must satisfy the traversal capabilities required by the prototype. |
| `T` | The type of object to construct in the storage, i.e. the type of value. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The start iterator or pointer of the target storage range; the pointed-to storage has no constructed objects yet. |
| `last` | Input | The end position of the target storage range, exclusive; the storage in the range has no constructed objects yet. |
| `value` | Input | The value to copy-construct at every position in the range. |

## Return Value

No return value.

## Constraints

- The storage is provided by the caller and satisfies the alignment requirements.
- When a rollback would throw, the related operations on the device side must not throw.

## Example

The following Host snippet uses valid objects or aligned storage; the constructed objects are destroyed at the end of the example.

```cpp
#include <asc/std/memory>

void example()
{
    alignas(int) unsigned char storage[sizeof(int) * 4];
    int* output = reinterpret_cast<int*>(storage);
    asc::std::uninitialized_fill(output, output + 4, 7);
    asc::std::destroy_n(output, 4);
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
