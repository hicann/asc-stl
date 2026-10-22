# asc::std::ranges::repeat_view::iterator::`operator-`

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

`repeat_view::iterator::operator-`: subtraction of an iterator and a difference.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

The owning iterator type is obtained through `decltype(view.begin())`; the declaration summary below uses iterator and difference_type in its in-class context. Those marked friend are hidden friends, invoked with operator expressions.

### Prototype 1

```cpp
friend constexpr iterator operator-(iterator iter, difference_type value);
```

### Prototype 2

```cpp
friend constexpr difference_type operator-(iterator left, iterator right);
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `iter` | Input | The source iterator. |
| `value` | Input | The signed position distance; a negative value means moving forward. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left iterator in the same repetition sequence. |
| `right` | Input | The right iterator in the same repetition sequence. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `iterator` | Returns a new iterator offset backward by value. |
| Prototype 2 | `difference_type` | Returns the signed distance of the left position minus the right position. |

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
    const auto result = (first + 3) - 1;
    return result - first == 2 && *result == 7;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
