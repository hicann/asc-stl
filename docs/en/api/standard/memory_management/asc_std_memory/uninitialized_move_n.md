# asc::std::uninitialized_move_n

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

`asc::std::uninitialized_move_n` moves at most `count` objects starting from `first`, constructs objects one by one in the uninitialized storage starting at `result`, and returns the respective ends of the input and output. A non-positive count constructs no objects.

## Function Prototype

```cpp
namespace asc::std {
template<class InputIterator, class Size, class ForwardIterator> pair<InputIterator, ForwardIterator> uninitialized_move_n(InputIterator first, Size count, ForwardIterator result);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type used to read the input range's elements; must satisfy the traversal capabilities required by the prototype. |
| `Size` | The type or compile-time value representing an element count, dimension, bit width, or index, as determined by the declaration. |
| `ForwardIterator` | The iterator type used to traverse the input range; must satisfy the traversal capabilities required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The start iterator or pointer of the input range. |
| `count` | Input | The number of elements participating in the operation. |
| `result` | Output | The iterator pointing to the position of this operation; the pointed-to range must be valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `pair<InputIterator, ForwardIterator>` | The `first` member is the input iterator after the move completes, and the `second` member is the past-the-end iterator of the constructed output range; the two belong to the input and output ranges respectively. |

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
    int input[4] = {1, 2, 3, 4};
    const auto ends = asc::std::uninitialized_move_n(input, 4, output);
    const bool valid = ends.first == input + 4 && ends.second == output + 4
        && output[0] == 1 && output[3] == 4;
    asc::std::destroy_n(output, 4);
    return valid;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
