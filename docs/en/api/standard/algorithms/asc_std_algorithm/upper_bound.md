# asc::std::upper_bound

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

`asc::std::upper_bound` finds the first position in a sorted range that is greater than the target; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class T, class Compare>
[[nodiscard]] constexpr ForwardIterator upper_bound(
    ForwardIterator first, ForwardIterator last, const T& value, Compare comp);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class ForwardIterator, class T>
[[nodiscard]] constexpr ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `T` | Type of the boundary value to be searched for; must be usable as an argument of comp for comparison with elements. |
| `Compare` | Comparator type; invoked in the form comp(value, elem), returning bool and satisfying strict weak ordering. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the sorted input range. |
| `last` | Input | End position of the sorted input range, exclusive. |
| `value` | Input | Boundary value to be searched for; finds the position of the first element satisfying comp(value, elem). |
| `comp` | Input | Comparator invoked in the form comp(value, elem) returning bool, where true means value is ordered before elem; it must satisfy strict weak ordering and be consistent with the range's sorting rule. |

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
| `last` | Input | End position of the sorted input range, exclusive. |
| `value` | Input | Boundary value to be searched for; finds the position of the first element greater than this value. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `ForwardIterator` | Returns the position of the element satisfying the condition; returns the end position of the input range when none is found. |
| Prototype 2 | `ForwardIterator` | Returns the position of the element satisfying the condition; returns the end position of the input range when none is found. |

## Constraints

- Provides overloads that execute sequentially and perform no dynamic memory allocation.

- Accepts ordinary iterators and Device GM/UB object pointers; the returned iterator or pointer preserves the input address space.
- Device raw-pointer ranges of at most `2147483647` elements use a converging 32-bit index loop without scalar bit-count builtins. Larger ranges and non-pointer iterators use the generic implementation, with unchanged public types and comparison rules.

## Example

The following Host example checks the result and the output while the local ranges are still valid; the function returns a boolean value that can be checked independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto result = asc::std::upper_bound(values, values + 8, 5);
    return result == values + 5;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
