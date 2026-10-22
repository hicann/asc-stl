# asc::std::ranges::views::zip

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

`asc::std::ranges::views::zip` pairs exactly two sized random-access ranges by position, and the resulting view ends when the shorter input range ends.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

This name is a public constant function object; the implementation type of the object does not constitute an interface commitment. The following is the call form; omitted optional arguments follow the constraints of the prototypes.

```cpp
// Excerpt of the declaration inside asc::std::ranges::views; template parameters and other members are provided by the enclosing class.
zip(first_range, second_range);
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first_range` | Input | The first input range to be combined. |
| `second_range` | Input | The second input range to be combined. |

## Return Value

Returns a view that traverses the two input ranges in lockstep, with the length determined by the shorter input range.

| Call form | Return type |
| --- | --- |
| Two ranges | `zip_view<decltype(views::all(first_range)), decltype(views::all(second_range))>` |

## Constraints

- Seven names are listed.
- Bounded repeat, two-way random-access+sized zip reference write-back, single range|closure.
- Host, AI Core SIMD programming, and AI Core SIMT programming.
- This release supports only two ranges with random-access capability and determinable size.
- References of the resulting view must not outlive either input range.

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
    auto view = asc::std::ranges::views::zip(values, values);
    return asc::std::get<0>(*view.begin()) == 1;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
