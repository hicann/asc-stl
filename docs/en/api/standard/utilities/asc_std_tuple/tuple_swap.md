# asc::std::tuple::swap

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

Header: `<asc/std/tuple>`.

`asc::std::tuple::swap` exchanges the states or elements stored by two objects.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

The following is an equivalent declaration summary inside class `tuple<Types...>`, expressing the exception condition with the public element traits; empty tuples use the same member.

```cpp
constexpr void swap(tuple& other) noexcept((is_nothrow_swappable_v<Types> && ...));
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The other tuple of the same type; swapped item by item, and the elements on both sides must satisfy the corresponding swap requirements. |

## Return Value

No return value.

## Constraints

- All corresponding elements must be swappable; the exception condition is the conjunction of the noexcept of each element's swap.

- The utility itself allocates no additional container storage; element construction, assignment, swapping, or passing into a callable body may still allocate or throw according to their own semantics, so the whole call is not guaranteed to be allocation-free on this basis.

## Example

The following Host example provides concrete inputs and checks the result while the objects are still valid.

```cpp
#include <asc/std/tuple>

bool example()
{
    asc::std::tuple<int, int> left(1, 2), right(3, 4);
    left.swap(right);
    return asc::std::get<0>(left) == 3 && asc::std::get<1>(right) == 2;
}
```

## Related APIs

- [`asc::std::tuple`](tuple.md)
- [API list for this header](asc_std_tuple.md)
