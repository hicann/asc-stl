# asc::std::ranges::min_element

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

`asc::std::ranges::min_element` supports an iterator and a sentinel or a forward range with an optional comparator and projection, available since C++17; it returns the position of the minimum element, and the end position for an empty range. Non-borrowed temporary ranges return `dangling`.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Declaration

This name is a public constant function object; the object's implementation type is not part of the interface commitment. The following are the call forms; omitted optional parameters are governed by the constraints of each prototype.

```cpp
namespace asc::std::ranges {
min_element(first, last, compare, projection);
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
min_element(range, compare, projection);
}  // namespace asc::std::ranges
```

## Parameters

### Parameters of Call Form 1

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator to the start of the input range. |
| `last` | Input | Sentinel for the end of the input range. |
| `compare` | Input | Comparison object that determines the order of elements. |
| `projection` | Input | Projection function applied to elements before comparison or evaluation; when omitted, `asc::std::identity` is used. |

### Parameters of Call Form 2

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `range` | Input | Input range to be traversed or transformed; borrowed results are constrained by its lifetime. |
| `compare` | Input | Comparison object that determines the order of elements. |
| `projection` | Input | Projection function applied to elements before comparison or evaluation; when omitted, `asc::std::identity` is used. |

## Return Value

Returns the position of the minimum element; returns the end position for an empty range. The range overload returns `dangling` for non-borrowed temporary ranges.

| Call form | Return type |
| --- | --- |
| Iterator and sentinel | `Iterator` |
| Range | `borrowed_iterator_t<Range>` |

## Constraints

- When compare is omitted, `asc::std::ranges::less` is used; when projection is omitted, `asc::std::identity` is used.

- The comparator must be able to compare projected elements.
- The input must satisfy the forward traversal requirements.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4};
    return asc::std::ranges::min_element(values, values + 4) == values &&
        asc::std::ranges::min_element(values) == values;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
