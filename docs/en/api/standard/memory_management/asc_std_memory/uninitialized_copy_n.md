# asc::std::uninitialized_copy_n

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

`asc::std::uninitialized_copy_n` performs, on the specified number of objects in uninitialized storage, the construction, copy, or move operation named by the interface.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<class InputIterator, class Size, class ForwardIterator> ForwardIterator uninitialized_copy_n(InputIterator first, Size count, ForwardIterator result);
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
| `ForwardIterator` | Returns the position past the last fully constructed object; on construction failure, handled according to the exception constraints on this page. |

## Constraints

- The storage is provided by the caller and satisfies the alignment requirements.
- When a rollback would throw, the related operations on the device side must not throw.

## Example

The following Host snippet completes construction, result verification, and destruction inside the function, and does not return pointers to local storage out of the function.

```cpp
#include <asc/std/memory>

bool copy_elements()
{
    alignas(int) unsigned char storage[sizeof(int) * 4];
    int* output = reinterpret_cast<int*>(storage);
    const int input[4] = {1, 2, 3, 4};

    // Control construction by element count; the return value is the position past the last fully constructed object
    int* result = asc::std::uninitialized_copy_n(input, 4, output);
    bool ok = result == output + 4;
    for (int i = 0; i < 4; ++i) {
        ok = ok && output[i] == input[i];
    }
    asc::std::destroy_n(output, 4);  // 4 objects were constructed, so destroy 4
    return ok;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
