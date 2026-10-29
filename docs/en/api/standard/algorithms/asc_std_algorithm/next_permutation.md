# asc::std::next_permutation

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

`asc::std::next_permutation` rearranges the range into the next permutation in lexicographic order; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class BidirectionalIterator, class Compare>
constexpr bool next_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare compare);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class BidirectionalIterator>
constexpr bool next_permutation(BidirectionalIterator first, BidirectionalIterator last);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `BidirectionalIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Compare` | Comparison object type that defines the ordering of the elements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, not included. |
| `compare` | Input | Comparison object used to determine the ordering of the elements. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `BidirectionalIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, not included. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `bool` | Returns `true` when the condition holds, `false` otherwise. |
| Prototype 2 | `bool` | Returns `true` when the condition holds, `false` otherwise. |

## Constraints

- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer with sufficient capacity.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    const bool advanced = asc::std::next_permutation(values, values + 4);
    const int expected[4] = {1, 2, 4, 3};
    if (advanced != true) return false;
    for (int index = 0; index < 4; ++index) { if (values[index] != expected[index]) return false; }
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
