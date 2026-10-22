# asc::std::ranges::rbegin

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

Header: `<asc/std/ranges>`.

`asc::std::ranges::rbegin` obtains the reverse starting iterator of the range.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

This name is a public constant function object; the object's implementation type does not constitute an interface commitment. The following is the call form; omitted optional parameters are governed by the constraints of each prototype.

```cpp
namespace asc::std::ranges {
rbegin(range);
} // namespace asc::std::ranges
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `range` | Input | The input range to be accessed or transformed; borrowed results are bound by its lifetime. |

## Return Value

Returns the starting iterator of the input range; the validity of the resulting iterator is bound by the input range.

| Call form | Return type |
| --- | --- |
| Range | Result type of member `rbegin()`, or `reverse_iterator<decltype(ranges::end(range))>` |

## Constraints

- Supports arrays and user-defined ranges; does not support initializer_list expressions formed only of braces.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto result = asc::std::ranges::rbegin(values);
    return *result == 4;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
