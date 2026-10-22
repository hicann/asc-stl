# asc::std::binary_search

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

`asc::std::binary_search` determines whether an element equivalent to the target exists in a sorted range; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class T, class Compare>
[[nodiscard]] constexpr bool binary_search(
    ForwardIterator first, ForwardIterator last, const T& value, Compare compare);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class ForwardIterator, class T>
[[nodiscard]] constexpr bool binary_search(ForwardIterator first, ForwardIterator last, const T& value);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `T` | Type of the value to find; must be usable as an argument of compare for comparison with the elements. |
| `Compare` | Comparator type; invoked in the form compare(a, b), returns bool and must satisfy strict weak ordering. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the sorted input range. |
| `last` | Input | End position of the sorted input range, not included. |
| `value` | Input | The value to find; determines whether an element equivalent to this value exists in the range. |
| `compare` | Input | Comparator; invoked in the form compare(a, b), returns bool, where true means a is ordered before b; must satisfy strict weak ordering and be consistent with the ordering rule of the range. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `T` | Type of the input range elements or of the values participating in the operation. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the sorted input range. |
| `last` | Input | End position of the sorted input range, not included. |
| `value` | Input | The value to find; determines whether an element equivalent to this value exists in the range. |

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

decltype(auto) example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    return asc::std::binary_search(values, values + 8, 5);
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
