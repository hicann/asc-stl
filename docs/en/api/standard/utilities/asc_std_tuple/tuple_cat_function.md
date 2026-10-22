# asc::std::tuple_cat (function)

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

`asc::std::tuple_cat` concatenates the elements of multiple tuples in order.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

```cpp
namespace asc::std {
constexpr tuple<> tuple_cat();
} // namespace asc::std
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `tuple<>` | Returns the new tuple composed from the given elements or tuples. |

## Constraints

- The utility itself allocates no additional container storage; element construction, assignment, swapping, or passing into a callable body may still allocate or throw according to their own semantics, so the whole call is not guaranteed to be allocation-free on this basis.

## Example

The following Host example shows this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/tuple>

bool example()
{
    const auto left = asc::std::make_tuple(2, 3);
    const auto joined = asc::std::tuple_cat(left, asc::std::make_tuple(4));
    return asc::std::get<0>(joined) == 2 && asc::std::get<2>(joined) == 4;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
