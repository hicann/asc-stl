# asc::std::ranges::repeat_view::iterator::`operator++`

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

`repeat_view::iterator::operator++`: postfix increment, returning a copy made before the increment.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

The owning iterator type is obtained through `decltype(view.begin())`; the declaration summary below uses iterator and difference_type in its in-class context. Those marked friend are hidden friends, invoked with operator expressions.

### Prototype 1

```cpp
constexpr iterator& operator++();
```

### Prototype 2

```cpp
constexpr iterator operator++(int);
```

## Parameters

### Parameters of Prototype 1

No function parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `postfix marker` | Input | An int placeholder argument, used only to distinguish the postfix form and not indicating a movement distance. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `iterator&` | Prefix increment; advances one position in place and returns a reference to itself. |
| Prototype 2 | `iterator` | Postfix increment; advances one position in place and returns a copy of the iterator made before the update. |

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
    auto position = first;
    const auto previous = position++;
    auto& same = ++position;
    return previous == first && position - first == 2 && &same == &position && *position == 7;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
