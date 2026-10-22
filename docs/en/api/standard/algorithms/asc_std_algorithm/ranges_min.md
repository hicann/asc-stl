# asc::std::ranges::min

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

`asc::std::ranges::min` supports two values or an input range with an optional comparator and projection, available since C++17; the two-value call returns a constant reference to the selected object, and the range call returns the value of the minimum element.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Declaration

This name is a public constant function object; the object's implementation type is not part of the interface commitment. The following are the call forms; omitted optional parameters are governed by the constraints of each prototype.

```cpp
namespace asc::std::ranges {
min(left, right, compare, projection);
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
min(range, compare, projection);
}  // namespace asc::std::ranges
```

## Parameters

### Parameters of Call Form 1

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | First value participating in the comparison. |
| `right` | Input | Second value participating in the comparison. |
| `compare` | Input | Comparison object that determines the order of elements. |
| `projection` | Input | Projection function applied to elements before comparison or evaluation; when omitted, `asc::std::identity` is used. |

### Parameters of Call Form 2

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `range` | Input | Input range to be traversed or transformed; borrowed results are constrained by its lifetime. |
| `compare` | Input | Comparison object that determines the order of elements. |
| `projection` | Input | Projection function applied to elements before comparison or evaluation; when omitted, `asc::std::identity` is used. |

## Return Value

The two-value call returns a constant reference to the smaller value, whose validity is constrained by the arguments; the range call returns the minimum element by value.

| Call form | Return type |
| --- | --- |
| Two values | `const T&` |
| Range | `range_value_t<Range>` |

## Constraints

- When compare is omitted, `asc::std::ranges::less` is used; when projection is omitted, `asc::std::identity` is used.

- The range call requires a non-empty range and copyable elements.
- No initializer-list overload is provided in this release.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4};
    return asc::std::ranges::min(values[0], values[1]) == 1 && asc::std::ranges::min(values) == 1;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
