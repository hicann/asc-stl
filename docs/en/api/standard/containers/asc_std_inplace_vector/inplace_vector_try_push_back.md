# asc::std::inplace_vector::try_push_back

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

Header: `<asc/std/inplace_vector>`.

`asc::std::inplace_vector::try_push_back` attempts to append `value` to the end of the container. When capacity is sufficient it constructs the new element and returns a reference to it; when the container is full it returns an empty result and the container contents remain unchanged.

This interface supports both Host and the device side, both limited to the non-throwing operations listed on this page.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Function Prototype

Member of: [`inplace_vector<T, Capacity>`](inplace_vector.md). The following is the in-class declaration; type aliases and template parameters are provided by the owning class.

### Prototype 1

```cpp
constexpr optional<reference> try_push_back(const T& value);
```

### Prototype 2

```cpp
constexpr optional<reference> try_push_back(T&& value);
```

## Parameters

### Parameters of Prototype 1

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value used to copy-construct the new element at the end. |

### Parameters of Prototype 2

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value used to move-construct the new element at the end; the source may be consumed during construction. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `optional<reference>` | Borrows the new element when capacity is available; empty when capacity is full, without constructing or consuming the source. |
| Prototype 2 | `optional<reference>` | Borrows the new element when capacity is available; empty when capacity is full, without constructing or consuming the source. |

## Constraints

- Returns an empty optional when capacity is insufficient, without constructing a new element; returns an optional<T&> borrowing the new element when capacity is available.
- The element borrowed by a non-empty result must remain alive; the element construction requirements must still be satisfied.
- The corresponding construction, assignment, and destruction of elements must satisfy the non-throwing usage domain; the constexpr declaration does not guarantee constant evaluation for every T and language mode.

## Example

The following example shows both outcomes, successful insertion and exhausted capacity, and checks the container's final state.

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 2> values;
    const auto first = values.try_push_back(7);
    const auto second = values.try_push_back(9);
    const auto overflow = values.try_push_back(11);

    // The first two insertions succeed; once the fixed capacity is reached, the third insertion returns an empty result.
    return first.has_value() && *first == 7
        && second.has_value() && *second == 9
        && !overflow.has_value()
        && values.size() == 2;
}
```

## Related APIs

- [`asc::std::inplace_vector`](inplace_vector.md)
- [API list for this header](asc_std_inplace_vector.md)
