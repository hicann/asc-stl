# asc::std::uninitialized_fill_n

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

`asc::std::uninitialized_fill_n` performs, on the specified number of objects in uninitialized storage, the construction, copy, or move operation named by the interface.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<class ForwardIterator, class Size, class T> ForwardIterator uninitialized_fill_n(ForwardIterator first, Size count, const T& value);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | The iterator type pointing to the uninitialized target storage; must satisfy the traversal capabilities required by the prototype. |
| `Size` | The type representing the number of objects to construct, usually an integer type or an iterator difference type. |
| `T` | The type of object to construct in the storage, i.e. the type of value. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The start iterator or pointer of the target storage range; the pointed-to storage has no constructed objects yet. |
| `count` | Input | The number of objects starting from first to construct with value. |
| `value` | Input | The value to copy-construct at every position. |

## Return Value

| Return type | Description |
| --- | --- |
| `ForwardIterator` | Returns the position past the last fully constructed object; on construction failure, handled according to the exception constraints on this page. |

## Constraints

- The storage is provided by the caller and satisfies the alignment requirements.
- When a rollback would throw, the related operations on the device side must not throw.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>

bool example()
{
    alignas(int) unsigned char storage[sizeof(int) * 4];
    int* output = reinterpret_cast<int*>(storage);
    const auto end = asc::std::uninitialized_fill_n(output, 4, 7);
    const bool valid = end == output + 4 && output[0] == 7 && output[3] == 7;
    asc::std::destroy_n(output, 4);
    return valid;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
