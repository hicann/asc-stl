# asc::std::copy_backward

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

Header: `<asc/std/algorithm>`.

`asc::std::copy_backward` copies the range from the back toward the front, supporting ranges that overlap in the specified direction; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

```cpp
namespace asc::std {
template <class BidirectionalIterator1, class BidirectionalIterator2>
constexpr BidirectionalIterator2 copy_backward(
    BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result);
}  // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `BidirectionalIterator1` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `BidirectionalIterator2` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, not included. |
| `result` | Output | End (exclusive) of the output range; input elements are written in order before it, and there must be sufficient capacity ahead of it. |

## Return Value

| Return type | Description |
| --- | --- |
| `BidirectionalIterator2` | Returns the start position of the written portion of the output range. |

## Constraints

- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host example checks the result and output while the local range is still valid; the function returns a boolean value that can be evaluated independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[16] = {};
    auto result = asc::std::copy_backward(values, values + 8, output + 8);
    return result == output && output[0] == 1 && output[7] == 8;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
