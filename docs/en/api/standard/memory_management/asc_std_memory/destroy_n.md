# asc::std::destroy_n

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

`asc::std::destroy_n` ends the lifetime of the specified number of objects starting from the given position.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<class ForwardIterator, class Size> constexpr ForwardIterator destroy_n(ForwardIterator first, Size count);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | The iterator type used to traverse the input range; must satisfy the traversal capabilities required by the prototype. |
| `Size` | The type or compile-time value representing an element count, dimension, bit width, or index, as determined by the declaration. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The start iterator or pointer of the input range. |
| `count` | Input | The number of elements participating in the operation. |

## Return Value

| Return type | Description |
| --- | --- |
| `ForwardIterator` | Returns the position past the range of destroyed objects. |

## Constraints

- The storage is provided by the caller and satisfies the alignment requirements.
- When a rollback would throw, the related operations on the device side must not throw.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>

bool example()
{
    alignas(int) unsigned char storage[sizeof(int) * 2];
    int* output = reinterpret_cast<int*>(storage);
    asc::std::uninitialized_fill_n(output, 2, 7);
    const auto end = asc::std::destroy_n(output, 2);
    return end == output + 2;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
