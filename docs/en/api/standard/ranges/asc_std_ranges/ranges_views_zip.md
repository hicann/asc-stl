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

- This release supports exactly two random-access, sized ranges on Host and in device SIMD and SIMT programming.
- Traversal capability follows the modern `iterator_concept`. A value-returning `transform_view` can retain random-access traversal and participate in zip even when its legacy `iterator_category` is an input-iterator tag.
- Each tuple element preserves the corresponding underlying dereference type: references permit write-back to writable elements, while value-returning transformations produce stored values. Borrowed storage must remain valid throughout access.
- Iterators support default construction and composition with constrained `ranges` algorithms. The caller still provides output storage; zip does not allocate an output buffer.
- Const iteration requires both sides to be const-iterable with iterator types identical to their non-const forms.

## Example

This Host example calibrates candidate scores: lazily scale each score, pair it with its correction, and write calibrated scores for subsequent threshold filtering. Unequal lengths stop at the shorter input, without reading absent corrections or overwriting the output tail.

```cpp
#include <asc/std/ranges>
#include <asc/std/algorithm>
#include <asc/std/tuple>

bool example()
{
    int scores[] = {1, 6, -4, 3, 8};
    int correction[] = {0, -2, 7, 0};
    int calibrated[5] = {-99, -99, -99, -99, -99};
    auto scaled = scores | asc::std::ranges::views::transform([](int value) { return value * 2; });
    auto paired = asc::std::ranges::views::zip(scaled, correction);
    auto result = asc::std::ranges::transform(paired, calibrated, [](auto values) {
        return asc::std::get<0>(values) + asc::std::get<1>(values);
    });
    return result.out == calibrated + 4 && calibrated[0] == 2 && calibrated[1] == 10 &&
        calibrated[2] == -1 && calibrated[3] == 6 && calibrated[4] == -99;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
