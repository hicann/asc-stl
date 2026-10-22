# asc::std::ranges::repeat_view::iterator::`operator>`

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

`repeat_view::iterator::operator>`: greater-than comparison.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

The owning iterator type is obtained through `decltype(view.begin())`; the declaration summary below uses iterator and difference_type in its in-class context. Those marked friend are hidden friends, invoked with operator expressions.

### Prototype 1

```cpp
friend constexpr bool operator>(iterator left, iterator right);
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left iterator in the same sequence. |
| `right` | Input | The right iterator in the same sequence. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `bool` | Compares the positions stored in the two iterators; the result is bool, and the repeated values are not compared. |

## Constraints

- The iterators must be associated with the same repetition sequence; all arithmetic results must be representable by difference_type and the actual position type.
- The position of a bounded sequence must not move before 0; when accessing, it must also be before the end position. Decrement must not move past the start of the sequence.
- The iterator stores a pointer to the repeated value in the view; the view and the stored value must cover the iterator's period of use.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>

bool example()
{
    auto view = asc::std::ranges::views::repeat(7, 4);
    const auto first = view.begin();
    const auto second = first + 2;
    return second > first && !(first > second);
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
