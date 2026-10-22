# asc::std::ranges::views::common

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

`asc::std::ranges::views::common` makes a range use the same type for its iterator and end position.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

This public name is a constant callable object, not a free function; its implementation class is not part of the public contract. The following only queries the object type, where object_type is an example name. For the call forms, see Parameters and Example.

```cpp
using object_type = decltype(asc::std::ranges::views::common);
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `range` | Input | The input range to be accessed or transformed; the borrowed result is constrained by its lifetime. |

## Return Value

When the input already satisfies common_range, the type of views::all(range) is returned directly; other inputs return common_view<views::all_t<Range>>, which unifies differing iterator/sentinel types into common_iterator.

The exact result type can be queried on the corresponding input type with `decltype(asc::std::ranges::views::common(input))`; it cannot be uniformly written as a single wrapping view type.

## Constraints

- The input and return objects must satisfy the range, iterator, and construction conditions of the selected branch; the return type is selected according to the conditions above.
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
    auto result = asc::std::ranges::views::common(base);
    static_assert(asc::std::is_same_v<decltype(result), decltype(base)>);
    return result.size() == 4 && result.data() == values;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
