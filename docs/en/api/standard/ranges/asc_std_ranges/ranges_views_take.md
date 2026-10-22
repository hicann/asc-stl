# asc::std::ranges::views::take

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

`asc::std::ranges::views::take` presents only the specified number of leading elements of an input range.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

This public name is a constant callable object, not a free function; its implementation class is not part of the public contract. The following only queries the object type, where object_type is an example name. For the call forms, see Parameters and Example.

```cpp
using object_type = decltype(asc::std::ranges::views::take);
```

## Parameters

### Parameters of Call Form 1

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `range` | Input | The input range to be accessed or transformed; the borrowed result is constrained by its lifetime. |
| `count` | Input | The number of elements to process, keep, or skip. |

### Parameters of Call Form 2

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `count` | Input | The number of elements to process, keep, or skip. |

## Return Value

empty_view returns the original empty view type directly. Random-access and sized span, basic_string_view, and applicable subrange use pass-through reconstruction; a span result may have dynamic extent; iota_view is rebuilt from its start and truncated end, and the Bound type may change. repeat_view adjusts the count. Other inputs return take_view<views::all_t<Range>>.

The exact result type can be queried on the corresponding input type with `decltype(asc::std::ranges::views::take(input, count))`; it cannot be uniformly written as a single wrapping view type.

## Constraints

- The input and return objects must satisfy the range, iterator, and construction conditions of the selected branch; the return type is selected according to the conditions above.
- The count must be non-negative and representable by the range's difference type; bounded ranges are truncated to the actual length, and elements past the end are not accessed.
- The view keeps the ownership mode of the original range, and the borrowed element storage must cover the actual access period.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>
#include <asc/std/span>
#include <asc/std/type_traits>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::span<int> base(values);
    auto result = asc::std::ranges::views::take(base, 2);
    static_assert(asc::std::is_same_v<decltype(result), asc::std::span<int>>);
    return result.size() == 2 && result[0] == 1;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
